#include "PreCompile.h"
#include "GameEngineStructuredBuffer.h"

GameEngineStructuredBuffer::GameEngineStructuredBuffer()
	: Buffer(nullptr)
	, BufferDesc()
	, ShaderDesc()
	, SettingResources()
	, SRV(nullptr)
	, DataSize(0)
	, DataCount(0)
{
}

GameEngineStructuredBuffer::~GameEngineStructuredBuffer()
{
	Release();
}

void GameEngineStructuredBuffer::Release()
{
	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}

	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}


void GameEngineStructuredBuffer::Create(size_t _DataSize, size_t _DataCount, void* _StartData)
{
	if (_DataCount == DataCount)
	{
		return;
	}

	if (_DataSize == DataSize)
	{
		return;
	}

	Release();

	BufferDesc.ByteWidth = DataSize * DataCount; // GPU �� ������ ����ȭ ���� �޸� ũ��(�ּҴ��� ??)
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	BufferDesc.StructureByteStride = DataSize; // 1�� ũ�⵵ �־���� �Ѵ�.

	D3D11_SUBRESOURCE_DATA StartData;
	D3D11_SUBRESOURCE_DATA* StartDataPtr = nullptr;

	if (nullptr != _StartData)
	{
		StartData.pSysMem = _StartData;
	}


	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, StartDataPtr, &Buffer))
	{
		MsgBoxAssert("��Ʈ��ó�� ���� ������ �����߽��ϴ�.");
	}

	// Shader Resource View
	// ���̴� ���ҽ��� ����µ� ���۱�� 
	// D3D11_SRV_DIMENSION_BUFFEREX ���۱�� ���̴� ���ҽ� ���°��� �˷��ֱ� ���� �뵵
	D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
	tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	tSRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	tSRVDesc.BufferEx.FirstElement = 0;
	tSRVDesc.BufferEx.Flags = 0;
	tSRVDesc.BufferEx.NumElements = DataCount; // 10���� �츮���� m_pSRV�� �־�޶�.

	if (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(Buffer, &tSRVDesc, &SRV))
	{
		MsgBoxAssert("FAIL (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(GetBuffer(), &tSRVDesc, &m_pSRV))");
	}
}