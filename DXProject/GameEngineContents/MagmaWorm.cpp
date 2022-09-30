#include "PreCompile.h"
#include "MagmaWorm.h"
#include "MagmaWormBody.h"
#include <GameEngineBase/GameEngineRandom.h>

MagmaWorm::MagmaWorm() 
	: Direction_(GetTransform().GetRightVector())
	, ChaseUpFlg_(true)
{
	Speed_ = 1200.0f;
	AtkSpeed_ = 1.0f;
	MonsterHp_ = 1400;
	Damage_ = 30;
	Lv_ = 1;

	Exp_ = 3;

	ChaseFlg_ = true;

	BossName_ = "Magma Worm";
	BossSubName_ = "Ancient Lava Swimmer";

	IsHitted_ = false;
}

MagmaWorm::~MagmaWorm() 
{
}

void MagmaWorm::SetMoveDirection(float4 _Direction)
{
	_Direction.z = 0.0f;

	Direction_ = _Direction - MagmaWormBody_[0]->GetTransform().GetWorldPosition();
	DestPos_ = _Direction;

	Direction_.Normalize();
}

void MagmaWorm::Start()
{
	for (int i = 19; i > 0; i--)
	{
		MagmaWormBody_[i] = GetLevel()->CreateActor<MagmaWormBody>();
		MagmaWormBody_[i]->SetWormBodyScale(i);
		MagmaWormBody_[i]->SetSpeed(Speed_);
	}

	MagmaWormBody_[0] = GetLevel()->CreateActor<MagmaWormBody>();
	MagmaWormBody_[0]->SetHead();
	MagmaWormBody_[0]->SetSpeed(Speed_);

	// 낙하 체크를 하지 않음
	IsFallCheck_ = false;

	Monster::Start();
}

void MagmaWorm::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);

	// 데미지 처리
	for (MagmaWormBody* tmp : MagmaWormBody_)
	{
		HitFunction(tmp->OutputHittedDamage());
		tmp->ResetHittedDamageZero();
	}

	if (MonsterHp_ <= 0)
	{
		for (MagmaWormBody* tmp : MagmaWormBody_)
		{
			tmp->SetDeath();
		}
	}
}

void MagmaWorm::AnimationInit()
{
	WarningRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	WarningRenderer_->CreateFrameAnimationFolder(MAGMAWORM_ANIM_WARNING, FrameAnimation_DESC(MAGMAWORM_ANIM_WARNING, ANIMATION_FRAME_DELAY, true));
	WarningRenderer_->ChangeFrameAnimation(MAGMAWORM_ANIM_WARNING);
	WarningRenderer_->SetSamplingModePoint();
	WarningRenderer_->ScaleToTexture();

	WarningRenderer_->Off();

	// 사용하진 않지만 구조상 존재해야하므로..
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->Off();
}

