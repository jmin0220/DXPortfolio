#include "PreCompile.h"
#include "MiniNugget.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "Player.h"

MiniNugget::MiniNugget() 
{
}

MiniNugget::~MiniNugget() 
{
}


void MiniNugget::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->CreateFrameAnimationFolder(ITEM_ANIMATION_MEATNUGGET_IDLE, FrameAnimation_DESC(ITEM_ANIMATION_MEATNUGGET_IDLE, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(ITEM_ANIMATION_MEATNUGGET_JUMP, FrameAnimation_DESC(ITEM_ANIMATION_MEATNUGGET_JUMP, ANIMATION_FRAME_DELAY, false));
	Renderer_->ChangeFrameAnimation(ITEM_ANIMATION_MEATNUGGET_JUMP);
	Renderer_->SetSamplingModePoint();
	Renderer_->ScaleToTexture();

	if (0 == GameEngineRandom::MainRandom.RandomInt(0, 1))
	{
		CreatedDir_ = float4::LEFT;
	}
	else
	{
		CreatedDir_ = float4::RIGHT;
	}
}

void MiniNugget::Update(float _DeltaTime)
{
	GroundFall(_DeltaTime);

	// �÷��̾� ��ġ�� ������ ����
	FlyDir_ = PlayerPos_ - this->GetTransform().GetWorldPosition();

	// ������Ʈ�� ����� ������
	if (FlyDir_.Length() <= 15.0f)
	{
		int HealHp = static_cast<int>(Player::GetPlayerHp() * 0.08f);
		Player::AddNowHp(HealHp);

		this->Death();
	}
}

void MiniNugget::GroundFall(float _DeltaTime)
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// ���� ó��
	// �ϴ� �߾�
	float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 300 * _DeltaTime);

	// �ٴ��� ���� ������ ����
	if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		GetTransform().SetWorldMove(CreatedDir_ * 150.0f * _DeltaTime);
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * 30.0f * _DeltaTime);
	}
	else
	{
		Renderer_->ChangeFrameAnimation(ITEM_ANIMATION_MEATNUGGET_IDLE);
	}
}
