#include "PreCompile.h"
#include "GameEngineCore/GameEngineRenderer.h"
#include "CharacterSelecter.h"
#include "CharacterSelectEnum.h"

CharacterSelecter::CharacterSelecter() 
	: Renderer_(nullptr)
{
}

CharacterSelecter::~CharacterSelecter() 
{
}

void CharacterSelecter::Start()
{
	this->GetTransform().SetWorldPosition({ 0, 0, 0 });

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture(TEX_SELECTED_COMMANDO);
	Renderer_->SetPivot(PIVOTMODE::CENTER);
	Renderer_->ScaleToTexture();

	// 플레이어 액터 생성 초기값
	Option_.CharacterSelect_ = CharacterSelectEnum::Commando;

	// TODO::임시키
	if (false == GameEngineInput::GetInst()->IsKey("SetCommando"))
	{
		GameEngineInput::GetInst()->CreateKey("SetCommando", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("SetBandit", VK_RIGHT);
	}
}

void CharacterSelecter::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("SetCommando"))
	{
		Option_.CharacterSelect_ = CharacterSelectEnum::Commando;
		Renderer_->SetTexture(TEX_SELECTED_COMMANDO);
	}

	if (true == GameEngineInput::GetInst()->IsDown("SetBandit"))
	{
		Option_.CharacterSelect_ = CharacterSelectEnum::Bandit;
		Renderer_->SetTexture(TEX_SELECTED_BANDIT);
	}
}

