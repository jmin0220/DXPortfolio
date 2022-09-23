#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer()
	:PipeLine(nullptr)
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer()
{
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();

	// ���� �� ������ �ִٸ� ���⼭ �ض�.
}

void GameEngineDefaultRenderer::SetPipeLine(const std::string& _Name)
{
	PipeLine = GameEngineRenderingPipeLine::Find(_Name);

	if (nullptr == PipeLine)
	{
		MsgBoxAssert("�������� �ʴ� ������������ �����Ϸ��� �߽��ϴ�.");
		return;
	}

	ShaderResources.ResourcesCheck(PipeLine);

	if (true == ShaderResources.IsConstantBuffer("TRANSFORMDATA"))
	{
		ShaderResources.SetConstantBufferLink("TRANSFORMDATA", &GetTransformData(), sizeof(GetTransformData()));
	}

	if (true == ShaderResources.IsConstantBuffer("RENDEROPTION"))
	{
		ShaderResources.SetConstantBufferLink("RENDEROPTION", &renderOption, sizeof(renderOption));
	}

}

void GameEngineDefaultRenderer::Render(float _DeltaTime)
{
	if (nullptr == PipeLine)
	{
		MsgBoxAssert("������ ������������ ���õ��� ������ �������� �Ҽ� �����ϴ�.");
	}

	if (false == IsInstancing(GetPipeLine()))
	{
		// �غ�� ��� ���ҽ����� �� �������ش�.
		ShaderResources.AllResourcesSetting();
		PipeLine->Rendering();
		ShaderResources.AllResourcesReset();
	}
	else
	{
		InstancingDataSetting();
		// �����е��� ���ο� �������� ����� �ν��Ͻ��� �ϸ�
		// �� �κ��� �޶����� �մϴ�.
		// ������ �����Ʈ¥�� �ν���
		// Camera->PushInstancingIndex(PipeLine);
	}
}

void GameEngineDefaultRenderer::InstancingDataSetting()
{
	MsgBoxAssert("�ν��Ͻ� ������ó���� InstancingDataSetting ���������� �ʾҽ��ϴ�.");
}


GameEngineRenderingPipeLine* GameEngineDefaultRenderer::GetPipeLine()
{
	return PipeLine;
}

GameEngineRenderingPipeLine* GameEngineDefaultRenderer::GetClonePipeLine()
{
	if (false == PipeLine->IsOriginal())
	{
		return PipeLine;
	}

	PipeLine = ClonePipeLine(PipeLine);
	return PipeLine;
}

void GameEngineDefaultRenderer::InstancingOn()
{
	GameEngineRenderer::InstancingOn();

	Camera->PushInstancing(PipeLine, 1);
}