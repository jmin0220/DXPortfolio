#pragma once
#include "SingleColorRenderer.h"

// Ό³Έν :
class EndBG : public GameEngineActor
{
public:
	// constrcuter destructer
	EndBG();
	~EndBG();

	// delete Function
	EndBG(const EndBG& _Other) = delete;
	EndBG(EndBG&& _Other) noexcept = delete;
	EndBG& operator=(const EndBG& _Other) = delete;
	EndBG& operator=(EndBG&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	SingleColorRenderer* Black_;
	GameEngineFontRenderer* Font_;
};

