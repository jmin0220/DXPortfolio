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

	void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

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
	void MoveToDestinationHead(float4 _Direction, float4 _DestPos);

	void SetWormBodyScale(int _ScaleLevel);

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
	float4 DestPosHead_;
	// 렌더러, 콜리전이 회전할 방향
	// 목적지까지 체크할 타이머
	float MoveDestinationTimer_;
	// ScaleLevel에 따라서 크기가 조정될 렌더러비율
	float RenderScale_;

	float4 HeadDirection_;

	// 회전을 위한 변수
	// 직전의 각도
	float CurDegree_;
	// 현재 출력된 각도
	float NowDegree_;

	float DeltaTime_;
};

