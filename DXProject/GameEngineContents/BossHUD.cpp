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
	BossHp_->CreateFontRenderer<GameEngineUIRenderer>("0/0", float4::ZERO);
	BossHp_->GetTransform().SetWorldPosition({ 0.0f, GameEngineWindow::GetInst()->GetScale().hy() - 17.0f, -101.0f });
	BossHp_->Off();

	// TODO::Text�� �����ϴ� ������ ���� ����
	BossName_ = CreateComponent<GameEngineFontRenderer>();
	BossName_->SetText("Boss Name", FONT_RISKOFRAIN);
	BossName_->SetColor({ 1.0f, 1.0f, 179.0f / 255.0f });
	BossName_->SetSize(35);
	BossName_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	BossName_->SetScreenPostion({ GameEngineWindow::GetInst()->GetScale().hx(), 30.0f, 0.0f});

	BossSubName_ = CreateComponent<GameEngineFontRenderer>();
	BossSubName_->SetText("Boss Sub Name", FONT_RISKOFRAIN);
	BossSubName_->SetColor({ 192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f });
	BossSubName_->SetSize(17);
	BossSubName_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	BossSubName_->SetScreenPostion({ GameEngineWindow::GetInst()->GetScale().hx(), 80.0f, 0.0f });
}

void BossHUD::Update(float _DeltaTime)
{
	// TODO::HUD�� Off���� ������ ���������� On���� ����

	// TODO::������ ü�¿� �����ؼ� Renderer�� ũ�⸦ ����
	// TODO::������ ����ü�� / �ִ�ü�� �ؽ�Ʈ ���
	static int CurHp = 0;
	// ü�¿� ��ȭ�� �������� ������Ʈ
	if (CurHp != BossHpNum_)
	{
		CurHp = BossHpNum_;
		std::string HpString = std::to_string(BossHpNum_) + "/" + std::to_string(BossMaxHpNum_);
		BossHp_->ChangeFontRenderer<GameEngineUIRenderer>(HpString, float4::ZERO);
	}

	// Hp�� Exp�� ���¿� ���� Bar�� ������ ����
	HpRenderer_->GetTransform().SetWorldScale({ static_cast<float>(BossHpNum_) / static_cast<float>(BossMaxHpNum_) * BOSS_HP_MAX_SCALE, 18.0f });
	HpGlossRenderer_->GetTransform().SetWorldScale({ static_cast<float>(BossHpNum_) / static_cast<float>(BossMaxHpNum_) * BOSS_HP_MAX_SCALE, 7.0f });
}

