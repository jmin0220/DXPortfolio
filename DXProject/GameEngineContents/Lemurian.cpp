#include "PreCompile.h"
#include "Lemurian.h"

Lemurian::Lemurian() 
{
}

Lemurian::~Lemurian() 
{
}

void Lemurian::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	
	// 애니메이션 생성
	//Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_IDLE, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_IDLE, FrameAnimDelay_, true));
	//Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_JUMP, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_JUMP, FrameAnimDelay_, true));
	//Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_SHOOT, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_SHOOT, FrameAnimDelay_, true));
	//Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_SPAWN, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_SPAWN, FrameAnimDelay_, true));
	//Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_WALK, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_WALK, FrameAnimDelay_, true));
	//// ↓수정필요
	//Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_DEATH, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_WALK, FrameAnimDelay_, true));

	// 초기 애니메이션 전환
	//Renderer_->ChangeFrameAnimation(LEMURIAN_ANIM_IDLE);
	//Renderer_->SetScaleModeImage();
}

void Lemurian::StateInit()
{
	//StateManager_.CreateStateMember(MONSTER_FSM_IDLE, this, &Lemurian::IdleUpdate, &Lemurian::IdleStart, &Lemurian::IdleEnd);
	//StateManager_.CreateStateMember(MONSTER_FSM_MOVE, this, &Lemurian::MoveUpdate, &Lemurian::MoveStart, &Lemurian::MoveEnd);
	//StateManager_.CreateStateMember(MONSTER_FSM_CHASE, this, &Lemurian::ChaseUpdate, &Lemurian::ChaseStart, &Lemurian::ChaseEnd);
	//StateManager_.CreateStateMember(MONSTER_FSM_ATTACK, this, &Lemurian::AttackUpdate, &Lemurian::AttackStart, &Lemurian::AttackEnd);
	//StateManager_.CreateStateMember(MONSTER_FSM_DEATH, this, &Lemurian::DeathUpdate, &Lemurian::DeathStart, &Lemurian::DeathEnd);

	// 초기 스테이트전환
	//StateManager_.ChangeState(MONSTER_FSM_IDLE);
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
}
void Lemurian::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
void Lemurian::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
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
