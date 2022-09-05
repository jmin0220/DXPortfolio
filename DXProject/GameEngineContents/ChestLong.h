#pragma once
#include "ChestParent.h"

// ���� :
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

	// ���Ž� �������� ������ enum
	ItemList GetItem()
	{
		return ItemList_;
	}

protected:
	void Update(float _DeltaTime) override;

	void Initialize() override;

	inline void ChangeOpenAnim() override
	{
		// TODO::�÷��̾��� ��尡 �ݾ׿� �¾ƾ߸� Open���� ó��
		IsOpen_ = true;

		Renderer_->ChangeFrameAnimation(TEX_OBJECT_CHEST_LONG_OPEN);
	}

private:
	void WaveAnimItemRenderer(float _DeltaTime);		// �������� ���Ʒ��� �Ϸ��̴� �ִϸ��̼�
	bool CollisionFunc(GameEngineCollision* _This, GameEngineCollision* _Other);

	GameEngineTextureRenderer* ShowItemRenderer_;
	ItemList ItemList_;
};

