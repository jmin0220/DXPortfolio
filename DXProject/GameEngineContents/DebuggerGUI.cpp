#include "PreCompile.h"
#include "DebuggerGUI.h"

DebuggerGUI::DebuggerGUI()
	: CreateBossTrigger_(false)
{
}

DebuggerGUI::~DebuggerGUI() 
{
}

void DebuggerGUI::Initialize(class GameEngineLevel* _Level)
{

}

void DebuggerGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::string tmpGroundFlg = "false";

	if (true == PlayerGroundFlg_)
	{
		tmpGroundFlg = "true";
	}
	else
	{
		tmpGroundFlg = "false";
	}

	std::string PlayerPositionX = "PlayerPos.X     >> " + std::to_string(PlayerPos_.x);
	std::string PlayerPositionY = "PlayerPos.Y     >> " + std::to_string(PlayerPos_.y);
	std::string PlayerPositionZ = "PlayerPos.Z     >> " + std::to_string(PlayerPos_.z);

	std::string PlayerState		= "PlayerFSM State >> " + PlayerFSMState_;
	std::string PlayerJumpFlg	= "Player Jump Flg >> " + tmpGroundFlg;


	ImGui::Text("Player Position ==================");
	ImGui::NewLine();
	ImGui::Text(PlayerPositionX.c_str());
	ImGui::NewLine();
	ImGui::Text(PlayerPositionY.c_str());
	ImGui::NewLine();
	ImGui::Text(PlayerPositionZ.c_str());
	ImGui::NewLine();
	ImGui::NewLine();

	ImGui::Text("Player State & Flag ==============");
	ImGui::NewLine();
	ImGui::Text(PlayerState.c_str());
	ImGui::NewLine();
	ImGui::Text(PlayerJumpFlg.c_str());
	ImGui::NewLine();

	if (true == ImGui::Button("CreateBoss"))
	{
		CreateBossTrigger_ = true;
	}
}