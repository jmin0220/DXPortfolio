#include "PreCompile.h"
#include "Gold.h"

Gold::Gold() 
{
}

Gold::~Gold() 
{
}

void Gold::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetScaleModeImage();

	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_NORMAL_GOLD, FrameAnimation_DESC(TEX_EFFECT_NORMAL_GOLD, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_BIG_GOLD, FrameAnimation_DESC(TEX_EFFECT_BIG_GOLD, ANIMATION_FRAME_DELAY, true));

	Renderer_->ChangeFrameAnimation(TEX_EFFECT_NORMAL_GOLD);
}

void Gold::Update(float _DeltaTime)
{
}