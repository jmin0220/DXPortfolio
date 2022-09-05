#include "PreCompile.h"
#include "Gold.h"
#include "Player.h"
/*
* ������Ʈ�� ��ȭ��
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
	// ���� �߷��� ������ ����

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
		// ������Ʈ�� �÷��̾�� ����� �����ߴٸ�
		if (false == ChasePlayer())
		{
			// �÷��̾ ��� �߰�
			Player::AddGold(GoldValue_);

			// ������Ʈ ����
			this->Death();

			return;
		}
	}
}

void Gold::GroundFallCheck(float _DeltaTime)
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// ��� ���� ó��
	// �ϴ� �߾�
	float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 300 * _DeltaTime);

	// �ٴ��� ���� ������ ����
	if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		// Gold Popó��
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
	case 1: // 1���
		Renderer_->ChangeFrameAnimation(TEX_EFFECT_SMALL_GOLD);
		break;
	case 5: // 5���
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
	// �÷��̾� ��ġ�� ������ ����
	FlyDir_ = PlayerPos_ - this->GetTransform().GetWorldPosition();

	// ������Ʈ�� ����� ������
	if (FlyDir_.Length() <= 10.0f)
	{
		return false;
	}
	// ������Ʈ�� ����� �������� ����
	else
	{
		FlyDir_.Normalize();

		// �÷��̾ ���� �̵�
		this->GetTransform().SetWorldMove(FlyDir_ * GameEngineTime::GetDeltaTime() * 300.0f);
		return true;
	}
}