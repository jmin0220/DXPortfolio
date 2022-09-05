#include "PreCompile.h"
#include "TestLevel.h"
#include "TestActor.h"

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

	TestActor_ = CreateActor<TestActor>();
	
}

void TestLevel::Update(float _DeltaTime)
{
	TestActor_;
}

