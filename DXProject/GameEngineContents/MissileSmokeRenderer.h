#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>

// Ό³Έν :
class MissileSmokeRenderer : public GameEngineDefaultRenderer
{
public:
	// constrcuter destructer
	MissileSmokeRenderer();
	~MissileSmokeRenderer();

	// delete Function
	MissileSmokeRenderer(const MissileSmokeRenderer& _Other) = delete;
	MissileSmokeRenderer(MissileSmokeRenderer&& _Other) noexcept = delete;
	MissileSmokeRenderer& operator=(const MissileSmokeRenderer& _Other) = delete;
	MissileSmokeRenderer& operator=(MissileSmokeRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderPos_;
	void SetSingleColorRendererSetting();

	PixelData PixelDataInst;
	AtlasData AtlasDataInst;
};

