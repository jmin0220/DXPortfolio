#pragma once
#include "Player.h"

// 설명 :
class Bandit : public Player
{
public:
	// constrcuter destructer
	Bandit();
	~Bandit();

	// delete Function
	Bandit(const Bandit& _Other) = delete;
	Bandit(Bandit&& _Other) noexcept = delete;
	Bandit& operator=(const Bandit& _Other) = delete;
	Bandit& operator=(Bandit&& _Other) noexcept = delete;

protected:
	void AnimationInit() override;
	void StateInit() override;

	void IdleStart(const StateInfo& _Info) override;
	void MoveStart(const StateInfo& _Info) override;
	void Skill1Start(const StateInfo& _Info) override;
	void Skill2Start(const StateInfo& _Info) override;
	void Skill3Start(const StateInfo& _Info) override;
	void Skill4Start(const StateInfo& _Info) override;
	void ClimbStart(const StateInfo& _Info) override;
	void DeathStart(const StateInfo& _Info) override;

	void IdleUpdate(float _DeltaTime, const StateInfo& _Info) override;
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info) override;
	void Skill1Update(float _DeltaTime, const StateInfo& _Info) override;
	void Skill2Update(float _DeltaTime, const StateInfo& _Info) override;
	void Skill3Update(float _DeltaTime, const StateInfo& _Info) override;
	void Skill4Update(float _DeltaTime, const StateInfo& _Info) override;
	void ClimbUpdate(float _DeltaTime, const StateInfo& _Info) override;
	void DeathUpdate(float _DeltaTime, const StateInfo& _Info) override;

	void IdleEnd(const StateInfo& _Info) override;
	void MoveEnd(const StateInfo& _Info) override;
	void Skill1End(const StateInfo& _Info) override;
	void Skill2End(const StateInfo& _Info) override;
	void Skill3End(const StateInfo& _Info) override;
	void Skill4End(const StateInfo& _Info) override;
	void ClimbEnd(const StateInfo& _Info) override;
	void DeathEnd(const StateInfo& _Info) override;

	// 애니메이션 종료시
	void EndAnimation(const FrameAnimation_DESC& _Info);
	// 프레임마다
	void FrameAnimation(const FrameAnimation_DESC& _Info);

private:
};

