#include "PreCompile.h"
#include "Bandit.h"
#include "Bullet.h"
#include <GameEngineBase/GameEngineRandom.h>

Bandit::Bandit()
{
	// https://riskofrain.fandom.com/wiki/Bandit
	Hp_ = 115;
	MaxHp_ = 115;
	LvPerHp_ = 25;

	HpRegen_ = 0.6;
	LvPerHpRegen_ = 0.12;

	Damage_ = 12;
	LvPerDamage_ = 4;

	AtkSpeed_ = 0.7;
}

Bandit::~Bandit() 
{
}

void Bandit::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	// 애니메이션 생성
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_IDLE, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_IDLE, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_SKILL1, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_SKILL1, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_SKILL2, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_SKILL2, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_SKILL3, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_SKILL3, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_SKILL4, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_SKILL4, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_WALK, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_WALK, FrameAnimDelay_, true));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_JUMP, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_JUMP, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_CLIMB, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_CLIMB, FrameAnimDelay_, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_DEATH, FrameAnimation_DESC(TEX_PLAYER_ANIM_BANDIT_DEATH, FrameAnimDelay_, false));


	// 프레임 시작할때 실행할 함수
	Renderer_->AnimationBindStart(PLAYER_ANIM_SKILL2, [=](const FrameAnimation_DESC& _Info)
		{
			// 수류탄 생성
			CreateBullet(0, 0, BulletType::PiercingBullet, 2.5f, 800.0f);
		});
		
	Renderer_->AnimationBindFrame(PLAYER_ANIM_SKILL1, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 1 || _Info.CurFrame == 3)
			{
				CreateBullet(_Info.CurFrame, 3, BulletType::Bullet, 0.6f);
			}
		});

	Renderer_->AnimationBindFrame(PLAYER_ANIM_SKILL4, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 1 || _Info.CurFrame == 3)
			{
				CreateBullet(_Info.CurFrame, 3, BulletType::Bullet, 0.6f);
			}
		});

	Renderer_->AnimationBindFrame(PLAYER_ANIM_IDLE, std::bind(&Bandit::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_SKILL1, std::bind(&Bandit::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_SKILL2, std::bind(&Bandit::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_SKILL3, std::bind(&Bandit::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_SKILL4, std::bind(&Bandit::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_WALK, std::bind(&Bandit::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_JUMP, std::bind(&Bandit::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_CLIMB, std::bind(&Bandit::FrameAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_DEATH, std::bind(&Bandit::FrameAnimation, this, std::placeholders::_1));


	// 프레임 종료마다 실행할 함수
	Renderer_->AnimationBindEnd(PLAYER_ANIM_IDLE, std::bind(&Bandit::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_SKILL1, std::bind(&Bandit::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_SKILL2, std::bind(&Bandit::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_SKILL3, std::bind(&Bandit::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_SKILL4, std::bind(&Bandit::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_WALK, std::bind(&Bandit::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_JUMP, std::bind(&Bandit::EndAnimation, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd(PLAYER_ANIM_DEATH, std::bind(&Bandit::EndAnimation, this, std::placeholders::_1));


	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_IDLE);
	Renderer_->SetScaleModeImage();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::Player);
	Collision_->GetTransform().SetWorldScale({ 16.0f, 22.0f, 1.0f });
}

void Bandit::StateInit()
{
	StateManager_.CreateStateMember(PLAYER_STATE_IDLE, std::bind(&Bandit::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Bandit::IdleStart, this, std::placeholders::_1)
													 , std::bind(&Bandit::IdleEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_MOVE, std::bind(&Bandit::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Bandit::MoveStart, this, std::placeholders::_1)
													 , std::bind(&Bandit::MoveEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL1, std::bind(&Bandit::Skill1Update, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Bandit::Skill1Start, this, std::placeholders::_1)
													 , std::bind(&Bandit::Skill1End, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL2, std::bind(&Bandit::Skill2Update, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Bandit::Skill2Start, this, std::placeholders::_1)
													 , std::bind(&Bandit::Skill2End, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL3, std::bind(&Bandit::Skill3Update, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Bandit::Skill3Start, this, std::placeholders::_1)
													 , std::bind(&Bandit::Skill3End, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL4, std::bind(&Bandit::Skill4Update, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Bandit::Skill4Start, this, std::placeholders::_1)
													 , std::bind(&Bandit::Skill4End, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_CLIMB, std::bind(&Bandit::ClimbUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Bandit::ClimbStart, this, std::placeholders::_1)
													 , std::bind(&Bandit::ClimbEnd, this, std::placeholders::_1));
	StateManager_.CreateStateMember(PLAYER_STATE_DEATH, std::bind(&Bandit::DeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
													 , std::bind(&Bandit::DeathStart, this, std::placeholders::_1)
													 , std::bind(&Bandit::DeathEnd, this, std::placeholders::_1));


	StateManager_.ChangeState(PLAYER_STATE_IDLE);
}

void Bandit::EndAnimation(const FrameAnimation_DESC& _Info)
{
	// 스테이트 전환
	StateManager_.ChangeState(PLAYER_STATE_IDLE);
}

void Bandit::FrameAnimation(const FrameAnimation_DESC& _Info)
{
}