#pragma once
#include "PreCompile.h"
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CharacterSelecter : public GameEngineActor
{
public:
	// constrcuter destructer
	CharacterSelecter();
	~CharacterSelecter();

	// delete Function
	CharacterSelecter(const CharacterSelecter& _Other) = delete;
	CharacterSelecter(CharacterSelecter&& _Other) noexcept = delete;
	CharacterSelecter& operator=(const CharacterSelecter& _Other) = delete;
	CharacterSelecter& operator=(CharacterSelecter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRenderer* Renderer_;
};

