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
	Renderer_->SetSamplingModePoint();
	Renderer_->SetTexture(TEX_STAGE_ONE);
	Renderer_->GetTransform().SetWorldPosition({ 0, 0, static_cast<float>(ZOrder::StageBackGround) });
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

	// ���
	BackGroundRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BackGroundRenderer_->SetSamplingModePoint();
	BackGroundRenderer_->SetTexture(TEX_BG_BLUE_STARTS);
	BackGroundRenderer_->GetTransform().SetLocalScale({ 51200, 29000 });
	BackGroundRenderer_->SetPivot(PIVOTMODE::CENTER);
	BackGroundRenderer_->GetTransform().SetWorldPosition({ Renderer_->GetCurTexture()->GetScale().hx(), Renderer_->GetCurTexture()->GetScale().hy(), 10000});

}

void StageGround::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		ColRenderer_->OnOffSwitch();
	}
}

