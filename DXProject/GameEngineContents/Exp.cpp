#include "PreCompile.h"
#include "Exp.h"

Exp::Exp() 
{
}

Exp::~Exp() 
{
}

void Exp::SetDestPos(float4 _DestPos)
{
	DestPos_.x = this->GetTransform().GetWorldPosition().x + _DestPos.x;
	DestPos_.y = this->GetTransform().GetWorldPosition().y + _DestPos.y;

	this->GetTransform().SetWorldPosition(DestPos_);
}

void Exp::Start()
{
	// 경험치는 중력의 영향을 받지 않음.

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetScaleModeImage();

	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_NORMAL_EXP, FrameAnimation_DESC(TEX_EFFECT_NORMAL_EXP, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_SMALL_EXP, FrameAnimation_DESC(TEX_EFFECT_SMALL_EXP, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_DEATH_EXP, FrameAnimation_DESC(TEX_EFFECT_DEATH_EXP, ANIMATION_FRAME_DELAY, true));

	Renderer_->ChangeFrameAnimation(TEX_EFFECT_SMALL_EXP);
}

void Exp::Update(float _DeltaTime)
{
}