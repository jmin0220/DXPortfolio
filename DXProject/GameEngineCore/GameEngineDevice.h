#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineWindow.h>

// �׷���ī�忡 ����

// ���� :
class GameEngineDevice
{
private:
	static GameEngineDevice* Inst;

public:
	static GameEngineDevice& GetInst() 
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

public:
	~GameEngineDevice();

	// delete Function
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator=(GameEngineDevice&& _Other) noexcept = delete;

	static void Initialize();
	static void DeviceCreate();
	static void CreateSwapChain();

protected:

private:
	// ���̷�Ʈ 11�� ���鼭 �����д��� �ϰ� �������̽��� �����ߴ�.
	
	// ���̷�Ʈ 9���� ����̽��ۿ� �����µ�.
	// ���ҽ��� �޸� �о߸� �ý��ϴ�.
	// �׷���ī�忡 ����� �ؽ�ó
	static ID3D11Device* Device_;

	// �׷���ī�忡 ������ ����� �� �ְ� �Ǵµ�.
	// �������� ���õ� ��� ����� �̰ɷ� ������.
	static ID3D11DeviceContext* Context_;

	// api�� �����
	static IDXGISwapChain* SwapChain_;

	GameEngineDevice();
};

