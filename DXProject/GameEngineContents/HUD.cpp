#include "PreCompile.h"
#include "HUD.h"

HUD::HUD() 
	: UIRenderer_(nullptr)
{
}

HUD::~HUD() 
{
}

void HUD::Start()
{
	UIRenderer_ = CreateComponent<GameEngineUIRenderer>();
	UIRenderer_->SetTexture(TEX_INTERFACE_HUD);

	UIRenderer_->ScaleToTexture();
	UIRenderer_->GetTransform().SetWorldPosition({0, 400, 0});
}
