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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	// 초기화 함수
	virtual void AnimationInit() {};
	virtual void StateInit() {};

	// 업데이트 함수
	void CheckNegativeX();
	void JumpUpdate();
	void GroundFallCheck();
	bool GroundRightCheck();
	bool GroundLeftCheck();

	void MonsterJump();

	// FSM 매니저
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

	// 속도 관련
	float Speed_;
	float JumpSpeed_;
	float FallSpeed_;

	// 애니메이션 프레임간의 시간
	float FrameAnimDelay_;

	// 땅에 닿아있음 판정
	bool IsGround_;
	// 스테이트에서 넣어줄 점프플래그
	bool IsJump_;

	// 방향 관련
	float4 MoveDir_;
	// 색깔 체크용 공통 포지션
	float4 ColorCheckPos_;

	// 충돌용 맵 정보
	GameEngineTexture* ColMap_;
};

