#include "PreCompile.h"
#include "Commando.h"

// ������Ʈ
void Commando::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonIdleUpdate();
}


void Commando::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonMoveUpdate();
}

void Commando::Skill1Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::Skill2Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::Skill3Update(float _DeltaTime, const StateInfo& _Info)
{
	// ������� �⺻ �ӵ��� ������� �̵���

	if (MoveDir_.CompareInt3D(float4::LEFT))
	{
		if (true == GroundLeftCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * 3 * DeltaTime_);

		return;
	}

	if (MoveDir_.CompareInt3D(float4::RIGHT))
	{
		if (true == GroundRightCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * 3 * DeltaTime_);

		return;
	}
}

void Commando::Skill4Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::ClimbUpdate(float _DeltaTime, const StateInfo& _Info)
{
	CommonClimbUpdate();
}

void Commando::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

}


// ��ŸƮ
void Commando::IdleStart(const StateInfo& _Info)
{
	CommonIdleStart();
}

void Commando::MoveStart(const StateInfo& _Info)
{
	CommonMoveStart();
}

void Commando::Skill1Start(const StateInfo& _Info)
{
	CommonSkill1Start();
}

void Commando::Skill2Start(const StateInfo& _Info)
{
	CommonSkill2Start();
}

void Commando::Skill3Start(const StateInfo& _Info)
{
	CommonSkill3Start();
}

void Commando::Skill4Start(const StateInfo& _Info)
{
	// TODO:: 4_1�� 4_2�� ��ų �б� �߰�
	Skill4_2();
}

void Commando::Skill4_1()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_COMMANDO_SKILL4_1);
	Renderer_->ScaleToTexture();
}

void Commando::Skill4_2()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_COMMANDO_SKILL4_2);
	Renderer_->ScaleToTexture();
}

void Commando::ClimbStart(const StateInfo& _Info)
{
	CommonClimbStart();
}

void Commando::DeathStart(const StateInfo& _Info)
{

}


// ����
void Commando::IdleEnd(const StateInfo& _Info)
{

}

void Commando::MoveEnd(const StateInfo& _Info)
{

}

void Commando::Skill1End(const StateInfo& _Info)
{

}

void Commando::Skill2End(const StateInfo& _Info)
{

}

void Commando::Skill3End(const StateInfo& _Info)
{

}

void Commando::Skill4End(const StateInfo& _Info)
{

}

void Commando::ClimbEnd(const StateInfo& _Info)
{
	IsClimb_ = false;
}

void Commando::DeathEnd(const StateInfo& _Info)
{

}
