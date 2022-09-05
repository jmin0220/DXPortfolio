#include "PreCompile.h"
#include "HarvesterScythe.h"

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
	// 5%�� �߰� ������ ����
	// TODO::�ÿ��� ���� ���� �ø������� ��������
	PlayerStatus_.CritChance_ = PlayerStatus_.CritChance_ + 5 * OverlapCounter_;
}