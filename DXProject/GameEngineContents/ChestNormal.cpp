#include "PreCompile.h"
#include "ChestNormal.h"
#include "Drops.h"

ChestNormal::ChestNormal()
{
	ChestPrice_ = 25;
}

ChestNormal::~ChestNormal()
{
}

void ChestNormal::Initialize()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetScaleModeImage();

	Renderer_->CreateFrameAnimationFolder(TEX_OBJECT_CHEST_NORMAL_IDLE, FrameAnimation_DESC(TEX_OBJECT_CHEST_NORMAL_IDLE, ANIMATION_FRAME_DELAY, false));
	Renderer_->CreateFrameAnimationFolder(TEX_OBJECT_CHEST_NORMAL_OPEN, FrameAnimation_DESC(TEX_OBJECT_CHEST_NORMAL_OPEN, ANIMATION_FRAME_DELAY, false));

	Renderer_->AnimationBindEnd(TEX_OBJECT_CHEST_NORMAL_OPEN, [=](const FrameAnimation_DESC& _Info)
		{
			Drops::CreateCoinsAndExp(GoldValue_, ExpValue_, this->GetTransform().GetWorldPosition(), GetLevel());
		});

	Renderer_->ChangeFrameAnimation(TEX_OBJECT_CHEST_NORMAL_IDLE);
	Renderer_->SetPivot(PIVOTMODE::BOT);

	FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	FontRenderer_->SetText("Press 'A' to purchase chest ($ " + std::to_string(ChestPrice_) + ")", "riskofrainfont");
	FontRenderer_->SetSize(15);
	FontRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	FontRenderer_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();

	Collision_->ChangeOrder(ObjectGroup::Chest);
	Collision_->GetTransform().SetWorldScale({ 44.0f, 26.0f, 1.0f });
	Collision_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x
												, this->GetTransform().GetWorldPosition().y + 13.0f
												, this->GetTransform().GetWorldPosition().z });
}