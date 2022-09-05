#include "PreCompile.h"
#include "ChestLongSet.h"
#include "ChestLong.h"


ChestLongSet::ChestLongSet()
	: SomethingOpendFlg_(false)
{
}

ChestLongSet::~ChestLongSet() 
{
}

void ChestLongSet::Start()
{
	for (int i = 0; i < 3; i++)
	{
		ChestLong_[i] = GetLevel()->CreateActor<ChestLong>();
	}
}

void ChestLongSet::Update(float _DeltaTime)
{
	for (int i = 0; i < 3; i++)
	{
		if (true == ChestLong_[i]->GetIsOpen())
		{
			SomethingOpendFlg_ = true;
		}
	}


}

void ChestLongSet::CreateChestLongSet(float4 _Pos)
{
	// 기준이 되는 포지션
	float4 StandardPos = _Pos;
	
	ChestLong_[0]->GetTransform().SetWorldPosition({ StandardPos.x - 76, StandardPos.y, StandardPos.z });
	ChestLong_[1]->GetTransform().SetWorldPosition(StandardPos);
	ChestLong_[2]->GetTransform().SetWorldPosition({ StandardPos.x + 76, StandardPos.y, StandardPos.z });
}