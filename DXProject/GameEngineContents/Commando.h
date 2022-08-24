#pragma once
#include "Player.h"

// ���� :
class Commando : public Player
{
public:
	// constrcuter destructer
	Commando();
	~Commando();

	// delete Function
	Commando(const Commando& _Other) = delete;
	Commando(Commando&& _Other) noexcept = delete;
	Commando& operator=(const Commando& _Other) = delete;
	Commando& operator=(Commando&& _Other) noexcept = delete;

protected:
	void AnimationInit() override;
	void StateInit() override;

	void IdleStart(const StateInfo& _Info);
	void MoveStart(const StateInfo& _Info);
	void Skill1Start(const StateInfo& _Info);
	void Skill2Start(const StateInfo& _Info);
	void Skill3Start(const StateInfo& _Info);
	void Skill4Start(const StateInfo& _Info);
	void ClimbStart(const StateInfo& _Info);
	void DeathStart(const StateInfo& _Info);

	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void Skill1Update(float _DeltaTime, const StateInfo& _Info);
	void Skill2Update(float _DeltaTime, const StateInfo& _Info);
	void Skill3Update(float _DeltaTime, const StateInfo& _Info);
	void Skill4Update(float _DeltaTime, const StateInfo& _Info);
	void ClimbUpdate(float _DeltaTime, const StateInfo& _Info);
	void DeathUpdate(float _DeltaTime, const StateInfo& _Info);

	void IdleEnd(const StateInfo& _Info);
	void MoveEnd(const StateInfo& _Info);
	void Skill1End(const StateInfo& _Info);
	void Skill2End(const StateInfo& _Info);
	void Skill3End(const StateInfo& _Info);
	void Skill4End(const StateInfo& _Info);
	void ClimbEnd(const StateInfo& _Info);
	void DeathEnd(const StateInfo& _Info);

	// 4����ų 2����
	void Skill4_1();
	void Skill4_2();

	// �ִϸ��̼� �����
	void EndAnimation(const FrameAnimation_DESC& _Info);
	// �����Ӹ���
	void FrameAnimation(const FrameAnimation_DESC& _Info);

private:
};