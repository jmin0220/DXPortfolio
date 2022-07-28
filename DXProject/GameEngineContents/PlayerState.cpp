#include "PreCompile.h"
//#include "Player.h"
//
//// 업데이트
//void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
//{
//	if (true == IsShootKeyDown())
//	{
//		StateManager_.ChangeState(PLAYER_STATE_SHOOT);
//		return;
//	}
//
//
//	// 이동키가 눌리면 이동
//	if (true == IsMoveKeyDown())
//	{
//		StateManager_.ChangeState(PLAYER_STATE_MOVE);
//		return;
//	}
//}
//
//
//void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
//{
//	// 키가 떨어졌을경우 Idle상태로 전환
//	if (false == IsMoveKeyPress())
//	{
//		StateManager_.ChangeState(PLAYER_STATE_IDLE);
//		return;
//	}
//
//	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_LEFT))
//	{
//		if (true == GroundLeftCheck())
//		{
//			return;
//		}
//
//		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * DeltaTime_);
//
//		// TODO::픽셀체크함수 생성시 수정요
//		MoveDir_ = float4::LEFT;
//	}
//	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_RIGHT))
//	{
//		if (true == GroundRightCheck())
//		{
//			return;
//		}
//
//		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);
//
//		// TODO::픽셀체크함수 생성시 수정요
//		MoveDir_ = float4::RIGHT;
//	}
//	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_UP))
//	{
//		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * DeltaTime_);
//
//	}
//	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_DOWN))
//	{
//		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * DeltaTime_);
//
//	}
//}
//
//
//void Player::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill1Update(float _DeltaTime, const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill2Update(float _DeltaTime, const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill3Update(float _DeltaTime, const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill4Update(float _DeltaTime, const StateInfo& _Info)
//{
//
//}
//
//void Player::ClimbUpdate(float _DeltaTime, const StateInfo& _Info)
//{
//
//}
//
//void Player::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
//{
//
//}
//
//
//// 스타트
//void Player::IdleStart(const StateInfo& _Info)
//{
//	// 애니메이션 전환
//	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_IDLE);
//}
//
//void Player::MoveStart(const StateInfo& _Info)
//{
//	// 애니메이션 전환
//	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_WALK);
//}
//
//void Player::ShootStart(const StateInfo& _Info)
//{
//	// 애니메이션 전환
//	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_SHOOT);
//	//Renderer_->AnimationBindEnd(PLAYER_ANIM_BANDIT_SHOOT, &::EndAnimation, this);
//}
//
//void Player::Skill1Start(const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill2Start(const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill3Start(const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill4Start(const StateInfo& _Info)
//{
//
//}
//
//void Player::ClimbStart(const StateInfo& _Info)
//{
//
//}
//
//void Player::DeathStart(const StateInfo& _Info)
//{
//
//}
//
//
//// 엔드
//void Player::IdleEnd(const StateInfo& _Info)
//{
//
//}
//
//void Player::MoveEnd(const StateInfo& _Info)
//{
//
//}
//
//void Player::ShootEnd(const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill1End(const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill2End(const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill3End(const StateInfo& _Info)
//{
//
//}
//
//void Player::Skill4End(const StateInfo& _Info)
//{
//
//}
//
//void Player::ClimbEnd(const StateInfo& _Info)
//{
//
//}
//
//void Player::DeathEnd(const StateInfo& _Info)
//{
//
//}
