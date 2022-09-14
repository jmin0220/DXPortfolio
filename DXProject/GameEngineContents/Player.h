#pragma once
#include "Item.h"

enum class BulletType
{
	Bullet,
	PiercingBullet,
};

// 설명 :
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

	// 초기화 관련 함수
	void KeyInit();
	virtual void AnimationInit() {};
	virtual void StateInit() {};
	void PlayerBuffStatusInit();
	void PlayerCommonInit();

	// 키입력 관련 함수
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


	// 업데이트 함수
	void CheckNegativeX();
	void CameraUpdate();
	void JumpUpdate();
	void GroundFallCheck();
	bool GroundRightCheck();
	bool GroundLeftCheck();

	void PlayerJump();
	void PlayerLevelUp();
	void PlayerUseItem();

	// FSM 매니저
	GameEngineStateManager StateManager_;

	// 공통화된 기능
	// 상속받은 클래스에서 공통된 기능으로 호출하도록
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

	// 기능
	bool CanClimb(int _CheckPosFlg);

	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;
	float DeltaTime_;

	// 레벨업 이펙트
	GameEngineTextureRenderer* LevelUpEffectRenderer_;

	// 난이도 체크용 플레이타임 타이머
	static float PlayTimeTimer_;

	// 애니메이션 프레임간의 시간
	float FrameAnimDelay_;

	// 땅에 닿아있음 판정
	bool IsGround_;
	// 줄에 타고 있는지 판정
	bool IsClimb_;

	// 아이템이 추가되었다
	// AddItem함수에서 사용해야 해서 static으로 선언됨.
	static bool AddItemFlg_;
	static bool AddUseItemFlg_;

	// 방향 관련
	float4 MoveDir_;
	// 색깔 체크용 공통 포지션
	float4 ColorCheckPos_;

	// 충돌용 맵 정보
	GameEngineTexture* ColMap_;

	// 스킬창등의 UI
	HUD* HUD_;

	// 기반이 될 플레이어 스테이터스
	// 속도 관련
	float Speed_;
	float JumpSpeed_;
	float FallSpeed_;

	static int Hp_;			// 현재 HP
	static int MaxHp_;		// HP 최대치
	float LvPerHp_;			// 레벨당 증가할HP
	float HpRegen_;			// HP 회복률
	float LvPerHpRegen_;	// 레벨당 증가할 HP회복률

	int Damage_;
	int LvPerDamage_;
	float AtkSpeed_;	// 공격속도
	float AtkTimer_;	// 공격간의 딜레이 측정용 타이머

	static int Lv_;
	static int Gold_;
	static int Exp_;
	static int MaxExp_;

	// 크리티컬찬스 (MAX = 100)
	int CritChance_;

	void CreateBullet(int _CurFrame, int _LastFrame, BulletType _BulletType, float _DmgRatio = 1.0f, float _PiercingLength = 1.0f);
};

