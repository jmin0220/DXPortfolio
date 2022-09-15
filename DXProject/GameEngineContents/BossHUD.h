#pragma once
#include "SingleColorRenderer.h"
#include "ContentsFont.h"

// º≥∏Ì :
class BossHUD : public GameEngineActor
{
public:
	// constrcuter destructer
	BossHUD();
	~BossHUD();

	// delete Function
	BossHUD(const BossHUD& _Other) = delete;
	BossHUD(BossHUD&& _Other) noexcept = delete;
	BossHUD& operator=(const BossHUD& _Other) = delete;
	BossHUD& operator=(BossHUD&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineUIRenderer* HpBarRenderer_;
	SingleColorRenderer* HpRenderer_;
	SingleColorRenderer* HpGlossRenderer_;	// Hp¿« ±§≈√ ∑ª¥ı∑Ø

	ContentsFont* BossHp_;
	GameEngineFontRenderer* BossName_;
	GameEngineFontRenderer* BossSubName_;
};

