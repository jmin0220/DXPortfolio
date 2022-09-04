#pragma once
#include "Item.h"

// Ό³Έν :
class HarvesterScythe : public Item
{
public:
	// constrcuter destructer
	HarvesterScythe();
	~HarvesterScythe();

	// delete Function
	HarvesterScythe(const HarvesterScythe& _Other) = delete;
	HarvesterScythe(HarvesterScythe&& _Other) noexcept = delete;
	HarvesterScythe& operator=(const HarvesterScythe& _Other) = delete;
	HarvesterScythe& operator=(HarvesterScythe&& _Other) noexcept = delete;

	void Initialize() override;

	void BuffItemUpdate() override;
protected:

private:

};

