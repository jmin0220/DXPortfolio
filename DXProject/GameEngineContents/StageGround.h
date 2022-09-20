#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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

	inline GameEngineTextureRenderer* GetStage()
	{
		return Renderer_;
	}

	inline GameEngineTextureRenderer* GetColStage()
	{
		return ColRenderer_;
	}

	void SetStage1Map();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineTextureRenderer* ColRenderer_;

	GameEngineTextureRenderer* BackGroundRenderer_;
};

