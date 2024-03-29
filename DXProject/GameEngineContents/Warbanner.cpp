#include "PreCompile.h"
#include "Warbanner.h"
#include "WarbannerFlg.h"

Warbanner::Warbanner() 
{
}

Warbanner::~Warbanner() 
{
}

void Warbanner::Initialize()
{
	ItemName_ = "Warbanner";

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetTexture(ITEM_NAME_WARBANNER);
	Renderer_->SetPivot(PIVOTMODE::CENTER);
	Renderer_->ScaleToTexture();

	ItemNameRenderer_ = CreateComponent<GameEngineFontRenderer>();
	ItemNameRenderer_->SetText("Warbanner", FONT_RISKOFRAIN);
	ItemNameRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ItemNameRenderer_->SetSize(25.0f);
	ItemNameRenderer_->Off();

	PickUpRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PickUpRenderer_->SetText("Drop a Warbanner on leveling up, giving you great strength.", FONT_RISKOFRAIN);
	PickUpRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PickUpRenderer_->SetSize(15.0f);
	PickUpRenderer_->Off();
}

void Warbanner::LevelUpItemUpdate(float4 _PlayerPos)
{
	WarbannerFlg* tmpFlg = GetLevel()->CreateActor<WarbannerFlg>();
	tmpFlg->GetTransform().SetWorldPosition({ _PlayerPos.x, _PlayerPos.y, _PlayerPos.z});
	tmpFlg->GroundFall();	// 대충 땅에 박혀있게
}
