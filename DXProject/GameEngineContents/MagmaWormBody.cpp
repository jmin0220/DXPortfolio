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

	// 0.1초마다 목적지를 갱신
	if (MoveDestinationTimer_ >= 0.1)
	{
		DestPos_ = _DestPos;
		MoveDestinationTimer_ = 0.0f;
	}
	else
	{
		MoveDir_ = DestPos_ - this->GetTransform().GetWorldPosition();
		MoveDir_.Normalize();

		this->GetTransform().SetWorldMove(MoveDir_ * 100.0f * DeltaTime_);
	}

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
	Renderer_->SetScaleModeImage();

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
