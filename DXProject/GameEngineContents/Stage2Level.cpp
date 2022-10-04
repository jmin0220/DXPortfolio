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

	StageActor_->SetStage2Map();
	BossCreateOption_ = 1;

	ObjectCreater_->SetColMapInfo(StageActor_->GetColStage()->GetCurTexture());
	ObjectCreater_->CreateObject();
	Portal_ = ObjectCreater_->GetPortal();
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
