#include "PreCompile.h"
#include "Drops.h"

float4 Drops::PlayerPos_ = float4::ZERO;

Drops::Drops() 
	: PlayerChaseTimer_(0.0f)
{
}

Drops::~Drops() 
{
}

bool Drops::ChasePlayer()
{
	// �÷��̾� ��ġ�� ������ ����
	FlyDir_ = PlayerPos_ - this->GetTransform().GetWorldPosition();
	
	// ������Ʈ�� ����� ������
	if (FlyDir_.Length() <= 10.0f)
	{
		return false;
	}
	// ������Ʈ�� ����� �������� ����
	else
	{
		FlyDir_.Normalize();

		// �÷��̾ ���� �̵�
		this->GetTransform().SetWorldMove(FlyDir_ * GameEngineTime::GetDeltaTime() * 300.0f);
		return true;
	}
}