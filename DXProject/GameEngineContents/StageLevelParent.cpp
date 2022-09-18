#include "PreCompile.h"
#include "StageLevelParent.h"
#include <GameEngineCore/GameEngineStatusWindow.h>
#include "DebuggerGUI.h"

DebuggerGUI* StageLevelParent::DebuggerGUI_ = nullptr;

StageLevelParent::StageLevelParent() 
{
}

StageLevelParent::~StageLevelParent() 
{
}

void StageLevelParent::LevelStartEvent()
{
	if (nullptr == DebuggerGUI_)
	{
		DebuggerGUI_ = GameEngineGUI::CreateGUIWindow<DebuggerGUI>("CharacterStatus", nullptr);
	}
}

void StageLevelParent::Update(float _DeltaTime)
{
	CommonFunction::CommonFunction_->Update(_DeltaTime);
}
