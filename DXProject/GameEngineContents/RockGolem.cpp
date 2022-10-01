#include "PreCompile.h"
#include "RockGolem.h"

RockGolem::RockGolem() 
{
	Speed_ = Player_MOVE_SPEED - 30.0f;
	AtkSpeed_ = 1.3f;
	MonsterHp_ = 200;
	Damage_ = 14;
	Lv_ = 1;

	Exp_ = 3;
	IsHitted_ = false;
}

RockGolem::~RockGolem() 
{
}

void RockGolem::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	// 애니메이션 생성
	Renderer_->CreateFrameAnimationFolder(ROCKGOLEM_ANIM_IDLE,  FrameAnimation_DESC(ROCKGOLEM_ANIM_IDLE, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(ROCKGOLEM_ANIM_SHOOT, FrameAnimation_DESC(ROCKGOLEM_ANIM_SHOOT, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(ROCKGOLEM_ANIM_SPAWN, FrameAnimation_DESC(ROCKGOLEM_ANIM_SPAWN, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(ROCKGOLEM_ANIM_WALK,  FrameAnimation_DESC(ROCKGOLEM_ANIM_WALK, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(ROCKGOLEM_ANIM_DEATH, FrameAnimation_DESC(ROCKGOLEM_ANIM_DEATH, FrameAnimDelay_, false));

	// 프레임이 종료되었을 때
	Renderer_->AnimationBindEnd(ROCKGOLEM_ANIM_SPAWN, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_IDLE); Collision_->On(); });
	Renderer_->AnimationBindEnd(ROCKGOLEM_ANIM_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			StateManager_.ChangeState(MONSTER_FSM_CHASE);
		});

	Renderer_->AnimationBindFrame(ROCKGOLEM_ANIM_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 5)
			{
				CommonFunction::CommonFunction_->CameraShakeEffectOn(0.3f, 1.0f);
			}
		});

	// 초기 애니메이션 전환
	Renderer_->ChangeFrameAnimation(ROCKGOLEM_ANIM_SPAWN);
	Renderer_->SetScaleModeImage();
}

void RockGolem::CollisionInit()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 40.0f, 58.0f, 1.0f });
	Collision_->ChangeOrder(ObjectGroup::Monster);

	// 초기에 콜리전 off, spawn 애니메이션 종료후에 활성화
	Collision_->Off();
}

void RockGolem::StateInit()
{
	// StateSpawn = 애니메이션이 끝날때까지 대기하는 상태
	StateManager_.CreateStateMember(MONSTER_FSM_SPAWN, [=](float _DeltaTime, const StateInfo& _Info) {});
	StateManager_.CreateStateMember(MONSTER_FSM_IDLE, std::bind(&RockGolem::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&RockGolem::IdleStart, this, std::placeholders::_1)
													, std::bind(&RockGolem::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_MOVE, std::bind(&RockGolem::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&RockGolem::MoveStart, this, std::placeholders::_1)
													, std::bind(&RockGolem::MoveEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_CHASE, std::bind(&RockGolem::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&RockGolem::ChaseStart, this, std::placeholders::_1)
													 , std::bind(&RockGolem::ChaseEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_ATTACK, std::bind(&RockGolem::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
													  , std::bind(&RockGolem::AttackStart, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_DEATH, std::bind(&RockGolem::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&RockGolem::DeathStart, this, std::placeholders::_1)
													 , std::bind(&RockGolem::DeathEnd, this, std::placeholders::_1));

	// 초기 스테이트전환
	StateManager_.ChangeState(MONSTER_FSM_SPAWN);
}

void RockGolem::IdleStart(const StateInfo& _Info)
{
	CommonIdleStart(ROCKGOLEM_ANIM_IDLE);
}

void RockGolem::MoveStart(const StateInfo& _Info)
{
	CommonMoveStart(ROCKGOLEM_ANIM_WALK);
}

void RockGolem::ChaseStart(const StateInfo& _Info)
{
	CommonMoveStart(ROCKGOLEM_ANIM_WALK);
}

void RockGolem::AttackStart(const StateInfo& _Info)
{
	CommonAttackStart(ROCKGOLEM_ANIM_SHOOT);
}

void RockGolem::DeathStart(const StateInfo& _Info)
{
	CommonDeathStart(ROCKGOLEM_ANIM_DEATH);
}

void RockGolem::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonIdleUpdate();
}

void RockGolem::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonMoveUpdate();
}

void RockGolem::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonChaseUpdate(20.0f);
}

void RockGolem::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void RockGolem::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void RockGolem::IdleEnd(const StateInfo& _Info)
{
}

void RockGolem::MoveEnd(const StateInfo& _Info)
{
}

void RockGolem::ChaseEnd(const StateInfo& _Info)
{
}

void RockGolem::DeathEnd(const StateInfo& _Info)
{
}
