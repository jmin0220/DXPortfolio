#include "PreCompile.h"
#include "AttackDrone.h"

AttackDrone::AttackDrone() 
{
}

AttackDrone::~AttackDrone() 
{
}

void AttackDrone::AnimInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->SetSamplingModePoint();
	Renderer_->CreateFrameAnimationFolder(DRONE_ATTACK_IDLE, FrameAnimation_DESC(DRONE_ATTACK_IDLE, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(DRONE_ATTACK_SHOOT, FrameAnimation_DESC(DRONE_ATTACK_SHOOT, ANIMATION_FRAME_DELAY, false));
	Renderer_->ChangeFrameAnimation(DRONE_ATTACK_IDLE);
	Renderer_->ScaleToTexture();
	Renderer_->SetScaleModeImage();
}