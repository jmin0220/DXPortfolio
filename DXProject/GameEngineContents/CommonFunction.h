#pragma once
#include <GameEngineCore/GameEngineCameraActor.h>

// 설명 : 공통적으로 반복되어 사용되는 함수들을 모아놓는 클래스
class CommonFunction
{
public:
	static CommonFunction* CommonFunction_;

private:
	// constrcuter destructer
	CommonFunction();
	~CommonFunction();

	// delete Function
	CommonFunction(const CommonFunction& _Other) = delete;
	CommonFunction(CommonFunction&& _Other) noexcept = delete;
	CommonFunction& operator=(const CommonFunction& _Other) = delete;
	CommonFunction& operator=(CommonFunction&& _Other) noexcept = delete;


public:

	void Update(float _DeltaTime);

	inline void CameraShakeEffectOn(float _Time = 1.0f)
	{
		CameraShakeEffectFlg_ = true;
		CameraShakeEffectTimer_ = _Time;
	}

	void CameraShakeEffect(GameEngineCameraActor* _CameraActor);

protected:

private:
	bool CameraShakeEffectFlg_;
	float CameraShakeEffectTimer_;
};

