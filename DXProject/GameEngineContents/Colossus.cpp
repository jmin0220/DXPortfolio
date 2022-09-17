#include "PreCompile.h"
#include "Colossus.h"

Colossus::Colossus() 
{
	Speed_ = 50.0f;
	AtkSpeed_ = 1.0f;
	MonsterHp_ = 1400;
	Damage_ = 30;
	Lv_ = 1;

	Exp_ = 3;

	ChaseFlg_ = true;

	BossName_ = "Colossus";
	BossSubName_ = "Giant Stone Guardian";
}

Colossus::~Colossus() 
{
}

void Colossus::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	// �ִϸ��̼� ������ ����Ǵ� ���̿� 1���� �����̰� ���� -> �� �κ��� Idle�� ����
	// �ִϸ��̼� ����
	Renderer_->CreateFrameAnimationFolder(COLOSSUS_ANIM_IDLE, FrameAnimation_DESC(COLOSSUS_ANIM_IDLE, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(COLOSSUS_ANIM_DEATH, FrameAnimation_DESC(COLOSSUS_ANIM_DEATH, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(COLOSSUS_ANIM_SHOOT1, FrameAnimation_DESC(COLOSSUS_ANIM_SHOOT1, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(COLOSSUS_ANIM_SHOOT2, FrameAnimation_DESC(COLOSSUS_ANIM_SHOOT2, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(COLOSSUS_ANIM_WALK, FrameAnimation_DESC(COLOSSUS_ANIM_WALK, FrameAnimDelay_, true));

	// �������� ����Ǿ��� ��
	//Renderer_->AnimationBindEnd(LEMURIAN_ANIM_SPAWN, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_IDLE); Collision_->On(); });
	Renderer_->AnimationBindEnd(COLOSSUS_ANIM_SHOOT1, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_CHASE); });
	//Renderer_->AnimationBindEnd(LEMURIAN_ANIM_HITTED, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_CHASE); });

	// �ʱ� �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(COLOSSUS_ANIM_IDLE);
	Renderer_->SetScaleModeImage();
	Renderer_->Off(); //-> State Spawn���� On���� 
}

void Colossus::CollisionInit()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 160.0f, 226.0f, 1.0f });
	Collision_->ChangeOrder(ObjectGroup::Monster);

	// �ʱ⿡ �ݸ��� off, spawn �����Ŀ� Ȱ��ȭ
	Collision_->Off();
}

void Colossus::StateInit()
{
	StateManager_.CreateStateMember(MONSTER_FSM_SPAWN, std::bind(&Colossus::SpawnUpdate, this, std::placeholders::_1, std::placeholders::_2));
	StateManager_.CreateStateMember(MONSTER_FSM_IDLE, std::bind(&Colossus::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Colossus::IdleStart, this, std::placeholders::_1)
													, std::bind(&Colossus::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_CHASE, std::bind(&Colossus::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Colossus::ChaseStart, this, std::placeholders::_1)
													 , std::bind(&Colossus::ChaseEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_ATTACK, std::bind(&Colossus::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
													  , std::bind(&Colossus::AttackStart, this, std::placeholders::_1)
													  , [=](const StateInfo) {});
	StateManager_.CreateStateMember(MONSTER_FSM_ATTACK2, std::bind(&Colossus::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
													   , std::bind(&Colossus::AttackStart, this, std::placeholders::_1)
													   , [=](const StateInfo) {});
	StateManager_.CreateStateMember(MONSTER_FSM_DEATH, std::bind(&Colossus::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Colossus::DeathStart, this, std::placeholders::_1)
													 , std::bind(&Colossus::DeathEnd, this, std::placeholders::_1));
	// �ʱ� ������Ʈ��ȯ
	StateManager_.ChangeState(MONSTER_FSM_SPAWN);
}

void Colossus::IdleStart(const StateInfo& _Info)
{
	CommonIdleStart(COLOSSUS_ANIM_IDLE);
}

void Colossus::ChaseStart(const StateInfo& _Info)
{
	CommonChaseStart(COLOSSUS_ANIM_WALK);
}

void Colossus::AttackStart(const StateInfo& _Info)
{
	CommonAttackStart(COLOSSUS_ANIM_SHOOT1);
}

void Colossus::Attack2Start(const StateInfo& _Info)
{
	CommonAttackStart(COLOSSUS_ANIM_SHOOT1);
}

void Colossus::DeathStart(const StateInfo& _Info)
{
	CommonDeathStart(COLOSSUS_ANIM_DEATH);
}

void Colossus::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonIdleUpdate();
}

void Colossus::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonChaseUpdate();
}

void Colossus::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Colossus::Attack2Update(float _DeltaTime, const StateInfo& _Info)
{
}

void Colossus::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Colossus::SpawnUpdate(float _DeltaTime, const StateInfo& _Info)
{
	BossSpawnState(_DeltaTime);
}

void Colossus::IdleEnd(const StateInfo& _Info)
{
}

void Colossus::ChaseEnd(const StateInfo& _Info)
{
}

void Colossus::DeathEnd(const StateInfo& _Info)
{
}
