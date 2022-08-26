#include "PreCompile.h"
#include "GameEngineCore/GameEngineRenderer.h"
#include "CharacterSelecter.h"
#include "CharacterSelectEnum.h"

CharacterSelecter::CharacterSelecter() 
	: BGRenderer_(nullptr)
	, CharacterRenderer_(nullptr)
{
}

CharacterSelecter::~CharacterSelecter() 
{
}

void CharacterSelecter::Start()
{
	this->GetTransform().SetWorldPosition({ 0, 0, 0 });

	// ���� ��׶��� ����
	BGRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BGRenderer_->SetTexture(TEX_SELECTED_COMMANDO);
	BGRenderer_->SetPivot(PIVOTMODE::CENTER);
	BGRenderer_->ScaleToTexture();

	// ĳ���� ������ ����
	CharacterRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	CharacterRenderer_->CreateFrameAnimationFolder(TEX_PLAYER_ANIM_COMMANDO_SELECT, FrameAnimation_DESC(COMMANDO_ANIM_SELECT, ANIMATION_FRAME_DELAY, false));
	CharacterRenderer_->CreateFrameAnimationFolder(TEX_PLAYER_ANIM_BANDIT_SELECT, FrameAnimation_DESC(BANDIT_ANIM_SELECT, ANIMATION_FRAME_DELAY, false));
	
	// ����Ʈ�� Commando�� ����
	CharacterRenderer_->ChangeFrameAnimation(TEX_PLAYER_ANIM_COMMANDO_SELECT);
	CharacterRenderer_->GetTransform().SetWorldScale({ 56.0f, 148.0f });
	CharacterRenderer_->GetTransform().SetWorldPosition({ 392, 160, 0 });

	// �÷��̾� ���� ���� �ʱⰪ
	Option_.CharacterSelect_ = CharacterSelectEnum::Commando;

	// TODO::�ӽ�Ű
	if (false == GameEngineInput::GetInst()->IsKey("SetCommando"))
	{
		GameEngineInput::GetInst()->CreateKey("SetCommando", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("SetBandit", VK_RIGHT);
	}
}

void CharacterSelecter::Update(float _DeltaTime)
{
	// ĳ���� ����
	if (true == GameEngineInput::GetInst()->IsDown("SetCommando"))
	{
		Option_.CharacterSelect_ = CharacterSelectEnum::Commando;
		BGRenderer_->SetTexture(TEX_SELECTED_COMMANDO);

		CharacterRenderer_->ChangeFrameAnimation(TEX_PLAYER_ANIM_COMMANDO_SELECT);
		CharacterRenderer_->GetTransform().SetWorldPosition({ 392, 160, 0 });
	}

	if (true == GameEngineInput::GetInst()->IsDown("SetBandit"))
	{
		Option_.CharacterSelect_ = CharacterSelectEnum::Bandit;
		BGRenderer_->SetTexture(TEX_SELECTED_BANDIT);

		CharacterRenderer_->ChangeFrameAnimation(TEX_PLAYER_ANIM_BANDIT_SELECT);
		CharacterRenderer_->GetTransform().SetWorldPosition({ 496, 160, 0 });
	}
}