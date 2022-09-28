#include "PreCompile.h"
#include "TestLevel.h"
#include "TestActor.h"
#include "Missile.h"

TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
}

void TestLevel::Start()
{
	//GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
	//GetMainCamera()->GetTransform().SetWorldPosition({ 0.0f,0.0f,-5000.0f });

	//MagmaWorm_ = CreateActor<MagmaWorm>();

	GameEngineInput::GetInst()->CreateKey("TestLeft", 'A');
	GameEngineInput::GetInst()->CreateKey("TestDown", 'S');
	GameEngineInput::GetInst()->CreateKey("TestRight", 'D');
	GameEngineInput::GetInst()->CreateKey("TestUp", 'W');

	Missile_ = CreateActor<Missile>();

}

void TestLevel::Update(float _DeltaTime)
{

	if (GameEngineInput::GetInst()->IsPress("TestLeft"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetLeftVector() * 500.0f * _DeltaTime);
		Missile_->SetTargetPos({ -1000.0f, 0.0f });
	}
	if (GameEngineInput::GetInst()->IsPress("TestDown"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetDownVector() * 500.0f * _DeltaTime);
		Missile_->SetTargetPos({ 0.0f, -1000.0f });
	}
	if (GameEngineInput::GetInst()->IsPress("TestRight"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetRightVector() * 500.0f * _DeltaTime);
		Missile_->SetTargetPos({ 1000.0f, 0.0f });
	}
	if (GameEngineInput::GetInst()->IsPress("TestUp"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetUpVector() * 500.0f * _DeltaTime);
		Missile_->SetTargetPos({ 0.0f, 1000.0f });
	}
}

