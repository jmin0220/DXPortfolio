#include "PreCompile.h"
#include "CharacterCreater.h"
#include <GameEngineBase/GameEngineRandom.h>

CharacterCreater::CharacterCreater() 
	: ColMap_(nullptr)
	, CreatePlayerPos_(float4::ZERO)
{
}

CharacterCreater::~CharacterCreater() 
{
}

void CharacterCreater::Start()
{
	


}

void CharacterCreater::Update(float _DeltaTime)
{

}

void CharacterCreater::MakePosition()
{
	GameEngineRandom* Random = new GameEngineRandom();

	CreatePlayerPos_.x = Random->RandomInt(100, ColMap_->GetScale().x - 100);
	CreatePlayerPos_.y = Random->RandomInt(0, ColMap_->GetScale().y);

	float4 Color2 = ColMap_->GetPixelToFloat4(897, 736);

	// x축으로 플레이어가 생성될 수 있는 위치 검색
	for (;;)
	{
		float4 Color = ColMap_->GetPixelToFloat4(CreatePlayerPos_.x, CreatePlayerPos_.y);

		// 땅 검색
		if (true == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			for (;;)
			{
				// 만들어질 수 없는 위치면 천장을 향해 탐색
				CreatePlayerPos_.y--;
				Color = ColMap_->GetPixelToFloat4(CreatePlayerPos_.x, CreatePlayerPos_.y);

				// 더이상 땅이 아니면 반복 종료
				if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
				{
					break;
				}
			}
			break;
		}

		// 땅이 아니었다면 xy좌표를 다시 검색하여 재탐색
		CreatePlayerPos_.x = Random->RandomInt(100, ColMap_->GetScale().x - 100);
		CreatePlayerPos_.y = Random->RandomInt(0, ColMap_->GetScale().y);
	}

	// 플레이어에게 반영하기 위하여 y값 조정
	CreatePlayerPos_.y = -CreatePlayerPos_.y + 30;

	//CreatePlayerPos_ = { 33, -597 };

	int a = 0;
}