#pragma once
#include "AutoAtkObject.h"

// Ό³Έν :
class MissileSmokeRenderer;
class Missile : public AutoAtkObject
{
public:
	// constrcuter destructer
	Missile();
	~Missile();

	// delete Function
	Missile(const Missile& _Other) = delete;
	Missile(Missile&& _Other) noexcept = delete;
	Missile& operator=(const Missile& _Other) = delete;
	Missile& operator=(Missile&& _Other) noexcept = delete;

	void SetTargetPos(float4 _Pos)
	{
		TargetPos_ = _Pos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Explosion();

	int Damage_;
	bool IsExplosion_;
	bool SetPositionFlg_;

	float DegreeX_;
	float Speed_;
	float ChaseTimer_;
	float SuicideTimer_;

	float NowDegree_;
	float CurDegree_;

	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineCollision* ExplosionCollision_;

	CollisionReturn CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn ExplosionCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

};

