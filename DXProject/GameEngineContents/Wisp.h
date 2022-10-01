#pragma once
#include "Monster.h"

// 설명 :
class Wisp : public Monster
{
public:
	// constrcuter destructer
	Wisp();
	~Wisp();

	// delete Function
	Wisp(const Wisp& _Other) = delete;
	Wisp(Wisp&& _Other) noexcept = delete;
	Wisp& operator=(const Wisp& _Other) = delete;
	Wisp& operator=(Wisp&& _Other) noexcept = delete;

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

