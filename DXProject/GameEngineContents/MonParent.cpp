#include "PreCompile.h"
#include "MonParent.h"
#include "CommonFunction.h"

MonParent::MonParent()
{
	Speed_ = Player_MOVE_SPEED - 30.0f;
	AtkSpeed_ = 1.3f;
	MonsterHp_ = 200;
	Damage_ = 14;
	Lv_ = 1;

	Exp_ = 3;
	IsHitted_ = false;
}

MonParent::~MonParent()
{
}

void MonParent::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	// 애니메이션 생성
	Renderer_->CreateFrameAnimationFolder(PARENT_ANIM_IDLE, FrameAnimation_DESC(PARENT_ANIM_IDLE, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(PARENT_ANIM_SHOOT, FrameAnimation_DESC(PARENT_ANIM_SHOOT, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(PARENT_ANIM_SPAWN, FrameAnimation_DESC(PARENT_ANIM_SPAWN, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PARENT_ANIM_WALK, FrameAnimation_DESC(PARENT_ANIM_WALK, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(PARENT_ANIM_DEATH, FrameAnimation_DESC(PARENT_ANIM_DEATH, FrameAnimDelay_, false));

	// 프레임이 종료되었을 때
	Renderer_->AnimationBindEnd(PARENT_ANIM_SPAWN, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_IDLE); Collision_->On(); });
	Renderer_->AnimationBindEnd(PARENT_ANIM_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			StateManager_.ChangeState(MONSTER_FSM_CHASE);
		});

	Renderer_->AnimationBindFrame(PARENT_ANIM_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 5)
			{
				CommonFunction::CommonFunction_->CameraShakeEffectOn(0.3f, 1.0f);
			}
		});

	// 초기 애니메이션 전환
	Renderer_->ChangeFrameAnimation(PARENT_ANIM_SPAWN);
	Renderer_->SetScaleModeImage();
}

void MonParent::CollisionInit()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 92.0f, 132.0f, 1.0f });
	Collision_->ChangeOrder(ObjectGroup::Monster);

	// 초기에 콜리전 off, spawn 애니메이션 종료후에 활성화
	Collision_->Off();
}

void MonParent::StateInit()
{
	// StateSpawn = 애니메이션이 끝날때까지 대기하는 상태
	StateManager_.CreateStateMember(MONSTER_FSM_SPAWN, [=](float _DeltaTime, const StateInfo& _Info) {});
	StateManager_.CreateStateMember(MONSTER_FSM_IDLE, std::bind(&MonParent::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&MonParent::IdleStart, this, std::placeholders::_1)
													, std::bind(&MonParent::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_MOVE, std::bind(&MonParent::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&MonParent::MoveStart, this, std::placeholders::_1)
													, std::bind(&MonParent::MoveEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_CHASE, std::bind(&MonParent::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&MonParent::ChaseStart, this, std::placeholders::_1)
													 , std::bind(&MonParent::ChaseEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_ATTACK, std::bind(&MonParent::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
													  , std::bind(&MonParent::AttackStart, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_DEATH, std::bind(&MonParent::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&MonParent::DeathStart, this, std::placeholders::_1)
													 , std::bind(&MonParent::DeathEnd, this, std::placeholders::_1));

	// 초기 스테이트전환
	StateManager_.ChangeState(MONSTER_FSM_SPAWN);
}

void MonParent::IdleStart(const StateInfo& _Info)
{
	CommonIdleStart(PARENT_ANIM_IDLE);
}

void MonParent::MoveStart(const StateInfo& _Info)
{
	CommonMoveStart(PARENT_ANIM_WALK);
}

void MonParent::ChaseStart(const StateInfo& _Info)
{
	CommonChaseStart(PARENT_ANIM_WALK);
}

void MonParent::AttackStart(const StateInfo& _Info)
{
	CommonAttackStart(PARENT_ANIM_SHOOT);
	GameEngineSound::SoundPlayOneShot("wChildGShoot1.wav");
}

void MonParent::DeathStart(const StateInfo& _Info)
{
	CommonDeathStart(PARENT_ANIM_DEATH);
}

void MonParent::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonIdleUpdate();
}

void MonParent::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonMoveUpdate();
}

void MonParent::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonChaseUpdate(40.0f);
}

void MonParent::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MonParent::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MonParent::IdleEnd(const StateInfo& _Info)
{
}

void MonParent::MoveEnd(const StateInfo& _Info)
{
}

void MonParent::ChaseEnd(const StateInfo& _Info)
{
}

void MonParent::DeathEnd(const StateInfo& _Info)
{
}
