#pragma once


// Ό³Έν :
class Item;
class ItemManager : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemManager();
	~ItemManager();

	// delete Function
	ItemManager(const ItemManager& _Other) = delete;
	ItemManager(ItemManager&& _Other) noexcept = delete;
	ItemManager& operator=(const ItemManager& _Other) = delete;
	ItemManager& operator=(ItemManager&& _Other) noexcept = delete;

	static std::vector<Item*> ItemVector_;

	static void CreateItem(GameEngineLevel* _Level, float4 _Pos);

	static void CreateItem(GameEngineLevel* _Level, ItemList _ItemList, float4 _Pos);

	static inline void SetPlayerPos(float4 _Pos)
	{
		PlayerPos_ = _Pos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static float4 PlayerPos_;

	float4 ToPlayerLength_;

};

