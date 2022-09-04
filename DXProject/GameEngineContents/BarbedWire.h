#pragma once
#include "Item.h"

// Ό³Έν :
class BarbedWire : public Item
{
public:
	// constrcuter destructer
	BarbedWire();
	~BarbedWire();

	// delete Function
	BarbedWire(const BarbedWire& _Other) = delete;
	BarbedWire(BarbedWire&& _Other) noexcept = delete;
	BarbedWire& operator=(const BarbedWire& _Other) = delete;
	BarbedWire& operator=(BarbedWire&& _Other) noexcept = delete;

	void Initialize() override;

protected:

private:

};

