#pragma once
#include "DroneItem.h"

// Ό³Έν :
class AttackDroneItem : public DroneItem
{
public:
	// constrcuter destructer
	AttackDroneItem();
	~AttackDroneItem();

	// delete Function
	AttackDroneItem(const AttackDroneItem& _Other) = delete;
	AttackDroneItem(AttackDroneItem&& _Other) noexcept = delete;
	AttackDroneItem& operator=(const AttackDroneItem& _Other) = delete;
	AttackDroneItem& operator=(AttackDroneItem&& _Other) noexcept = delete;

protected:
	void Initialize() override;
	void AddDrone() override;
private:

};

