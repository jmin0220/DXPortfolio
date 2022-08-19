#include "PreCompile.h"
#include "HUD.h"
#include <GameEngineCore/GameEngineFontRenderer.h>

HUD::HUD() 
	: HUDRenderer_(nullptr)
{
	SkillPos_[0] = { -74, -370, -100 };
	SkillPos_[1] = { -28, -370, -100 };
	SkillPos_[2] = { 18, -370, -100 };
	SkillPos_[3] = { 64, -370, -100 };
}

HUD::~HUD() 
{
}

void HUD::Start()
{	
	// HUD
	HUDRenderer_ = CreateComponent<GameEngineUIRenderer>();
	DifficultyHUDRenderer_ = CreateComponent<GameEngineUIRenderer>();
	DifficultyTimerRenderer_ = CreateComponent<GameEngineUIRenderer>();

	for (int i = 0; i < 4; i++)
	{
		SkillRenderer_[i] = CreateComponent<GameEngineUIRenderer>();
	}

	HUDRenderer_->SetTexture(TEX_INTERFACE_HUD);

	HUDRenderer_->ScaleToTexture();
	HUDRenderer_->GetTransform().SetWorldPosition({0, -390, -100});

	DifficultyHUDRenderer_->SetTexture(TEX_INTERFACE_DIFFICULTY_HUD);
	DifficultyHUDRenderer_->ScaleToTexture();
	DifficultyHUDRenderer_->GetTransform().SetWorldPosition({ GameEngineWindow::GetInst()->GetScale().x / 2 - 80
															, GameEngineWindow::GetInst()->GetScale().y / 2 - 110, -101});

	DifficultyTimerRenderer_->SetTexture(TEX_INTERFACE_DIFFICULTY_TIMER);
	DifficultyTimerRenderer_->ScaleToTexture();
	DifficultyTimerRenderer_->GetTransform().SetWorldPosition({ GameEngineWindow::GetInst()->GetScale().x / 2 - 83
															  , GameEngineWindow::GetInst()->GetScale().y / 2 - 119, -100 });


	// ������
	GoldIconRenderer_ = CreateComponent<GameEngineUIRenderer>();
	GoldIconRenderer_->SetTexture(TEX_INTERFACE_MONEY_INTERFACE);
	GoldIconRenderer_->ScaleToTexture();
	GoldIconRenderer_->GetTransform().SetWorldPosition({ -GameEngineWindow::GetInst()->GetScale().x / 2 + 50
													   , GameEngineWindow::GetInst()->GetScale().y / 2 - 50, -100 });

	GoldFontRenderer_ = CreateComponent<GameEngineFontRenderer>();

	// �����Ǵ� �÷��̾��� ������ ���� HUD ��ų ������ ����
	switch (Option_.CharacterSelect_)
	{
	case CharacterSelectEnum::Commando:

		SkillRenderer_[0]->SetTexture(TEX_SKILLICON_COMMANDO_0);
		SkillRenderer_[1]->SetTexture(TEX_SKILLICON_COMMANDO_1);
		SkillRenderer_[2]->SetTexture(TEX_SKILLICON_COMMANDO_2);
		SkillRenderer_[3]->SetTexture(TEX_SKILLICON_COMMANDO_3);

		break;
	case CharacterSelectEnum::Bandit:

		SkillRenderer_[0]->SetTexture(TEX_SKILLICON_BANDIT_0);
		SkillRenderer_[1]->SetTexture(TEX_SKILLICON_BANDIT_1);
		SkillRenderer_[2]->SetTexture(TEX_SKILLICON_BANDIT_2);
		SkillRenderer_[3]->SetTexture(TEX_SKILLICON_BANDIT_3);

		break;
	case CharacterSelectEnum::None:
		break;
	default:
		break;
	}


	SkillRenderer_[0]->ScaleToTexture();
	SkillRenderer_[0]->GetTransform().SetWorldPosition(SkillPos_[0]);
	SkillRenderer_[1]->ScaleToTexture();
	SkillRenderer_[1]->GetTransform().SetWorldPosition(SkillPos_[1]);
	SkillRenderer_[2]->ScaleToTexture();
	SkillRenderer_[2]->GetTransform().SetWorldPosition(SkillPos_[2]);
	SkillRenderer_[3]->ScaleToTexture();
	SkillRenderer_[3]->GetTransform().SetWorldPosition(SkillPos_[3]);

	// ��Ʈ
	FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	FontRenderer_->SetText("123123", "riskofrainfont");
	FontRenderer_->SetColor({ 1.0f, 1.0f, 1.0f });
	FontRenderer_->SetScreenPostion({ 800, 840});
}

void HUD::Update(float _DeltaTime)
{
	// TODO::���� ���翡 ���� ��Ʈ ��ġ �̵�
	GoldFontRenderer_->SetText("25", "riskofrainfont");
	GoldFontRenderer_->SetColor({ 1.0f, 1.0f, 1.0f });
	GoldFontRenderer_->SetScreenPostion({ 100, 50 });
	GoldFontRenderer_->SetSize(30.0f);
}
