#include "PreCompile.h"
#include "Tutorial.h"

Tutorial::Tutorial() 
{
}

Tutorial::~Tutorial() 
{
}

void Tutorial::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationFolder(TEX_INTERFACE_TUTORIAL, FrameAnimation_DESC(TEX_INTERFACE_TUTORIAL, 2.0f, true));
	Renderer_->ChangeFrameAnimation(TEX_INTERFACE_TUTORIAL);
	Renderer_->ScaleToTexture();
}

void Tutorial::Update(float _DeltaTime)
{

}