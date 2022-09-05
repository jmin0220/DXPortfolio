#include "PreCompile.h"
#include "Gold.h"
#include "Player.h"
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
	PlayerChaseTimer_ += _DeltaTime;

	if (PlayerChaseTimer_ <= 2.0f)
	{
		GroundFallCheck(_DeltaTime);
	}
	else
	{
		// 오브젝트가 플레이어에게 충분히 근접했다면
		if (false == ChasePlayer())
		{
			// 플레이어에 골드 추가
			Player::AddGold(GoldValue_);

			// 오브젝트 삭제
			this->Death();

			return;
		}
	}
}

void Gold::GroundFallCheck(float _DeltaTime)
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 골드 낙하 처리
	// 하단 중앙
	float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 300 * _DeltaTime);

	// 바닥이 닿지 않으면 낙하
	if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		// Gold Pop처리
		PopSpeed_ += GameEngineTime::GetDeltaTime() * 270.0f;

		if (PopSpeed_ >= 270.0f)
		{
			PopSpeed_ = 270.0f;
		}

		GetTransform().SetWorldMove(GetTransform().GetDownVector()* PopSpeed_* _DeltaTime);
		GetTransform().SetWorldMove(FlyDir_ * _DeltaTime);
	}
	else
	{
		PopSpeed_ = 0.0f;
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

void Gold::GoldPop()
{
	PopSpeed_ = -100.0f;
}

bool Gold::ChasePlayer()
{
	// 플레이어 위치로 방향을 설정
	FlyDir_ = PlayerPos_ - this->GetTransform().GetWorldPosition();

	// 오브젝트가 충분히 근접함
	if (FlyDir_.Length() <= 10.0f)
	{
		return false;
	}
	// 오브젝트가 충분히 근접하지 못함
	else
	{
		FlyDir_.Normalize();

		// 플레이어를 향해 이동
		this->GetTransform().SetWorldMove(FlyDir_ * GameEngineTime::GetDeltaTime() * 300.0f);
		return true;
	}
}