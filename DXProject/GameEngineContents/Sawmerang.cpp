#include "PreCompile.h"
#include "Sawmerang.h"
#include "SawmerangEffect.h"

Sawmerang::Sawmerang() 
{
}

Sawmerang::~Sawmerang() 
{
}

void Sawmerang::Initialize()
{
	IsUseItem_ = true;
	ItemName_ = "Sawmerang";

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetTexture(ITEM_NAME_SAWMERANG);
	Renderer_->SetPivot(PIVOTMODE::CENTER);
	Renderer_->ScaleToTexture();

	InventoryRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	InventoryRenderer_->SetSamplingModePoint();
	InventoryRenderer_->SetTexture(ITEM_NAME_SAWMERAN_INVENTORY);
	InventoryRenderer_->SetPivot(PIVOTMODE::CENTER);
	InventoryRenderer_->ScaleToTexture();
	InventoryRenderer_->Off();

	ItemNameRenderer_ = CreateComponent<GameEngineFontRenderer>();
	ItemNameRenderer_->SetText("Sawmerang", FONT_RISKOFRAIN);
	ItemNameRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ItemNameRenderer_->SetSize(25.0f);
	ItemNameRenderer_->Off();

	PickUpRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PickUpRenderer_->SetText("Mow them down!", FONT_RISKOFRAIN);
	PickUpRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PickUpRenderer_->SetSize(15.0f);
	PickUpRenderer_->Off();

}

void Sawmerang::UseItemUpdate(float4 _PlayerPos, float4 _Dir)
{
	SawmerangEffect* tmpEffect = GetLevel()->CreateActor<SawmerangEffect>();
	tmpEffect->GetTransform().SetWorldPosition(_PlayerPos);
	tmpEffect->SetDirection(_Dir);
}