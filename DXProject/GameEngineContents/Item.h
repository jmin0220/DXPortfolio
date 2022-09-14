#pragma once

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

	

	// 각 아이템마다 필요한 업데이트만을 상속받아서
	// 자신의 업데이트를 실행시킴
	// 내가 없는 업데이트라면 아무것도 하지 않고 종료
	virtual void FrameItemUpdate(float4 _PlayerPos) { return; };					// 매 프레임마다 실행되어야할 아이템
	virtual void AtkItemUpdate() { return; };										// 공격을 하는 순간에 실행
	virtual void BulletItemUpdate(float4 _BulletPos, bool _CritFlg) { return; };	// 총알이 몬스터에 부딪히는 순간에 실행
	virtual void LevelUpItemUpdate(float4 _PlayerPos) { return; };					// 레벨업하는 순간에 실행
	virtual void BuffItemUpdate() { return; };										// 아이템을 습득하는 순간에 실행
	virtual void UseItemUpdate(float4 _PlayerPos, float4 _Dir = float4::ZERO) { return; };						// 사용아이템 버튼을 누르는 순간에 실행

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	GameEngineTextureRenderer* Renderer_;
	GameEngineTextureRenderer* InventoryRenderer_;
	GameEngineFontRenderer* ItemNameRenderer_;
	GameEngineFontRenderer* PickUpRenderer_;

	PlayerStatus PlayerStatus_;

	// 아이템 이름
	std::string ItemName_;

	// 중복된 아이템을 얼마나 먹었나
	int OverlapCounter_;

	// 사용아이템여부(사용아이템은 1개만 가질 수 있으므로)
	bool IsUseItem_;
private:
	// 습득된 아이템인가
	bool ItemRootingFlg_;
	bool RootingEffectEndFlg_;

	float4 PlayerPos_;

	float PosYTimer_;
	float PosY_;
};

