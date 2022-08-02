#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"

// Ό³Έν :
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend class GameEngineLevel;
	friend class GameEngineCamera;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// float4x4 ViewPort;
	void ChangeCamera(CAMERAORDER _Order);

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

	CAMERAORDER CameraOrder;

	void PushRendererToMainCamera();
	void PushRendererToUICamera();

private:
	virtual void Render(float _DeltaTime) = 0;

};

