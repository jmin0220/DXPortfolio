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

	void SetMoveDirection(float4 _Direction);

	inline float4 GetMagmaWormPosition()
	{
		return MagmaWormBody_[0]->GetTransform().GetWorldPosition();
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	MagmaWormBody* MagmaWormBody_[20];
	float4 Direction_;
	float4 DestPos_;
};

