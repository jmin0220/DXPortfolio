#pragma once
#include "Drops.h"

// 설명 :
class Exp : public Drops
{
public:
	// constrcuter destructer
	Exp();
	~Exp();

	// delete Function
	Exp(const Exp& _Other) = delete;
	Exp(Exp&& _Other) noexcept = delete;
	Exp& operator=(const Exp& _Other) = delete;
	Exp& operator=(Exp&& _Other) noexcept = delete;

	inline void SetExpValue(int _Value)
	{
		ExpValue_ = _Value;
	}

	void SetDestPos(float4 _DestPos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	// 경험치양
	int ExpValue_;

	// 날아갈 위치
	float4 DestPos_;

	bool ChasePlayer();
};

