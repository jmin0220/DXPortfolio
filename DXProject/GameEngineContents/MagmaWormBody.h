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

	void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

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
	void MoveToDestinationHead(float4 _Direction, float4 _DestPos);

	void SetWormBodyScale(int _ScaleLevel);

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
	float4 DestPosHead_;
	// ������, �ݸ����� ȸ���� ����
	// ���������� üũ�� Ÿ�̸�
	float MoveDestinationTimer_;
	// ScaleLevel�� ���� ũ�Ⱑ ������ ����������
	float RenderScale_;

	float4 HeadDirection_;

	// ȸ���� ���� ����
	// ������ ����
	float CurDegree_;
	// ���� ��µ� ����
	float NowDegree_;

	float DeltaTime_;
};

