#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	inline void SetColMapInfo(GameEngineTexture* _ColMap)
	{
		ColMap_ = _ColMap;
	}

	inline void SetPlayerPos(float4 _Pos)
	{
		PlayerPos_ = _Pos;
	}

	virtual inline void HitFunction(int _Damage)
	{
		MonsterHp_ -= _Damage;

		if (MonsterHp_ < 0)
		{
			MonsterHp_ = 0;
		}
	}

	inline bool GetMonsterDeath() const
	{
		return IsMonsterDeath_;
	}

	inline void ChangeStateToHitted()
	{
		//StateManager_.ChangeState(MONSTER_FSM_HITTED);
	}

	inline int GetMonsterGold() const
	{
		return Gold_;
	}

	inline int GetMonsterExp() const
	{
		return Exp_;
	}

	inline int GetMonsterHp() const
	{
		return MonsterHp_;
	}

	inline void SetJumpSpeedByBouncer()
	{
		JumpSpeed_ = BOUNCER_JUMP_SPEED;
	}

	inline std::string GetCurState()
	{
		return StateManager_.GetCurStateStateName();
	}

	inline void ForcedSetStateIdle()
	{
		StateManager_.ChangeState(MONSTER_FSM_IDLE);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	// 초기화 함수
	virtual void AnimationInit() {};
	virtual void StateInit() {};
	virtual void CollisionInit() {};

	// 업데이트 함수
	void CheckNegativeX();
	void JumpUpdate();
	void GroundFallCheck();
	bool GroundRightCheck();
	bool GroundLeftCheck();
	void ChaseFlgUpdate();

	void MonsterJump();
	
	void DeathSwitch();

	bool IsFallCheck_;

	// FSM 매니저
	GameEngineStateManager StateManager_;

#pragma region Common FSM
	void CommonIdleStart(std::string _AnimName);
	void CommonMoveStart(std::string _AnimName);
	void CommonAttackStart(std::string _AnimName);
	void CommonChaseStart(std::string _AnimName);
	void CommonDeathStart(std::string _AnimName);

	void CommonIdleUpdate();
	void CommonMoveUpdate();
	void CommonChaseUpdate(float _ChaseLength = 0.0f);
#pragma endregion

	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;
	float DeltaTime_;

	// 속도 관련
	float Speed_;
	float JumpSpeed_;
	float FallSpeed_;
	float AtkSpeed_;

	// 애니메이션 프레임간의 시간
	float FrameAnimDelay_;
	// 공격간의 타이머
	float AtkTimer_;

	// 땅에 닿아있음 판정
	bool IsGround_;
	// 스테이트에서 넣어줄 점프플래그
	bool IsJump_;
	// 죽음처리(시체남음)
	bool IsMonsterDeath_;

	// 방향 관련
	float4 MoveDir_;
	// 색깔 체크용 공통 포지션
	float4 ColorCheckPos_;
	// 플레이어의 위치
	float4 PlayerPos_;

	// 충돌용 맵 정보
	GameEngineTexture* ColMap_;

	// FSM전환용 수치값
	float ToMoveGauge_;
	bool MoveDirFlg_;	// 0 ->Left 1 -> Right
	// Move->Idle 스테이트 변경치
	float ToIdleGauge_;
	// 추척관련 수치
	bool ChaseFlg_;
	float ChaseRange_;

	// 몬스터 스테이터스
	int MonsterHp_;
	int Damage_;

	// TODO::레벨은 경과한 시간에 따라서 증가
	int Lv_;

	// 몬스터가 죽었을때 드랍할 골드와 경험치
	int Gold_;
	int Exp_;
};

