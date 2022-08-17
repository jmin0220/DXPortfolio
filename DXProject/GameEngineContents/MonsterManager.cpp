#include "PreCompile.h"
#include "MonsterManager.h"
#include "CharacterCreater.h"
#include "Lemurian.h"
#include "Exp.h"
#include "Gold.h"
#include <GameEngineBase/GameEngineRandom.h>

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
			int GoldValue = (*MonsteriterStart)->GetMonsterGold();
			// 5���¥�� ����
			int GoldFive = GoldValue / 5;
			// 1���¥�� ����
			int GoldOne = GoldValue % 5;

			GameEngineRandom* Random = new GameEngineRandom();

			// 5��� ���
			for (int i = 0; i < GoldFive; i++)
			{
				// ��� ����
				Gold* tmpGold = GetLevel()->CreateActor<Gold>();
				tmpGold->GetTransform().SetWorldPosition((*MonsteriterStart)->GetTransform().GetWorldPosition());
				tmpGold->SetGoldValue(5);
				tmpGold->UpdateGoldOption();

				// TODO::��尡 �����ɶ� ������ ������ ����
				tmpGold->SetFlyDir({ Random->RandomFloat(-1.0, 1.0), 0.0f, 0.0f });
				tmpGold->GoldPop();

			}

			// 1��� ���
			for (int i = 0; i < GoldOne; i++)
			{
				// ��� ����
				Gold* tmpGold = GetLevel()->CreateActor<Gold>();
				tmpGold->GetTransform().SetWorldPosition((*MonsteriterStart)->GetTransform().GetWorldPosition());
				tmpGold->SetGoldValue(1);
				tmpGold->UpdateGoldOption();

				// TODO::��尡 �����ɶ� ������ ������ ����
				tmpGold->SetFlyDir({ Random->RandomFloat(-1.0, 1.0), 0.0f, 0.0f });
				tmpGold->GoldPop();
			}
			
			
			// ����ġ ����
			// TODO::����ġ�� �����ɶ� ���� �̵���ġ�� ����
			//Exp* tmpExp = GetLevel()->CreateActor<Exp>();
			//tmpExp->GetTransform().SetWorldPosition((*MonsteriterStart)->GetTransform().GetWorldPosition());

			// ���� ���͸� �Ŵ������� ����
			MonsteriterStart = Monster_.erase(MonsteriterStart);

			delete Random;
			Random = nullptr;

			continue;
		}
		else
		{
			(*MonsteriterStart)->SetPlayerPos(PlayerPos_);
			++MonsteriterStart;
		}
	}
}