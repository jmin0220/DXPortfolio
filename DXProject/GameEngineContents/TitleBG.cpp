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
	Renderer_->CreateFrameAnimationFolder(TEX_TITLE_BG, FrameAnimation_DESC(TEX_TITLE_BG, 0.1f, false));
	Renderer_->ChangeFrameAnimation(TEX_TITLE_BG);
	//Renderer_->GetTransform().SetLocalScale({ 1600, 900 });
	Renderer_->ScaleToTexture();
}

void TitleBG::Update(float _DeltaTime)
{
}

