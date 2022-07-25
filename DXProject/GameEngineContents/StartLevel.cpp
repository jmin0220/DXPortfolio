#include "PreCompile.h"
#include "StartLevel.h"
#include "ObjectGroup.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "TitleBG.h"

StartLevel::StartLevel() 
{
}

StartLevel::~StartLevel() 
{
}

void StartLevel::Start()
{
	// 카메라 액터 생성
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	CreateActor<TitleBG>(0);


	if (false == GameEngineInput::GetInst()->IsKey("ChangeStage"))
	{
		GameEngineInput::GetInst()->CreateKey("ChangeStage", VK_RETURN);
	}
}

void StartLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("ChangeStage"))
	{
		GEngine::ChangeLevel(LEVEL_STAGE1);
	}
}

void StartLevel::End()
{

}