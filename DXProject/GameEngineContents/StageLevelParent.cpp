#include "PreCompile.h"
#include "StageLevelParent.h"
#include <GameEngineCore/GameEngineStatusWindow.h>

StageLevelParent::StageLevelParent() 
{
	// TODO::Imgui������
	DubugererGUI_ = GameEngineGUI::CreateGUIWindow<GameEngineGUIWindow>("CharacterStatus", nullptr);
}

StageLevelParent::~StageLevelParent() 
{
}
