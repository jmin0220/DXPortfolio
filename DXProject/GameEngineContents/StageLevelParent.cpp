#include "PreCompile.h"
#include "StageLevelParent.h"
#include <GameEngineCore/GameEngineStatusWindow.h>

GameEnGameEngineGUIWindowgineGUI* StageLevelParent::DubugererGUI_ = nullptr;

StageLevelParent::StageLevelParent() 
{
	// TODO::Imgui만들어보기
	//DubugererGUI_ = GameEngineGUI::CreateGUIWindow<GameEnGameEngineGUIWindowgineGUI>("CharacterStatus", nullptr);
}

StageLevelParent::~StageLevelParent() 
{
}
