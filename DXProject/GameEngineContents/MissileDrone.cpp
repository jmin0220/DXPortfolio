#include "PreCompile.h"
#include "MissileDrone.h"
#include "Missile.h"

MissileDrone::MissileDrone() 
{
}

MissileDrone::~MissileDrone() 
{
}

void MissileDrone::AnimInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->SetSamplingModePoint();
	Renderer_->CreateFrameAnimationFolder(DRONE_MISSILE_IDLE, FrameAnimation_DESC(DRONE_MISSILE_IDLE, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(DRONE_MISSILE_SHOOT, FrameAnimation_DESC(DRONE_MISSILE_SHOOT, ANIMATION_FRAME_DELAY, false));
	Renderer_->ChangeFrameAnimation(DRONE_MISSILE_IDLE);
	Renderer_->ScaleToTexture();
	Renderer_->SetScaleModeImage();

	Renderer_->AnimationBindFrame(DRONE_MISSILE_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 1)
			{
				Missile* tmp = GetLevel()->CreateActor<Missile>();
				tmp->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());
				tmp->GetTransform().SetWorldMove({ 0.0f, 10.0f, 0.0f });
				tmp->GetTransform().SetAddWorldRotation({ 0.0f, 0.0f, 90.0f, 0.0f });
			}
		});

	Renderer_->AnimationBindEnd(DRONE_MISSILE_SHOOT, [=](const FrameAnimation_DESC& _Info)
		{
			StateManager_.ChangeState(DRONE_FSM_IDLE);
		});

}

void MissileDrone::StateInit()
{
	StateManager_.CreateStateMember(DRONE_FSM_IDLE, std::bind(&MissileDrone::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
												  , std::bind(&MissileDrone::IdleStart, this, std::placeholders::_1)
												  , std::bind(&MissileDrone::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(DRONE_FSM_ACTION, std::bind(&MissileDrone::ActionUpdate, this, std::placeholders::_1, std::placeholders::_2)
													, std::bind(&MissileDrone::ActionStart, this, std::placeholders::_1)
													, std::bind(&MissileDrone::ActionEnd, this, std::placeholders::_1));

	StateManager_.ChangeState(DRONE_FSM_IDLE);
}

void MissileDrone::IdleStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation(DRONE_MISSILE_IDLE);
}

void MissileDrone::ActionStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation(DRONE_MISSILE_SHOOT);
}

void MissileDrone::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() < 0.7f)
	{
		return;
	}

	// 대상을 찾았을 경우 스테이트 변경
	if (true == FindChaseMonster())
	{
		StateManager_.ChangeState(DRONE_FSM_ACTION);
		ReSetAccTime();
	}
}

void MissileDrone::ActionUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MissileDrone::IdleEnd(const StateInfo& _Info)
{
}

void MissileDrone::ActionEnd(const StateInfo& _Info)
{
}
