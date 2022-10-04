#include "PreCompile.h"
#include "EndLevel.h"
#include "EndBG.h"

EndLevel::EndLevel() 
{
}

EndLevel::~EndLevel() 
{
}

void EndLevel::Start()
{
	EndBG_ = CreateActor<EndBG>();
}

void EndLevel::Update(float _DeltaTime)
{
}

void EndLevel::End()
{

}