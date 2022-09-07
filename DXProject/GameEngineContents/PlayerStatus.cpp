#include "PreCompile.h"

float PlayerStatus::Speed_ = 0.0f;
float PlayerStatus::Damage_ = 0.0f;
float PlayerStatus::AtkSpeed_ = 0.0f;
int PlayerStatus::Hp_ = 0;
int PlayerStatus::CritChance_ = 0;

float PlayerStatus::BaseSpeed_ = 0.0f;
float PlayerStatus::BaseDamage_ = 0.0f;
float PlayerStatus::BaseAtkSpeed_ = 0.0f;
int PlayerStatus::BaseHp_ = 0;
int PlayerStatus::BaseCritChance_ = 0;

float PlayerStatus::BuffedSpeed_ =0.0f;
float PlayerStatus::BuffedDamage_ =0.0f;
float PlayerStatus::BuffedAtkSpeed_ =0.0f;
int PlayerStatus::BuffedHp_	=0;
int PlayerStatus::BuffedCritChance_ =0;

float PlayerStatus::FrameSpeed_ = 0.0f;
float PlayerStatus::FrameDamage_ = 0.0f;
float PlayerStatus::FrameAtkSpeed_ = 0.0f;
int PlayerStatus::FrameHp_ = 0;
int PlayerStatus::FrameCritChance_ = 0;

// TrueStatus를 BaseStatus로 초기화
void PlayerStatus::ResetStatus()
{
	Speed_	    = BaseSpeed_;
	Damage_     = BaseDamage_;
	AtkSpeed_   = BaseAtkSpeed_;
	Hp_         = BaseHp_;
	CritChance_ = BaseCritChance_;
}

// FrameStatus를 초기화
void PlayerStatus::ResetFrameStatus()
{
	// 스탯을 되돌리고
	Speed_		= BaseSpeed_		+ BuffedSpeed_;
	Damage_		= BaseDamage_		+ BuffedDamage_;
	AtkSpeed_	= BaseAtkSpeed_		+ BuffedAtkSpeed_;
	Hp_			= BaseHp_			+ BuffedHp_;
	CritChance_ = BaseCritChance_	+ BuffedCritChance_;

	// 버프량도 초기화
	FrameSpeed_		 = 0.0f;
	FrameDamage_	 = 0.0f;
	FrameAtkSpeed_	 = 0.0f;
	FrameHp_		 = 0;
	FrameCritChance_ = 0;
}

// BaseStatus += FrameStatus
void PlayerStatus::AddFrameStatusToTrueStatus()
{
	Speed_		+= FrameSpeed_;
	Damage_		+= FrameDamage_;
	AtkSpeed_	+= FrameAtkSpeed_;
	Hp_			+= FrameHp_;
	CritChance_ += FrameCritChance_;
}
