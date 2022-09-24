#include "PreCompile.h"
#include "TestLevel.h"
#include "TestActor.h"
#include "MagmaWorm.h"
#include <GameEngineBase/GameEngineInput.h>

TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start()
{
	// 카메라 액터 생성
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	/*GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
	GetMainCamera()->*/

	MagmaWorm_ = CreateActor<MagmaWorm>();

	GameEngineInput::GetInst()->CreateKey("TestLeft", 'A');
	GameEngineInput::GetInst()->CreateKey("TestDown", 'S');
	GameEngineInput::GetInst()->CreateKey("TestRight", 'D');
	GameEngineInput::GetInst()->CreateKey("TestUp", 'W');

}

void TestLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsPress("TestLeft"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetLeftVector() * 2000.0f * _DeltaTime);
		MagmaWorm_->SetMoveDirection(GetMainCameraActorTransform().GetLeftVector());
	}
	if (GameEngineInput::GetInst()->IsPress("TestDown"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetDownVector() * 2000.0f * _DeltaTime);
		MagmaWorm_->SetMoveDirection(GetMainCameraActorTransform().GetDownVector());
	}
	if (GameEngineInput::GetInst()->IsPress("TestRight"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetRightVector() * 2000.0f * _DeltaTime);
		MagmaWorm_->SetMoveDirection(GetMainCameraActorTransform().GetRightVector());
	}
	if (GameEngineInput::GetInst()->IsPress("TestUp"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetUpVector() * 2000.0f * _DeltaTime);
		MagmaWorm_->SetMoveDirection(GetMainCameraActorTransform().GetUpVector());
	}

}

