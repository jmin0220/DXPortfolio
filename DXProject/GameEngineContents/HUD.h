#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Option.h"

enum class DifficultyText
{
	VeryEasy,
	Easy,
	Medium,
	Hard,
	VeryHard,
	Insane,
	Impossible,
	ISEEYOU,
	IMCOMINGFORYOU,
	HAHAHAHA,
};

// ���� :
class ContentsFont;
class SingleColorRenderer;
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

	// �ϴܿ� ������ �������� ���������� ǥ��
	void AddItemUpdate();

	// ��� �������� ǥ��
	void AddUseItemUpdate();

	// ��Ż�� �۵��Ǳ� ��
	inline void SetTargetFontStringNonAct()
	{
		TartgetFontString_ = "Find the Teleporter.";
	}

	// ��Ż�� �۵��� ��  / ������ ������ ��
	inline void SetTargetFontStringAct()
	{
		TartgetFontString_ = "Stay alive!";
	}

	// ��Ż�� �۵��� ��  / ������ ���� ��
	inline void SetTargetFontStringBoss()
	{
		TartgetFontString_ = "Kill remaining enemies";
	}

	// ��Ż�� �۵��� �� / ������ �����߸� ��
	inline void SetTargetFontStringNextLevel()
	{
		TartgetFontString_ = "Go to the teleporter to advance to the next level!";
	}

	void ActorAllOverLevel();

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

	// ���̵� ǥ�� �ؽ�Ʈ
	GameEngineFontRenderer* DifficultyText_;
	// ���̵�ǥ�� ������ ���� ī����
	int DifficultyTextCounter_;

	void DifficultyTextUpdate();

	// ��Ʈ���� ������
	GameEngineFontRenderer* TargetFontRenderer_;
	std::string TartgetFontString_;
	std::string CurTartgetString_;

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
	SingleColorRenderer* HpRatingRenderer_;
	SingleColorRenderer* ExpRatingRenderer_;

	// ��� ������ ĭ�� �׷��� ������ ������
	GameEngineUIRenderer* UseItemRenderer_;

	int RecentGold_;
	int RecentHp_;

	float4 SkillPos_[4];

	Option Option_;
};

