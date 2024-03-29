#include "PreCompile.h"
#include "HarvesterScythe.h"
#include "Player.h"

HarvesterScythe::HarvesterScythe() 
{
}

HarvesterScythe::~HarvesterScythe() 
{
}

void HarvesterScythe::Initialize()
{
	ItemName_ = "HarvesterScythe";

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetTexture(ITEM_NAME_HARVESTERSCYTHE);
	Renderer_->SetPivot(PIVOTMODE::CENTER);
	Renderer_->ScaleToTexture();

	ItemNameRenderer_ = CreateComponent<GameEngineFontRenderer>();
	ItemNameRenderer_->SetText("Harvester's Scythe", FONT_RISKOFRAIN);
	ItemNameRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ItemNameRenderer_->SetSize(25.0f);
	ItemNameRenderer_->Off();

	PickUpRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PickUpRenderer_->SetText("Critical hits heal you.", FONT_RISKOFRAIN);
	PickUpRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PickUpRenderer_->SetSize(15.0f);
	PickUpRenderer_->Off();
}

void HarvesterScythe::BuffItemUpdate()
{
	// 5%의 추가 찬스를 얻음
	// TODO::시연을 위해 값을 늘리는편이 좋을지도
	PlayerStatus_.BuffedCritChance_ += PlayerStatus_.BaseCritChance_ + 5 * OverlapCounter_;
}


void HarvesterScythe::BulletItemUpdate(float4 _Pos, bool _CritFlg)
{	
	if (true == _CritFlg)
	{
		// 크리티컬이면 힐을 함
		Player::AddNowHp(10);
	}
}
