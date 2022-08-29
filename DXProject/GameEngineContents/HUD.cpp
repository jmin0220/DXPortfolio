#include "PreCompile.h"
#include "HUD.h"
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "Player.h"

HUD::HUD() 
	: HUDRenderer_(nullptr)
	, RecentGold_(0)
	, RecentHp_(0)
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



	// 생성되는 플레이어의 종류에 따라 HUD 스킬 아이콘 생성
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

	// 현재 타겟폰트
	TargetFontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	TargetFontRenderer_->SetText("Find the Teleporter.", "riskofrainfont");
	TargetFontRenderer_->SetSize(14);
	TargetFontRenderer_->SetColor({ 1.0f, 1.0f, 1.0f });
	TargetFontRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	TargetFontRenderer_->SetScreenPostion({ 800, 760});

	// 소지금 아이콘
	GoldIconRenderer_ = CreateComponent<GameEngineUIRenderer>();
	GoldIconRenderer_->SetTexture(TEX_INTERFACE_MONEY_INTERFACE);
	GoldIconRenderer_->ScaleToTexture();
	GoldIconRenderer_->GetTransform().SetWorldPosition({ -GameEngineWindow::GetInst()->GetScale().x / 2 + 50
													   , GameEngineWindow::GetInst()->GetScale().y / 2 - 50, -100 });

	// 소지금
	GoldFontRenderer_ = GetLevel()->CreateActor<ContentsFont>();
	GoldFontRenderer_->CreateFontRenderer<GameEngineUIRenderer>(std::to_string(Player::GetPlayerGold()), {0, 0}, TextType::Large);
	GoldFontRenderer_->GetTransform().SetWorldPosition({ GoldIconRenderer_->GetTransform().GetWorldPosition().x + 40.0f, GoldIconRenderer_->GetTransform().GetWorldPosition().y });

	PlayerHpFontRenderer_ = GetLevel()->CreateActor<ContentsFont>();
	PlayerHpFontRenderer_->CreateFontRenderer<GameEngineUIRenderer>(std::to_string(Player::GetPlayerHp()) + "/" + std::to_string(Player::GetPlayerMaxHp()), {0, 0}, TextType::Normal);
	PlayerHpFontRenderer_->GetTransform().SetWorldPosition({ -GameEngineWindow::GetInst()->GetScale().x / 2 + 764
															, GameEngineWindow::GetInst()->GetScale().y / 2 - 867, -110 });
}

void HUD::Update(float _DeltaTime)
{
	// 변경이 있을때만 Change함수를 실행
	if (RecentGold_ != Player::GetPlayerGold())
	{
		RecentGold_ = Player::GetPlayerGold();
		GoldFontRenderer_->ChangeFontRenderer<GameEngineUIRenderer>(std::to_string(Player::GetPlayerGold()), { 0, 0 }, TextType::Large);
	}

	if (RecentHp_ != Player::GetPlayerHp())
	{
		RecentHp_ = Player::GetPlayerHp();
		PlayerHpFontRenderer_->ChangeFontRenderer<GameEngineUIRenderer>(std::to_string(Player::GetPlayerHp()) + "/" + std::to_string(Player::GetPlayerMaxHp()), { 0, 0 }, TextType::Normal);
	}
}