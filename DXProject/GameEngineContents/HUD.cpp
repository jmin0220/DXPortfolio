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
	HUDRenderer_->SetTexture(TEX_INTERFACE_HUD);

	HUDRenderer_->ScaleToTexture();
	HUDRenderer_->GetTransform().SetWorldPosition({0, -390, -100});

	for (int i = 0; i < 4; i++)
	{
		SkillRenderer_[i] = CreateComponent<GameEngineUIRenderer>();
	}

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

	GameEngineFontRenderer* FontRenderer_;
	FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	FontRenderer_->SetText("안녕하세요");
}
