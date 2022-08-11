#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineCollision;
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	void CheckNegativeX();

	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	void BulletDeath();

	GameEngineCollision* Collision_;
	GameEngineTextureRenderer* Renderer_;

	int Damage_;
	float4 Direction_;
	float FlyLength_;
	bool BulletDeathFlg_;
};

