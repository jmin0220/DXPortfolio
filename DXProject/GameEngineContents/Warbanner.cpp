#include "PreCompile.h"
#include "Warbanner.h"

Warbanner::Warbanner() 
{
}

Warbanner::~Warbanner() 
{
}

void Warbanner::Initialize()
{
	ItemType_ = ItemType::LevelUpItem;

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(ITEM_NAME_WARBANNER);

	ItemNameRenderer_ = CreateComponent<GameEngineFontRenderer>();
	ItemNameRenderer_->SetText("Warbanner", FONT_RISKOFRAIN);
	ItemNameRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ItemNameRenderer_->Off();

	PickUpRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PickUpRenderer_->SetText("Drop a Warbanner on leveling up, giving you great strength.", FONT_RISKOFRAIN);
	PickUpRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PickUpRenderer_->Off();
}