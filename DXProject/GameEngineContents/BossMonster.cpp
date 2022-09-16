#include "PreCompile.h"
#include "BossMonster.h"

BossMonster::BossMonster() 
{
}

BossMonster::~BossMonster() 
{
}

void BossMonster::BossSpawnState(float _DeltaTime)
{
	static float SpawnTimer = 0.0f;

	SpawnTimer += _DeltaTime;

	if (SpawnTimer >= 10.0f)
	{
		// ������, �ݸ��� On
		Renderer_->On();
		Collision_->On();

		// ���͸� ������ ��ġ�� �̵�
		// �ϴ� �߾�
		float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
		// �ϴ� ����
		float4 ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 2
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
		// �ϴ� ����
		float4 ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

		for (;;)
		{
			// ���� ��ĭ �ø�
			this->GetTransform().SetWorldUpMove(1.0f, DeltaTime_);

			// �ø����� �ȼ� ���
			// �ϴ� �߾�
			ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// �ϴ� ����
			ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// �ϴ� ����
			ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

			// ���� ���� �ö������ Ż��
			if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
				false == ColorDownLeft.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
				false == ColorDownRight.CompareInt4D({ 1.0f, 0.0f, 1.0f })
				)
			{
				// �ٽ� ��ĭ ����
				this->GetTransform().SetWorldDownMove(1.0f, DeltaTime_);
				break;
			}
		}

		StateManager_.ChangeState(MONSTER_FSM_IDLE);
	}
}

