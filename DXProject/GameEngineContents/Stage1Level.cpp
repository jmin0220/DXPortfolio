#include "PreCompile.h"
#include "Stage1Level.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "StageGround.h"
#include "CharacterSelectEnum.h"
#include "Bandit.h"
#include "Commando.h"
#include "ObjectGroup.h"

Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{	
	// ī�޶� ���� ����
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	StageActor_ = CreateActor<StageGround>(ObjectGroup::Stage);
}

void Stage1Level::Update(float _DeltaTime)
{

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
		Player_ = CreateActor<Commando>(ObjectGroup::Player);
		break;
	case CharacterSelectEnum::Bandit:
		Player_ = CreateActor<Bandit>(ObjectGroup::Player);
		break;
	case CharacterSelectEnum::None:
		break;
	default:
		break;
	}

	// �÷��̾�� �浹�� ����
	Player_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
}
