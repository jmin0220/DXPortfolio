#include "PreCompile.h"
#include "StageLevelParent.h"
#include <GameEngineCore/GameEngineStatusWindow.h>
#include "DebuggerGUI.h"
#include "StageGround.h"
#include "Gold.h"
#include "Drops.h"
#include "ItemManager.h"
#include "Bandit.h"
#include "Commando.h"
#include "Portal.h"
#include "HUD.h"
#include "Missile.h"

DebuggerGUI* StageLevelParent::DebuggerGUI_ = nullptr;
Player* StageLevelParent::Player_ = nullptr;

StageLevelParent::StageLevelParent() 
	: BossCreateOption_(0)
{
}

StageLevelParent::~StageLevelParent() 
{
}

void StageLevelParent::Start()
{
	if (nullptr == DebuggerGUI_)
	{
		DebuggerGUI_ = GameEngineGUI::CreateGUIWindow<DebuggerGUI>("CharacterStatus", nullptr);
	}

	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	MonsterManager_ = CreateActor<MonsterManager>();
	CharacterCreater_ = CreateActor<CharacterCreater>();
	StageActor_ = CreateActor<StageGround>();
	ItemManager_ = CreateActor<ItemManager>();
	Portal_ = CreateActor<Portal>();
}

void StageLevelParent::Update(float _DeltaTime)
{
	// ĳ���� ũ�������Ϳ� �÷��̾� ��ġ�� ����
	CharacterCreater_->SetCurPlayerPos(Player_->GetTransform().GetWorldPosition());

	// ���͸Ŵ����� �÷��̾� ��ġ�� ����
	MonsterManager_->SetPlayerPos(Player_->GetTransform().GetWorldPosition());

	// ���� ����ġ�� �÷��̾� ��ġ�� ����
	Drops::SetPlayerPos(Player_->GetTransform().GetWorldPosition());
	ItemManager::SetPlayerPos(Player_->GetTransform().GetWorldPosition());
	Missile::SetMonsterList(MonsterManager_->GetAllMonsterList());

	DebuggerGUI_->SetPlayerPos(Player_->GetTransform().GetWorldPosition());
	DebuggerGUI_->SetPlayerGroundFlg(Player_->GetIsGroundFlg());
	DebuggerGUI_->SetPlayerFsmStateName(Player_->GetState());

	switch (LevelProcess_)
	{
	case LevelProcess::NonActivePortal:
		Player_->GetHUD()->SetTargetFontStringNonAct();
		Portal_->SetPortalState(PortalState::NonActivate);

		// �÷��̾ ��Ż�� ���۽�Ű��
		if (true == Portal_->GetRespawnBossFlg())
		{
			LevelProcess_ = LevelProcess::ActivePortal;
		}

		break;
	case LevelProcess::ActivePortal:
		Player_->GetHUD()->SetTargetFontStringAct();
		Portal_->SetPortalState(PortalState::Activate);

		// ���� ������� Ÿ�̸Ӱ� ����Ǿ�����
		if (true == Portal_->IsCreateBoss())
		{
			// ���� ����
			MonsterManager_->CreateBossFlgOn(BossCreateOption_);
			LevelProcess_ = LevelProcess::CreatedBoss;
		}

		break;
	case LevelProcess::CreatedBoss:
		Player_->GetHUD()->SetTargetFontStringBoss();

		// ������ �׿�����
		if (true == MonsterManager_->GetBossKilledFlg())
		{
			LevelProcess_ = LevelProcess::KIllBoss;
		}

		break;
	case LevelProcess::KIllBoss:
		Player_->GetHUD()->SetTargetFontStringNextLevel();
		Portal_->SetPortalState(PortalState::KillBoss);
		Portal_->PortalNextLevelOnRenderer();
		
		// Portal���� LevelChange
		break;
	default:
		MsgBoxAssert("�߸��� ���� ����ܰ�");
		break;
	}

	// ����׿� ���� ����
	if (true == DebuggerGUI_->GetCreateBossTrigger())
	{
		MonsterManager_->CreateBossFlgOn(1);
	}
}

void StageLevelParent::LevelStartEvent()
{

	CharacterCreater_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	CharacterCreater_->MakePlayerPosition();
	Player_->GetTransform().SetWorldPosition(CharacterCreater_->OutputPlayerCreatePos());
	Player_->GetTransform().SetWorldPosition({ 100, -750, static_cast<float>(ZOrder::Player) });

	// �÷��̾�� �浹�� ����
	Player_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	MonsterManager_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	Drops::SetColMap(StageActor_->GetColStage()->GetCurTexture());
}