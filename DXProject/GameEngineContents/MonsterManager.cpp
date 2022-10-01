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

		// TODO::�ð����� �����ϴ� ���͸� �߰��ؾ���
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
	// �̹� �����Ǿ��ִٸ� ����
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

	// �ϴ� �÷��̾� ��ġ�� ������ �����ϰ�, Spawn->Idle�� ����Ǹ鼭 RendererOn, ��ġ ���� ���...
	BossMonster_->GetTransform().SetWorldPosition(PlayerPos_);
	BossMonster_->SetColMapInfo(ColMap_);

	// �����ʱ��� Hp�� �ִ�ü��
	BossHUD_->BossHpFontOn();
	BossHUD_->SetBossMaxHp(BossMonster_->GetMonsterHp());
	// HUD�� ǥ�õ� �̸��� ����
	BossHUD_->SetBossNames(BossMonster_->GetBossName(), BossMonster_->GetBossSubName());
}