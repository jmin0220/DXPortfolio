#include "PreCompile.h"
#include "Crab.h"

Crab::Crab() 
{
	Speed_ = Player_MOVE_SPEED - 50.0f;
	AtkSpeed_ = 1.3f;
	MonsterHp_ = 200;
	Damage_ = 14;
	Lv_ = 1;

	Exp_ = 3;
	IsHitted_ = false;
}

Crab::~Crab() 
{
}

void Crab::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	// 애니메이션 생성
	Renderer_->CreateFrameAnimationFolder(CRAB_ANIM_IDLE,  FrameAnimation_DESC(CRAB_ANIM_IDLE, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(CRAB_ANIM_SHOOT, FrameAnimation_DESC(CRAB_ANIM_SHOOT, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(CRAB_ANIM_SPAWN, FrameAnimation_DESC(CRAB_ANIM_SPAWN, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(CRAB_ANIM_WALK,  FrameAnimation_DESC(CRAB_ANIM_WALK, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(CRAB_ANIM_DEATH, FrameAnimation_DESC(CRAB_ANIM_DEATH, FrameAnimDelay_, false));

	// 프레임이 종료되었을 때
	Renderer_->AnimationBindEnd(CRAB_ANIM_SPAWN, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_IDLE); Collision_->On(); });
	Renderer_->AnimationBindEnd(CRAB_ANIM_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			StateManager_.ChangeState(MONSTER_FSM_CHASE);
		});

	Renderer_->AnimationBindFrame(CRAB_ANIM_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 5)
			{
				CommonFunction::CommonFunction_->CameraShakeEffectOn(0.3f, 1.0f);
			}
		});

	// 초기 애니메이션 전환
	Renderer_->ChangeFrameAnimation(CRAB_ANIM_SPAWN);
	Renderer_->SetScaleModeImage();
}

void Crab::CollisionInit()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 58.0f, 54.0f, 1.0f });
	Collision_->ChangeOrder(ObjectGroup::Monster);

	// 초기에 콜리전 off, spawn 애니메이션 종료후에 활성화
	Collision_->Off();
}

void Crab::StateInit()
{
	// StateSpawn = 애니메이션이 끝날때까지 대기하는 상태
	StateManager_.CreateStateMember(MONSTER_FSM_SPAWN, [=](float _DeltaTime, const StateInfo& _Info) {});
	StateManager_.CreateStateMember(MONSTER_FSM_IDLE, std::bind(&Crab::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Crab::IdleStart, this, std::placeholders::_1)
													, std::bind(&Crab::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_MOVE, std::bind(&Crab::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Crab::MoveStart, this, std::placeholders::_1)
													, std::bind(&Crab::MoveEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_CHASE, std::bind(&Crab::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Crab::ChaseStart, this, std::placeholders::_1)
													 , std::bind(&Crab::ChaseEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_ATTACK, std::bind(&Crab::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
													  , std::bind(&Crab::AttackStart, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_DEATH, std::bind(&Crab::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Crab::DeathStart, this, std::placeholders::_1)
													 , std::bind(&Crab::DeathEnd, this, std::placeholders::_1));

	// 초기 스테이트전환
	StateManager_.ChangeState(MONSTER_FSM_SPAWN);
}

void Crab::IdleStart(const StateInfo& _Info)
{
	CommonIdleStart(CRAB_ANIM_IDLE);
}

void Crab::MoveStart(const StateInfo& _Info)
{
	CommonMoveStart(CRAB_ANIM_WALK);
}

void Crab::ChaseStart(const StateInfo& _Info)
{
	CommonMoveStart(CRAB_ANIM_WALK);
}

void Crab::AttackStart(const StateInfo& _Info)
{
	CommonAttackStart(CRAB_ANIM_SHOOT);
}

void Crab::DeathStart(const StateInfo& _Info)
{
	CommonDeathStart(CRAB_ANIM_DEATH);
}

void Crab::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonIdleUpdate();
}

void Crab::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonMoveUpdate();
}

void Crab::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonChaseUpdate(20.0f);
}

void Crab::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Crab::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Crab::IdleEnd(const StateInfo& _Info)
{
}

void Crab::MoveEnd(const StateInfo& _Info)
{
}

void Crab::ChaseEnd(const StateInfo& _Info)
{
}

void Crab::DeathEnd(const StateInfo& _Info)
{
}
