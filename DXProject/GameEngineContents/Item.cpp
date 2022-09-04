#include "PreCompile.h"
#include "Item.h"
#include "Player.h"

Item::Item()
	: ItemRootingFlg_(false)
	, RootingEffectEndFlg_(false)
	, PosYTimer_(0.0f)
	, PosY_(0.0f)
{
}

Item::~Item() 
{
}

void Item::Start()
{

}

void Item::Update(float _DeltaTime)
{
	if (false == RootingEffectEndFlg_ && true == ItemRootingFlg_)
	{
		PosYTimer_ += _DeltaTime;

		if (PosYTimer_ >= 0.3f)
		{
			PosY_ -= 5.0f;
			PosYTimer_ = 0.0f;
		}

		float4 thisPos = this->GetTransform().GetWorldPosition();
		float4 MainCameraPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();

		ItemNameRenderer_->SetScreenPostion({ thisPos.x - MainCameraPos.x + GameEngineWindow::GetScale().x / 2
									  , -(thisPos.y - MainCameraPos.y - GameEngineWindow::GetScale().y / 2) - 20.0f + PosY_ });

		PickUpRenderer_->SetScreenPostion({ thisPos.x - MainCameraPos.x + GameEngineWindow::GetScale().x / 2
									  , -(thisPos.y - MainCameraPos.y - GameEngineWindow::GetScale().y / 2) + 10.0f + PosY_ });

		if (PosY_ <= -50.0f)
		{
			ItemNameRenderer_->Off();
			PickUpRenderer_->Off();

			RootingEffectEndFlg_ = true;
		}
	}
}

void Item::SetItemRootingFlgTrue()
{
	ItemRootingFlg_ = true;
	this->GetTransform().SetWorldPosition(PlayerPos_);

	Renderer_->Off();
	ItemNameRenderer_->On();
	PickUpRenderer_->On();
}