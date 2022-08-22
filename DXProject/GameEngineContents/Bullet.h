#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ContentsFont;
class Bullet : public GameEngineActor
{
public:
	// constrcuter destructer
	Bullet();
	~Bullet();

	// delete Function
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

	void SetDamage(int _Damage)
	{
		Damage_ = _Damage;
	}

	void SetDirection(float4 _Direction)
	{
		Direction_ = _Direction;
	}

	void SetBulletYPositionLevel(int _PosLevel)
	{
		BulletYPositionLevel_ = _PosLevel;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	void CheckNegativeX();

	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	void BulletDeath();

	GameEngineCollision* Collision_;
	GameEngineTextureRenderer* Renderer_;
	ContentsFont* DamageFont_;

	int Damage_;
	float4 Direction_;
	float FlyLength_;
	bool BulletDeathFlg_;

	int BulletYPositionLevel_;
};

