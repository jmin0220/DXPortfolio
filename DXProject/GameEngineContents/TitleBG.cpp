#include "PreCompile.h"
#include "TitleBG.h"
#include "GameEngineCore/GameEngineRenderer.h"

TitleBG::TitleBG()
	:Renderer_(nullptr)
{
}

TitleBG::~TitleBG() 
{
}

void TitleBG::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(TEX_TITLE_BG);
	Renderer_->ScaleToTexture();
}

void TitleBG::Update(float _DeltaTime)
{
}

