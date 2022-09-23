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

	void ChangeOpenAnimChestLong();

	ItemList GetItemList()
	{
		return ItemList_;
	}

protected:
	void Update(float _DeltaTime) override;

	void Initialize() override;

	void ChangeOpenAnim() override;

private:
	void WaveAnimItemRenderer(float _DeltaTime);		// �������� ���Ʒ��� �Ϸ��̴� �ִϸ��̼�
	CollisionReturn CollisionFunc(GameEngineCollision* _This, GameEngineCollision* _Other);


	GameEngineTextureRenderer* ShowItemRenderer_;
	ItemList ItemList_;

	bool IsSelected_;
};

