#pragma once

// Ό³Έν :
class GameEngineState
{
public:
	// constrcuter destructer
	GameEngineState();
	~GameEngineState();

	// delete Function
	GameEngineState(const GameEngineState& _Other) = delete;
	GameEngineState(GameEngineState&& _Other) noexcept = delete;
	GameEngineState& operator=(const GameEngineState& _Other) = delete;
	GameEngineState& operator=(GameEngineState&& _Other) noexcept = delete;

protected:

private:

};

