#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Option.h"

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
	void Update(float _DeltaTime) {}
	void End() {}

private:
	// �ϴ� HUD
	GameEngineUIRenderer* HUDRenderer_;
	// ��ų������
	GameEngineUIRenderer* SkillRenderer_[4];

	GameEngineUIRenderer* DifficultyHUDRenderer_;
	GameEngineUIRenderer* DifficultyTimerRenderer_;

	float4 SkillPos_[4];

	Option Option_;
};

