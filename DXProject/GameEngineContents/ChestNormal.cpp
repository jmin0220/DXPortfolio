#include "PreCompile.h"
#include "ChestNormal.h"
#include "Drops.h"

ChestNormal::ChestNormal()
{
}

ChestNormal::~ChestNormal()
{
}

void ChestNormal::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();

	Renderer_->CreateFrameAnimationFolder(TEX_OBJECT_CHEST_NORMAL_IDLE, FrameAnimation_DESC(TEX_OBJECT_CHEST_NORMAL_IDLE, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_OBJECT_CHEST_NORMAL_OPEN, FrameAnimation_DESC(TEX_OBJECT_CHEST_NORMAL_OPEN, ANIMATION_FRAME_DELAY, true));

	Renderer_->AnimationBindEnd(TEX_OBJECT_CHEST_NORMAL_OPEN, [=](const FrameAnimation_DESC& _Info)
		{
			Drops::CreateCoinsAndExp(GoldValue_, ExpValue_, this->GetTransform().GetWorldPosition(), GetLevel());
		});
}

