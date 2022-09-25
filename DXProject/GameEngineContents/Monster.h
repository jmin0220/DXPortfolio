#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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

	// �ʱ�ȭ �Լ�
	virtual void AnimationInit() {};
	virtual void StateInit() {};
	virtual void CollisionInit() {};

	// ������Ʈ �Լ�
	void CheckNegativeX();
	void JumpUpdate();
	void GroundFallCheck();
	bool GroundRightCheck();
	bool GroundLeftCheck();
	void ChaseFlgUpdate();

	void MonsterJump();
	
	void DeathSwitch();

	bool IsFallCheck_;

	// FSM �Ŵ���
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

	// �ӵ� ����
	float Speed_;
	float JumpSpeed_;
	float FallSpeed_;
	float AtkSpeed_;

	// �ִϸ��̼� �����Ӱ��� �ð�
	float FrameAnimDelay_;
	// ���ݰ��� Ÿ�̸�
	float AtkTimer_;

	// ���� ������� ����
	bool IsGround_;
	// ������Ʈ���� �־��� �����÷���
	bool IsJump_;
	// ����ó��(��ü����)
	bool IsMonsterDeath_;

	// ���� ����
	float4 MoveDir_;
	// ���� üũ�� ���� ������
	float4 ColorCheckPos_;
	// �÷��̾��� ��ġ
	float4 PlayerPos_;

	// �浹�� �� ����
	GameEngineTexture* ColMap_;

	// FSM��ȯ�� ��ġ��
	float ToMoveGauge_;
	bool MoveDirFlg_;	// 0 ->Left 1 -> Right
	// Move->Idle ������Ʈ ����ġ
	float ToIdleGauge_;
	// ��ô���� ��ġ
	bool ChaseFlg_;
	float ChaseRange_;

	// ���� �������ͽ�
	int MonsterHp_;
	int Damage_;

	// TODO::������ ����� �ð��� ���� ����
	int Lv_;

	// ���Ͱ� �׾����� ����� ���� ����ġ
	int Gold_;
	int Exp_;
};

