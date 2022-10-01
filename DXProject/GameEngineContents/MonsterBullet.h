#pragma once

// 설명 :
class ContentsFont;
class MonsterBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterBullet();
	~MonsterBullet();

	// delete Function
	MonsterBullet(const MonsterBullet& _Other) = delete;
	MonsterBullet(MonsterBullet&& _Other) noexcept = delete;
	MonsterBullet& operator=(const MonsterBullet& _Other) = delete;
	MonsterBullet& operator=(MonsterBullet&& _Other) noexcept = delete;

	inline void SetDamage(int _Damage)
	{
		Damage_ = _Damage;
	}

	inline void SetDirection(float4 _Direction)
	{
		Direction_ = _Direction;
	}

	inline void SetBulletYPositionLevel(int _PosLevel)
	{
		BulletYPositionLevel_ = _PosLevel;
	}

	void SetBulletAnim(std::string _AnimName);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void CheckNegativeX();

	CollisionReturn CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
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

