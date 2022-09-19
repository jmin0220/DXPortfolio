#include "PreCompile.h"
#include "CommonFunction.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineTime.h>

CommonFunction* CommonFunction::CommonFunction_ = new CommonFunction();

CommonFunction::CommonFunction() 
	: CameraShakeEffectFlg_(false)
{
}

CommonFunction::~CommonFunction() 
{
	if (nullptr != CommonFunction_)
	{
		delete CommonFunction_;
		CommonFunction_ = nullptr;
	}
}

void CommonFunction::Update(float _DeltaTime)
{
}

void CommonFunction::CameraShakeEffect(GameEngineCameraActor* _CameraActor)
{
	if (false == CameraShakeEffectFlg_)
	{
		return;
	}

	float4 MainCameraBeginPosition = _CameraActor->GetTransform().GetWorldPosition();

	// Random�Լ��� ����
	MainCameraBeginPosition = { MainCameraBeginPosition.x + GameEngineRandom::MainRandom.RandomInt(-3, 3),
								MainCameraBeginPosition.y + GameEngineRandom::MainRandom.RandomInt(-3, 3),
								MainCameraBeginPosition.z,
								MainCameraBeginPosition.w };

	_CameraActor->GetTransform().SetWorldPosition(MainCameraBeginPosition);

	// Ÿ�̸� ����
	CameraShakeEffectTimer_ -= GameEngineTime::GetDeltaTime();

	// ����Ʈ ����
	if (CameraShakeEffectTimer_ <= 0.0f)
	{
		CameraShakeEffectFlg_ = false;
	}
}

