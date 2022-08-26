#pragma once

// Ό³Έν :
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

	virtual void AnimationInit() {};

	GameEngineTextureRenderer* Renderer_;

	int GoldValue_;
	int ExpValue_;
};

