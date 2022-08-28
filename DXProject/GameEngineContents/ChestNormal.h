#pragma once
#include "ChestParent.h"

// Ό³Έν :
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
	void Initialize() override;

	inline void ChangeOpenAnim() override
	{
		IsOpen_ = true;
		Renderer_->ChangeFrameAnimation(TEX_OBJECT_CHEST_NORMAL_OPEN);
	}

private:

};

