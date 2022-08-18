#include "PreCompile.h"
#include "TutorialUse.h"

TutorialUse::TutorialUse() 
{
}

TutorialUse::~TutorialUse() 
{
}

void TutorialUse::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationFolder(TEX_INTERFACE_TUTORIAL_USE, FrameAnimation_DESC(TEX_INTERFACE_TUTORIAL_USE, 1.0f, true));
	Renderer_->ChangeFrameAnimation(TEX_INTERFACE_TUTORIAL_USE);
}

void TutorialUse::Update(float _DeltaTime)
{

}

