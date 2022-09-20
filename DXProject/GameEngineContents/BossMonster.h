#pragma once
#include "Monster.h"

// Ό³Έν :
class BossMonster : public Monster
{
public:
	// constrcuter destructer
	BossMonster();
	~BossMonster();

	// delete Function
	BossMonster(const BossMonster& _Other) = delete;
	BossMonster(BossMonster&& _Other) noexcept = delete;
	BossMonster& operator=(const BossMonster& _Other) = delete;
	BossMonster& operator=(BossMonster&& _Other) noexcept = delete;

	std::string GetBossName() const
	{
		return BossName_;
	}

	std::string GetBossSubName() const
	{
		return BossSubName_;
	}

protected:

	void BossSpawnState(float _DeltaTime);

	std::string BossName_;
	std::string BossSubName_;

};

