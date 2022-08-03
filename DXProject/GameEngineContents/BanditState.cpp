#include "PreCompile.h"
#include "Bandit.h"

// 업데이트
void Bandit::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonIdleUpdate();
}


void Bandit::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonMoveUpdate();
}

void Bandit::Skill1Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Bandit::Skill2Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Bandit::Skill3Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Bandit::Skill4Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Bandit::ClimbUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonClimbUpdate();
}

void Bandit::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

}


// 스타트
void Bandit::IdleStart(const StateInfo& _Info)
{
	CommonIdleStart();
}

void Bandit::MoveStart(const StateInfo& _Info)
{
	CommonMoveStart();
}

void Bandit::Skill1Start(const StateInfo& _Info)
{
	CommonSkill1Start();
}

void Bandit::Skill2Start(const StateInfo& _Info)
{

}

void Bandit::Skill3Start(const StateInfo& _Info)
{

}

void Bandit::Skill4Start(const StateInfo& _Info)
{

}

void Bandit::ClimbStart(const StateInfo& _Info)
{
	CommonClimbStart();
}

void Bandit::DeathStart(const StateInfo& _Info)
{

}


// 엔드
void Bandit::IdleEnd(const StateInfo& _Info)
{

}

void Bandit::MoveEnd(const StateInfo& _Info)
{

}

void Bandit::Skill1End(const StateInfo& _Info)
{

}

void Bandit::Skill2End(const StateInfo& _Info)
{

}

void Bandit::Skill3End(const StateInfo& _Info)
{

}

void Bandit::Skill4End(const StateInfo& _Info)
{

}

void Bandit::ClimbEnd(const StateInfo& _Info)
{
	IsClimb_ = false;
}

void Bandit::DeathEnd(const StateInfo& _Info)
{

}
