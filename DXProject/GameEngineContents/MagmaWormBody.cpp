#include "PreCompile.h"
#include "MagmaWormBody.h"

MagmaWormBody::MagmaWormBody()
	: IsHead_(false)
	, DeltaTime_(0.0f)
	, MoveDestinationTimer_(0.0f)
	, CurDegree_(0.0f)
{
}

MagmaWormBody::~MagmaWormBody()
{
}

void MagmaWormBody::MovetoDestination(float4 _DestPos)
{
	MoveDestinationTimer_ += DeltaTime_;
	_DestPos.z = 0.0f;

	// 0.1초마다 목적지를 갱신
	// or 너무 멀면 갱신함.
	if (MoveDestinationTimer_ >= 0.01f &&
		(_DestPos - this->GetTransform().GetWorldPosition()).Length() >= Renderer_->GetCurTexture()->GetScale().x * RenderScale_ - 18.0f * RenderScale_)
	{
		DestPos_ = _DestPos;
		MoveDestinationTimer_ = 0.0f;

		// 회전
		NowDegree_ = float4::VectorXYtoDegree(this->GetTransform().GetWorldPosition(), _DestPos);

		float RealRotateDegree = NowDegree_ - CurDegree_;
		CurDegree_ = NowDegree_;
		this->GetTransform().SetAddWorldRotation({0.0f, 0.0f, RealRotateDegree, 0.0f });
	}

	// 이동
	float4 MoveDir = DestPos_ - this->GetTransform().GetWorldPosition();
	MoveDir.z = 0.0f;
	this->GetTransform().SetWorldMove(MoveDir.NormalizeReturn() * Speed_ * DeltaTime_);
}

void MagmaWormBody::MoveToDestinationHead(float4 _Direction, float4 _DestPos)
{
	_DestPos.z = 0.0f;;
	_Direction.z = 0.0f;;

	// 회전
	NowDegree_ = float4::VectorXYtoDegree(this->GetTransform().GetWorldPosition(), _DestPos);

	float RealRotateDegree = NowDegree_ - CurDegree_;
	CurDegree_ = NowDegree_;
	Renderer_->GetTransform().SetAddWorldRotation({ 0.0f, 0.0f, RealRotateDegree, 0.0f });

	HeadDirection_ = _Direction;
}

void MagmaWormBody::SetWormBodyScale(int _ScaleLevel)
{
	RenderScale_ = 1.0f - (static_cast<float>(_ScaleLevel) * 0.02f);

	// ScaleLevel이 높을수록 점점 작아짐.
	// 제일 큰 크기는 RendererScale * 1.0f, 제일 작은 크기는 RendererScale * 0.n
	Renderer_->GetTransform().SetWorldScale(Renderer_->GetTransform().GetWorldScale() * RenderScale_);
	Collision_->GetTransform().SetWorldScale(Renderer_->GetTransform().GetWorldScale() * RenderScale_);
	
}

void MagmaWormBody::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->CreateFrameAnimationFolder(MAGMAWORM_ANIM_HEAD, FrameAnimation_DESC(MAGMAWORM_ANIM_HEAD, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(MAGMAWORM_ANIM_HEAD_DEAD, FrameAnimation_DESC(MAGMAWORM_ANIM_HEAD_DEAD, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(MAGMAWORM_ANIM_BODY, FrameAnimation_DESC(MAGMAWORM_ANIM_BODY, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(MAGMAWORM_ANIM_BODY_DEAD, FrameAnimation_DESC(MAGMAWORM_ANIM_BODY_DEAD, ANIMATION_FRAME_DELAY, true));

	Renderer_->ChangeFrameAnimation(MAGMAWORM_ANIM_BODY);
	Renderer_->ScaleToTexture();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::Monster);
	Collision_->GetTransform().SetWorldScale({ Renderer_->GetCurTexture()->GetScale().x, Renderer_->GetCurTexture()->GetScale().y, 1.0f});

	IsHitted_ = false;
}

void MagmaWormBody::Update(float _DeltaTime)
{
	DeltaTime_ = _DeltaTime;

	if (true == IsHead_)
	{
		// 이동
		this->GetTransform().SetWorldMove(HeadDirection_ * Speed_ * DeltaTime_);
	}
}

void MagmaWormBody::SetHead()
{
	Renderer_->ChangeFrameAnimation(MAGMAWORM_ANIM_HEAD);
	Renderer_->ScaleToTexture();

	IsHead_ = true;
}

void MagmaWormBody::SetDeath()
{
	// 머리일때는 머리애니메이션으로
	if (true == IsHead_)
	{
		Renderer_->ChangeFrameAnimation(MAGMAWORM_ANIM_HEAD_DEAD);
		
		return;
	}


	Renderer_->ChangeFrameAnimation(MAGMAWORM_ANIM_BODY_DEAD);
}
