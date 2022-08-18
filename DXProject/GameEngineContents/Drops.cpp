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
	// 플레이어 위치로 방향을 설정
	FlyDir_ = PlayerPos_ - this->GetTransform().GetWorldPosition();
	
	// 오브젝트가 충분히 근접함
	if (FlyDir_.Length() <= 10.0f)
	{
		return false;
	}
	// 오브젝트가 충분히 근접하지 못함
	else
	{
		FlyDir_.Normalize();

		// 플레이어를 향해 이동
		this->GetTransform().SetWorldMove(FlyDir_ * GameEngineTime::GetDeltaTime() * 300.0f);
		return true;
	}
}