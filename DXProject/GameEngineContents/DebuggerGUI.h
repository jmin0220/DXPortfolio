#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineBase/GameEngineMath.h>

// Ό³Έν :
class DebuggerGUI : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	DebuggerGUI();
	~DebuggerGUI();

	// delete Function
	DebuggerGUI(const DebuggerGUI& _Other) = delete;
	DebuggerGUI(DebuggerGUI&& _Other) noexcept = delete;
	DebuggerGUI& operator=(const DebuggerGUI& _Other) = delete;
	DebuggerGUI& operator=(DebuggerGUI&& _Other) noexcept = delete;

	void SetPlayerPos(float4 _PlayerPos)
	{
		PlayerPos_ = _PlayerPos;
	}

	void SetPlayerGroundFlg(bool _JumpFlg)
	{
		PlayerGroundFlg_ = _JumpFlg;
	}

	void SetPlayerFsmStateName(std::string _StateName)
	{
		PlayerFSMState_ = _StateName;
	}

	bool GetCreateBossTrigger() const
	{
		return CreateBossTrigger_;
	}

protected:

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	float4 PlayerPos_;
	bool PlayerGroundFlg_;
	std::string PlayerFSMState_;

	bool CreateBossTrigger_;
};

