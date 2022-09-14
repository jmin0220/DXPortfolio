#pragma once

struct PlayerStatus
{
public:
	static void ResetStatus();
	static void ResetFrameStatus();
	static void AddFrameStatusToTrueStatus();

	static int GetiDamage()
	{
		return static_cast<int>(Damage_);
	}

	// 최종적으로 적용될 스테이터스(TrueStatus)
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

	// 버프가 적용될 스테이터스
	static float BuffedSpeed_;
	static float BuffedDamage_;
	static float BuffedAtkSpeed_;
	static int BuffedHp_;
	static int BuffedCritChance_;

	// 프레임마다 계산 될 스테이터스 -> FrameItem의 업데이트 종료 후에 TrueStatus에 더해질것
	static float FrameSpeed_;
	static float FrameDamage_;
	static float FrameAtkSpeed_;
	static int FrameHp_;
	static int FrameCritChance_;
};


/*
Base Status -> 계산의 기본이 될 값
Buffed Status -> 버프 아이템의 효과를 받은 값 (아이템 획득시 or 레벨업 할때마다 갱신)

Frame Statue -> 매 프레임마다 상태를 확인하여 효과를 받거나 받지 않을 값 -> ??????????????



True Status -> 최종적으로 적용될 값
*/