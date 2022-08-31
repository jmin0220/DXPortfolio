#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Option.h"
#include "ContentsFont.h"

// 설명 :
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

	// 폰트파일 렌더러
	GameEngineFontRenderer* TargetFontRenderer_;

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

	int RecentGold_;
	int RecentHp_;

	float4 SkillPos_[4];

	Option Option_;
};

