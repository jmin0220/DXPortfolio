#include "PreCompile.h"
#include "StageLevelParent.h"
#include <GameEngineCore/GameEngineStatusWindow.h>
#include "DebuggerGUI.h"
#include "StageGround.h"
#include "Bandit.h"
#include "Commando.h"
#include "Gold.h"
#include "Drops.h"
#include "ItemManager.h"
#include "DebuggerGUI.h"

DebuggerGUI* StageLevelParent::DebuggerGUI_ = nullptr;

StageLevelParent::StageLevelParent() 
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

	DebuggerGUI_->SetPlayerPos(Player_->GetTransform().GetWorldPosition());
	DebuggerGUI_->SetPlayerGroundFlg(Player_->GetIsGroundFlg());
	DebuggerGUI_->SetPlayerFsmStateName(Player_->GetState());

	// 보스 생성
	if (true == DebuggerGUI_->GetCreateBossTrigger())
	{
		MonsterManager_->CreateBossFlgOn();
	}
}

void StageLevelParent::LevelStartEvent()
{
	// 플레이어 액터 생성
	switch (Option_.CharacterSelect_)
	{
	case CharacterSelectEnum::Commando:
		Player_ = CreateActor<Commando>();
		break;
	case CharacterSelectEnum::Bandit:
		Player_ = CreateActor<Bandit>();
		break;
	case CharacterSelectEnum::None:
		break;
	default:
		break;
	}

	CharacterCreater_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	CharacterCreater_->MakePlayerPosition();
	Player_->GetTransform().SetWorldPosition(CharacterCreater_->OutputPlayerCreatePos());
	Player_->GetTransform().SetWorldPosition({ 100, -750, static_cast<float>(ZOrder::Player) });

	// 플레이어에게 충돌맵 설정
	Player_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	MonsterManager_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	Drops::SetColMap(StageActor_->GetColStage()->GetCurTexture());
}