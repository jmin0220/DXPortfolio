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
#include "Colossus.h"

Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{
	StageLevelParent::LevelStartEvent();
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	// TODO::스테이지 레벨에 따라 다른 맵을 생성
	MonsterManager_ = CreateActor<MonsterManager>();
	CharacterCreater_ = CreateActor<CharacterCreater>();
	StageActor_ = CreateActor<StageGround>();
	ItemManager_ = CreateActor<ItemManager>();
}

void Stage1Level::Update(float _DeltaTime)
{
	StageLevelParent::Update(_DeltaTime);

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

void Stage1Level::End()
{

}

void Stage1Level::LevelStartEvent()
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
	Player_->GetTransform().SetWorldPosition({100, -750, static_cast<float>(ZOrder::Player) });

	// 키 튜토리얼 생성
	Tutorial_ = CreateActor<Tutorial>();
	Tutorial_->GetTransform().SetWorldPosition({ Player_->GetTransform().GetWorldPosition().x, Player_->GetTransform().GetWorldPosition().y + 100.0f });

	// 플레이어에게 충돌맵 설정
	Player_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	MonsterManager_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	Drops::SetColMap(StageActor_->GetColStage()->GetCurTexture());

	// Bouncer생성
	CreateActor<Bouncer>();
	// TODO::테스트코드
	//ChestNormal* TmpChestNormal = CreateActor<ChestNormal>();
	//TmpChestNormal->GetTransform().SetWorldPosition({ 106.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	//ChestBig* TmpChestBig = CreateActor<ChestBig>();
	//TmpChestBig->GetTransform().SetWorldPosition({ 50.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	ChestLongSet* TmpChestLongSet = CreateActor<ChestLongSet>();
	TmpChestLongSet->CreateChestLongSet({ 350.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	ItemManager_->CreateItem(this, ItemList::Sawmerang ,{ 156.0f, -804.0f });


	// TODO::임시코드 = 보스몬스터 생성 플래그 on
	//MonsterManager_->CreateBossFlgOn();

	//Colossus* tmpColossus = CreateActor<Colossus>();
	//tmpColossus->GetTransform().SetWorldPosition({ 1500.0f, -400.0f });
	//tmpColossus->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
}

void Stage1Level::LevelEndEvent()
{
}
