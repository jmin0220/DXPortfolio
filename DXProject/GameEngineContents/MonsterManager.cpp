#include "PreCompile.h"
#include "MonsterManager.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "CharacterCreater.h"
#include "Exp.h"
#include "Gold.h"
#include "BossHUD.h"

#pragma region Monster

#include "Lemurian.h"
#include "Child.h"
#include "MonParent.h"
#include "RockGolem.h"
#include "Crab.h"
#include "Wisp.h"

#pragma endregion

#pragma region Boss

#include "Colossus.h"
#include "MagmaWorm.h"

#pragma endregion


MonsterManager::MonsterManager() 
	: SingleMonsterRespawnTimer_(0.0f)
	, GroupMonsterRespawnTimer_(0.0f)
	, RespawnPos_(float4::ZERO)
	, CreateBossFlg_(false)
	, BossKilledFlg_(false)
{
}

MonsterManager::~MonsterManager() 
{
}



void MonsterManager::Start()
{
	CharacterCreater_ = GetLevel()->CreateActor<CharacterCreater>();

	BossHUD_ = GetLevel()->CreateActor<BossHUD>();
	BossHUD_->Off();
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

		// TODO::시간별로 등장하는 몬스터를 추가해야함
		Monster* NewMonster_ = GetLevel()->CreateActor<Wisp>();
		//Monster* NewMonster_ = GetLevel()->CreateActor<Lemurian>();
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
			Drops::CreateCoinsAndExp((*MonsteriterStart)->GetMonsterGold(), (*MonsteriterStart)->GetMonsterExp(), (*MonsteriterStart)->GetTransform().GetWorldPosition(), GetLevel());

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

	if (true == CreateBossFlg_ && BossMonster_ != nullptr)
	{
		BossMonster_->SetPlayerPos(PlayerPos_);

		BossHUD_->SetBossHp(BossMonster_->GetMonsterHp());

		if (true == BossMonster_->GetMonsterDeath())
		{
			BossKilledFlg_ = true;
		}
	}
}


void MonsterManager::AllMonsterStateChangeToIdle()
{
	for (Monster* tmpMonster : Monster_)
	{
		if ( MONSTER_FSM_CHASE == tmpMonster->GetCurState())
		{
			tmpMonster->ForcedSetStateIdle();
		}
	}
}

void MonsterManager::CreateBoss(int bossOption)
{
	// 이미 생성되어있다면 종료
	if (true == CreateBossFlg_)
	{
		return;
	}

	BossHUD_->On();

	if (bossOption == 0)
	{
		BossMonster_ = GetLevel()->CreateActor<Colossus>();
	}
	else if (bossOption == 1)
	{
		BossMonster_ = GetLevel()->CreateActor<MagmaWorm>();
		PlayerPos_.z = static_cast<float>(ZOrder::MagmaWorm);
	}

	// 일단 플레이어 위치에 보스를 생성하고, Spawn->Idle로 변경되면서 RendererOn, 위치 조정 등등...
	BossMonster_->GetTransform().SetWorldPosition(PlayerPos_);
	BossMonster_->SetColMapInfo(ColMap_);

	// 생성초기의 Hp가 최대체력
	BossHUD_->BossHpFontOn();
	BossHUD_->SetBossMaxHp(BossMonster_->GetMonsterHp());
	// HUD에 표시될 이름과 별명
	BossHUD_->SetBossNames(BossMonster_->GetBossName(), BossMonster_->GetBossSubName());
}