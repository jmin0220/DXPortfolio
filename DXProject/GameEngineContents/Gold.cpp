#include "PreCompile.h"
#include "Gold.h"

//https://riskofrain.fandom.com/wiki/Gold?so=search
/*
* 오브젝트당 금화량
Small coins now represent 1
Coins now represent 5
Gold coins now represent 25
Platinum coins now represent 125
Bag of Coins represent 625
Platinum Bag of Coins represent 3125
*/
Gold::Gold() 
{
}

Gold::~Gold() 
{
}

void Gold::Start()
{
	// 골드는 중력의 영향을 받음

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetScaleModeImage();

	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_SMALL_GOLD, FrameAnimation_DESC(TEX_EFFECT_SMALL_GOLD, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_COIN, FrameAnimation_DESC(TEX_EFFECT_COIN, ANIMATION_FRAME_DELAY, true));

	Renderer_->ChangeFrameAnimation(TEX_EFFECT_SMALL_GOLD);
}

void Gold::Update(float _DeltaTime)
{
}