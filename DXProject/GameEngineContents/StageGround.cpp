#include "PreCompile.h"
#include "StageGround.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

StageGround::StageGround() 
	: Renderer_(nullptr)
{
}

StageGround::~StageGround() 
{
}

void StageGround::Start()
{
	// È­¸é¿¡ Ç¥½ÃµÇ´Â ¸Ê
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(TEX_STAGE_ONE);
	Renderer_->GetTransform().SetWorldPosition(float4::ZERO);
	Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);

	// Ä³¸¯ÅÍ Ãæµ¹¿ë ¸Ê
	ColRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	ColRenderer_->SetTexture(TEX_STAGE_ONE_COLLISION);
	ColRenderer_->GetTransform().SetWorldPosition(float4::ZERO);
	ColRenderer_->ScaleToTexture();
	ColRenderer_->SetPivot(PIVOTMODE::LEFTTOP);

	// ÇÈ¼¿¸Ê ¼û±â±â
	ColRenderer_->OnOffSwitch();

	BackGroundRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BackGroundRenderer_->SetTexture(TEX_BG_PURPLE_STARS);
	BackGroundRenderer_->GetTransform().SetLocalScale({ 2000, 2000 });
	BackGroundRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	BackGroundRenderer_->GetTransform().SetWorldPosition({ 0, 0, 5000});

}

void StageGround::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		ColRenderer_->OnOffSwitch();
	}
}

