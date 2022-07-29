#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UnitFsm.h"

// 설명 :
class HUD;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetColMapInfo(GameEngineTexture* _ColMap)
	{
		ColMap_ = _ColMap;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	// 초기화 관련 함수
	void KeyInit();
	virtual void AnimationInit() {};
	virtual void StateInit() {};

	// 키입력 관련 함수
	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();

	bool IsShootKeyDown();
	bool IsShootKeyPress();
	bool IsShootKeyUp();

	// 업데이트 함수
	void CheckNegativeX();
	void CameraUpdate();
	void JumpUpdate();
	void GroundFallCheck();
	bool GroundRightCheck();
	bool GroundLeftCheck();

	// FSM 관련 함수
	GameEngineStateManager StateManager_;
	//void StateChange(STATE _State);
	//void StateUpdate();

	virtual void IdleStart(const StateInfo& _Info) {};
	virtual void MoveStart(const StateInfo& _Info) {};
	virtual void ShootStart(const StateInfo& _Info) {};
	virtual void Skill1Start(const StateInfo& _Info) {};
	virtual void Skill2Start(const StateInfo& _Info) {};
	virtual void Skill3Start(const StateInfo& _Info) {};
	virtual void Skill4Start(const StateInfo& _Info) {};
	virtual void ClimbStart(const StateInfo& _Info) {};
	virtual void DeathStart(const StateInfo& _Info) {};

	virtual void IdleUpdate(float _DeltaTime, const StateInfo& _Info) {};
	virtual void MoveUpdate(float _DeltaTime, const StateInfo& _Info) {};
	virtual void ShootUpdate(float _DeltaTime, const StateInfo& _Info) {};
	virtual void Skill1Update(float _DeltaTime, const StateInfo& _Info) {};
	virtual void Skill2Update(float _DeltaTime, const StateInfo& _Info) {};
	virtual void Skill3Update(float _DeltaTime, const StateInfo& _Info) {};
	virtual void Skill4Update(float _DeltaTime, const StateInfo& _Info) {};
	virtual void ClimbUpdate(float _DeltaTime, const StateInfo& _Info) {};
	virtual void DeathUpdate(float _DeltaTime, const StateInfo& _Info) {};

	virtual void IdleEnd(const StateInfo& _Info) {};
	virtual void MoveEnd(const StateInfo& _Info) {};
	virtual void ShootEnd(const StateInfo& _Info) {};
	virtual void Skill1End(const StateInfo& _Info) {};
	virtual void Skill2End(const StateInfo& _Info) {};
	virtual void Skill3End(const StateInfo& _Info) {};
	virtual void Skill4End(const StateInfo& _Info) {};
	virtual void ClimbEnd(const StateInfo& _Info) {};
	virtual void DeathEnd(const StateInfo& _Info) {};


	GameEngineTextureRenderer* Renderer_;
	float Speed_;
	STATE CurrentState_;
	float DeltaTime_;
	float4 MoveDir_;

	GameEngineTexture* ColMap_;

	HUD* HUD_;
private:
	
};

