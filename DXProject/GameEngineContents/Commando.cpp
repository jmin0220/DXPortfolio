#include "PreCompile.h"
#include "Commando.h"

Commando::Commando() 
{
}

Commando::~Commando() 
{
}

void Commando::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_IDLE, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_IDLE, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_SHOOT, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_SHOOT, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_WALK, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_WALK, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_JUMP, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_JUMP, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_CLIMB, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_CLIMB, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_DEATH, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_DEATH, FrameAnimDelay_, false));

	Renderer_->AnimationBindFrame(PLAYER_ANIM_IDLE, &Commando::FrameAnimation, this);
	Renderer_->AnimationBindFrame(PLAYER_ANIM_SHOOT, &Commando::FrameAnimation, this);
	Renderer_->AnimationBindFrame(PLAYER_ANIM_WALK, &Commando::FrameAnimation, this);
	Renderer_->AnimationBindFrame(PLAYER_ANIM_JUMP, &Commando::FrameAnimation, this);
	Renderer_->AnimationBindFrame(PLAYER_ANIM_CLIMB, &Commando::FrameAnimation, this);
	Renderer_->AnimationBindFrame(PLAYER_ANIM_DEATH, &Commando::FrameAnimation, this);

	Renderer_->AnimationBindEnd(PLAYER_ANIM_IDLE, &Commando::EndAnimation, this);
	Renderer_->AnimationBindEnd(PLAYER_ANIM_SHOOT, &Commando::EndAnimation, this);
	Renderer_->AnimationBindEnd(PLAYER_ANIM_WALK, &Commando::EndAnimation, this);

	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_IDLE);
	Renderer_->SetScaleModeImage();
}

void Commando::StateInit()
{
	StateManager_.CreateStateMember(PLAYER_STATE_IDLE, this, &Commando::IdleUpdate, &Commando::IdleStart, &Commando::IdleEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_MOVE, this, &Commando::MoveUpdate, &Commando::MoveStart, &Commando::MoveEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_SHOOT, this, &Commando::ShootUpdate, &Commando::ShootStart, &Commando::ShootEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL1, this, &Commando::Skill1Update, &Commando::Skill1Start, &Commando::Skill1End);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL2, this, &Commando::Skill2Update, &Commando::Skill2Start, &Commando::Skill2End);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL3, this, &Commando::Skill3Update, &Commando::Skill3Start, &Commando::Skill3End);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL4, this, &Commando::Skill4Update, &Commando::Skill4Start, &Commando::Skill4End);
	StateManager_.CreateStateMember(PLAYER_STATE_CLIMB, this, &Commando::ClimbUpdate, &Commando::ClimbStart, &Commando::ClimbEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_DEATH, this, &Commando::DeathUpdate, &Commando::DeathStart, &Commando::DeathEnd);

	StateManager_.ChangeState(PLAYER_STATE_IDLE);
}

void Commando::EndAnimation(const FrameAnimation_DESC& _Info)
{
	// 스테이트 전환
	StateManager_.ChangeState(PLAYER_STATE_IDLE);


	//GameEngineDebug::OutPutString(StateManager_.GetCurStateStateName() + " State End ");
}

void Commando::FrameAnimation(const FrameAnimation_DESC& _Info)
{
	// 디버그용
	// 애니메이션의 각 프레임마다 크기를 출력
	//std::string x = std::to_string( Renderer_->GetTransform().GetLocalScale().x);
	//std::string y = std::to_string(Renderer_->GetTransform().GetLocalScale().y);

	//GameEngineDebug::OutPutString(Renderer_->GetCurTexture()->GetNameCopy() + "  " + StateManager_.GetCurStateStateName() + " >> x : " + x + " , y : " + y);
}