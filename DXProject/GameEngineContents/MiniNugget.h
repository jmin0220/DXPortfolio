#pragma once
#include "Drops.h"

// Ό³Έν :
class MiniNugget : public Drops
{
public:
	// constrcuter destructer
	MiniNugget();
	~MiniNugget();

	// delete Function
	MiniNugget(const MiniNugget& _Other) = delete;
	MiniNugget(MiniNugget&& _Other) noexcept = delete;
	MiniNugget& operator=(const MiniNugget& _Other) = delete;
	MiniNugget& operator=(MiniNugget&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;

	void GroundFall(float _DeltaTime);

	float4 CreatedDir_;
};

