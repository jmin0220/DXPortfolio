#include "PreCompile.h"
#include "Player.h"

Player::Player() 
	:Renderer_(nullptr)
	, Speed_(50.0f)
	, DeltaTime_(0.0f)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	KeyInit();
	AnimationInit();
}

void Player::Update(float _DeltaTime)
{
	DeltaTime_ = _DeltaTime;
	StateUpdate();
}

void Player::End()
{

}


void Player::KeyInit()
{
	if (false == GameEngineInput::GetInst()->IsKey(PLAYER_KEY_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_LEFT, 'A');
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_RIGHT, 'D');
	}
}


void Player::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_IDLE, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_IDLE, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_SHOOT, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_SHOOT, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_WALK, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_WALK, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_JUMP, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_JUMP, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_CLIMB, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_CLIMB, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_DEATH, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_DEATH, 0.1f, false));

	//Renderer_->GetTransform().SetLocalScale({ 66, 30 });
	//Renderer_->CreateFrameAnimationFolder("BanditShoot2", FrameAnimation_DESC("BanditShoot2", 0.1f));
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_IDLE);
	Renderer_->ScaleToTexture();
}

void Player::StateChange(STATE _State)
{

	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case STATE::Idle:
			IdleStart();
			break;
		case STATE::Move:
			MoveStart();
			break;
		case STATE::Jump:
			JumpStart();
			break;
		case STATE::SHOOT:
			ShootStart();
			break;
		case STATE::SKILL1:
			Skill1Start();
			break;
		case STATE::SKILL2:
			Skill2Start();
			break;
		case STATE::SKILL3:
			Skill3Start();
			break;
		case STATE::SKILL4:
			Skill4Start();
			break;
		case STATE::CLIMB:
			ClimbStart();
			break;
		case STATE::Death:
			DeathStart();
			break;
		case STATE::None:
			CurrentState_ = _State;
			return;
		default:
			break;
		}
	}

	CurrentState_ = _State;
}

void Player::StateUpdate()
{
	switch (CurrentState_)
	{
	case STATE::Idle:
		IdleUpdate();
		break;
	case STATE::Move:
		MoveUpdate();
		break;
	case STATE::Jump:
		JumpUpdate();
		break;
	case STATE::SHOOT:
		ShootUpdate();
		break;
	case STATE::SKILL1:
		Skill1Update();
		break;
	case STATE::SKILL2:
		Skill2Update();
		break;
	case STATE::SKILL3:
		Skill3Update();
		break;
	case STATE::SKILL4:
		Skill4Update();
		break;
	case STATE::CLIMB:
		ClimbUpdate();
		break;
	case STATE::Death:
		DeathUpdate();
		break;
	case STATE::None:
		return;
	default:
		break;
	}
}

bool Player::IsMoveKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_RIGHT)
		)
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_RIGHT)
		)
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_RIGHT)
		)
	{
		return false;
	}

	return true;
}