#include "PreCompile.h"
#include "MeatNugget.h"
#include "MiniNugget.h"
#include <GameEngineBase/GameEngineRandom.h>

MeatNugget::MeatNugget() 
{
}

MeatNugget::~MeatNugget() 
{
}

void MeatNugget::Initialize()
{
	ItemName_ = "MeatNugget";

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetTexture(ITEM_NAME_MEATNUGGET);
	Renderer_->SetPivot(PIVOTMODE::CENTER);
	Renderer_->ScaleToTexture();

	ItemNameRenderer_ = CreateComponent<GameEngineFontRenderer>();
	ItemNameRenderer_->SetText("MeatNugget", FONT_RISKOFRAIN);
	ItemNameRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ItemNameRenderer_->SetSize(25.0f);
	ItemNameRenderer_->Off();

	PickUpRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PickUpRenderer_->SetText("Enemies drop chunks of healing meat.", FONT_RISKOFRAIN);
	PickUpRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PickUpRenderer_->SetSize(15.0f);
	PickUpRenderer_->Off();
}

void MeatNugget::BulletItemUpdate(float4 _BulletPos, bool _CritFlg)
{
	if (GameEngineRandom::MainRandom.RandomInt(0, 99) < 8)
	{
		MiniNugget* temp = GetLevel()->CreateActor<MiniNugget>();
		temp->GetTransform().SetWorldPosition(_BulletPos);
	}
}