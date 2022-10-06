#include "PreCompile.h"
#include "Child.h"

Child::Child() 
{
	Speed_ = Player_MOVE_SPEED - 20.0f;
	AtkSpeed_ = 0.3f;
	MonsterHp_ = 100;
	Damage_ = 14;
	Lv_ = 1;

	Exp_ = 3;
}

Child::~Child() 
{
}

void Child::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	// �ִϸ��̼� ����
	Renderer_->CreateFrameAnimationFolder(CHILD_ANIM_IDLE, FrameAnimation_DESC(CHILD_ANIM_IDLE, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(CHILD_ANIM_SHOOT, FrameAnimation_DESC(CHILD_ANIM_SHOOT, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(CHILD_ANIM_SPAWN, FrameAnimation_DESC(CHILD_ANIM_SPAWN, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(CHILD_ANIM_WALK, FrameAnimation_DESC(CHILD_ANIM_WALK, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(CHILD_ANIM_DEATH, FrameAnimation_DESC(CHILD_ANIM_DEATH, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(CHILD_ANIM_HITTED, FrameAnimation_DESC(CHILD_ANIM_HITTED, FrameAnimDelay_, false));

	// �������� ����Ǿ��� ��
	Renderer_->AnimationBindEnd(CHILD_ANIM_SPAWN, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_IDLE); Collision_->On(); });
	Renderer_->AnimationBindEnd(CHILD_ANIM_SHOOT, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_CHASE); });
	Renderer_->AnimationBindEnd(CHILD_ANIM_HITTED, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_CHASE); });

	// �ʱ� �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(CHILD_ANIM_SPAWN);
	Renderer_->SetScaleModeImage();
}

void Child::CollisionInit()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 28.0f, 40.0f, 1.0f });
	Collision_->ChangeOrder(ObjectGroup::Monster);

	// �ʱ⿡ �ݸ��� off, spawn �ִϸ��̼� �����Ŀ� Ȱ��ȭ
	Collision_->Off();
}

void Child::StateInit()
{
	// StateSpawn = �ִϸ��̼��� ���������� ����ϴ� ����
	StateManager_.CreateStateMember(MONSTER_FSM_SPAWN, [=](float _DeltaTime, const StateInfo& _Info) {});
	StateManager_.CreateStateMember(MONSTER_FSM_IDLE, std::bind(&Child::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Child::IdleStart, this, std::placeholders::_1)
													, std::bind(&Child::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_MOVE, std::bind(&Child::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Child::MoveStart, this, std::placeholders::_1)
													, std::bind(&Child::MoveEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_CHASE, std::bind(&Child::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Child::ChaseStart, this, std::placeholders::_1)
													 , std::bind(&Child::ChaseEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_ATTACK, std::bind(&Child::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
													  , std::bind(&Child::AttackStart, this, std::placeholders::_1)
													  , [=](const StateInfo) {});
	StateManager_.CreateStateMember(MONSTER_FSM_DEATH, std::bind(&Child::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Child::DeathStart, this, std::placeholders::_1)
													 , std::bind(&Child::DeathEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_HITTED, [=](float _DeltaTime, const StateInfo& _Info_) {CommonHitted(); }
													  , [=](const StateInfo& _Info_) 
		{ /*Start*/ 
			GameEngineSound::SoundPlayOneShot("wChildHit.wav");
			Renderer_->ChangeFrameAnimation(CHILD_ANIM_HITTED); 
		});

	// �ʱ� ������Ʈ��ȯ
	StateManager_.ChangeState(MONSTER_FSM_SPAWN);
}

void Child::IdleStart(const StateInfo& _Info)
{
	CommonIdleStart(CHILD_ANIM_IDLE);
}

void Child::MoveStart(const StateInfo& _Info)
{
	CommonMoveStart(CHILD_ANIM_WALK);
}

void Child::ChaseStart(const StateInfo& _Info)
{
	CommonChaseStart(CHILD_ANIM_WALK);
}

void Child::AttackStart(const StateInfo& _Info)
{
	CommonAttackStart(CHILD_ANIM_SHOOT);
	GameEngineSound::SoundPlayOneShot("wChildShoot1.wav");
}

void Child::DeathStart(const StateInfo& _Info)
{
	CommonDeathStart(CHILD_ANIM_DEATH);

	if (false == DeathSoundFlg_)
	{
		DeathSoundFlg_ = true;
		GameEngineSound::SoundPlayOneShot("wChildDeath.wav");
	}
}

void Child::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonIdleUpdate();
}

void Child::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonMoveUpdate();
}

void Child::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonChaseUpdate(15.0f);
}

void Child::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Child::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Child::IdleEnd(const StateInfo& _Info)
{
}

void Child::MoveEnd(const StateInfo& _Info)
{
}

void Child::ChaseEnd(const StateInfo& _Info)
{
}

void Child::DeathEnd(const StateInfo& _Info)
{
}
