#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Option.h"

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
	void Update(float _DeltaTime) {}
	void End() {}

private:
	// 하단 HUD
	GameEngineUIRenderer* HUDRenderer_;
	// 스킬아이콘
	GameEngineUIRenderer* SkillRenderer_[4];

	GameEngineUIRenderer* DifficultyHUDRenderer_;
	GameEngineUIRenderer* DifficultyTimerRenderer_;

	float4 SkillPos_[4];

	Option Option_;
};

