#include "PreCompile.h"
#include "AttackDrone.h"
#include "Bullet.h"

AttackDrone::AttackDrone() 
	: YPosLevel_(0)
{
}

AttackDrone::~AttackDrone() 
{
}

void AttackDrone::AnimInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->SetSamplingModePoint();
	Renderer_->CreateFrameAnimationFolder(DRONE_ATTACK_IDLE, FrameAnimation_DESC(DRONE_ATTACK_IDLE, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(DRONE_ATTACK_SHOOT, FrameAnimation_DESC(DRONE_ATTACK_SHOOT, ANIMATION_FRAME_DELAY, false));
	Renderer_->ChangeFrameAnimation(DRONE_ATTACK_IDLE);
	Renderer_->ScaleToTexture();
	Renderer_->SetScaleModeImage();

	Renderer_->AnimationBindFrame(DRONE_ATTACK_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 0 || _Info.CurFrame == 3 || _Info.CurFrame == 6)
			{
				CreateBullet(_Info.CurFrame, 6);
			}
		});

	Renderer_->AnimationBindEnd(DRONE_ATTACK_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			StateManager_.ChangeState(DRONE_FSM_IDLE);
		});
}

void AttackDrone::StateInit()
{
	StateManager_.CreateStateMember(DRONE_FSM_IDLE, std::bind(&AttackDrone::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
												  , std::bind(&AttackDrone::IdleStart, this, std::placeholders::_1)
												  , std::bind(&AttackDrone::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(DRONE_FSM_ACTION, std::bind(&AttackDrone::ActionUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&AttackDrone::ActionStart, this, std::placeholders::_1)
													, std::bind(&AttackDrone::ActionEnd, this, std::placeholders::_1));

	StateManager_.ChangeState(DRONE_FSM_IDLE);
}

void AttackDrone::IdleStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation(DRONE_ATTACK_IDLE);
}

void AttackDrone::ActionStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation(DRONE_ATTACK_SHOOT);
}

void AttackDrone::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 대상을 찾았을 경우 스테이트 변경
	if (true == FindChaseMonster(600.0f))
	{
		    // 오른쪽을 바라보고 있으면서 대상이 오른쪽에 있을경우
		if ((PlayerDir_.CompareInt2D(float4::RIGHT) && this->GetTransform().GetWorldPosition().x < TargetPos_.x)
			// 왼쪽을 바라보고 있으면서 대상이 왼쪽에 있을경우
		 || (PlayerDir_.CompareInt2D(float4::LEFT) && this->GetTransform().GetWorldPosition().x > TargetPos_.x))
		{
			StateManager_.ChangeState(DRONE_FSM_ACTION);
		}
	}
}

void AttackDrone::ActionUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void AttackDrone::IdleEnd(const StateInfo& _Info)
{
}

void AttackDrone::ActionEnd(const StateInfo& _Info)
{
}

void AttackDrone::CreateBullet(int _CurFrame, int _LastFrame)
{
	Bullet* bullet = GetLevel()->CreateActor<Bullet>();

	float4 tmpDir = TargetPos_ - Renderer_->GetTransform().GetWorldPosition();

	bullet->GetTransform().SetWorldPosition(Renderer_->GetTransform().GetWorldPosition());
	bullet->SetDamage(PlayerStatus::Damage_);
	bullet->SetDirection(tmpDir.NormalizeReturn());
	bullet->SetBulletYPositionLevel(YPosLevel_);

	YPosLevel_++;

	// 이번 애니메이션에서 총알을 모두 쏨
	if (_CurFrame == _LastFrame)
	{
		YPosLevel_ = 0;
	}
}
