#include "PreCompile.h"
#include "AttackDroneItem.h"
#include "AttackDrone.h"

AttackDroneItem::AttackDroneItem() 
{
	DronePrice_ = 25;
}

AttackDroneItem::~AttackDroneItem() 
{
}

void AttackDroneItem::Initialize()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetScaleModeImage();

	Renderer_->CreateFrameAnimationFolder(DRONE_ATTACK_ITEM, FrameAnimation_DESC(DRONE_ATTACK_ITEM, ANIMATION_FRAME_DELAY, false));

	Renderer_->ChangeFrameAnimation(DRONE_ATTACK_ITEM);
	Renderer_->SetPivot(PIVOTMODE::BOT);

	FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	FontRenderer_->SetText("Press 'A' to Repair the Drone ($ " + std::to_string(DronePrice_) + ")", FONT_RISKOFRAIN);
	FontRenderer_->SetSize(15);
	FontRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	FontRenderer_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();

	Collision_->ChangeOrder(ObjectGroup::Chest);
	Collision_->GetTransform().SetWorldScale({ 38.0f, 36.0f, 1.0f });
	Collision_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x
												, this->GetTransform().GetWorldPosition().y + 18.0f
												, this->GetTransform().GetWorldPosition().z });
}

void AttackDroneItem::AddDrone()
{
	AttackDrone* tmp = 	GetLevel()->CreateActor<AttackDrone>();
	tmp->GetTransform().SetWorldPosition(PlayerPos_);

	this->Death();
}