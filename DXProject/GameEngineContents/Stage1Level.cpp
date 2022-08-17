#include "PreCompile.h"
#include "Stage1Level.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "StageGround.h"
#include "CharacterSelectEnum.h"
#include "Bandit.h"
#include "Commando.h"

Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{	
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	StageActor_ = CreateActor<StageGround>();
	MonsterManager_ = CreateActor<MonsterManager>();
	CharacterCreater_ = CreateActor<CharacterCreater>();
}

void Stage1Level::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		//GetMainCameraActor()->FreeCameraModeOnOff();
	}

	// ĳ���� ũ�������Ϳ� �÷��̾� ��ġ�� ����
	CharacterCreater_->SetCurPlayerPos(Player_->GetTransform().GetWorldPosition());

	// ���͸Ŵ����� �÷��̾� ��ġ�� ����
	MonsterManager_->SetPlayerPos(Player_->GetTransform().GetWorldPosition());

}

void Stage1Level::End()
{

}

void Stage1Level::OnEvent()
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
	Player_->GetTransform().SetWorldPosition({100, 100});

	// �÷��̾�� �浹�� ����
	Player_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	MonsterManager_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
}
