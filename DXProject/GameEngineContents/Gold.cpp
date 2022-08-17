#include "PreCompile.h"
#include "Gold.h"

/*
* 오브젝트당 금화량
https://riskofrain.fandom.com/wiki/Gold?so=search

Small coins now represent 1
Coins now represent 5
Gold coins now represent 25
Platinum coins now represent 125
Bag of Coins represent 625
Platinum Bag of Coins represent 3125
*/

GameEngineTexture* Gold::ColMap_ = nullptr;

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

}

void Gold::Update(float _DeltaTime)
{
	GroundFallCheck(_DeltaTime);
}

void Gold::GroundFallCheck(float _DeltaTime)
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 하단 중앙
	float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 300 * _DeltaTime);

	// 하단 3점이 모두 땅에 닿지 않아야 바닥으로
	if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * 300 * _DeltaTime);
	}
}

void Gold::UpdateGoldOption()
{
	switch (GoldValue_)
	{
	case 1: // 1골드
		Renderer_->ChangeFrameAnimation(TEX_EFFECT_SMALL_GOLD);
		break;
	case 5: // 5골드
		Renderer_->ChangeFrameAnimation(TEX_EFFECT_COIN);
		break;
	default:
		break;
	}
}