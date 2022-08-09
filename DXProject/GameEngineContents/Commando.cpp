#include "PreCompile.h"
#include "Commando.h"

Commando::Commando() 
{
	// https://riskofrain.fandom.com/wiki/Commando_(RoR)?so=search
	Hp_ = 110;
	LvPerHp_ = 32;

	HpRegen_ = 0.6;
	LvPerHpRegen_ = 0.12;

	Damage_ = 12;
	LvPerDamage_ = 3;

	AtkSpeed_ = 163.63;
}

Commando::~Commando() 
{
}

void Commando::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	// 애니메이션 생성
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_IDLE, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_IDLE, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_SKILL1, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_SKILL1, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_SKILL2, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_SKILL2, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_SKILL3, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_SKILL3, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_COMMANDO_SKILL4_1, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_SKILL4_1, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_COMMANDO_SKILL4_2, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_SKILL4_2, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_WALK, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_WALK, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_JUMP, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_JUMP, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_CLIMB, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_CLIMB, FrameAnimDelay_ * 3, true));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_DEATH, FrameAnimation_DESC(TEX_PLAYER_ANIM_COMMANDO_DEATH, FrameAnimDelay_, false));

	// 프레임마다 실행할 함수
	Renderer_->AnimationBindFrame(PLAYER_ANIM_IDLE, std::bind(&Commando::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_SKILL1, std::bind(&Commando::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_SKILL2, std::bind(&Commando::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_SKILL3, std::bind(&Commando::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_COMMANDO_SKILL4_1, std::bind(&Commando::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_COMMANDO_SKILL4_2, std::bind(&Commando::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_WALK, std::bind(&Commando::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_JUMP, std::bind(&Commando::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_CLIMB, std::bind(&Commando::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_DEATH, std::bind(&Commando::FrameAnimation, this, std::placeholders::_1));

	// 프레임 종료마다 실행할 함수
	Renderer_->AnimationBindEnd(PLAYER_ANIM_IDLE, std::bind(&Commando::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_SKILL1, std::bind(&Commando::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_SKILL2, std::bind(&Commando::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_SKILL3, std::bind(&Commando::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_COMMANDO_SKILL4_1, std::bind(&Commando::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_COMMANDO_SKILL4_2, std::bind(&Commando::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_WALK, std::bind(&Commando::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_JUMP, std::bind(&Commando::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_DEATH, std::bind(&Commando::EndAnimation, this, std::placeholders::_1));

	// 초기 애니메이션 전환
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_IDLE);
	Renderer_->SetScaleModeImage();
}

void Commando::StateInit()
{
	StateManager_.CreateStateMember(PLAYER_STATE_IDLE, std::bind(&Commando::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		                                             , std::bind(&Commando::IdleStart, this, std::placeholders::_1)
		                                             , std::bind(&Commando::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_MOVE, std::bind(&Commando::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
											   		 , std::bind(&Commando::MoveStart, this, std::placeholders::_1)
													 , std::bind(&Commando::MoveEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL1, std::bind(&Commando::Skill1Update, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Commando::Skill1Start, this, std::placeholders::_1)
													 , std::bind(&Commando::Skill1End, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL2, std::bind(&Commando::Skill2Update, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Commando::Skill2Start, this, std::placeholders::_1)
													 , std::bind(&Commando::Skill2End, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL3, std::bind(&Commando::Skill3Update, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Commando::Skill3Start, this, std::placeholders::_1)
													 , std::bind(&Commando::Skill3End, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL4, std::bind(&Commando::Skill4Update, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Commando::Skill4Start, this, std::placeholders::_1)
													 , std::bind(&Commando::Skill4End, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_CLIMB, std::bind(&Commando::ClimbUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Commando::ClimbStart, this, std::placeholders::_1)
													 , std::bind(&Commando::ClimbEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_DEATH, std::bind(&Commando::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Commando::DeathStart, this, std::placeholders::_1)
													 , std::bind(&Commando::DeathEnd, this, std::placeholders::_1));

	// 초기 스테이트전환
	StateManager_.ChangeState(PLAYER_STATE_IDLE);
}

void Commando::EndAnimation(const FrameAnimation_DESC& _Info)
{
	// 스테이트 전환
	StateManager_.ChangeState(PLAYER_STATE_IDLE);
}

void Commando::FrameAnimation(const FrameAnimation_DESC& _Info)
{
	// 디버그용
	// 애니메이션의 각 프레임마다 크기를 출력
	//std::string x = std::to_string( Renderer_->GetTransform().GetLocalScale().x);
	//std::string y = std::to_string(Renderer_->GetTransform().GetLocalScale().y);

	//GameEngineDebug::OutPutString(Renderer_->GetCurTexture()->GetNameCopy() + "  " + StateManager_.GetCurStateStateName() + " >> x : " + x + " , y : " + y);
}