#include "PreCompile.h"
#include "MissileDroneItem.h"
#include "MissileDrone.h"

MissileDroneItem::MissileDroneItem() 
{
	DronePrice_ = 25;
}

MissileDroneItem::~MissileDroneItem() 
{
}


void MissileDroneItem::Initialize()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetScaleModeImage();

	Renderer_->CreateFrameAnimationFolder(DRONE_MISSILE_ITEM, FrameAnimation_DESC(DRONE_MISSILE_ITEM, ANIMATION_FRAME_DELAY, false));

	Renderer_->ChangeFrameAnimation(DRONE_MISSILE_ITEM);
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

void MissileDroneItem::AddDrone()
{
	GameEngineSound::SoundPlayOneShot("wDrone1Spawn.wav");

	MissileDrone* tmp = GetLevel()->CreateActor<MissileDrone>();
	tmp->GetTransform().SetWorldPosition(PlayerPos_);

	this->Death();
}