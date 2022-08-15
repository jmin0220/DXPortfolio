#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Drops : public GameEngineActor
{
public:
	// constrcuter destructer
	Drops();
	~Drops();

	// delete Function
	Drops(const Drops& _Other) = delete;
	Drops(Drops&& _Other) noexcept = delete;
	Drops& operator=(const Drops& _Other) = delete;
	Drops& operator=(Drops&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	GameEngineTextureRenderer* Renderer_;
private:

};

