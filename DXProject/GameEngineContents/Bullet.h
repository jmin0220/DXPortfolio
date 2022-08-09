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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineCollision* Collision_;
	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	int Damage_;
};

