#include "PreCompile.h"
#include "Stage1Level.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "StageGround.h"
#include "Bandit.h"
#include "Commando.h"
#include "Bouncer.h"
#include "Tutorial.h"
#include "ChestNormal.h"
#include "ChestBig.h"
#include "ChestLongSet.h"
#include "ItemManager.h"
#include "Portal.h"
#include "AttackDrone.h"
#include "AttackDroneItem.h"
#include "MissileDroneItem.h"
#include "AtGMissileMk1.h"

Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{
	StageLevelParent::Start();

	StageActor_->SetStage1Map();
	BossCreateOption_ = 0;

	ObjectCreater_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	ObjectCreater_->CreateObject();
	Portal_ = ObjectCreater_->GetPortal();
}

void Stage1Level::Update(float _DeltaTime)
{
	StageLevelParent::Update(_DeltaTime);
}

void Stage1Level::End()
{

}

void Stage1Level::LevelStartEvent()
{
	BGMSoundPlayer_ = GameEngineSound::SoundPlayControl("musicStage1.ogg", 1000);

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

	StageLevelParent::LevelStartEvent();
	// 키 튜토리얼 생성
	Tutorial_ = CreateActor<Tutorial>();
	Tutorial_->GetTransform().SetWorldPosition({ Player_->GetTransform().GetWorldPosition().x, Player_->GetTransform().GetWorldPosition().y + 100.0f });

	// Bouncer생성
	//CreateActor<Bouncer>();
	// TODO::테스트코드
	//ChestNormal* TmpChestNormal = CreateActor<ChestNormal>();
	//TmpChestNormal->GetTransform().SetWorldPosition({ 106.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	//ChestBig* TmpChestBig = CreateActor<ChestBig>();
	//TmpChestBig->GetTransform().SetWorldPosition({ 50.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	//ChestLongSet* TmpChestLongSet = CreateActor<ChestLongSet>();
	//TmpChestLongSet->CreateChestLongSet({ 350.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	//ItemManager_->CreateItem(this, ItemList::Sawmerang,{ 156.0f, -804.0f });
	//AttackDroneItem* tmp = CreateActor<AttackDroneItem>();
	//tmp->GetTransform().SetWorldPosition({ 556.0f, -854.0f });
	//MissileDroneItem* tmp2 = CreateActor<MissileDroneItem>();
	//tmp2->GetTransform().SetWorldPosition({ 596.0f, -854.0f });

	//Portal_->GetTransform().SetWorldPosition({ 350.0f, -864.0f, static_cast<float>(ZOrder::Teleportal) });
}

void Stage1Level::LevelEndEvent()
{
	BGMSoundPlayer_.Stop();
}
