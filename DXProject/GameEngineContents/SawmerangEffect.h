#pragma once
#include "Drops.h"

// 설명 :
class SawmerangEffect : public Drops
{
public:
	// constrcuter destructer
	SawmerangEffect();
	~SawmerangEffect();

	// delete Function
	SawmerangEffect(const SawmerangEffect& _Other) = delete;
	SawmerangEffect(SawmerangEffect&& _Other) noexcept = delete;
	SawmerangEffect& operator=(const SawmerangEffect& _Other) = delete;
	SawmerangEffect& operator=(SawmerangEffect&& _Other) noexcept = delete;

	void SetDirection(float4 _Dir)
	{
		FlyDirection_ = _Dir;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;

	// 날아간 거리
	float FlyLength_;
	float Speed_;

	// 날아가는 중 = False, 돌아오는 중 = true;
	bool IsReturn_;

	// 날아갈 방향
	float4 FlyDirection_;

	std::list<GameEngineCollision*> CheckedMonster_;
	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
};

