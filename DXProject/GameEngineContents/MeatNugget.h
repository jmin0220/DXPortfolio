#pragma once
#include "Item.h"

// Ό³Έν :
class MeatNugget : public Item
{
public:
	// constrcuter destructer
	MeatNugget();
	~MeatNugget();

	// delete Function
	MeatNugget(const MeatNugget& _Other) = delete;
	MeatNugget(MeatNugget&& _Other) noexcept = delete;
	MeatNugget& operator=(const MeatNugget& _Other) = delete;
	MeatNugget& operator=(MeatNugget&& _Other) noexcept = delete;

	void Initialize() override;

protected:

private:

};

