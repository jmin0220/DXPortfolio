#pragma once

// ���׷��̵�Ǵ� ���� Chest 
// Press 'A' to offer for a chance of rewards... ($<�ݾ�>)

// Chect����
// Press 'A' to purchase chest ($<�ݾ�>)

// ChestLong (����)
// Press 'A' to buy item ($<�ݾ�>)

// Container(����)
// Press 'A' to open container

// Drone
// Press 'A' to repair the drone ($<�ݾ�>)

// ���� :
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

