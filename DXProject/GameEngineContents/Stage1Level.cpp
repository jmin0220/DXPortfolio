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

	StageLevelParent::LevelStartEvent();
	// Ű Ʃ�丮�� ����
	Tutorial_ = CreateActor<Tutorial>();
	Tutorial_->GetTransform().SetWorldPosition({ Player_->GetTransform().GetWorldPosition().x, Player_->GetTransform().GetWorldPosition().y + 100.0f });

	// Bouncer����
	CreateActor<Bouncer>();
	// TODO::�׽�Ʈ�ڵ�
	//ChestNormal* TmpChestNormal = CreateActor<ChestNormal>();
	//TmpChestNormal->GetTransform().SetWorldPosition({ 106.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	//ChestBig* TmpChestBig = CreateActor<ChestBig>();
	//TmpChestBig->GetTransform().SetWorldPosition({ 50.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	//ChestLongSet* TmpChestLongSet = CreateActor<ChestLongSet>();
	//TmpChestLongSet->CreateChestLongSet({ 350.0f, -864.0f, static_cast<float>(ZOrder::Chest) });
	ItemManager_->CreateItem(this, ItemList::Sawmerang ,{ 156.0f, -804.0f });

	Portal_->GetTransform().SetWorldPosition({ 350.0f, -864.0f, static_cast<float>(ZOrder::Teleportal) });
}

void Stage1Level::LevelEndEvent()
{
}
