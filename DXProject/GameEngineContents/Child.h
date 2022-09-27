#pragma once
#include "Monster.h"

// ���� :
class Child : public Monster
{
public:
	// constrcuter destructer
	Child();
	~Child();

	// delete Function
	Child(const Child& _Other) = delete;
	Child(Child&& _Other) noexcept = delete;
	Child& operator=(const Child& _Other) = delete;
	Child& operator=(Child&& _Other) noexcept = delete;

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

