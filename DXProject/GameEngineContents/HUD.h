#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Option.h"
#include "ContentsFont.h"

// ���� :
class HUD : public GameEngineActor
{
public:
	// constrcuter destructer
	HUD();
	~HUD();

	// delete Function
	HUD(const HUD& _Other) = delete;
	HUD(HUD&& _Other) noexcept = delete;
	HUD& operator=(const HUD& _Other) = delete;
	HUD& operator=(HUD&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	// �������� �̸�
	GameEngineFontRenderer* StageMainName_;
	GameEngineFontRenderer* StageSubName_;

	// �ϴ� HUD
	GameEngineUIRenderer* HUDRenderer_;
	// ��ų������
	GameEngineUIRenderer* SkillRenderer_[4];

	// �ð� �� ���̵� �������̽�
	GameEngineUIRenderer* DifficultyHUDRenderer_;
	GameEngineUIRenderer* DifficultyTimerRenderer_;
	GameEngineUIRenderer* DifficultyIcon_;

	// ��Ʈ���� ������
	GameEngineFontRenderer* TargetFontRenderer_;

	// TODO::�ϴ� �������̽� ���� ������ ǥ���� �� �ֵ��� ������Ʈ
	GameEngineFontRenderer* LevelFontRenderer_;
	// TODO::���� �������̽� ���� �ð��� ǥ���� �� �ֵ��� ������Ʈ
	GameEngineFontRenderer* TimerMinuteFontRenderer_;
	GameEngineFontRenderer* TimerSecendFontRenderer_;
	// TODO::�ϴ� �������̽� ���� ��ų ��Ÿ���� ǥ���� �� �ֵ��� ������Ʈ
	GameEngineFontRenderer* SkillCooldownFontRenderer_;

	// ������ ������
	GameEngineUIRenderer* GoldIconRenderer_;
	// ������
	ContentsFont* GoldFontRenderer_;
	// �÷��̾� HP
	ContentsFont* PlayerHpFontRenderer_;

	int RecentGold_;
	int RecentHp_;

	float4 SkillPos_[4];

	Option Option_;
};

