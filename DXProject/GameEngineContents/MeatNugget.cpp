#include "PreCompile.h"
#include "MeatNugget.h"

MeatNugget::MeatNugget() 
{
}

MeatNugget::~MeatNugget() 
{
}

void MeatNugget::Initialize()
{
	ItemType_ = ItemType::AtkItem;

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(ITEM_NAME_MEATNUGGET);

	ItemNameRenderer_ = CreateComponent<GameEngineFontRenderer>();
	ItemNameRenderer_->SetText("MeatNugget", FONT_RISKOFRAIN);
	ItemNameRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ItemNameRenderer_->Off();

	PickUpRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PickUpRenderer_->SetText("Enemies drop chunks of healing meat.", FONT_RISKOFRAIN);
	PickUpRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PickUpRenderer_->Off();
}