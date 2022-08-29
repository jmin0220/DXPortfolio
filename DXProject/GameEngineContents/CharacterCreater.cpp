#include "PreCompile.h"
#include "CharacterCreater.h"
#include <GameEngineBase/GameEngineRandom.h>

GameEngineTexture* CharacterCreater::ColMap_ = nullptr;
float4 CharacterCreater::CurPlayerPos_ = float4::ZERO;

CharacterCreater::CharacterCreater() 
	: CreatePlayerPos_(float4::ZERO)
{
}

CharacterCreater::~CharacterCreater() 
{
}

void CharacterCreater::MakePlayerPosition()
{
	CreatePlayerPos_ = MakePosition(0);
}

void CharacterCreater::MakeMonsterPosition()
{
	CreateMonsterPos_ = MakePosition(1);
}

void CharacterCreater::Start()
{
	
}

void CharacterCreater::Update(float _DeltaTime)
{

}

float4 CharacterCreater::MakePosition(int _CreateMod)
{
	/*
	_CreateMod == 0 -> 플레이어 생성
				  1 -> 몬스터 생성
				  2 -> 오브젝트 생성?
	*/


	GameEngineRandom* Random = new GameEngineRandom();
	float4 CreatePos = float4::ZERO;

	// 둘중 하나라도 입력되지 않았을경우

	switch (_CreateMod)
	{
	case 0:
		CreatePos.x = Random->RandomInt(100, ColMap_->GetScale().x - 100);
		CreatePos.y = Random->RandomInt(100, ColMap_->GetScale().y - 100);
		CreatePos.z = static_cast<float>(ZOrder::Player);
		break;
	case 1:
		CreatePos.x = Random->RandomInt(CurPlayerPos_.x - 1000, CurPlayerPos_.x + 1000);
		CreatePos.y = Random->RandomInt(CurPlayerPos_.y - 1000, CurPlayerPos_.y + 1000);
		CreatePos.y = -CreatePos.y;

		if (CreatePos.x >= ColMap_->GetScale().x)
		{
			CreatePos.x = ColMap_->GetScale().x - 100;
		}
		if (CreatePos.y >= ColMap_->GetScale().y)
		{
			CreatePos.y = ColMap_->GetScale().y - 100;
		}

		CreatePos.z = static_cast<float>(ZOrder::Monsters);

		break;
	case 2:
		// TODO::오브젝트 생성 위치?
		break;
	default:
		break;
	}

	int Count_ = 0;

	// x축으로 플레이어가 생성될 수 있는 위치 검색
	for (;;)
	{
		float4 Color = ColMap_->GetPixelToFloat4(CreatePos.x, CreatePos.y);

		// 땅 검색
		if (true == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			for (;;)
			{
				// 만들어질 수 없는 위치면 천장을 향해 탐색
				CreatePos.y--;
				Color = ColMap_->GetPixelToFloat4(CreatePos.x, CreatePos.y);

				// 더이상 땅이 아니면 반복 종료
				if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
				{
					break;
				}
			}
			break;
		}

		// 땅이 아니었다면 xy좌표를 다시 검색하여 재탐색
		switch (_CreateMod)
		{
		case 0:
			CreatePos.x = Random->RandomInt(100, ColMap_->GetScale().x - 100);
			CreatePos.y = Random->RandomInt(100, ColMap_->GetScale().y - 100);
			CreatePos.z = static_cast<float>(ZOrder::Player);
			break;
		case 1:
			CreatePos.x = Random->RandomInt(CurPlayerPos_.x - 1000, CurPlayerPos_.x + 1000);
			CreatePos.y = Random->RandomInt(CurPlayerPos_.y - 1000, CurPlayerPos_.y + 1000);
			CreatePos.y = -CreatePos.y;

			if (CreatePos.x >= ColMap_->GetScale().x)
			{
				CreatePos.x = ColMap_->GetScale().x - 100;
			}
			if (CreatePos.y >= ColMap_->GetScale().y)
			{
				CreatePos.y = ColMap_->GetScale().y - 100;
			}
			CreatePos.z = static_cast<float>(ZOrder::Monsters);

			break;
		case 2:
			// TODO::오브젝트 생성 위치?
			break;
		default:
			break;
		}
	}

	// 플레이어에게 반영하기 위하여 y값 조정
	CreatePos.y = -CreatePos.y + 30;

	// 디버그용 위치
	//CreatePos = { 33, -597 };

	delete Random;
	Random = nullptr;

	return CreatePos;
}