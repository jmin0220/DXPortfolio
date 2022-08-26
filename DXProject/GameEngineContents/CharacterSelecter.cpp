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

	// 설명 백그라운드 생성
	BGRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BGRenderer_->SetTexture(TEX_SELECTED_COMMANDO);
	BGRenderer_->SetPivot(PIVOTMODE::CENTER);
	BGRenderer_->ScaleToTexture();

	// 캐릭터 랜더러 생성
	CharacterRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	CharacterRenderer_->CreateFrameAnimationFolder(TEX_PLAYER_ANIM_COMMANDO_SELECT, FrameAnimation_DESC(COMMANDO_ANIM_SELECT, ANIMATION_FRAME_DELAY, false));
	CharacterRenderer_->CreateFrameAnimationFolder(TEX_PLAYER_ANIM_BANDIT_SELECT, FrameAnimation_DESC(BANDIT_ANIM_SELECT, ANIMATION_FRAME_DELAY, false));
	
	// 디폴트값 Commando의 설정
	CharacterRenderer_->ChangeFrameAnimation(TEX_PLAYER_ANIM_COMMANDO_SELECT);
	CharacterRenderer_->GetTransform().SetWorldScale({ 56.0f, 148.0f });
	CharacterRenderer_->GetTransform().SetWorldPosition({ 392, 160, 0 });

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
	// 캐릭터 선택
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