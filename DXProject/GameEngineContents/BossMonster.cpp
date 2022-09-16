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
		// 렌더러, 콜리전 On
		Renderer_->On();
		Collision_->On();

		// 몬스터를 적절한 위치에 이동
		// 하단 중앙
		float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
		// 하단 좌측
		float4 ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 2
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
		// 하단 우측
		float4 ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

		for (;;)
		{
			// 위로 한칸 올림
			this->GetTransform().SetWorldUpMove(1.0f, DeltaTime_);

			// 올린뒤의 픽셀 취득
			// 하단 중앙
			ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// 하단 좌측
			ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// 하단 우측
			ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

			// 가장 위로 올라왔으면 탈출
			if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
				false == ColorDownLeft.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
				false == ColorDownRight.CompareInt4D({ 1.0f, 0.0f, 1.0f })
				)
			{
				// 다시 한칸 내림
				this->GetTransform().SetWorldDownMove(1.0f, DeltaTime_);
				break;
			}
		}

		StateManager_.ChangeState(MONSTER_FSM_IDLE);
	}
}

