#pragma once
#include "Drone.h"

// Ό³Έν :
class AttackDrone : public Drone
{
public:
	// constrcuter destructer
	AttackDrone();
	~AttackDrone();

	// delete Function
	AttackDrone(const AttackDrone& _Other) = delete;
	AttackDrone(AttackDrone&& _Other) noexcept = delete;
	AttackDrone& operator=(const AttackDrone& _Other) = delete;
	AttackDrone& operator=(AttackDrone&& _Other) noexcept = delete;

protected:
	void AnimInit() override;
	void StateInit() override;

private:
	void IdleStart(const StateInfo& _Info);
	void ActionStart(const StateInfo& _Info);

	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void ActionUpdate(float _DeltaTime, const StateInfo& _Info);

	void IdleEnd(const StateInfo& _Info);
	void ActionEnd(const StateInfo& _Info);

	void CreateBullet(int _CurFrame, int _LastFrame);
	int YPosLevel_;
};

