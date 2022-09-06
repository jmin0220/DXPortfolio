#pragma once
#include "ChestLong.h"

// Ό³Έν :
class ChestLongSet : public GameEngineActor
{
public:
	// constrcuter destructer
	ChestLongSet();
	~ChestLongSet();

	// delete Function
	ChestLongSet(const ChestLongSet& _Other) = delete;
	ChestLongSet(ChestLongSet&& _Other) noexcept = delete;
	ChestLongSet& operator=(const ChestLongSet& _Other) = delete;
	ChestLongSet& operator=(ChestLongSet&& _Other) noexcept = delete;

	void CreateChestLongSet(float4 _Pos);

protected:
	void Start();
	void Update(float _DeltaTime);

	ChestLong* ChestLong_[3];
	ItemList CreatedItem_[3];

private:
	bool SomethingOpendFlg_;
};

