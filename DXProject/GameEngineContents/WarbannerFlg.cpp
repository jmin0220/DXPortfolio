#include "PreCompile.h"
#include "WarbannerFlg.h"
#include "PlayerStatus.h"

WarbannerFlg::WarbannerFlg() 
{
}

WarbannerFlg::~WarbannerFlg() 
{
}

void WarbannerFlg::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationFolder(ITEM_ANIMATION_WARBANNER_FLAG, FrameAnimation_DESC(ITEM_ANIMATION_WARBANNER_FLAG, ANIMATION_FRAME_DELAY, false));
	Renderer_->ChangeFrameAnimation(ITEM_ANIMATION_WARBANNER_FLAG);
	Renderer_->SetSamplingModePoint();
	Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::BOT);

	CircleRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	CircleRenderer_->CreateFrameAnimationFolder(ITEM_ANIMATION_WARBANNER_CIRCLE, FrameAnimation_DESC(ITEM_ANIMATION_WARBANNER_CIRCLE, ANIMATION_FRAME_DELAY, false));
	CircleRenderer_->ChangeFrameAnimation(ITEM_ANIMATION_WARBANNER_CIRCLE);
	CircleRenderer_->SetSamplingModePoint();
	CircleRenderer_->ScaleToTexture();

	GroundFall();
}

void WarbannerFlg::Update(float _DeltaTime)
{
	float4 thisPos = this->GetTransform().GetWorldPosition();
	float4 ToPlayerLength = thisPos - PlayerPos_;

	// Warbanner의 원안에 캐릭터가 들어와있다면
	if (CircleRenderer_->GetCurTexture()->GetScale().y >= ToPlayerLength.Length())
	{
		// TODO::스탯 게산식 변경필요
		PlayerStatus::Damage_ = PlayerStatus::Damage_ + PlayerStatus::BaseDamage_ + 4;
		PlayerStatus::AtkSpeed_ = PlayerStatus::AtkSpeed_ + PlayerStatus::BaseAtkSpeed_ * 30.0f;
		PlayerStatus::Speed_ = PlayerStatus::Speed_ + PlayerStatus::BaseSpeed_ * 30.0f;
	}
}



void WarbannerFlg::GroundFall()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 하단 중앙
	float4 ColorDown = float4::ZERO;

	// 바닥이 닿지 않으면 낙하
	for (;;)
	{
		ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix()
										   , -this->GetTransform().GetWorldPosition().iy());

		if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			GetTransform().SetWorldMove(GetTransform().GetDownVector() * 2.0f);
		}
		else
		{
			// 땅에 파묻힘 방지
			for (;;)
			{
				ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix()
					                               , -this->GetTransform().GetWorldPosition().iy());

				if (true == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
				{
					GetTransform().SetWorldMove(GetTransform().GetUpVector());
				}
				else
				{
					GetTransform().SetWorldMove(GetTransform().GetDownVector());
					break;
				}
			}

			break;
		}
	}

	Renderer_->GetTransform().SetWorldMove(GetTransform().GetDownVector() * (Renderer_->GetCurTexture()->GetScale().hy() / 2));
}
