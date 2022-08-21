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
	// �ϴ� HUD
	GameEngineUIRenderer* HUDRenderer_;
	// ��ų������
	GameEngineUIRenderer* SkillRenderer_[4];

	// �ð� �� ���̵� �������̽�
	GameEngineUIRenderer* DifficultyHUDRenderer_;
	GameEngineUIRenderer* DifficultyTimerRenderer_;

	// ��Ʈ���� ������
	GameEngineFontRenderer* FontRenderer_;

	// ������ ������
	GameEngineUIRenderer* GoldIconRenderer_;
	// ������
	ContentsFont* GoldFontRenderer_;

	float4 SkillPos_[4];

	Option Option_;
};

