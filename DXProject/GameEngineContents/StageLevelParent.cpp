#include "PreCompile.h"
#include "StageLevelParent.h"
#include <GameEngineCore/GameEngineStatusWindow.h>
#include "DebuggerGUI.h"

DebuggerGUI* StageLevelParent::DebuggerGUI_ = nullptr;

StageLevelParent::StageLevelParent() 
{
	DebuggerGUI_ = GameEngineGUI::CreateGUIWindow<DebuggerGUI>("CharacterStatus", nullptr);
}

StageLevelParent::~StageLevelParent() 
{
}
