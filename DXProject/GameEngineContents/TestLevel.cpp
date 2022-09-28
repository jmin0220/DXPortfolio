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

}

void TestLevel::Update(float _DeltaTime)
{
	TestActor_;
}

