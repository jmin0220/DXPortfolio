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
	// ȭ�鿡 ǥ�õǴ� ��
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(TEX_STAGE_ONE);
	Renderer_->GetTransform().SetWorldPosition(float4::ZERO);
	Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);

	// ĳ���� �浹�� ��
	ColRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	ColRenderer_->SetTexture(TEX_STAGE_ONE_COLLISION);
	ColRenderer_->GetTransform().SetWorldPosition(float4::ZERO);
	ColRenderer_->ScaleToTexture();
	ColRenderer_->SetPivot(PIVOTMODE::LEFTTOP);

	// �ȼ��� �����
	ColRenderer_->OnOffSwitch();
}

void StageGround::Update(float _DeltaTime)
{
}

