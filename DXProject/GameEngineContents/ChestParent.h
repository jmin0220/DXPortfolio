#pragma once

// 업그레이드되는 유료 Chest 
// Press 'A' to offer for a chance of rewards... ($<금액>)

// Chect공통
// Press 'A' to purchase chest ($<금액>)

// ChestLong (구매)
// Press 'A' to buy item ($<금액>)

// Container(무료)
// Press 'A' to open container

// Drone
// Press 'A' to repair the drone ($<금액>)

// 설명 :
class ChestParent : public GameEngineActor
{
public:
	// constrcuter destructer
	ChestParent();
	~ChestParent();

	// delete Function
	ChestParent(const ChestParent& _Other) = delete;
	ChestParent(ChestParent&& _Other) noexcept = delete;
	ChestParent& operator=(const ChestParent& _Other) = delete;
	ChestParent& operator=(ChestParent&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	virtual void Initialize() {};

	virtual void ChangeOpenAnim() {};

	GameEngineTextureRenderer* Renderer_;
	GameEngineFontRenderer* FontRenderer_;
	GameEngineCollision* Collision_;

	int ChestPrice_;
	int GoldValue_;
	int ExpValue_;

	bool IsOpen_;

private:
	bool CollisionCheckPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);
};

