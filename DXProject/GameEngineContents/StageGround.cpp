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
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	ColRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BackGroundRenderer_ = CreateComponent<GameEngineTextureRenderer>();
}

void StageGround::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		ColRenderer_->OnOffSwitch();
	}
}

void StageGround::SetStage1Map()
{
	// ȭ�鿡 ǥ�õǴ� ��
	Renderer_->SetSamplingModePoint();
	Renderer_->SetTexture(TEX_STAGE_ONE);
	Renderer_->GetTransform().SetWorldPosition({ 0, 0, static_cast<float>(ZOrder::StageBackGround) });
	Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);

	// ĳ���� �浹�� ��
	ColRenderer_->SetTexture(TEX_STAGE_ONE_COLLISION);
	ColRenderer_->GetTransform().SetWorldPosition(float4::ZERO);
	ColRenderer_->ScaleToTexture();
	ColRenderer_->SetPivot(PIVOTMODE::LEFTTOP);

	// �ȼ��� �����
	ColRenderer_->OnOffSwitch();

	// ���
	BackGroundRenderer_->SetSamplingModePoint();
	BackGroundRenderer_->SetTexture(TEX_BG_BLUE_STARTS);
	BackGroundRenderer_->GetTransform().SetLocalScale({ 51200, 29000 });
	BackGroundRenderer_->SetPivot(PIVOTMODE::CENTER);
	BackGroundRenderer_->GetTransform().SetWorldPosition({ Renderer_->GetCurTexture()->GetScale().hx(), Renderer_->GetCurTexture()->GetScale().hy(), 10000 });
}


void StageGround::SetStage2Map()
{
	// ȭ�鿡 ǥ�õǴ� ��
	Renderer_->SetSamplingModePoint();
	Renderer_->SetTexture(TEX_STAGE_TWO);
	Renderer_->GetTransform().SetWorldPosition({ 0, 0, static_cast<float>(ZOrder::StageBackGround) });
	Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);

	// ĳ���� �浹�� ��
	ColRenderer_->SetTexture(TEX_STAGE_TWO_COLLISION);
	ColRenderer_->GetTransform().SetWorldPosition(float4::ZERO);
	ColRenderer_->ScaleToTexture();
	ColRenderer_->SetPivot(PIVOTMODE::LEFTTOP);

	// �ȼ��� �����
	ColRenderer_->OnOffSwitch();

	// ���
	BackGroundRenderer_->SetSamplingModePoint();
	BackGroundRenderer_->SetTexture(TEX_BG_BLUE_STARTS);
	BackGroundRenderer_->GetTransform().SetLocalScale({ 51200, 29000 });
	BackGroundRenderer_->SetPivot(PIVOTMODE::CENTER);
	BackGroundRenderer_->GetTransform().SetWorldPosition({ Renderer_->GetCurTexture()->GetScale().hx(), Renderer_->GetCurTexture()->GetScale().hy(), 10000 });
}
