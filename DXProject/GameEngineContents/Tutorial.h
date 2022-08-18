#pragma once

// Ό³Έν :
class Tutorial : public GameEngineActor
{
public:
	// constrcuter destructer
	Tutorial();
	~Tutorial();

	// delete Function
	Tutorial(const Tutorial& _Other) = delete;
	Tutorial(Tutorial&& _Other) noexcept = delete;
	Tutorial& operator=(const Tutorial& _Other) = delete;
	Tutorial& operator=(Tutorial&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	GameEngineTextureRenderer* Renderer_;
};

