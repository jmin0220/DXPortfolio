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
		CreatedItem_[i] = ChestLong_[i]->GetItemList();
	}

	for (;;)
	{
		bool ItemRecreateFlg = false;

		if (CreatedItem_[0] == CreatedItem_[1])
		{
			ChestLong_[1]->Death();
			ChestLong_[1] = GetLevel()->CreateActor<ChestLong>();
			CreatedItem_[1] = ChestLong_[1]->GetItemList();

			ItemRecreateFlg = true;
		}

		if (CreatedItem_[0] == CreatedItem_[2] ||
			CreatedItem_[1] == CreatedItem_[2])
		{
			ChestLong_[2]->Death();
			ChestLong_[2] = GetLevel()->CreateActor<ChestLong>();
			CreatedItem_[2] = ChestLong_[2]->GetItemList();

			ItemRecreateFlg = true;
		}

		if (false == ItemRecreateFlg)
		{
			break;
		}
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

	if (true == SomethingOpendFlg_)
	{
		for (int i = 0; i < 3; i++)
		{
			ChestLong_[i]->ChangeOpenAnimChestLong();
		}

		// Chest가 열렸으면 세트를 삭제
		this->Death();
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