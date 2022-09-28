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
	// 캐릭터 크리에이터에 플레이어 위치를 갱신
	CharacterCreater_->SetCurPlayerPos(Player_->GetTransform().GetWorldPosition());

	// 몬스터매니저에 플레이어 위치를 갱신
	MonsterManager_->SetPlayerPos(Player_->GetTransform().GetWorldPosition());

	// 골드와 경험치에 플레이어 위치를 갱신
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

		// 플레이어가 포탈을 동작시키면
		if (true == Portal_->GetRespawnBossFlg())
		{
			LevelProcess_ = LevelProcess::ActivePortal;
		}

		break;
	case LevelProcess::ActivePortal:
		Player_->GetHUD()->SetTargetFontStringAct();
		Portal_->SetPortalState(PortalState::Activate);

		// 보스 생성대기 타이머가 종료되었으면
		if (true == Portal_->IsCreateBoss())
		{
			// 보스 생성
			MonsterManager_->CreateBossFlgOn(BossCreateOption_);
			LevelProcess_ = LevelProcess::CreatedBoss;
		}

		break;
	case LevelProcess::CreatedBoss:
		Player_->GetHUD()->SetTargetFontStringBoss();

		// 보스를 죽였으면
		if (true == MonsterManager_->GetBossKilledFlg())
		{
			LevelProcess_ = LevelProcess::KIllBoss;
		}

		break;
	case LevelProcess::KIllBoss:
		Player_->GetHUD()->SetTargetFontStringNextLevel();
		Portal_->SetPortalState(PortalState::KillBoss);
		Portal_->PortalNextLevelOnRenderer();
		
		// Portal에서 LevelChange
		break;
	default:
		MsgBoxAssert("잘못된 레벨 진행단계");
		break;
	}

	// 디버그용 보스 생성
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

	// 플레이어에게 충돌맵 설정
	Player_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	MonsterManager_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	Drops::SetColMap(StageActor_->GetColStage()->GetCurTexture());
}