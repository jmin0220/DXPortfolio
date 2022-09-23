#pragma once
#include "BossMonster.h"

// ���� :
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

	// �� Ŭ������ �Ӹ��� �� Ŭ����
	void SetHead();

	void SetDeath();

	// �������� ������ ���� �������� �����ϰ�, MagmaWormŬ������ ���
	inline void HitFunction(int _Damage) override
	{
		HittedDamage_ = _Damage;
	}

	// �̹� �����ӿ� ���� �������� ���
	inline int OutputHittedDamage()
	{
		return HittedDamage_;
	}

	// ����
	inline void ResetHittedDamageZero()
	{
		HittedDamage_ = 0;
	}

	void MovetoDestination(float4 _DestPos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;

	bool IsHead_;

	int HittedDamage_;	// �̹� �����ӿ� ���� �������� ����

	// ������
	float4 DestPos_;
	float4 MoveDir_;
	// ���������� üũ�� Ÿ�̸�
	float MoveDestinationTimer_;

	float DeltaTime_;
};

