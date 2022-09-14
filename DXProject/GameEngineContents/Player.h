#pragma once
#include "Item.h"

enum class BulletType
{
	Bullet,
	PiercingBullet,
};

// ���� :
class HUD;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	static inline float GetPlayTimeTimer()
	{
		return PlayTimeTimer_;
	}

	inline void SetColMapInfo(GameEngineTexture* _ColMap)
	{
		ColMap_ = _ColMap;
	}

	static inline void AddGold(int _Gold)
	{
		Gold_ += _Gold;
	}

	static inline void AddExp(int _Exp)
	{
		Exp_ += _Exp;
	}

	static inline void AddNowHp(int _Hp)
	{
		Hp_ += _Hp;
		
		if (Hp_ >= MaxHp_)
		{
			Hp_ = MaxHp_;
		}
	}

	static inline int GetPlayerLv()
	{
		return Lv_;
	}

	static inline int GetPlayerHp()
	{
		return Hp_;
	}

	static inline int GetPlayerMaxHp()
	{
		return MaxHp_;
	}

	static inline int GetPlayerGold()
	{
		return Gold_;
	}

	static inline int GetPlayerExp()
	{
		return Exp_;
	}

	static inline int GetPlayerMaxExp()
	{
		return MaxExp_;
	}

	inline bool GetIsGroundFlg()
	{
		return IsGround_;
	}

	inline std::string GetState()
	{
		return StateManager_.GetCurStateStateName();
	}

	inline void SetJumpSpeedByBouncer()
	{
		JumpSpeed_ = BOUNCER_JUMP_SPEED;
	}

	static std::vector<Item*> ItemVector_;

	static Item* UseItem_;

	void AddItem(Item* _Item);

	inline void AddUseItem()
	{
		AddUseItemFlg_ = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	// �ʱ�ȭ ���� �Լ�
	void KeyInit();
	virtual void AnimationInit() {};
	virtual void StateInit() {};
	void PlayerBuffStatusInit();
	void PlayerCommonInit();

	// Ű�Է� ���� �Լ�
#pragma region KeyInput

	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();

	bool IsJumpKeyDown();
	bool IsJumpKeyPress();
	bool IsJumpKeyUp();

	bool IsUpKeyDown();
	bool IsUpKeyPress();
	bool IsUpKeyUp();

	bool IsDownKeyDown();
	bool IsDownKeyPress();
	bool IsDownKeyUp();

	bool IsSkill1KeyDown();
	bool IsSkill1KeyPress();
	bool IsSkill1KeyUp();

	bool IsSkill2KeyDown();
	bool IsSkill2KeyPress();
	bool IsSkill2KeyUp();

	bool IsSkill3KeyDown();
	bool IsSkill3KeyPress();
	bool IsSkill3KeyUp();

	bool IsSkill4KeyDown();
	bool IsSkill4KeyPress();
	bool IsSkill4KeyUp();
#pragma endregion


	// ������Ʈ �Լ�
	void CheckNegativeX();
	void CameraUpdate();
	void JumpUpdate();
	void GroundFallCheck();
	bool GroundRightCheck();
	bool GroundLeftCheck();

	void PlayerJump();
	void PlayerLevelUp();
	void PlayerUseItem();

	// FSM �Ŵ���
	GameEngineStateManager StateManager_;

	// ����ȭ�� ���
	// ��ӹ��� Ŭ�������� ����� ������� ȣ���ϵ���
#pragma region Common FSM

	void CommonIdleStart();
	void CommonMoveStart();
	void CommonSkill1Start();
	void CommonSkill2Start();
	void CommonSkill3Start();
	void CommonSkill4Start();
	void CommonClimbStart();
	void CommonDeathStart();

	void CommonIdleUpdate();
	void CommonMoveUpdate();
	void CommonSkill1Update();
	void CommonSkill2Update();
	void CommonSkill3Update();
	void CommonSkill4Update();
	void CommonClimbUpdate();
	void CommonDeathUpdate();

	void CommonIdleEnd();
	void CommonMoveEnd();
	void CommonSkill1End();
	void CommonSkill2End();
	void CommonSkill3End();
	void CommonSkill4End();
	void CommonClimbEnd();
	void CommonDeathEnd();
#pragma endregion

	// ���
	bool CanClimb(int _CheckPosFlg);

	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;
	float DeltaTime_;

	// ������ ����Ʈ
	GameEngineTextureRenderer* LevelUpEffectRenderer_;

	// ���̵� üũ�� �÷���Ÿ�� Ÿ�̸�
	static float PlayTimeTimer_;

	// �ִϸ��̼� �����Ӱ��� �ð�
	float FrameAnimDelay_;

	// ���� ������� ����
	bool IsGround_;
	// �ٿ� Ÿ�� �ִ��� ����
	bool IsClimb_;

	// �������� �߰��Ǿ���
	// AddItem�Լ����� ����ؾ� �ؼ� static���� �����.
	static bool AddItemFlg_;
	static bool AddUseItemFlg_;

	// ���� ����
	float4 MoveDir_;
	// ���� üũ�� ���� ������
	float4 ColorCheckPos_;

	// �浹�� �� ����
	GameEngineTexture* ColMap_;

	// ��ųâ���� UI
	HUD* HUD_;

	// ����� �� �÷��̾� �������ͽ�
	// �ӵ� ����
	float Speed_;
	float JumpSpeed_;
	float FallSpeed_;

	static int Hp_;			// ���� HP
	static int MaxHp_;		// HP �ִ�ġ
	float LvPerHp_;			// ������ ������HP
	float HpRegen_;			// HP ȸ����
	float LvPerHpRegen_;	// ������ ������ HPȸ����

	int Damage_;
	int LvPerDamage_;
	float AtkSpeed_;	// ���ݼӵ�
	float AtkTimer_;	// ���ݰ��� ������ ������ Ÿ�̸�

	static int Lv_;
	static int Gold_;
	static int Exp_;
	static int MaxExp_;

	// ũ��Ƽ������ (MAX = 100)
	int CritChance_;

	void CreateBullet(int _CurFrame, int _LastFrame, BulletType _BulletType, float _DmgRatio = 1.0f, float _PiercingLength = 1.0f);
};

