#include "PreCompile.h"
#include "Commando.h"

// 업데이트
void Commando::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonIdleUpdate();
}


void Commando::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonMoveUpdate();
}


void Commando::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::Skill1Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::Skill2Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::Skill3Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::Skill4Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::ClimbUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonClimbUpdate();
}

void Commando::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

}


// 스타트
void Commando::IdleStart(const StateInfo& _Info)
{
	CommonIdleStart();
}

void Commando::MoveStart(const StateInfo& _Info)
{
	CommonMoveStart();
}

void Commando::ShootStart(const StateInfo& _Info)
{
	CommonShootStart();
}

void Commando::Skill1Start(const StateInfo& _Info)
{

}

void Commando::Skill2Start(const StateInfo& _Info)
{

}

void Commando::Skill3Start(const StateInfo& _Info)
{

}

void Commando::Skill4Start(const StateInfo& _Info)
{

}

void Commando::ClimbStart(const StateInfo& _Info)
{
	CommonClimbStart();
}

void Commando::DeathStart(const StateInfo& _Info)
{

}


// 엔드
void Commando::IdleEnd(const StateInfo& _Info)
{

}

void Commando::MoveEnd(const StateInfo& _Info)
{

}

void Commando::ShootEnd(const StateInfo& _Info)
{

}

void Commando::Skill1End(const StateInfo& _Info)
{

}

void Commando::Skill2End(const StateInfo& _Info)
{

}

void Commando::Skill3End(const StateInfo& _Info)
{

}

void Commando::Skill4End(const StateInfo& _Info)
{

}

void Commando::ClimbEnd(const StateInfo& _Info)
{
	IsClimb_ = false;
}

void Commando::DeathEnd(const StateInfo& _Info)
{

}
