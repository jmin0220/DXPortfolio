#pragma once
#include "Monster.h"

// 설명 :
class Crab : public Monster
{
public:
	// constrcuter destructer
	Crab();
	~Crab();

	// delete Function
	Crab(const Crab& _Other) = delete;
	Crab(Crab&& _Other) noexcept = delete;
	Crab& operator=(const Crab& _Other) = delete;
	Crab& operator=(Crab&& _Other) noexcept = delete;

protected:

	// 초기화 함수
	void AnimationInit() override;
	void CollisionInit() override;
	void StateInit() override;

	void IdleStart(const StateInfo& _Info);
	void MoveStart(const StateInfo& _Info);
	void ChaseStart(const StateInfo& _Info);
	void AttackStart(const StateInfo& _Info);
	void DeathStart(const StateInfo& _Info);

	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void ChaseUpdate(float _DeltaTime, const StateInfo& _Info);
	void AttackUpdate(float _DeltaTime, const StateInfo& _Info);
	void DeathUpdate(float _DeltaTime, const StateInfo& _Info);

	void IdleEnd(const StateInfo& _Info);
	void MoveEnd(const StateInfo& _Info);
	void ChaseEnd(const StateInfo& _Info);
	void DeathEnd(const StateInfo& _Info);

};

