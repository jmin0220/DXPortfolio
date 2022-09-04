#pragma once
#include "Item.h"

// Ό³Έν :
class RedWhip : public Item
{
public:
	// constrcuter destructer
	RedWhip();
	~RedWhip();

	// delete Function
	RedWhip(const RedWhip& _Other) = delete;
	RedWhip(RedWhip&& _Other) noexcept = delete;
	RedWhip& operator=(const RedWhip& _Other) = delete;
	RedWhip& operator=(RedWhip&& _Other) noexcept = delete;

	void Initialize() override;

	void BuffItemUpdate() override;

protected:

private:

};

