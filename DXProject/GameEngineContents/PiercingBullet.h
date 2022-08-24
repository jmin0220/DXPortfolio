#pragma once

// 설명 :
class ContentsFont;
class PiercingBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	PiercingBullet();
	~PiercingBullet();

	// delete Function
	PiercingBullet(const PiercingBullet& _Other) = delete;
	PiercingBullet(PiercingBullet&& _Other) noexcept = delete;
	PiercingBullet& operator=(const PiercingBullet& _Other) = delete;
	PiercingBullet& operator=(PiercingBullet&& _Other) noexcept = delete;

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

	inline void SetPiercingLength(float _PiercingLength)
	{
		PiercingLength_ = _PiercingLength;
		ChangeCollisionPivot();
	}

	inline void SetBulletYPositionLevel(int _PosLevel)
	{
		BulletYPositionLevel_ = _PosLevel;
	}

	inline void ResizePiercingBulletXSize()
	{
		Collision_->GetTransform().SetWorldScale({ PiercingLength_, 10.0f, 1.0f });
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	void ChangeCollisionPivot();

	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	void CreateHitEffect();

	GameEngineCollision* Collision_;
	GameEngineTextureRenderer* Renderer_;
	ContentsFont* DamageFont_;

	// 데미지
	int Damage_;
	// 크리티컬
	bool CirtFlg_;
	// 날아갈 방향
	float4 Direction_;
	// 총알 길이
	float PiercingLength_;

	// Death타이머가 세팅되어있는가
	bool BulletDeathFlg_;

	int BulletYPositionLevel_;

	std::list<GameEngineCollision*> CheckedMonster_;
};

