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
	// ĳ���� ũ�������Ϳ� �÷��̾� ��ġ�� ����
	CharacterCreater_->SetCurPlayerPos(Player_->GetTransform().GetWorldPosition());

	// ���͸Ŵ����� �÷��̾� ��ġ�� ����
	MonsterManager_->SetPlayerPos(Player_->GetTransform().GetWorldPosition());

	// ���� ����ġ�� �÷��̾� ��ġ�� ����
	Drops::SetPlayerPos(Player_->GetTransform().GetWorldPosition());
	ItemManager::SetPlayerPos(Player_->GetTransform().GetWorldPosition());

	DebuggerGUI_->SetPlayerPos(Player_->GetTransform().GetWorldPosition());
	DebuggerGUI_->SetPlayerGroundFlg(Player_->GetIsGroundFlg());
	DebuggerGUI_->SetPlayerFsmStateName(Player_->GetState());

	// ���� ����
	if (true == DebuggerGUI_->GetCreateBossTrigger())
	{
		MonsterManager_->CreateBossFlgOn();
	}
}

void StageLevelParent::LevelStartEvent()
{
	// �÷��̾� ���� ����
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

	// �÷��̾�� �浹�� ����
	Player_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	MonsterManager_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	Drops::SetColMap(StageActor_->GetColStage()->GetCurTexture());
}