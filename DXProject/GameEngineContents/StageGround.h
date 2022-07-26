#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class StageGround : public GameEngineActor
{
public:
	// constrcuter destructer
	StageGround();
	~StageGround();

	// delete Function
	StageGround(const StageGround& _Other) = delete;
	StageGround(StageGround&& _Other) noexcept = delete;
	StageGround& operator=(const StageGround& _Other) = delete;
	StageGround& operator=(StageGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
};

