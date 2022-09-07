#include "PreCompile.h"
#include "StageLevelParent.h"
#include <GameEngineCore/GameEngineStatusWindow.h>

StageLevelParent::StageLevelParent() 
{
	// TODO::Imgui만들어보기
	DubugererGUI_ = GameEngineGUI::CreateGUIWindow<GameEngineGUIWindow>("CharacterStatus", nullptr);
}

StageLevelParent::~StageLevelParent() 
{
}
