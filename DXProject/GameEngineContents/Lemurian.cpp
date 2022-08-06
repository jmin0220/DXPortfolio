#include "PreCompile.h"
#include "Lemurian.h"

Lemurian::Lemurian() 
{
	Speed_ = Player_MOVE_SPEED;

}

Lemurian::~Lemurian() 
{
}

void Lemurian::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	
	// 애니메이션 생성
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_IDLE, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_IDLE, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_JUMP, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_JUMP, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_SHOOT, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_SHOOT, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_SPAWN, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_SPAWN, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_WALK, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_WALK, FrameAnimDelay_, true));
	// ↓수정필요
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_DEATH, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_WALK, FrameAnimDelay_, true));

	// 프레임이 종료되었을 때
	Renderer_->AnimationBindEnd(LEMURIAN_ANIM_SPAWN, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_IDLE); });

	// 초기 애니메이션 전환
	Renderer_->ChangeFrameAnimation(LEMURIAN_ANIM_SPAWN);
	Renderer_->SetScaleModeImage();
}

void Lemurian::StateInit()
{
	// StateSpawn = 애니메이션이 끝날때까지 대기하는 상태
	StateManager_.CreateStateMember(MONSTER_FSM_SPAWN, [=](float _DeltaTime, const StateInfo& _Info) {});
	StateManager_.CreateStateMember(MONSTER_FSM_IDLE, std::bind(&Lemurian::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Lemurian::IdleStart, this, std::placeholders::_1)
													, std::bind(&Lemurian::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_MOVE, std::bind(&Lemurian::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Lemurian::MoveStart, this, std::placeholders::_1)
													, std::bind(&Lemurian::MoveEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_CHASE, std::bind(&Lemurian::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Lemurian::ChaseStart, this, std::placeholders::_1)
													, std::bind(&Lemurian::ChaseEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_ATTACK, std::bind(&Lemurian::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Lemurian::AttackStart, this, std::placeholders::_1)
													, std::bind(&Lemurian::AttackEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_DEATH, std::bind(&Lemurian::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Lemurian::DeathStart, this, std::placeholders::_1)
													, std::bind(&Lemurian::DeathEnd, this, std::placeholders::_1));

	// 초기 스테이트전환
	StateManager_.ChangeState(MONSTER_FSM_SPAWN);
}

#pragma region FSM

void Lemurian::IdleStart(const StateInfo& _Info)
{
	CommonIdleStart(LEMURIAN_ANIM_IDLE);
}
void Lemurian::MoveStart(const StateInfo& _Info)
{
	CommonMoveStart(LEMURIAN_ANIM_WALK);
}
void Lemurian::ChaseStart(const StateInfo& _Info)
{
	CommonChaseStart(LEMURIAN_ANIM_WALK);
}
void Lemurian::AttackStart(const StateInfo& _Info)
{
	CommonAttackStart(LEMURIAN_ANIM_SHOOT);
}
void Lemurian::DeathStart(const StateInfo& _Info)
{
	CommonDeathStart(LEMURIAN_ANIM_DEATH);
}

void Lemurian::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonIdleUpdate();
}

void Lemurian::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonMoveUpdate();
}

void Lemurian::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonChaseUpdate();
}

void Lemurian::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
void Lemurian::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Lemurian::IdleEnd(const StateInfo& _Info)
{
}
void Lemurian::MoveEnd(const StateInfo& _Info)
{
}
void Lemurian::ChaseEnd(const StateInfo& _Info)
{
}
void Lemurian::AttackEnd(const StateInfo& _Info)
{
}
void Lemurian::DeathEnd(const StateInfo& _Info)
{
}
#pragma endregion
