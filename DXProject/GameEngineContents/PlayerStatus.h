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

	// ���������� ����� �������ͽ�(TrueStatus)
	static float Speed_;
	static float Damage_;
	static float AtkSpeed_;
	static int Hp_;
	static int CritChance_;

	// ����� �� �������ͽ�
	static float BaseSpeed_;
	static float BaseDamage_;
	static float BaseAtkSpeed_;
	static int BaseHp_;
	static int BaseCritChance_;

	// ������ ����� �������ͽ�
	static float BuffedSpeed_;
	static float BuffedDamage_;
	static float BuffedAtkSpeed_;
	static int BuffedHp_;
	static int BuffedCritChance_;

	// �����Ӹ��� ��� �� �������ͽ� -> FrameItem�� ������Ʈ ���� �Ŀ� TrueStatus�� ��������
	static float FrameSpeed_;
	static float FrameDamage_;
	static float FrameAtkSpeed_;
	static int FrameHp_;
	static int FrameCritChance_;
};


/*
Base Status -> ����� �⺻�� �� ��
Buffed Status -> ���� �������� ȿ���� ���� �� (������ ȹ��� or ������ �Ҷ����� ����)

Frame Statue -> �� �����Ӹ��� ���¸� Ȯ���Ͽ� ȿ���� �ްų� ���� ���� �� -> ??????????????



True Status -> ���������� ����� ��
*/