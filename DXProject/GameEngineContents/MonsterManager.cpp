#include "PreCompile.h"
#include "MonsterManager.h"
#include "CharacterCreater.h"
#include "Lemurian.h"

MonsterManager::MonsterManager() 
	: SingleMonsterRespawnTimer_(0.0f)
	, GroupMonsterRespawnTimer_(0.0f)
	, RespawnPos_(float4::ZERO)
{
}

MonsterManager::~MonsterManager() 
{
}



void MonsterManager::Start()
{
	CharacterCreater_ = GetLevel()->CreateActor<CharacterCreater>();
}

void MonsterManager::Update(float _DeltaTime)
{
	// 리스폰 간격 타이머
	SingleMonsterRespawnTimer_ += _DeltaTime;
	GroupMonsterRespawnTimer_ += _DeltaTime;

	// 몬스터 생성타이머
	if (SingleMonsterRespawnTimer_ >= 5.0f)
	{
		// 몬스터는 플레이어 주위에 생성 가능한 위치에 무작위로 생성됨
		// 캐릭터Creater에서 플레이어 위치를 받아서, 다음에 생성할 몬스터의 위치를 조정
		CharacterCreater_->MakeMonsterPosition();

		// 적이 생성될 포지션 입력
		RespawnPos_ = CharacterCreater_->OutputMonsterCreatePos();

		Monster* NewMonster_ = GetLevel()->CreateActor<Lemurian>();
		NewMonster_->GetTransform().SetWorldPosition(RespawnPos_);
		NewMonster_->SetColMapInfo(ColMap_);

		Monster_.push_back(NewMonster_);

		SingleMonsterRespawnTimer_ = 0.0f;
	}


	std::list<Monster*>::iterator MonsteriterStart = Monster_.begin();
	std::list<Monster*>::iterator MonsteriterEnd = Monster_.end();

	for (; MonsteriterStart != MonsteriterEnd;)
	{
		if (true == (*MonsteriterStart)->GetMonsterDeath())
		{
			// 죽은 몬스터를 매니저에서 삭제
			MonsteriterStart = Monster_.erase(MonsteriterStart);
			
			continue;
		}
		else
		{
			(*MonsteriterStart)->SetPlayerPos(PlayerPos_);
			++MonsteriterStart;
		}
	}
}