#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineCamera.h"
#include "GameEngineInstancing.h"


#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"


GameEngineRenderer::GameEngineRenderer()
	: CameraOrder(CAMERAORDER::MAINCAMERA)
	, RenderingOrder(0)
{
}

GameEngineRenderer::~GameEngineRenderer()
{
	int a = 0;
}

void GameEngineRenderer::Start()
{
}

void GameEngineRenderer::PushRendererToMainCamera()
{
	GetActor()->GetLevel()->PushRendererToMainCamera(this);
}

void GameEngineRenderer::SetRenderingOrder(int _Order)
{
	Camera->ChangeRenderingOrder(this, _Order);
}

void GameEngineRenderer::PushRendererToUICamera()
{
	GetActor()->GetLevel()->PushRendererToUICamera(this);
}

GameEngineRenderingPipeLine* GameEngineRenderer::ClonePipeLine(GameEngineRenderingPipeLine* _Rendering)
{
	// �̸����� �༮���� �����.
	GameEngineRenderingPipeLine* Clone = GameEngineRenderingPipeLine::Create();
	Clone->Copy(_Rendering);
	return Clone;
}

bool GameEngineRenderer::IsInstancing(GameEngineRenderingPipeLine* _Rendering)
{
	std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator InstancingIter = Camera->InstancingMap.find(_Rendering);

	if (InstancingIter == Camera->InstancingMap.end())
	{
		return false;
	}

	return true == IsInstancing_ && GameEngineInstancing::MinInstancingCount <= InstancingIter->second.Count;
}

//void GameEngineRenderer::Render(float _DeltaTime)
//{
//	//// ������
//	////GameEngineVertexBuffer* Vertex = GameEngineVertexBuffer::Find("Rect");
//	////GameEngineIndexBuffer* Index = GameEngineIndexBuffer::Find("Rect");
//
//	//GameEngineVertexBuffer* Vertex = GameEngineVertexBuffer::Find("Box");
//	//GameEngineIndexBuffer* Index = GameEngineIndexBuffer::Find("Box");
//	//
//	//std::vector<POINT> DrawVertex;
//	//DrawVertex.resize(Index->Indexs.size());
//
//	//std::vector<float4> CopyBuffer;
//	//CopyBuffer.resize(Index->Indexs.size());
//
//
//	//for (size_t i = 0; i < Index->Indexs.size(); i++)
//	//{
//	//	int TriIndex = Index->Indexs[i];
//
//	//	// 0 ��° ������ ���� �˴ϴ�.
//	//	// ���ʿ� ���� �Ž��� ���� �����մϴ�.
//	//	CopyBuffer[i] = Vertex->Vertexs[TriIndex];
//
//	//	auto& tran = GetTransform();
//
//	//	// ���ؽ����̴�
//	//	CopyBuffer[i] = CopyBuffer[i] * GetTransform().GetWorldViewProjection();
//
//
//	//	// �����Ͷ�����
//	//	//// ����س��� z������ �����°�
//	//	CopyBuffer[i] = CopyBuffer[i] / CopyBuffer[i].w;
//
//
//	//	DrawVertex[i] = CopyBuffer[i].GetConvertWindowPOINT();
//	//}
//	//
//	//for (size_t i = 0; i < DrawVertex.size(); i += 3)
//	//{
//	//	Polygon(GameEngineWindow::GetHDC(), &DrawVertex[i], 3);
//	//}
//}

void GameEngineRenderer::ChangeCamera(CAMERAORDER _Order)
{
	GetActor()->GetLevel()->PushRenderer(this, _Order);
}


