#include "PreCompile.h"
#include "MagmaWormBody.h"

MagmaWormBody::MagmaWormBody()
	: IsHead_(false)
	, DeltaTime_(0.0f)
	, MoveDestinationTimer_(0.0f)
{
}

MagmaWormBody::~MagmaWormBody()
{
}

void MagmaWormBody::MovetoDestination(float4 _DestPos)
{
	MoveDestinationTimer_ += DeltaTime_;

	// 0.1�ʸ��� �������� ����
	// or �ʹ� �ָ� ������.
	if (MoveDestinationTimer_ >= 0.01f &&
		(_DestPos - this->GetTransform().GetWorldPosition()).Length() >= Renderer_->GetCurTexture()->GetScale().x * RenderScale_ - 15.0f * RenderScale_)
	{
		DestPos_ = _DestPos;
		MoveDestinationTimer_ = 0.0f;
	}

	MoveDir_ = DestPos_ - this->GetTransform().GetWorldPosition();
	this->GetTransform().SetWorldMove(MoveDir_.NormalizeReturn() * Speed_ * DeltaTime_);
}

void MagmaWormBody::SetWormBodyScale(int _ScaleLevel)
{
	RenderScale_ = 1.0f - (static_cast<float>(_ScaleLevel) * 0.02f);

	// ScaleLevel�� �������� ���� �۾���.
	// ���� ū ũ��� RendererScale * 1.0f, ���� ���� ũ��� RendererScale * 0.n
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
}

void MagmaWormBody::Update(float _DeltaTime)
{
	DeltaTime_ = _DeltaTime;
}

void MagmaWormBody::SetHead()
{
	Renderer_->ChangeFrameAnimation(MAGMAWORM_ANIM_HEAD);
	Renderer_->ScaleToTexture();

	IsHead_ = true;
}

void MagmaWormBody::SetDeath()
{
	// �Ӹ��϶��� �Ӹ��ִϸ��̼�����
	if (true == IsHead_)
	{
		Renderer_->ChangeFrameAnimation(MAGMAWORM_ANIM_HEAD_DEAD);
		
		return;
	}


	Renderer_->ChangeFrameAnimation(MAGMAWORM_ANIM_BODY_DEAD);
}
