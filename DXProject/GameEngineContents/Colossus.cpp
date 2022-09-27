#include "PreCompile.h"
#include "Colossus.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "CommonFunction.h"

Colossus::Colossus() 
{
	Speed_ = 600.0f;
	AtkSpeed_ = 1.0f;
	MonsterHp_ = 1400;
	Damage_ = 30;
	Lv_ = 1;

	Exp_ = 3;

	ChaseFlg_ = true;

	BossName_ = "Colossus";
	BossSubName_ = "Giant Stone Guardian";

	IsHitted_ = false;
}

Colossus::~Colossus() 
{
}

void Colossus::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	//FrameAnimDelay_ = 0.3f;

	// 애니메이션 동작이 변경되는 사이에 1초의 딜레이가 존재 -> 이 부분이 Idle로 설정
	// 애니메이션 생성
	Renderer_->CreateFrameAnimationFolder(COLOSSUS_ANIM_IDLE, FrameAnimation_DESC(COLOSSUS_ANIM_IDLE, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(COLOSSUS_ANIM_DEATH, FrameAnimation_DESC(COLOSSUS_ANIM_DEATH, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(COLOSSUS_ANIM_SHOOT1, FrameAnimation_DESC(COLOSSUS_ANIM_SHOOT1, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(COLOSSUS_ANIM_SHOOT2, FrameAnimation_DESC(COLOSSUS_ANIM_SHOOT2, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(COLOSSUS_ANIM_WALK, FrameAnimation_DESC(COLOSSUS_ANIM_WALK, FrameAnimDelay_, true));


	Renderer_->AnimationBindFrame(COLOSSUS_ANIM_WALK, [=](const FrameAnimation_DESC& _Info) 
		{
			// 특정 프레임에만 앞으로 움직임
			if (_Info.CurFrame == 1 || _Info.CurFrame == 2 || _Info.CurFrame == 3
				|| _Info.CurFrame == 12 || _Info.CurFrame == 13 || _Info.CurFrame == 14)
			{
				if (true == MoveDir_.CompareInt2D(float4::LEFT))
				{
					GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * DeltaTime_);

				}
				else
				{
					GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);
				}
			}
		});

	Renderer_->AnimationBindFrame(COLOSSUS_ANIM_SHOOT1, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 5)
			{
				CommonFunction::CommonFunction_->CameraShakeEffectOn(0.5f);
			}
		});

	Renderer_->AnimationBindFrame(COLOSSUS_ANIM_SHOOT2, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 8)
			{
				CommonFunction::CommonFunction_->CameraShakeEffectOn(0.5f);
			}
		});



	// 프레임이 종료되었을 때
	Renderer_->AnimationBindEnd(COLOSSUS_ANIM_SHOOT1, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_IDLE); });
	Renderer_->AnimationBindEnd(COLOSSUS_ANIM_SHOOT2, [=](const FrameAnimation_DESC& _Info) { StateManager_.ChangeState(MONSTER_FSM_IDLE); });

	// 초기 애니메이션 전환
	Renderer_->ChangeFrameAnimation(COLOSSUS_ANIM_IDLE);
	Renderer_->SetScaleModeImage();
	Renderer_->Off(); //-> State Spawn에서 On으로 
}

void Colossus::CollisionInit()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 160.0f, 226.0f, 1.0f });
	Collision_->ChangeOrder(ObjectGroup::Monster);

	// 초기에 콜리전 off, spawn 종료후에 활성화
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
													  , std::bind(&Colossus::AttackStart, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_ATTACK2, std::bind(&Colossus::Attack2Update, this, std::placeholders::_1, std::placeholders::_2)
													   , std::bind(&Colossus::Attack2Start, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_DEATH, std::bind(&Colossus::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Colossus::DeathStart, this, std::placeholders::_1)
													 , std::bind(&Colossus::DeathEnd, this, std::placeholders::_1));
	// 초기 스테이트전환
	StateManager_.ChangeState(MONSTER_FSM_SPAWN);
}

void Colossus::IdleStart(const StateInfo& _Info)
{
	this->ReSetAccTime();
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
	CommonAttackStart(COLOSSUS_ANIM_SHOOT2);
}

void Colossus::DeathStart(const StateInfo& _Info)
{
	CommonDeathStart(COLOSSUS_ANIM_DEATH);
}

void Colossus::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	this->AddAccTime(_DeltaTime);

	if (this->GetAccTime() >= 1.0f)
	{

		StateManager_.ChangeState(MONSTER_FSM_CHASE);
		this->ReSetAccTime();
	}
}

void Colossus::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MonsterPos = this->GetTransform().GetWorldPosition();

	// 몬스터와 플레이어 사이의 거리를 취득
	float4 MonsterLength = { this->GetTransform().GetWorldPosition().x
						   , this->GetTransform().GetWorldPosition().y, 0.0f };
	float4 PlayerLength = { PlayerPos_.x, PlayerPos_.y, 0.0f };
	float4 Length = MonsterLength - PlayerLength;

	// 거리가 몬스터와 가까워졌을경우 이동 정지
	if (Length.Length() <= 160.0f)
	{
		// 공격 쿨타임이 돌아오면 공격
		if (AtkTimer_ >= AtkSpeed_)
		{
			AtkTimer_ = 0.0f;

			if (0 == GameEngineRandom::MainRandom.RandomInt(0, 1))
			{
				StateManager_.ChangeState(MONSTER_FSM_ATTACK);
			}
			else
			{
				StateManager_.ChangeState(MONSTER_FSM_ATTACK2);
			}
		}
		else
		{
			StateManager_.ChangeState(MONSTER_FSM_IDLE);
		}

		return;
	}

	// FSM에서는 방향만 지정.
	// 실제로 움직이는것은 Animation에서 특정 프레임마다 이동처리
	// 오른쪽으로 
	if (MonsterPos.x <= PlayerPos_.x)
	{
		MoveDir_ = float4::RIGHT;
	}
	// 왼쪽으로
	else if (MonsterPos.x >= PlayerPos_.x)
	{
		MoveDir_ = float4::LEFT;
	}
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
