#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UnitFsm.h"

// ���� :
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

private:
	// �ʱ�ȭ ���� �Լ�
	void KeyInit();
	void AnimationInit();

	// Ű�Է� ���� �Լ�
	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();

	bool IsShootKeyDown();
	bool IsShootKeyPress();
	bool IsShootKeyUp();

	// ������Ʈ �Լ�
	void CheckNegativeX();
	void CameraUpdate();
	void GroundFallCheck();
	bool GroundRightCheck();
	bool GroundLeftCheck();

	// FSM ���� �Լ�
	GameEngineStateManager StateManager_;
	//void StateChange(STATE _State);
	//void StateUpdate();

	void IdleStart(const StateInfo& _Info);
	void MoveStart(const StateInfo& _Info);
	void ShootStart(const StateInfo& _Info);
	void Skill1Start(const StateInfo& _Info);
	void Skill2Start(const StateInfo& _Info);
	void Skill3Start(const StateInfo& _Info);
	void Skill4Start(const StateInfo& _Info);
	void ClimbStart(const StateInfo& _Info);
	void DeathStart(const StateInfo& _Info);

	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShootUpdate(float _DeltaTime, const StateInfo& _Info);
	void Skill1Update(float _DeltaTime, const StateInfo& _Info);
	void Skill2Update(float _DeltaTime, const StateInfo& _Info);
	void Skill3Update(float _DeltaTime, const StateInfo& _Info);
	void Skill4Update(float _DeltaTime, const StateInfo& _Info);
	void ClimbUpdate(float _DeltaTime, const StateInfo& _Info);
	void DeathUpdate(float _DeltaTime, const StateInfo& _Info);

	void IdleEnd(const StateInfo& _Info);
	void MoveEnd(const StateInfo& _Info);
	void ShootEnd(const StateInfo& _Info);
	void Skill1End(const StateInfo& _Info);
	void Skill2End(const StateInfo& _Info);
	void Skill3End(const StateInfo& _Info);
	void Skill4End(const StateInfo& _Info);
	void ClimbEnd(const StateInfo& _Info);
	void DeathEnd(const StateInfo& _Info);

	// �ִϸ��̼� �����
	void EndAnimation(const FrameAnimation_DESC& _Info);

	GameEngineTextureRenderer* Renderer_;
	float Speed_;
	STATE CurrentState_;
	float DeltaTime_;
	float4 MoveDir_;

	GameEngineTexture* ColMap_;
};

