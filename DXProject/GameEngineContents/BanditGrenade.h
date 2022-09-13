#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class BanditGrenade : public GameEngineActor
{
public:
	// constrcuter destructer
	BanditGrenade();
	~BanditGrenade();

	// delete Function
	BanditGrenade(const BanditGrenade& _Other) = delete;
	BanditGrenade(BanditGrenade&& _Other) noexcept = delete;
	BanditGrenade& operator=(const BanditGrenade& _Other) = delete;
	BanditGrenade& operator=(BanditGrenade&& _Other) noexcept = delete;

	inline void SetColMap(GameEngineTexture* _ColMap)
	{
		ColMap_ = _ColMap;
	}

	inline void SetDir(float4 _Dir)
	{
		CreatedDir_ = _Dir;
	}

	inline void SetDamage(float _Damage)
	{
		Damage_ = _Damage;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTexture* ColMap_;
	GameEngineTextureRenderer* Renderer_;
	GameEngineTextureRenderer* EffectRenderer_;

	GameEngineCollision* Collision_;

	// 날아갈 방향
	float4 CreatedDir_;
	float Damage_;
	float JumpSpeed_;

	bool IsExplosion_;

	void GroundFall(float _DeltaTime);
	void CreateExplosion();
	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
};

