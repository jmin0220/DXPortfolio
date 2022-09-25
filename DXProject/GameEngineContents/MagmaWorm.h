#pragma once
#include "BossMonster.h"
#include "MagmaWormBody.h"

// Ό³Έν :
class MagmaWorm : public BossMonster
{
public:
	// constrcuter destructer
	MagmaWorm();
	~MagmaWorm();

	// delete Function
	MagmaWorm(const MagmaWorm& _Other) = delete;
	MagmaWorm(MagmaWorm&& _Other) noexcept = delete;
	MagmaWorm& operator=(const MagmaWorm& _Other) = delete;
	MagmaWorm& operator=(MagmaWorm&& _Other) noexcept = delete;

	inline void SetWarningOn(float4 _Pos)
	{
		WarningRenderer_->On();
		WarningRenderer_->GetTransform().SetWorldPosition(_Pos);
	}

	inline void WarningOff()
	{
		WarningRenderer_->Off();
	}

	void SetMoveDirection(float4 _Direction);

	inline float4 GetMagmaWormPosition()
	{
		return MagmaWormBody_[0]->GetTransform().GetWorldPosition();
	}

protected:
	void Start() override;

	void AnimationInit() override;
	void StateInit() override;

	void AttackStart(const StateInfo& _Info);
	void SpawnStart(const StateInfo& _Info);
	void DeathStart(const StateInfo& _Info);

	void AttackUpdate(float _DeltaTime, const StateInfo& _Info);
	void DeathUpdate(float _DeltaTime, const StateInfo& _Info);
	void SpawnUpdate(float _DeltaTime, const StateInfo& _Info);

	void DeathEnd(const StateInfo& _Info);

private:
	MagmaWormBody* MagmaWormBody_[20];
	float4 Direction_;
	float4 DestPos_;

	GameEngineTextureRenderer* WarningRenderer_;
};