void MagmaWorm::StateInit()
{
	StateManager_.CreateStateMember(MONSTER_FSM_SPAWN, std::bind(&MagmaWorm::SpawnUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&MagmaWorm::SpawnStart, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_ATTACK, std::bind(&MagmaWorm::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
													  , std::bind(&MagmaWorm::AttackStart, this, std::placeholders::_1));
	StateManager_.CreateStateMember(MONSTER_FSM_DEATH, std::bind(&MagmaWorm::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&MagmaWorm::DeathStart, this, std::placeholders::_1)
													 , std::bind(&MagmaWorm::DeathEnd, this, std::placeholders::_1));
	// 초기 스테이트전환
	StateManager_.ChangeState(MONSTER_FSM_SPAWN); 
}


void MagmaWorm::AttackStart(const StateInfo& _Info)
{
	// 경고 표시
	WarningRenderer_->On();
	WarningRenderer_->GetTransform().SetWorldPosition(PlayerPos_);

	this->SetMoveDirection(PlayerPos_);

	MagmaWormBody_[0]->MoveToDestinationHead(Direction_, PlayerPos_);
}

void MagmaWorm::SpawnStart(const StateInfo& _Info)
{
}

void MagmaWorm::DeathStart(const StateInfo& _Info)
{

}

void MagmaWorm::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{

	// 상승중이라면
	if (true == ChaseUpFlg_)
	{
		// 플레이어에게 근접하면 카메라 떨림 효과
		if (MagmaWormBody_[0]->GetTransform().GetWorldPosition().y >= PlayerPos_.y - 300.0f
			&& MagmaWormBody_[0]->GetTransform().GetWorldPosition().y < PlayerPos_.y)
		{
			CommonFunction::CommonFunction_->CameraShakeEffectOn();
		}
	}

	// MagmaWorm이 최대상승 or 최대하강을 했다면 
	if ((MagmaWormBody_[0]->GetTransform().GetWorldPosition().y >= PlayerPos_.y + 1300.0f && ChaseUpFlg_ == true)
		|| (MagmaWormBody_[0]->GetTransform().GetWorldPosition().y <= PlayerPos_.y - 2000.0f && ChaseUpFlg_ == false))
	{
		// true였으면 이제 내려올 차례
		if (true == ChaseUpFlg_)
		{
			WarningRenderer_->Off();
		}
		// false였으면 이제 올라올 차례
		else
		{
			if (MonsterHp_ <= 0)
			{
				StateManager_.ChangeState(MONSTER_FSM_DEATH);
			}

			// 경고 표시
			WarningRenderer_->On();
			WarningRenderer_->GetTransform().SetWorldPosition(PlayerPos_);

			float tmpRandom = GameEngineRandom::MainRandom.RandomFloat(-400.0f, 400.0f);

			// 너무 어색해보여서 위치를 재조정
			for (int i = 0; i < 20; i++)
			{
				MagmaWormBody_[i]->GetTransform().SetWorldPosition({ PlayerPos_.x + tmpRandom
																   , MagmaWormBody_[i]->GetTransform().GetWorldPosition().y
																   , static_cast<float>(ZOrder::MagmaWorm) });
			}
		}

		// 플래그 반전
		ChaseUpFlg_ = !ChaseUpFlg_;

		// 머리에게 방향과 위치를 재설정
		this->SetMoveDirection(PlayerPos_);
		MagmaWormBody_[0]->MoveToDestinationHead(Direction_, PlayerPos_);
	}

	// 몸의 포지션들을 결정
	for (int i = 0; i < 19; i++)
	{
		MagmaWormBody_[i + 1]->MovetoDestination(MagmaWormBody_[i]->GetTransform().GetWorldPosition());
	}
}

void MagmaWorm::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

	// MagmaWorm이 최대상승 or 최대하강을 했다면 
	if ((MagmaWormBody_[0]->GetTransform().GetWorldPosition().y >= PlayerPos_.y + 1300.0f && ChaseUpFlg_ == true)
		|| (MagmaWormBody_[0]->GetTransform().GetWorldPosition().y <= PlayerPos_.y - 2000.0f && ChaseUpFlg_ == false))
	{
		// true였으면 이제 내려올 차례
		if (true == ChaseUpFlg_)
		{
			WarningRenderer_->Off();
		}
		// false였으면 이제 올라올 차례
		else
		{
			// 밑에서 사라짐 처리
			this->Off();
			return;
		}

		// 플래그 반전
		ChaseUpFlg_ = !ChaseUpFlg_;

		// 머리에게 방향과 위치를 재설정
		this->SetMoveDirection(PlayerPos_);
		MagmaWormBody_[0]->MoveToDestinationHead(Direction_, PlayerPos_);
	}

	// 몸의 포지션들을 결정
	for (int i = 0; i < 19; i++)
	{
		MagmaWormBody_[i + 1]->MovetoDestination(MagmaWormBody_[i]->GetTransform().GetWorldPosition());
	}
}

void MagmaWorm::SpawnUpdate(float _DeltaTime, const StateInfo& _Info)
{
	static float SpawnTimer = 0.0f;

	SpawnTimer += _DeltaTime;

	// n초가 지난다음에 활동을 시작
	if (SpawnTimer >= 5.0f)
	{
		for (int i = 0; i < 20; i++)
		{
			MagmaWormBody_[i]->GetTransform().SetWorldPosition({ PlayerPos_.x, PlayerPos_.y - 1000.0f, static_cast<float>(ZOrder::MagmaWorm) });
		}

		StateManager_.ChangeState(MONSTER_FSM_ATTACK);
	}
}

void MagmaWorm::DeathEnd(const StateInfo& _Info)
{
}

