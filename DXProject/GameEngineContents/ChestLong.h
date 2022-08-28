#pragma once
#include "ChestParent.h"

// 설명 :
class ChestLong : public ChestParent
{
public:
	// constrcuter destructer
	ChestLong();
	~ChestLong();

	// delete Function
	ChestLong(const ChestLong& _Other) = delete;
	ChestLong(ChestLong&& _Other) noexcept = delete;
	ChestLong& operator=(const ChestLong& _Other) = delete;
	ChestLong& operator=(ChestLong&& _Other) noexcept = delete;

protected:
	void Initialize() override;

	inline void ChangeOpenAnim() override
	{
		// TODO::플레이어의 골드가 금액에 맞아야만 Open으로 처리
		IsOpen_ = true;

		Renderer_->ChangeFrameAnimation(TEX_OBJECT_CHEST_LONG_OPEN);
	}

private:

};

