#pragma once

// ���� :
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

	// ������
	int Damage_;
	// ũ��Ƽ��
	bool CirtFlg_;
	// ���ư� ����
	float4 Direction_;
	// ���ư� �Ÿ�
	float FlyLength_;
	float BulletSpeed_;
	// DeathŸ�̸Ӱ� ���õǾ��ִ°�
	bool BulletDeathFlg_;

	int BulletYPositionLevel_;
};

