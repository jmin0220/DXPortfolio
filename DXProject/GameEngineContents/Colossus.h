#pragma once
#include "BossMonster.h"

// 설명 :
class Colossus : public BossMonster
{
public:
	// constrcuter destructer
	Colossus();
	~Colossus();

	// delete Function
	Colossus(const Colossus& _Other) = delete;
	Colossus(Colossus&& _Other) noexcept = delete;
	Colossus& operator=(const Colossus& _Other) = delete;
	Colossus& operator=(Colossus&& _Other) noexcept = delete;

protected:

	// 초기화 함수
	void AnimationInit() override;
	void CollisionInit() override;
	void StateInit() override;

	void IdleStart(const StateInfo& _Info);
	void ChaseStart(const StateInfo& _Info);
	void AttackStart(const StateInfo& _Info);
	void Attack2Start(const StateInfo& _Info);
	void DeathStart(const StateInfo& _Info);

	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void ChaseUpdate(float _DeltaTime, const StateInfo& _Info);
	void AttackUpdate(float _DeltaTime, const StateInfo& _Info);
	void Attack2Update(float _DeltaTime, const StateInfo& _Info);
	void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
	void SpawnUpdate(float _DeltaTime, const StateInfo& _Info);

	void IdleEnd(const StateInfo& _Info);
	void ChaseEnd(const StateInfo& _Info);
	void DeathEnd(const StateInfo& _Info);

};

