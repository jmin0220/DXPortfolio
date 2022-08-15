#include "PreCompile.h"
#include "Exp.h"

Exp::Exp() 
{
}

Exp::~Exp() 
{
}

void Exp::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetScaleModeImage();

	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_NORMAL_EXP, FrameAnimation_DESC(TEX_EFFECT_NORMAL_EXP, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_BIG_EXP, FrameAnimation_DESC(TEX_EFFECT_BIG_EXP, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_DEATH_EXP, FrameAnimation_DESC(TEX_EFFECT_DEATH_EXP, ANIMATION_FRAME_DELAY, true));

	Renderer_->ChangeFrameAnimation(TEX_EFFECT_NORMAL_EXP);
}

void Exp::Update(float _DeltaTime)
{
}