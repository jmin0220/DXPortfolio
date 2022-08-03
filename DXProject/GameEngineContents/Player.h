#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "UnitFsm.h"

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

	void SetColMapInfo(GameEngineTexture* _ColMap)
	{
		ColMap_ = _ColMap;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	// 초기화 관련 함수
	void KeyInit();
	virtual void AnimationInit() {};
	virtual void StateInit() {};

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

	// FSM 관련 함수
	GameEngineStateManager StateManager_;

	// 상속해줄 FSM함수
	// 캐릭터마다 다른기능일수도
	// 함수포인터를 사용하기 위해서
#pragma region Virtual FSM

	virtual void IdleStart(const StateInfo& _Info) {};
	virtual void MoveStart(const StateInfo& _Info) {};
	virtual void Skill1Start(const StateInfo& _Info) {};
	virtual void Skill2Start(const StateInfo& _Info) {};
	virtual void Skill3Start(const StateInfo& _Info) {};
	virtual void Skill4Start(const StateInfo& _Info) {};
	virtual void ClimbStart(const StateInfo& _Info) {};
	virtual void DeathStart(const StateInfo& _Info) {};

	virtual void IdleUpdate(float _DeltaTime, const StateInfo& _Info) {};
	virtual void MoveUpdate(float _DeltaTime, const StateInfo& _Info) {};
	virtual void Skill1Update(float _DeltaTime, const StateInfo& _Info) {};
	virtual void Skill2Update(float _DeltaTime, const StateInfo& _Info) {};
	virtual void Skill3Update(float _DeltaTime, const StateInfo& _Info) {};
	virtual void Skill4Update(float _DeltaTime, const StateInfo& _Info) {};
	virtual void ClimbUpdate(float _DeltaTime, const StateInfo& _Info) {};
	virtual void DeathUpdate(float _DeltaTime, const StateInfo& _Info) {};

	virtual void IdleEnd(const StateInfo& _Info) {};
	virtual void MoveEnd(const StateInfo& _Info) {};
	virtual void Skill1End(const StateInfo& _Info) {};
	virtual void Skill2End(const StateInfo& _Info) {};
	virtual void Skill3End(const StateInfo& _Info) {};
	virtual void Skill4End(const StateInfo& _Info) {};
	virtual void ClimbEnd(const StateInfo& _Info) {};
	virtual void DeathEnd(const StateInfo& _Info) {};
#pragma endregion

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
	float DeltaTime_;
	
	// 속도 관련
	float Speed_;
	float JumpSpeed_;
	float FallSpeed_;

	// 애니메이션 프레임간의 시간
	float FrameAnimDelay_;

	// 땅에 닿아있음 판정
	bool IsGround_;
	// 줄에 타고 있는지 판정
	bool IsClimb_;

	// 방향 관련
	float4 MoveDir_;
	// 색깔 체크용 공통 포지션
	float4 ColorCheckPos_;

	// 충돌용 맵 정보
	GameEngineTexture* ColMap_;

	// 스킬창등의 UI
	HUD* HUD_;

};

