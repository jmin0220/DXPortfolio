#include "PreCompile.h"
#include "CharacterSelect.h"
#include "CharacterSelecter.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

CharacterSelect::CharacterSelect() 
{
}

CharacterSelect::~CharacterSelect() 
{
}

void CharacterSelect::Start()
{
	// ī�޶� ���� ����
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	CharacterSelecter_ = CreateActor<CharacterSelecter>();	


	if (false == GameEngineInput::GetInst()->IsKey(CHANGE_LECEL_STAGE1))
	{
		GameEngineInput::GetInst()->CreateKey(CHANGE_LECEL_STAGE1, VK_RETURN);
	}
}

void CharacterSelect::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown(CHANGE_LEVEL_CHRACTER_SELECT))
	{
		GEngine::ChangeLevel(LEVEL_STAGE1);
	}
}

void CharacterSelect::End()
{

}