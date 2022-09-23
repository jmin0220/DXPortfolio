#include "PreCompile.h"
#include "MagmaWorm.h"
#include "MagmaWormBody.h"

MagmaWorm::MagmaWorm() 
{
}

MagmaWorm::~MagmaWorm() 
{
}

void MagmaWorm::Start()
{

	for (int i = 9; i > 0; i--)
	{
		MagmaWormBody_[i] = GetLevel()->CreateActor<MagmaWormBody>();
	}

	MagmaWormBody_[0] = GetLevel()->CreateActor<MagmaWormBody>();
	MagmaWormBody_[0]->SetHead();
}

void MagmaWorm::Update(float _DeltaTime)
{
	// 몸의 포지션들을 결정
	for (int i = 0; i < 9; i++)
	{
		MagmaWormBody_[i + 1]->MovetoDestination(MagmaWormBody_[i]->GetTransform().GetWorldPosition());
	}

	MagmaWormBody_[0]->GetTransform().SetWorldMove(GetTransform().GetRightVector() * 100.0f * _DeltaTime);
}

