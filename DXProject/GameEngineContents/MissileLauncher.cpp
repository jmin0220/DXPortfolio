#include "PreCompile.h"
#include "MissileLauncher.h"
#include "Missile.h"

MissileLauncher::MissileLauncher() 
{
}

MissileLauncher::~MissileLauncher() 
{
}

void MissileLauncher::Initialize()
{
	IsUseItem_ = true;
	ItemName_ = "Disposable Missile Launcher";

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetTexture(ITEM_NAME_MISSILE_LAUNCHER);
	Renderer_->SetPivot(PIVOTMODE::CENTER);
	Renderer_->ScaleToTexture();

	InventoryRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	InventoryRenderer_->SetSamplingModePoint();
	InventoryRenderer_->SetTexture(ITEM_NAME_MISSILE_LAUNCHER_INVENTORY);
	InventoryRenderer_->SetPivot(PIVOTMODE::CENTER);
	InventoryRenderer_->ScaleToTexture();
	InventoryRenderer_->Off();

	ItemNameRenderer_ = CreateComponent<GameEngineFontRenderer>();
	ItemNameRenderer_->SetText("Disposable Missile Launcher", FONT_RISKOFRAIN);
	ItemNameRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ItemNameRenderer_->SetSize(25.0f);
	ItemNameRenderer_->Off();

	PickUpRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PickUpRenderer_->SetText("Fire a swarm of missiles", FONT_RISKOFRAIN);
	PickUpRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PickUpRenderer_->SetSize(15.0f);
	PickUpRenderer_->Off();

}

void MissileLauncher::UseItemUpdate(float4 _PlayerPos, float4 _Dir)
{
	{
		Missile* tmp = GetLevel()->CreateActor<Missile>();
		tmp->GetTransform().SetWorldPosition(_PlayerPos);
		tmp->GetTransform().SetWorldMove({ -5.0f, 25.0f, 0.0f });
		tmp->GetTransform().SetAddWorldRotation({ 0.0f, 0.0f, 95.0f, 0.0f });
	}
	{
		Missile* tmp = GetLevel()->CreateActor<Missile>();
		tmp->GetTransform().SetWorldPosition(_PlayerPos);
		tmp->GetTransform().SetWorldMove({ 0.0f, 25.0f, 0.0f });
		tmp->GetTransform().SetAddWorldRotation({ 0.0f, 0.0f, 90.0f, 0.0f });
	}
	{
		Missile* tmp = GetLevel()->CreateActor<Missile>();
		tmp->GetTransform().SetWorldPosition(_PlayerPos);
		tmp->GetTransform().SetWorldMove({ 5.0f, 25.0f, 0.0f });
		tmp->GetTransform().SetAddWorldRotation({ 0.0f, 0.0f, 85.0f, 0.0f });
	}
}