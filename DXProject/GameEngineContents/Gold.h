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
		flyDir_ = _Dir;
	}

	static inline void SetColMap(GameEngineTexture* _ColMap)
	{
		ColMap_ = _ColMap;
	}

	void UpdateGoldOption();
	void GoldPop();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	// 금액
	int GoldValue_;
	// 등장한 뒤 날아갈 방향
	float4 flyDir_;
	// 코인이 튕겨질 속도
	float PopSpeed_;
	// 추락 판정용 맵정보
	static GameEngineTexture* ColMap_;

	void GroundFallCheck(float _DeltaTime);
};

