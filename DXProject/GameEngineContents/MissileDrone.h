#pragma once
#include "Drone.h"

// Ό³Έν :
class MissileDrone : public Drone
{
public:
	// constrcuter destructer
	MissileDrone();
	~MissileDrone();

	// delete Function
	MissileDrone(const MissileDrone& _Other) = delete;
	MissileDrone(MissileDrone&& _Other) noexcept = delete;
	MissileDrone& operator=(const MissileDrone& _Other) = delete;
	MissileDrone& operator=(MissileDrone&& _Other) noexcept = delete;

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
};

