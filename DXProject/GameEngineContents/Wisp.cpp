#include "PreCompile.h"
#include "Wisp.h"

Wisp::Wisp() 
{
	Speed_ = Player_MOVE_SPEED - 30.0f;
	AtkSpeed_ = 1.3f;
	MonsterHp_ = 130;
	Damage_ = 14;
	Lv_ = 1;

	Exp_ = 3;
	IsHitted_ = false;
}

Wisp::~Wisp() 
{
}

void Wisp::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	// 애니메이션 생성
	Renderer_->CreateFrameAnimationFolder(WISP_ANIM_IDLE,  FrameAnimation_DESC(WISP_ANIM_IDLE, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(WISP_ANIM_SHOOT, FrameAnimation_DESC(WISP_ANIM_SHOOT, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(WISP_ANIM_SPAWN, FrameAnimation_DESC(WISP_ANIM_SPAWN, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(WISP_ANIM_DEATH, FrameAnimation_DESC(WISP_ANIM_DEATH, FrameAnimDelay_, false));

	// 프레임이 종료되었을 때
	Renderer_->AnimationBindEnd(WISP_ANIM_SPAWN, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_IDLE); Collision_->On(); });
	Renderer_->AnimationBindEnd(WISP_ANIM_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			StateManager_.ChangeState(MONSTER_FSM_CHASE);
		});

	Renderer_->AnimationBindFrame(WISP_ANIM_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 7)
			{
				CommonBulletAttackStart(WISP_ANIM_SPARK);
			}
		});

	// 초기 애니메이션 전환
	Renderer_->ChangeFrameAnimation(WISP_ANIM_SPAWN);
	Renderer_->SetScaleModeImage();
}

void Wisp::CollisionInit()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 18.0f, 32.0f, 1.0f });
	Collision_->ChangeOrder(ObjectGroup::Monster);

	// 초기에 콜리전 off, spawn 애니메이션 종료후에 활성화
	Collision_->Off();
}

void Wisp::StateInit()
{
	// StateSpawn = 애니메이션이 끝날때까지 대기하는 상태
	StateManager_.CreateStateMember(MONSTER_FSM_SPAWN, [=](float _DeltaTime, const StateInfo& _Info) {});
	StateManager_.CreateStateMember(MONSTER_FSM_IDLE, std::bind(&Wisp::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Wisp::IdleStart, this, std::placeholders::_1)
													, std::bind(&Wisp::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_MOVE, std::bind(&Wisp::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Wisp::MoveStart, this, std::placeholders::_1)
													, std::bind(&Wisp::MoveEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_CHASE, std::bind(&Wisp::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Wisp::ChaseStart, this, std::placeholders::_1)
													 , std::bind(&Wisp::ChaseEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_ATTACK, std::bind(&Wisp::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
													  , std::bind(&Wisp::AttackStart, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_DEATH, std::bind(&Wisp::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Wisp::DeathStart, this, std::placeholders::_1)
													 , std::bind(&Wisp::DeathEnd, this, std::placeholders::_1));

	// 초기 스테이트전환
	StateManager_.ChangeState(MONSTER_FSM_SPAWN);
}

void Wisp::IdleStart(const StateInfo& _Info)
{
	CommonIdleStart(WISP_ANIM_IDLE);
}

void Wisp::MoveStart(const StateInfo& _Info)
{
	CommonMoveStart(WISP_ANIM_IDLE);
}

void Wisp::ChaseStart(const StateInfo& _Info)
{
	CommonChaseStart(WISP_ANIM_IDLE);
}

void Wisp::AttackStart(const StateInfo& _Info)
{
	CommonAttackStart(WISP_ANIM_SHOOT);
}

void Wisp::DeathStart(const StateInfo& _Info)
{
	CommonDeathStart(WISP_ANIM_DEATH);
}

void Wisp::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonIdleUpdate();
}

void Wisp::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonMoveUpdate();
}

void Wisp::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonChaseUpdate(170.0f);
}

void Wisp::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Wisp::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Wisp::IdleEnd(const StateInfo& _Info)
{
}

void Wisp::MoveEnd(const StateInfo& _Info)
{
}

void Wisp::ChaseEnd(const StateInfo& _Info)
{
}

void Wisp::DeathEnd(const StateInfo& _Info)
{
}
