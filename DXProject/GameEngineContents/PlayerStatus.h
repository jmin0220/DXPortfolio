#pragma once

struct PlayerStatus
{
public:
	// 최종적으로 적용될 스테이터스
	static float Speed_;
	static float Damage_;
	static float AtkSpeed_;
	static int Hp_;
	static int CritChance_;

	// 기반이 될 스테이터스
	static float BaseSpeed_;
	static float BaseDamage_;
	static float BaseAtkSpeed_;
	static int BaseHp_;
	static int BaseCritChance_;
};