#pragma once

// 설명 :
class Drone : public GameEngineActor
{
public:
	// constrcuter destructer
	Drone();
	~Drone();

	// delete Function
	Drone(const Drone& _Other) = delete;
	Drone(Drone&& _Other) noexcept = delete;
	Drone& operator=(const Drone& _Other) = delete;
	Drone& operator=(Drone&& _Other) noexcept = delete;

	static inline void SetPlayerPosDir(float4 _Pos, float4 _Dir)
	{
		PlayerPos_ = _Pos;
		PlayerDir_ = _Dir;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	virtual void AnimInit() {}

	GameEngineTextureRenderer* Renderer_;

	// 플레이어의 위치정보
	static float4 PlayerPos_;
	static float4 PlayerDir_;

	float AtkTimer_;
	float Speed_;

private:
	float MovedYPos_ = 0.0f;
	float Ypos_ = 8.0f;
	void Move(float _DeltaTime);

	void CheckNegativeX();
};

