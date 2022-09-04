#include "PreCompile.h"
#include "RedWhip.h"

RedWhip::RedWhip()
{
}

RedWhip::~RedWhip() 
{
}

void RedWhip::Initialize()
{
	ItemType_ = ItemType::BuffItem;

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(ITEM_NAME_REDWHIP);

	ItemNameRenderer_ = CreateComponent<GameEngineFontRenderer>();
	ItemNameRenderer_->SetText("Warbanner", FONT_RISKOFRAIN);
	ItemNameRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ItemNameRenderer_->Off();

	PickUpRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PickUpRenderer_->SetText("Move fast out of combat.", FONT_RISKOFRAIN);
	PickUpRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PickUpRenderer_->Off();
}

