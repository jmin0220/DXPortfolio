#pragma once
#include "BossMonster.h"

// 설명 :
class MagmaWormBody : public BossMonster
{
public:
	// constrcuter destructer
	MagmaWormBody();
	~MagmaWormBody();

	// delete Function
	MagmaWormBody(const MagmaWormBody& _Other) = delete;
	MagmaWormBody(MagmaWormBody&& _Other) noexcept = delete;
	MagmaWormBody& operator=(const MagmaWormBody& _Other) = delete;
	MagmaWormBody& operator=(MagmaWormBody&& _Other) noexcept = delete;

	// 이 클래스는 머리가 될 클래스
	void SetHead();

	void SetDeath();

	// 데미지를 받으면 받은 데미지를 저장하고, MagmaWorm클래스에 출력
	inline void HitFunction(int _Damage) override
	{
		HittedDamage_ = _Damage;
	}

	// 이번 프레임에 받은 데미지를 출력
	inline int OutputHittedDamage()
	{
		return HittedDamage_;
	}

	// 리셋
	inline void ResetHittedDamageZero()
	{
		HittedDamage_ = 0;
	}

	void MovetoDestination(float4 _DestPos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;

	bool IsHead_;

	int HittedDamage_;	// 이번 프레임에 받은 데미지를 저장

	// 목적지
	float4 DestPos_;
	float4 MoveDir_;
	// 목적지까지 체크할 타이머
	float MoveDestinationTimer_;

	float DeltaTime_;
};

