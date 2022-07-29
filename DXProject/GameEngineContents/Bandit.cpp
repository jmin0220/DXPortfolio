#include "PreCompile.h"
#include "Bandit.h"

Bandit::Bandit()
{
}

Bandit::~Bandit() 
{
}

void Bandit::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_IDLE, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_IDLE, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_SHOOT, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_SHOOT, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_WALK, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_WALK, 0.1f, true));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_JUMP, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_JUMP, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_CLIMB, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_CLIMB, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_DEATH, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_DEATH, 0.1f, false));

	Renderer_->AnimationBindFrame(PLAYER_ANIM_IDLE, &Bandit::FrameAnimation, this);
	Renderer_->AnimationBindFrame(PLAYER_ANIM_SHOOT, &Bandit::FrameAnimation, this);
	Renderer_->AnimationBindFrame(PLAYER_ANIM_WALK, &Bandit::FrameAnimation, this);
	Renderer_->AnimationBindFrame(PLAYER_ANIM_JUMP, &Bandit::FrameAnimation, this);
	Renderer_->AnimationBindFrame(PLAYER_ANIM_CLIMB, &Bandit::FrameAnimation, this);
	Renderer_->AnimationBindFrame(PLAYER_ANIM_DEATH, &Bandit::FrameAnimation, this);

	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_IDLE);
	Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::LEFT);
}

void Bandit::StateInit()
{
	StateManager_.CreateStateMember(PLAYER_STATE_IDLE, this, &Bandit::IdleUpdate, &Bandit::IdleStart, &Bandit::IdleEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_MOVE, this, &Bandit::MoveUpdate, &Bandit::MoveStart, &Bandit::MoveEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_SHOOT, this, &Bandit::ShootUpdate, &Bandit::ShootStart, &Bandit::ShootEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL1, this, &Bandit::Skill1Update, &Bandit::Skill1Start, &Bandit::Skill1End);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL2, this, &Bandit::Skill2Update, &Bandit::Skill2Start, &Bandit::Skill2End);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL3, this, &Bandit::Skill3Update, &Bandit::Skill3Start, &Bandit::Skill3End);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL4, this, &Bandit::Skill4Update, &Bandit::Skill4Start, &Bandit::Skill4End);
	StateManager_.CreateStateMember(PLAYER_STATE_CLIMB, this, &Bandit::ClimbUpdate, &Bandit::ClimbStart, &Bandit::ClimbEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_DEATH, this, &Bandit::DeathUpdate, &Bandit::DeathStart, &Bandit::DeathEnd);
	StateManager_.ChangeState(PLAYER_STATE_IDLE);
}

void Bandit::EndAnimation(const FrameAnimation_DESC& _Info)
{
	// 스테이트 전환
	StateManager_.ChangeState(PLAYER_STATE_IDLE);
}

void Bandit::FrameAnimation(const FrameAnimation_DESC& _Info)
{
	//Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::LEFT);
}