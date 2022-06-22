#include "PreCompile.h"
#include "GameEngineDevice.h"
#include <GameEngineBase/GameEngineWindow.h>

GameEngineDevice* GameEngineDevice::Inst = new GameEngineDevice();
ID3D11Device* GameEngineDevice::Device_ = nullptr;
ID3D11DeviceContext* GameEngineDevice::Context_ = nullptr;
IDXGISwapChain* GameEngineDevice::SwapChain_ = nullptr;

GameEngineDevice::GameEngineDevice() 
{
}

GameEngineDevice::~GameEngineDevice() 
{
	if (nullptr != SwapChain_)
	{
		SwapChain_->Release();
		SwapChain_ = nullptr;
	}

	if (nullptr != Context_)
	{
		Context_->Release();
		Context_ = nullptr;
	}

	if (nullptr != Device_)
	{
		Device_->Release();
		Device_ = nullptr;
	}
}

void GameEngineDevice::DeviceCreate()
{
	if (nullptr == GameEngineWindow::GetHWND())
	{
		MsgBoxAssert("�����찡 ��������� �ʾҴµ� ����̽��� �ʱ�ȭ �Ϸ��� �߽��ϴ�.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	// soft
	if (
		S_OK != D3D11CreateDevice(
			// ���� �ڵ��� �׷���ī�� ����̹� ����� �ֳ���?
			nullptr,
			// �Ϲ����� ǥ���Ͽ��� ��������� �׷���ī�带 ����Ұ̴ϴ�.
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			iFlag,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&Device_,
			&Level,
			&Context_
		)
		)
	{
		MsgBoxAssert("����̽� ������ �����߽��ϴ�.");
	}

	if (Level != D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0)
	{
		MsgBoxAssert("11�� �������� �ʴ� ����̽� �Դϴ�.");
	}

	// ��Ƽ������ �ε��� �ɼ�.
	HRESULT Hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
}

void GameEngineDevice::CreateSwapChain()
{
	float4 ScreenSize = GameEngineWindow::GetScale();

	// ���̷�Ʈ�� �׷���ī�忡 ���� ����� ���� �����ϱ� ���� ������ �ѱ�°�
	// �̰� �׷���ī�忡 �� �޸𸮸� ����ų�
	// ���� ����� ����.
	DXGI_SWAP_CHAIN_DESC ScInfo = {0,};

	ScInfo.BufferCount = 2;
	ScInfo.BufferDesc.Width = ScreenSize.uix();
	ScInfo.BufferDesc.Height = ScreenSize.uix();

	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;

	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	ScInfo.SampleDesc.Quality = 0;
	ScInfo.SampleDesc.Count = 1;

	ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;

	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ScInfo.Windowed = true;

	// ����ü���� �������
	// �⺻������ ���丮��°� ����ų� ���;� �ϴµ�.
	// ����� ����� �ƴϰ�. 

	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	// �� ���α׷� ������ ����� ��ġ�� ���� �ϳ��� ���� ������ �̴ϴ�.
	// "54ec77fa-1377-44e6-8c32-88fd5f44c84c"
	// ����� ��ġ��
	Device_->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pD));
	if (nullptr == pD)
	{
		MsgBoxAssert("����̽� ���⿡ �����߽��ϴ�.");
	}

}

void GameEngineDevice::Initialize() 
{
	DeviceCreate();
	CreateSwapChain();
}

