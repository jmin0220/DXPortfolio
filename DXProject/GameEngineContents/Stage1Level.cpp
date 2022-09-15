#include "PreCompile.h"
#include "Stage1Level.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "StageGround.h"
#include "CharacterSelectEnum.h"
#include "Bandit.h"
#include "Commando.h"
#include "Gold.h"
#include "Drops.h"
#include "Bouncer.h"
#include "Tutorial.h"
#include "ChestNormal.h"
#include "ChestBig.h"
#include "ChestLongSet.h"
#include "ItemManager.h"
#include "DebuggerGUI.h"
#include "BossHUD.h"

Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	// TODO::�������� ������ ���� �ٸ� ���� ����
	MonsterManager_ = CreateActor<MonsterManager>();
	CharacterCreater_ = CreateActor<CharacterCreater>();
	StageActor_ = CreateActor<StageGround>();
	ItemManager_ = CreateActor<ItemManager>();

	CreateActor<BossHUD>();
}

void Stage1Level::Update(float _DeltaTime)
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
}

void Stage1Level::End()
{

}

void Stage1Level::LevelStartEvent()
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
	Player_->GetTransform().SetWorldPosition({100, -750, static_cast<float>(ZOrder::Player) });

	// Ű Ʃ�丮�� ����
	Tutorial_ = CreateActor<Tutorial>();
	Tutorial_->GetTransform().SetWorldPosition({ Player_->GetTransform().GetWorldPosition().x, Player_->GetTransform().GetWorldPosition().y + 100.0f });

	// �÷��̾�� �浹�� ����
	Player_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	MonsterManager_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	Drops::SetColMap(StageActor_->GetColStage()->GetCurTexture());

	// Bouncer����
	CreateActor<Bouncer>();
	// TODO::�׽�Ʈ�ڵ�
	//ChestNormal* TmpChestNormal = CreateActor<ChestNormal>();
	//TmpChestNormal->GetTransform().SetWorldPosition({ 106.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	//ChestBig* TmpChestBig = CreateActor<ChestBig>();
	//TmpChestBig->GetTransform().SetWorldPosition({ 50.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	ChestLongSet* TmpChestLongSet = CreateActor<ChestLongSet>();
	TmpChestLongSet->CreateChestLongSet({ 350.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	ItemManager_->CreateItem(this, ItemList::Sawmerang ,{ 156.0f, -804.0f });
}