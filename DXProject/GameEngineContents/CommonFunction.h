#pragma once

// ���� : ���������� �ݺ��Ǿ� ���Ǵ� �Լ����� ��Ƴ��� Ŭ����
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

protected:
	void CameraShakeEffect();

private:
	bool CameraShakeEffectFlg_;
	float CameraShakeEffectTimer_;
};

