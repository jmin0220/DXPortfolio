#include "PreCompile.h"
#include "Exp.h"
#include "Player.h"

Exp::Exp() 
{
}

Exp::~Exp() 
{
}

void Exp::SetDestPos(float4 _DestPos)
{
	DestPos_.x = this->GetTransform().GetWorldPosition().x + _DestPos.x;
	DestPos_.y = this->GetTransform().GetWorldPosition().y + _DestPos.y;

	this->GetTransform().SetWorldPosition(DestPos_);
}

void Exp::Start()
{
	// ����ġ�� �߷��� ������ ���� ����.

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetScaleModeImage();

	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_NORMAL_EXP, FrameAnimation_DESC(TEX_EFFECT_NORMAL_EXP, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_SMALL_EXP, FrameAnimation_DESC(TEX_EFFECT_SMALL_EXP, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_DEATH_EXP, FrameAnimation_DESC(TEX_EFFECT_DEATH_EXP, ANIMATION_FRAME_DELAY, true));

	Renderer_->ChangeFrameAnimation(TEX_EFFECT_SMALL_EXP);
}

void Exp::Update(float _DeltaTime)
{
	PlayerChaseTimer_ += _DeltaTime;

	if (PlayerChaseTimer_ <= 0.5f)
	{
		return;
	}
	else
	{
	// ������Ʈ�� �÷��̾�� ����� �����ߴٸ�
	if (false == ChasePlayer())
	{
		// �÷��̾ ��� �߰�
		Player::AddExp(ExpValue_);

		// ������Ʈ ����
		this->Death();

		return;
	}
	}

	FlyDir_ = PlayerPos_ - this->GetTransform().GetWorldPosition();

	// ������Ʈ�� ����� ������
	if (FlyDir_.Length() <= 10)
	{
		// �÷��̾ ��� �߰�
		Player::AddExp(ExpValue_);

		// ������Ʈ ����
		this->Death();

		return;
	}
}

bool Exp::ChasePlayer()
{
	// �÷��̾� ��ġ�� ������ ����
	FlyDir_ = PlayerPos_ - this->GetTransform().GetWorldPosition();

	// ������Ʈ�� ����� ������
	if (FlyDir_.Length() <= 10.0f)
	{
		return false;
	}
	// ������Ʈ�� ����� �������� ����
	else
	{
		FlyDir_.Normalize();

		// �÷��̾ ���� �̵�
		// TODO::Sin����� ���ư������� �ʳ�?
		this->GetTransform().SetWorldMove(FlyDir_ * GameEngineTime::GetDeltaTime() * 300.0f);
		return true;
	}
}