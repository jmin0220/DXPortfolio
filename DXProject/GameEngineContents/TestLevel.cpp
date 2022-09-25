#include "PreCompile.h"
#include "TestLevel.h"
#include "TestActor.h"
#include "MagmaWorm.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineInput.h>

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
		MagmaWorm_->SetMoveDirection({-1000.0f, 0.0f, 0.0f, 0.0f});
	}
	if (GameEngineInput::GetInst()->IsPress("TestDown"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetDownVector() * 2000.0f * _DeltaTime);
		MagmaWorm_->SetMoveDirection(MagmaWorm_->GetMagmaWormPosition() + GetMainCameraActorTransform().GetDownVector());
	}
	if (GameEngineInput::GetInst()->IsPress("TestRight"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetRightVector() * 2000.0f * _DeltaTime);
		MagmaWorm_->SetMoveDirection(MagmaWorm_->GetMagmaWormPosition() + GetMainCameraActorTransform().GetRightVector());
	}
	if (GameEngineInput::GetInst()->IsPress("TestUp"))
	{
		GetMainCameraActorTransform().SetWorldMove(GetMainCameraActorTransform().GetUpVector() * 2000.0f * _DeltaTime);
		MagmaWorm_->SetMoveDirection(MagmaWorm_->GetMagmaWormPosition() + GetMainCameraActorTransform().GetUpVector());
	}


	//MagmaWorm_->SetMoveDirection(GetMainCamera()->GetMouseWorldPosition());
}

