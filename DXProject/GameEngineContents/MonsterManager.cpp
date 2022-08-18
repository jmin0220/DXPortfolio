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
			int GoldValue = (*MonsteriterStart)->GetMonsterGold();
			// 5골드짜리 갯수
			int GoldFive = GoldValue / 5;
			// 1골드짜리 갯수
			int GoldOne = GoldValue % 5;

			GameEngineRandom* Random = new GameEngineRandom();

			// 5골드 출력
			for (int i = 0; i < GoldFive; i++)
			{
				// 골드 생성
				Gold* tmpGold = GetLevel()->CreateActor<Gold>();
				tmpGold->GetTransform().SetWorldPosition((*MonsteriterStart)->GetTransform().GetWorldPosition());
				tmpGold->SetGoldValue(5);
				tmpGold->UpdateGoldOption();

				// 골드가 생성될때 떨어질 각도를 설정
				tmpGold->SetFlyDir({ Random->RandomFloat(-50.0, 50.0), 0.0f, 0.0f });
				tmpGold->GoldPop();

			}

			// 1골드 출력
			for (int i = 0; i < GoldOne; i++)
			{
				// 골드 생성
				Gold* tmpGold = GetLevel()->CreateActor<Gold>();
				tmpGold->GetTransform().SetWorldPosition((*MonsteriterStart)->GetTransform().GetWorldPosition());
				tmpGold->SetGoldValue(1);
				tmpGold->UpdateGoldOption();

				// 골드가 생성될때 떨어질 각도를 설정
				tmpGold->SetFlyDir({ Random->RandomFloat(-50.0, 50.0), 0.0f, 0.0f });
				tmpGold->GoldPop();
			}
			
			
			// 경험치 생성
			int ExpValue = (*MonsteriterStart)->GetMonsterExp();
			// 5경험치짜리 갯수 -> 렌더러는 동일함
			int ExpFive = ExpValue / 5;
			// 1경험치짜리 갯수
			int ExpOne = ExpValue % 5;

			// 5경험치 출력
			for (int i = 0; i < ExpFive; i++)
			{
				// 경험치 생성
				Exp* tmpExp = GetLevel()->CreateActor<Exp>();
				tmpExp->GetTransform().SetWorldPosition((*MonsteriterStart)->GetTransform().GetWorldPosition());
				tmpExp->SetExpValue(5);

				// TODO::경험치가 생성될때 최종 이동위치를 설정
				tmpExp->SetDestPos({ Random->RandomFloat(-15.0, 15.0), Random->RandomFloat(-15.0, 15.0), 0.0f });
			}

			// 1경험치 출력
			for (int i = 0; i < ExpOne; i++)
			{
				// 경험치 생성
				Exp* tmpExp = GetLevel()->CreateActor<Exp>();
				tmpExp->GetTransform().SetWorldPosition((*MonsteriterStart)->GetTransform().GetWorldPosition());
				tmpExp->SetExpValue(5);

				// TODO::경험치가 생성될때 최종 이동위치를 설정
				tmpExp->SetDestPos({ Random->RandomFloat(-15.0, 15.0), Random->RandomFloat(-15.0, 15.0), 0.0f });
			}



			// 죽은 몬스터를 매니저에서 삭제
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