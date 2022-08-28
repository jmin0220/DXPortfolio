#pragma once
#include "ChestParent.h"

// Ό³Έν :
class ChestBig : public ChestParent
{
public:
	// constrcuter destructer
	ChestBig();
	~ChestBig();

	// delete Function
	ChestBig(const ChestBig& _Other) = delete;
	ChestBig(ChestBig&& _Other) noexcept = delete;
	ChestBig& operator=(const ChestBig& _Other) = delete;
	ChestBig& operator=(ChestBig&& _Other) noexcept = delete;

protected:
	void Initialize() override;

	inline void ChangeOpenAnim() override
	{
		IsOpen_ = true;
		Renderer_->ChangeFrameAnimation(TEX_OBJECT_CHEST_BIG_OPEN);
	}

private:

};

