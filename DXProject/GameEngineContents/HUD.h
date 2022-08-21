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
	// 하단 HUD
	GameEngineUIRenderer* HUDRenderer_;
	// 스킬아이콘
	GameEngineUIRenderer* SkillRenderer_[4];

	// 시간 및 난이도 인터페이스
	GameEngineUIRenderer* DifficultyHUDRenderer_;
	GameEngineUIRenderer* DifficultyTimerRenderer_;

	// 폰트파일 렌더러
	GameEngineFontRenderer* FontRenderer_;

	// 소지금 아이콘
	GameEngineUIRenderer* GoldIconRenderer_;
	// 소지금
	ContentsFont* GoldFontRenderer_;

	float4 SkillPos_[4];

	Option Option_;
};

