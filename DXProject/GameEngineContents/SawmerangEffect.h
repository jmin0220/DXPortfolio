#pragma once
#include "Drops.h"

// ���� :
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

	// ���ư� �Ÿ�
	float FlyLength_;
	float Speed_;

	// ���ư��� �� = False, ���ƿ��� �� = true;
	bool IsReturn_;

	// ���ư� ����
	float4 FlyDirection_;

	std::list<GameEngineCollision*> CheckedMonster_;
	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
};

