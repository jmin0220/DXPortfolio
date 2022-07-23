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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;


private:
	// �ʱ�ȭ ���� �Լ�
	void KeyInit();
	void AnimationInit();

	// Ű�Է� ���� �Լ�
	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();

	// FSM ���� �Լ�
	void StateChange(STATE _State);
	void StateUpdate();

	void IdleStart();
	void MoveStart();
	void JumpStart();
	void ShootStart();
	void Skill1Start();
	void Skill2Start();
	void Skill3Start();
	void Skill4Start();
	void ClimbStart();
	void DeathStart();

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void ShootUpdate();
	void Skill1Update();
	void Skill2Update();
	void Skill3Update();
	void Skill4Update();
	void ClimbUpdate();
	void DeathUpdate();

	void IdleEnd();
	void MoveEnd();
	void JumpEnd();
	void ShootEnd();
	void Skill1End();
	void Skill2End();
	void Skill3End();
	void Skill4End();
	void ClimbEnd();
	void DeathEnd();

	GameEngineTextureRenderer* Renderer_;
	float Speed_;
	STATE CurrentState_;
	float DeltaTime_;
};

