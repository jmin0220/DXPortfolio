#include "PreCompile.h"
#include "SingleColorRenderer.h"

SingleColorRenderer::SingleColorRenderer() 
{
}

SingleColorRenderer::~SingleColorRenderer() 
{
}


void SingleColorRenderer::SetTexture(const std::string& _Name)
{
	ShaderResources.SetTexture("Tex", _Name);
}

void SingleColorRenderer::SetColor(float4 _Color)
{
	PixelDataInst.MulColor.r = _Color.r;
	PixelDataInst.MulColor.g = _Color.g;
	PixelDataInst.MulColor.b = _Color.b;
	PixelDataInst.MulColor.a = _Color.a;
}

void SingleColorRenderer::SetPivot(PIVOTMODE _Mode)
{
	switch (_Mode)
	{
	case PIVOTMODE::CENTER:
		AtlasDataInst.PivotPos = float4::ZERO;
		break;
	case PIVOTMODE::BOT:
		AtlasDataInst.PivotPos = float4(0.0f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::TOP:
		AtlasDataInst.PivotPos = float4(0.0f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFT:
		AtlasDataInst.PivotPos = float4(0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHT:
		AtlasDataInst.PivotPos = float4(-0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTTOP:
		AtlasDataInst.PivotPos = float4(0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTTOP:
		AtlasDataInst.PivotPos = float4(-0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTBOT:
		AtlasDataInst.PivotPos = float4(0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTBOT:
		AtlasDataInst.PivotPos = float4(-0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::CUSTOM:
		break;
	default:
		break;
	}
}

void SingleColorRenderer::Start()
{
	PushRendererToUICamera();

	SetSingleColorRendererSetting();

	//this->GetTransform().SetWorldPosition({0, 0});
	//this->GetTransform().SetWorldScale({ 100, 100 });
	SetTexture("Empty.png");
}

void SingleColorRenderer::SetSingleColorRendererSetting()
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

