#pragma once
#include "Monster.h"

// ���� :
class RockGolem : public Monster
{
public:
	// constrcuter destructer
	RockGolem();
	~RockGolem();

	// delete Function
	RockGolem(const RockGolem& _Other) = delete;
	RockGolem(RockGolem&& _Other) noexcept = delete;
	RockGolem& operator=(const RockGolem& _Other) = delete;
	RockGolem& operator=(RockGolem&& _Other) noexcept = delete;

protected:

	// �ʱ�ȭ �Լ�
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

