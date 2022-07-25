#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TitleBG : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleBG();
	~TitleBG();

	// delete Function
	TitleBG(const TitleBG& _Other) = delete;
	TitleBG(TitleBG&& _Other) noexcept = delete;
	TitleBG& operator=(const TitleBG& _Other) = delete;
	TitleBG& operator=(TitleBG&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
};

