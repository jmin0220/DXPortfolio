#pragma once
#include "Drops.h"

// ���� :
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
	// �ݾ�
	int GoldValue_;
	// ������ ƨ���� �ӵ�
	float PopSpeed_;

	void GroundFallCheck(float _DeltaTime);

	bool ChasePlayer();
};

