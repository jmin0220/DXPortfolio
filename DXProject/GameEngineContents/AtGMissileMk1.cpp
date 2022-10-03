#include "PreCompile.h"
#include "AtGMissileMk1.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "Missile.h"

AtGMissileMk1::AtGMissileMk1() 
{
}

AtGMissileMk1::~AtGMissileMk1() 
{
}

void AtGMissileMk1::Initialize()
{
	ItemName_ = "AtG Missile Mk.1";

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetTexture(ITEM_NAME_AtGMISSILE_MK1);
	Renderer_->SetPivot(PIVOTMODE::CENTER);
	Renderer_->ScaleToTexture();

	ItemNameRenderer_ = CreateComponent<GameEngineFontRenderer>();
	ItemNameRenderer_->SetText("AtG Missile Mk.1", FONT_RISKOFRAIN);
	ItemNameRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ItemNameRenderer_->SetSize(25.0f);
	ItemNameRenderer_->Off();

	PickUpRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PickUpRenderer_->SetText("Chance to fire a missile. Watch for the backblast.", FONT_RISKOFRAIN);
	PickUpRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PickUpRenderer_->SetSize(15.0f);
	PickUpRenderer_->Off();
}

void AtGMissileMk1::AtkItemUpdate(float4 _PlayerPos)
{
	// 20%의 확률로 미사일 생성
	if (GameEngineRandom::MainRandom.RandomInt(0, 99) <= 19)
	{
		Missile* tmp = GetLevel()->CreateActor<Missile>();
		tmp->GetTransform().SetWorldPosition(_PlayerPos);
		tmp->GetTransform().SetWorldMove({ 0.0f, 25.0f, 0.0f });
		tmp->GetTransform().SetAddWorldRotation({ 0.0f, 0.0f, 90.0f, 0.0f });
	}
}

