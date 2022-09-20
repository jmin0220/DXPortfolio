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

// 설명 :
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

	// 하단에 습득한 아이템을 반투명으로 표시
	void AddItemUpdate();

	// 사용 아이템을 표시
	void AddUseItemUpdate();

	// 포탈이 작동되기 전
	inline void SetTargetFontStringNonAct()
	{
		TartgetFontString_ = "Find the Teleporter.";
	}

	// 포탈이 작동된 후  / 보스가 나오기 전
	inline void SetTargetFontStringAct()
	{
		TartgetFontString_ = "Stay alive!";
	}

	// 포탈이 작동된 후  / 보스가 나온 후
	inline void SetTargetFontStringBoss()
	{
		TartgetFontString_ = "Kill remaining enemies";
	}

	// 포탈이 작동된 후 / 보스를 쓰러뜨린 후
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
	// 스테이지 이름
	GameEngineFontRenderer* StageMainName_;
	GameEngineFontRenderer* StageSubName_;

	// 하단 HUD
	GameEngineUIRenderer* HUDRenderer_;
	// 스킬아이콘
	GameEngineUIRenderer* SkillRenderer_[4];

	// 시간 및 난이도 인터페이스
	GameEngineUIRenderer* DifficultyHUDRenderer_;
	GameEngineUIRenderer* DifficultyTimerRenderer_;
	GameEngineUIRenderer* DifficultyIcon_;

	// 난이도 표시 텍스트
	GameEngineFontRenderer* DifficultyText_;
	// 난이도표시 수준을 위한 카운터
	int DifficultyTextCounter_;

	void DifficultyTextUpdate();

	// 폰트파일 렌더러
	GameEngineFontRenderer* TargetFontRenderer_;
	std::string TartgetFontString_;
	std::string CurTartgetString_;

	// TODO::하단 인터페이스 위에 레벨을 표시할 수 있도록 업데이트
	GameEngineFontRenderer* LevelFontRenderer_;
	// TODO::우상단 인터페이스 위에 시간을 표시할 수 있도록 업데이트
	GameEngineFontRenderer* TimerMinuteFontRenderer_;
	GameEngineFontRenderer* TimerSecendFontRenderer_;
	// TODO::하단 인터페이스 위에 스킬 쿨타임을 표시할 수 있도록 업데이트
	GameEngineFontRenderer* SkillCooldownFontRenderer_;

	// 소지금 아이콘
	GameEngineUIRenderer* GoldIconRenderer_;
	// 소지금
	ContentsFont* GoldFontRenderer_;
	// 플레이어 HP
	ContentsFont* PlayerHpFontRenderer_;
	SingleColorRenderer* HpRatingRenderer_;
	SingleColorRenderer* ExpRatingRenderer_;

	// 사용 아이템 칸에 그려질 아이템 렌더러
	GameEngineUIRenderer* UseItemRenderer_;

	int RecentGold_;
	int RecentHp_;

	float4 SkillPos_[4];

	Option Option_;
};

