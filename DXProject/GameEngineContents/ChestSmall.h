#pragma once
#include "ChestParent.h"

// Ό³Έν :
class ChestSmall : public ChestParent
{
public:
	// constrcuter destructer
	ChestSmall();
	~ChestSmall();

	// delete Function
	ChestSmall(const ChestSmall& _Other) = delete;
	ChestSmall(ChestSmall&& _Other) noexcept = delete;
	ChestSmall& operator=(const ChestSmall& _Other) = delete;
	ChestSmall& operator=(ChestSmall&& _Other) noexcept = delete;

protected:
	void AnimationInit() override;

private:

};

