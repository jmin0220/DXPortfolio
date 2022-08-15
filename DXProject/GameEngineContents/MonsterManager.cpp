#include "PreCompile.h"
#include "MonsterManager.h"
#include "CharacterCreater.h"
#include "Lemurian.h"
#include "Exp.h"
#include "Gold.h"

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
	// ������ ���� Ÿ�̸�
	SingleMonsterRespawnTimer_ += _DeltaTime;
	GroupMonsterRespawnTimer_ += _DeltaTime;

	// ���� ����Ÿ�̸�
	if (SingleMonsterRespawnTimer_ >= 5.0f)
	{
		// ���ʹ� �÷��̾� ������ ���� ������ ��ġ�� �������� ������
		// ĳ����Creater���� �÷��̾� ��ġ�� �޾Ƽ�, ������ ������ ������ ��ġ�� ����
		CharacterCreater_->MakeMonsterPosition();

		// ���� ������ ������ �Է�
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
			// ��� ����
			Gold* tmpGold = GetLevel()->CreateActor<Gold>();
			tmpGold->GetTransform().SetWorldPosition((*MonsteriterStart)->GetTransform().GetWorldPosition());

			// ����ġ ����
			Exp* tmpExp = GetLevel()->CreateActor<Exp>();
			tmpExp->GetTransform().SetWorldPosition((*MonsteriterStart)->GetTransform().GetWorldPosition());

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