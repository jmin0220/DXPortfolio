#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class StartLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	StartLevel();
	~StartLevel();

	// delete Function
	StartLevel(const StartLevel& _Other) = delete;
	StartLevel(StartLevel&& _Other) noexcept = delete;
	StartLevel& operator=(const StartLevel& _Other) = delete;
	StartLevel& operator=(StartLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

