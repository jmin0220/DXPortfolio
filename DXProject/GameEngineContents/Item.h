#pragma once

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

	void ReturnItemOnField();

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

	inline GameEngineTextureRenderer* GetInventoryRenderer()
	{
		return InventoryRenderer_;
	}

	inline bool GetIsUseItem() const
	{
		return IsUseItem_;
	}

	virtual void Initialize() {};

	

	// �� �����۸��� �ʿ��� ������Ʈ���� ��ӹ޾Ƽ�
	// �ڽ��� ������Ʈ�� �����Ŵ
	// ���� ���� ������Ʈ��� �ƹ��͵� ���� �ʰ� ����
	virtual void FrameItemUpdate(float4 _PlayerPos) { return; };					// �� �����Ӹ��� ����Ǿ���� ������
	virtual void AtkItemUpdate() { return; };										// ������ �ϴ� ������ ����
	virtual void BulletItemUpdate(float4 _BulletPos, bool _CritFlg) { return; };	// �Ѿ��� ���Ϳ� �ε����� ������ ����
	virtual void LevelUpItemUpdate(float4 _PlayerPos) { return; };					// �������ϴ� ������ ����
	virtual void BuffItemUpdate() { return; };										// �������� �����ϴ� ������ ����
	virtual void UseItemUpdate(float4 _PlayerPos, float4 _Dir = float4::ZERO) { return; };						// �������� ��ư�� ������ ������ ����

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	GameEngineTextureRenderer* Renderer_;
	GameEngineTextureRenderer* InventoryRenderer_;
	GameEngineFontRenderer* ItemNameRenderer_;
	GameEngineFontRenderer* PickUpRenderer_;

	PlayerStatus PlayerStatus_;

	// ������ �̸�
	std::string ItemName_;

	// �ߺ��� �������� �󸶳� �Ծ���
	int OverlapCounter_;

	// �������ۿ���(���������� 1���� ���� �� �����Ƿ�)
	bool IsUseItem_;
private:
	// ����� �������ΰ�
	bool ItemRootingFlg_;
	bool RootingEffectEndFlg_;

	float4 PlayerPos_;

	float PosYTimer_;
	float PosY_;
};

