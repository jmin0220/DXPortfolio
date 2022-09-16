#pragma once
#include "SingleColorRenderer.h"
#include "ContentsFont.h"

// 설명 :
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

	inline void SetBossHp(int _BossHp)
	{
		BossHpNum_ = _BossHp;
	}

	inline void SetBossMaxHp(int _BossHp)
	{
		BossMaxHpNum_ = _BossHp;
	}

	inline void SetBossNames(std::string _BossName, std::string _BossSubName)
	{
		BossNameStr_ = _BossName;
		BossName_->SetText(BossNameStr_, FONT_RISKOFRAIN);

		BossSubNameStr_ = _BossSubName;
		BossSubName_->SetText(BossSubNameStr_, FONT_RISKOFRAIN);
	}

	inline void BossHpFontOn()
	{
		BossHp_->On();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineUIRenderer* HpBarRenderer_;
	SingleColorRenderer* HpRenderer_;
	SingleColorRenderer* HpGlossRenderer_;	// Hp의 광택 렌더러

	ContentsFont* BossHp_;
	GameEngineFontRenderer* BossName_;
	GameEngineFontRenderer* BossSubName_;

	int BossHpNum_;	// 수치화된 BossHp
	int BossMaxHpNum_;
	std::string BossNameStr_;
	std::string BossSubNameStr_;
};

