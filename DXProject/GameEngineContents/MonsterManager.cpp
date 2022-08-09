#include "PreCompile.h"
#include "MonsterManager.h"
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
}

void MonsterManager::Update(float _DeltaTime)
{
	// TODO::���� ������ ������ �Է�
	RespawnPos_ = { 600.0f, -800.0f, 0.0f, 0.0f };

	// TODO:: Ÿ�̸ӿ� ���� ������ ����
	SingleMonsterRespawnTimer_ += _DeltaTime;
	GroupMonsterRespawnTimer_ += _DeltaTime;

	// �ӽ� Ÿ�̸�
	if (SingleMonsterRespawnTimer_ >= 5.0f)
	{
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
			// ���� ���͸� �Ŵ������� ����
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