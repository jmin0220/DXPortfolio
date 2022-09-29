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
private:

};

