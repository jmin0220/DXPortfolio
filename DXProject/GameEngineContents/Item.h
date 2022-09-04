#pragma once

enum class ItemType
{
	FrameItem,		// 매 프레임마다 동작해야 하는 아이템
	AtkItem,		// 공격할때만 동작해야 하는 아이템
	LevelUpItem,	// 레벨업할때만 동작해야 하는 아이템
	BuffItem,		// 스테이터스 버프 아이템
};

// 설명 :
class Item : public GameEngineActor
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	void SetItemRootingFlgTrue();

	// 
	inline void AddOverlapCounter()
	{
		OverlapCounter_ ++;
	}

	inline std::string GetItemName()
	{
		return ItemName_;
	}

	inline void SetPlayerPos(float4 _Pos)
	{
		PlayerPos_ = _Pos;
	}

	virtual void Initialize() {};

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	ItemType ItemType_;

	GameEngineTextureRenderer* Renderer_;
	GameEngineFontRenderer* ItemNameRenderer_;
	GameEngineFontRenderer* PickUpRenderer_;

private:
	// 아이템 이름
	std::string ItemName_;
	// 습득된 아이템인가
	bool ItemRootingFlg_;
	bool RootingEffectEndFlg_;
	// 중복된 아이템을 얼마나 먹었나
	int OverlapCounter_;

	float4 PlayerPos_;
};

