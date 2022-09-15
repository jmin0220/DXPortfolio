#include "PreCompile.h"
#include "BossHUD.h"

BossHUD::BossHUD() 
{
}

BossHUD::~BossHUD() 
{
}

void BossHUD::Start()
{
	HpBarRenderer_ = CreateComponent<GameEngineUIRenderer>();
	HpBarRenderer_->SetTexture(TEX_INTERFACE_BOSS_HPBAR);
	HpBarRenderer_->ScaleToTexture();
	HpBarRenderer_->SetPivot(PIVOTMODE::CENTER);
	HpBarRenderer_->GetTransform().SetWorldPosition({ 0.0f, GameEngineWindow::GetInst()->GetScale().hy() - 17.0f, -98.0f});

	HpRenderer_ = CreateComponent<SingleColorRenderer>();
	HpRenderer_->SetColor({181.0f / 255.0f, 72.0f / 255.0f, 72.0f / 255.0f });
	HpRenderer_->SetPivot(PIVOTMODE::LEFT);
	HpRenderer_->GetTransform().SetWorldScale({ BOSS_HP_MAX_SCALE, 18.0f });
	HpRenderer_->GetTransform().SetWorldPosition({ -GameEngineWindow::GetInst()->GetScale().hx() + 12.0f
												 , GameEngineWindow::GetInst()->GetScale().hy() - 17.0f, -99.0f });

	HpGlossRenderer_ = CreateComponent<SingleColorRenderer>();
	HpGlossRenderer_->SetColor({ 209.0f / 255.0f, 146.0f / 255.0f, 146.0f / 255.0f });
	HpGlossRenderer_->SetPivot(PIVOTMODE::LEFTBOT);
	HpGlossRenderer_->GetTransform().SetWorldScale({ BOSS_HP_MAX_SCALE, 7.0f });
	HpGlossRenderer_->GetTransform().SetWorldPosition({ -GameEngineWindow::GetInst()->GetScale().hx() + 12.0f
													  , GameEngineWindow::GetInst()->GetScale().hy() - 17.0f, -100.0f });


	BossHp_ = GetLevel()->CreateActor<ContentsFont>();
	BossHp_->CreateFontRenderer<GameEngineUIRenderer>("1400/1400", float4::ZERO);
	BossHp_->GetTransform().SetWorldPosition({ 0.0f, GameEngineWindow::GetInst()->GetScale().hy() - 17.0f, -101.0f });

	// TODO::Text를 생성하는 보스에 따라서 변경
	BossName_ = CreateComponent<GameEngineFontRenderer>();
	BossName_->SetText("Colossus", FONT_RISKOFRAIN);
	BossName_->SetColor({ 1.0f, 1.0f, 179.0f / 255.0f });
	BossName_->SetSize(35);
	BossName_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	BossName_->SetScreenPostion({ GameEngineWindow::GetInst()->GetScale().hx(), 30.0f, 0.0f});

	BossSubName_ = CreateComponent<GameEngineFontRenderer>();
	BossSubName_->SetText("Giant Stone Guardian", FONT_RISKOFRAIN);
	BossSubName_->SetColor({ 192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f });
	BossSubName_->SetSize(17);
	BossSubName_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	BossSubName_->SetScreenPostion({ GameEngineWindow::GetInst()->GetScale().hx(), 80.0f, 0.0f });
}

void BossHUD::Update(float _DeltaTime)
{
	// TODO::HUD가 Off에서 보스가 등장했을때 On으로 변경

	// TODO::보스의 체력에 연동해서 Renderer의 크기를 조절
	// TODO::보스의 현재체력 / 최대체력 텍스트 출력
}

