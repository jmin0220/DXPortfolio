#include "PreCompile.h"
#include "MonsterManager.h"
#include "Lemurian.h"

MonsterManager::MonsterManager() 
	: SingleMonsterRespawnTimer_(0.0f)
	, GroupMonsterRespawnTimer_(0.0f)
	, RespawnPos_(float4::ZERO)
	, Monster_(nullptr)
{
}

MonsterManager::~MonsterManager() 
{
}



void MonsterManager::Start()
{
}

void MonsterManager::Update(float _DeltaTime)
{
	// TODO::적이 생성될 포지션 입력
	RespawnPos_ = { 600.0f, -800.0f, 0.0f, 0.0f };

	// TODO:: 타이머에 따라 리스폰 구현
	SingleMonsterRespawnTimer_ += _DeltaTime;
	GroupMonsterRespawnTimer_ += _DeltaTime;

	// 임시 타이머
	if (SingleMonsterRespawnTimer_ >= 3.0f)
	{
		Monster_ = GetLevel()->CreateActor<Lemurian>();
		Monster_->GetTransform().SetWorldPosition(RespawnPos_);

		Monster_->SetColMapInfo(ColMap_);

		SingleMonsterRespawnTimer_ = 0.0f;
	}
}