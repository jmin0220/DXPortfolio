#include "PreCompile.h"
#include "Lemurian.h"

Lemurian::Lemurian() 
{
	Speed_ = Player_MOVE_SPEED;
	MonsterHp_ = 100;
	Damage_ = 14;
	Lv_ = 1;

	Exp_ = 3;
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
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_SHOOT, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_SHOOT, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_SPAWN, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_SPAWN, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_WALK, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_WALK, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_DEATH, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_DEATH, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(LEMURIAN_ANIM_HITTED, FrameAnimation_DESC(TEX_MONSTER_ANIM_LEMURIAN_HITTED, FrameAnimDelay_, false));

	// 프레임이 종료되었을 때
	Renderer_->AnimationBindEnd(LEMURIAN_ANIM_SPAWN, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_IDLE); Collision_->On(); });
	Renderer_->AnimationBindEnd(LEMURIAN_ANIM_SHOOT, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_CHASE); });
	Renderer_->AnimationBindEnd(LEMURIAN_ANIM_HITTED, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_CHASE); });

	// 초기 애니메이션 전환
	Renderer_->ChangeFrameAnimation(LEMURIAN_ANIM_SPAWN);
	Renderer_->SetScaleModeImage();
}

void Lemurian::CollisionInit()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 15.0f, 30.0f, 1.0f });
	Collision_->ChangeOrder(ObjectGroup::Monster);

	// 초기에 콜리전 off, spawn 애니메이션 종료후에 활성화
	Collision_->Off();
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
													, [=](const StateInfo) {});
	StateManager_.CreateStateMember(MONSTER_FSM_DEATH, std::bind(&Lemurian::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&Lemurian::DeathStart, this, std::placeholders::_1)
													, std::bind(&Lemurian::DeathEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_HITTED, [=](float _DeltaTime, const StateInfo& _Info_) 
	{
			// Update
			float4 MonsterPos = this->GetTransform().GetWorldPosition();

			// 몬스터와 플레이어 사이의 거리를 취득
			float4 MonsterLength = { this->GetTransform().GetWorldPosition().x
								   , this->GetTransform().GetWorldPosition().y, 0.0f };
			float4 PlayerLength = { PlayerPos_.x, PlayerPos_.y, 0.0f };
			float4 Length = MonsterLength - PlayerLength;

			// 오른쪽으로 
			if (MonsterPos.x <= PlayerPos_.x)
			{
				MoveDir_ = float4::RIGHT;

				if (true == GroundLeftCheck())
				{
					return;
				}

				GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ / 3 * DeltaTime_);

			}
			// 왼쪽으로
			else if (MonsterPos.x >= PlayerPos_.x)
			{
				MoveDir_ = float4::LEFT;

				if (true == GroundRightCheck())
				{
					return;
				}

				GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ / 3 * DeltaTime_);
			}
	}
	, [=](const StateInfo& _Info_) { /*Start*/ Renderer_->ChangeFrameAnimation(LEMURIAN_ANIM_HITTED); });

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
	// TODO::플레이어와 충돌처리
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

void Lemurian::DeathEnd(const StateInfo& _Info)
{
}
#pragma endregion
