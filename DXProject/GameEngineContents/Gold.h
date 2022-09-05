#pragma once
#include "Drops.h"

// 설명 :
class Gold : public Drops
{
public:
	// constrcuter destructer
	Gold();
	~Gold();

	// delete Function
	Gold(const Gold& _Other) = delete;
	Gold(Gold&& _Other) noexcept = delete;
	Gold& operator=(const Gold& _Other) = delete;
	Gold& operator=(Gold&& _Other) noexcept = delete;

	inline void SetGoldValue(int _Value)
	{
		GoldValue_ = _Value;
	}

	inline void SetFlyDir(float4 _Dir)
	{
		FlyDir_ = _Dir;
	}

	void UpdateGoldOption();
	void GoldPop();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	// 금액
	int GoldValue_;
	// 코인이 튕겨질 속도
	float PopSpeed_;

	void GroundFallCheck(float _DeltaTime);

	bool ChasePlayer();
};

