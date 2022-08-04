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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	// �ʱ�ȭ �Լ�
	virtual void AnimationInit() {};
	virtual void StateInit() {};

	// ������Ʈ �Լ�
	void CheckNegativeX();
	void JumpUpdate();
	void GroundFallCheck();
	bool GroundRightCheck();
	bool GroundLeftCheck();

	void MonsterJump();

	// FSM �Ŵ���
	GameEngineStateManager StateManager_;

#pragma region Common FSM
	void CommonIdleStart(std::string _AnimName);
	void CommonMoveStart(std::string _AnimName);
	void CommonAttackStart(std::string _AnimName);
	void CommonChaseStart(std::string _AnimName);
	void CommonDeathStart(std::string _AnimName);
#pragma endregion


	GameEngineTextureRenderer* Renderer_;
	float DeltaTime_;

	// �ӵ� ����
	float Speed_;
	float JumpSpeed_;
	float FallSpeed_;

	// �ִϸ��̼� �����Ӱ��� �ð�
	float FrameAnimDelay_;

	// ���� ������� ����
	bool IsGround_;
	// ������Ʈ���� �־��� �����÷���
	bool IsJump_;

	// ���� ����
	float4 MoveDir_;
	// ���� üũ�� ���� ������
	float4 ColorCheckPos_;

	// �浹�� �� ����
	GameEngineTexture* ColMap_;
};

