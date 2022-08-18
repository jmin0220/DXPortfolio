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

	static inline void SetPlayerPos(float4 _Pos)
	{
		PlayerPos_ = _Pos;
	}

protected:
	void Start() override {};
	void Update(float _DeltaTime) override {};

	GameEngineTextureRenderer* Renderer_;

	bool ChasePlayer();
	float PlayerChaseTimer_;

	float4 FlyDir_;

	static float4 PlayerPos_;
};

