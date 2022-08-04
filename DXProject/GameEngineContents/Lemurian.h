#pragma once
#include "Monster.h"

// Ό³Έν :
class Lemurian : public Monster
{
public:
	// constrcuter destructer
	Lemurian();
	~Lemurian();

	// delete Function
	Lemurian(const Lemurian& _Other) = delete;
	Lemurian(Lemurian&& _Other) noexcept = delete;
	Lemurian& operator=(const Lemurian& _Other) = delete;
	Lemurian& operator=(Lemurian&& _Other) noexcept = delete;

protected:

private:

};

