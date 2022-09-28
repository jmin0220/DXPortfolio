#include "PreCompile.h"
#include "MissileSmokeRenderer.h"

MissileSmokeRenderer::MissileSmokeRenderer() 
{
}

MissileSmokeRenderer::~MissileSmokeRenderer() 
{
}

void MissileSmokeRenderer::Start()
{
	PushRendererToMainCamera();

	SetSingleColorRendererSetting();

	PixelDataInst.MulColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	ShaderResources.SetTexture("Tex", "Empty.png");

	RenderPos_ = this->GetTransform().GetWorldPosition();
	this->GetTransform().SetWorldScale({ 6.0f, 6.0f, 1.0f });
}

void MissileSmokeRenderer::Update(float _DeltaTime)
{
	this->GetTransform().SetWorldPosition(RenderPos_);

	// r = 226, g = 156, b = 84
	if (GetAccTime() <= 0.5f)
	{
		PixelDataInst.MulColor.r = float4::LerpLimit(1.0f, 226.0f / 255.0f, GetAccTime() * 2).r;
		PixelDataInst.MulColor.g = float4::LerpLimit(1.0f, 156.0f / 255.0f, GetAccTime() * 2).g;
		PixelDataInst.MulColor.b = float4::LerpLimit(1.0f, 84.0f / 255.0f, GetAccTime() * 2).b;
	}
	else
	{
		PixelDataInst.MulColor.a -= GameEngineTime::GetDeltaTime() * 2;

		if (PixelDataInst.MulColor.a < 0.0f)
		{
			this->Death();
		}
	}
}

void MissileSmokeRenderer::SetSingleColorRendererSetting()
{
	// 파이프라인 세팅
	SetPipeLine("TextureAtlas");

	AtlasDataInst.FrameData.PosX = 0.0f;
	AtlasDataInst.FrameData.PosY = 0.0f;
	AtlasDataInst.FrameData.SizeX = 1.0f;
	AtlasDataInst.FrameData.SizeY = 1.0f;
	AtlasDataInst.PivotPos = float4::ZERO;

	// 상수버퍼 링크
	ShaderResources.SetConstantBufferLink("AtlasData", AtlasDataInst);
	ShaderResources.SetConstantBufferLink("PixelData", PixelDataInst);
}