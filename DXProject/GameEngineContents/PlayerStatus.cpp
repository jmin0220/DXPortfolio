#include "PreCompile.h"

void PlayerStatus::ResetStatus()
{
	Speed_	    = BaseSpeed_;
	Damage_     = BaseDamage_;
	AtkSpeed_   = BaseAtkSpeed_;
	Hp_         = BaseHp_;
	CritChance_ = BaseCritChance_;
}
