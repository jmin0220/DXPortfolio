#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>

// Ό³Έν :
class SingleColorRenderer : public GameEngineDefaultRenderer
{
public:
	// constrcuter destructer
	SingleColorRenderer();
	~SingleColorRenderer();

	// delete Function
	SingleColorRenderer(const SingleColorRenderer& _Other) = delete;
	SingleColorRenderer(SingleColorRenderer&& _Other) noexcept = delete;
	SingleColorRenderer& operator=(const SingleColorRenderer& _Other) = delete;
	SingleColorRenderer& operator=(SingleColorRenderer&& _Other) noexcept = delete;

	void SetColor(float4 _Color);

	void SetPivot(PIVOTMODE _Mode);

protected:
	void Start() override;

private:
	void SetSingleColorRendererSetting();
	void SetTexture(const std::string& _Name);

	PixelData PixelDataInst;
	AtlasData AtlasDataInst;

};

