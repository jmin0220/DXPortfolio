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

	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}

	virtual void Initialize() {};

	

	// �� �����۸��� �ʿ��� ������Ʈ���� ��ӹ޾Ƽ�
	// �ڽ��� ������Ʈ�� �����Ŵ
	// ���� ���� ������Ʈ��� �ƹ��͵� ���� �ʰ� ����
	virtual void FrameItemUpdate() { return; };
	virtual void AtkItemUpdate() { return; };
	virtual void LevelUpItemUpdate() { return; };
	virtual void BuffItemUpdate() { return; };

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	ItemType ItemType_;

	GameEngineTextureRenderer* Renderer_;
	GameEngineFontRenderer* ItemNameRenderer_;
	GameEngineFontRenderer* PickUpRenderer_;

	PlayerStatus PlayerStatus_;

	// ������ �̸�
	std::string ItemName_;

private:
	// ����� �������ΰ�
	bool ItemRootingFlg_;
	bool RootingEffectEndFlg_;
	// �ߺ��� �������� �󸶳� �Ծ���
	int OverlapCounter_;

	float4 PlayerPos_;

	float PosYTimer_;
	float PosY_;
};

