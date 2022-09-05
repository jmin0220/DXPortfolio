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
	CreateActor<TitleBG>();


	if (false == GameEngineInput::GetInst()->IsKey("ChangeStage"))
	{
		GameEngineInput::GetInst()->CreateKey(CHANGE_LEVEL_CHRACTER_SELECT, VK_RETURN);
	}
}

void StartLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown(CHANGE_LEVEL_CHRACTER_SELECT))
	{
		GEngine::ChangeLevel(LEVEL_SELECT);
	}
}

void StartLevel::End()
{

}