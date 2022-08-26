#pragma once
#include "ChestParent.h"

// ���� :
class ChestNormal : public ChestParent
{
public:
	// constrcuter destructer
	ChestNormal();
	~ChestNormal();

	// delete Function
	ChestNormal(const ChestNormal& _Other) = delete;
	ChestNormal(ChestNormal&& _Other) noexcept = delete;
	ChestNormal& operator=(const ChestNormal& _Other) = delete;
	ChestNormal& operator=(ChestNormal&& _Other) noexcept = delete;

protected:
	void AnimationInit() override;

private:

};

