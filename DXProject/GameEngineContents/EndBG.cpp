#include "PreCompile.h"
#include "EndBG.h"

EndBG::EndBG() 
{
}

EndBG::~EndBG() 
{
}

void EndBG::Start()
{
	Black_ = CreateComponent<SingleColorRenderer>();
	Black_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	Black_->GetTransform().SetWorldScale({1700.0f, 1000.0f});
	Black_->GetTransform().SetWorldPosition({0.0f,0.0f, 0.0f, -300.0f});
	Black_->ChangeCamera(CAMERAORDER::UICAMERA);

	Font_ = CreateComponent<GameEngineFontRenderer>();
	Font_->SetText("Thanks to Watching!", FONT_RISKOFRAIN);
	Font_->SetSize(30);
	Font_->SetScreenPostion({ 800.0f, 450.0f });
	Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font_->ChangeCamera(CAMERAORDER::UICAMERA);
}

void EndBG::Update(float _DeltaTime)
{
	//Black_->GetTransform().SetWorldPosition(GetLevel()->GetMainCameraActorTransform().GetWorldPosition());
}

