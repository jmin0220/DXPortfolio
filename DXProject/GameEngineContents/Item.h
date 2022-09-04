#pragma once

enum class ItemType
{
	FrameItem,		// �� �����Ӹ��� �����ؾ� �ϴ� ������
	AtkItem,		// �����Ҷ��� �����ؾ� �ϴ� ������
	LevelUpItem,	// �������Ҷ��� �����ؾ� �ϴ� ������
	BuffItem,		// �������ͽ� ���� ������
};

// ���� :
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
	// ������ �̸�
	std::string ItemName_;
	// ����� �������ΰ�
	bool ItemRootingFlg_;
	bool RootingEffectEndFlg_;
	// �ߺ��� �������� �󸶳� �Ծ���
	int OverlapCounter_;

	float4 PlayerPos_;
};

