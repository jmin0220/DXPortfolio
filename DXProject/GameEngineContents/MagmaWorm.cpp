#include "PreCompile.h"
#include "MagmaWorm.h"
#include "MagmaWormBody.h"

MagmaWorm::MagmaWorm() 
	: Direction_(GetTransform().GetRightVector())
{
}

MagmaWorm::~MagmaWorm() 
{
}

void MagmaWorm::Start()
{
	Speed_ = 500.0f;

	for (int i = 19; i > 0; i--)
	{
		MagmaWormBody_[i] = GetLevel()->CreateActor<MagmaWormBody>();
		MagmaWormBody_[i]->SetWormBodyScale(i);
		MagmaWormBody_[i]->SetSpeed(Speed_);
	}

	MagmaWormBody_[0] = GetLevel()->CreateActor<MagmaWormBody>();
	MagmaWormBody_[0]->SetHead();
}

void MagmaWorm::Update(float _DeltaTime)
{
	MagmaWormBody_[0]->GetTransform().SetWorldMove(Direction_ * Speed_ * _DeltaTime);

	// 몸의 포지션들을 결정
	for (int i = 0; i < 19; i++)
	{
		MagmaWormBody_[i + 1]->MovetoDestination(MagmaWormBody_[i]->GetTransform().GetWorldPosition());
	}
}

