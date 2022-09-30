#pragma once
#include "DroneItem.h"

// Ό³Έν :
class MissileDroneItem : public DroneItem
{
public:
	// constrcuter destructer
	MissileDroneItem();
	~MissileDroneItem();

	// delete Function
	MissileDroneItem(const MissileDroneItem& _Other) = delete;
	MissileDroneItem(MissileDroneItem&& _Other) noexcept = delete;
	MissileDroneItem& operator=(const MissileDroneItem& _Other) = delete;
	MissileDroneItem& operator=(MissileDroneItem&& _Other) noexcept = delete;

protected:
	void Initialize() override;
	void AddDrone() override;
private:

};

