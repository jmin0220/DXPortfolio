#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
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

	inline void SetDamage(int _Damage)
	{
		Damage_ = _Damage;
	}

	inline void SetCritFlgTrue()
	{
		CirtFlg_ = true;
	}

	inline void SetDirection(float4 _Direction)
	{
		Direction_ = _Direction;
	}

	inline void SetBulletYPositionLevel(int _PosLevel)
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

	// 데미지
	int Damage_;
	// 크리티컬
	bool CirtFlg_;
	// 날아갈 방향
	float4 Direction_;
	// 날아간 거리
	float FlyLength_;
	float BulletSpeed_;
	// Death타이머가 세팅되어있는가
	bool BulletDeathFlg_;

	int BulletYPositionLevel_;
};

