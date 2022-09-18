#include "PreCompile.h"
#include "CommonFunction.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

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
	CameraShakeEffect();
}

void CommonFunction::CameraShakeEffect()
{
	if (false == CameraShakeEffectFlg_)
	{
		return;
	}

	GameEngineLevel* tmpLevel = nullptr;

	float4 MainCameraBeginPosition = tmpLevel->GetMainCameraActorTransform().GetWorldPosition();

	// TODO::Random함수로 흔들기
	tmpLevel->GetMainCameraActorTransform().SetWorldPosition(MainCameraBeginPosition);
}

