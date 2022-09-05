#include "PreCompile.h"
#include "TestActor.h"
#include "SingleColorRenderer.h"

TestActor::TestActor() 
{
}

TestActor::~TestActor() 
{
}

void TestActor::Start()
{
	SingleColorRenderer_ = CreateComponent<SingleColorRenderer>();
	SingleColorRenderer_->SetColor({ 1.0, 0.0, 0.0, 1.0 });
	//SingleColorRenderer_->GetTransform().SetWorldScale({ 100, 100 });
}

void TestActor::Update(float _DeltaTime)
{
}

