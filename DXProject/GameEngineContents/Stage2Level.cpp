#include "PreCompile.h"
#include "Stage2Level.h"
#include "StageGround.h"

Stage2Level::Stage2Level() 
{
}

Stage2Level::~Stage2Level() 
{
}

void Stage2Level::Start()
{
	StageLevelParent::Start();

	// TODO::다른 맵 이미지로 변경
	StageActor_->SetStage1Map();
	BossCreateOption_ = 1;
}

void Stage2Level::Update(float _DeltaTime)
{
	StageLevelParent::Update(_DeltaTime);
}

void Stage2Level::End()
{
}

void Stage2Level::LevelStartEvent()
{
	StageLevelParent::LevelStartEvent();
}

void Stage2Level::LevelEndEvent()
{
}
