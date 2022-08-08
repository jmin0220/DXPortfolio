#include "PreCompile.h"
#include "GameEngineCoreDebug.h"
#include <GameEngineBase/GameEngineTransform.h>
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineCore.h"
#include "GameEngineCamera.h"

namespace GameEngineDebug
{
	enum class DebugRenderType
	{
		Sphere,
		Box,
	};

	struct DebugInfo
	{
		int Type[4];
		float4 Color;

	public:
		DebugInfo(DebugRenderType _Type, const float4& _Color)
			: Type{ static_cast<int>(_Type) }
			, Color(_Color)
		{

		}
	};

	struct DebugRenderData
	{
	public:
		DebugInfo Info;
		TransformData Data;
	};

	std::vector<DebugRenderData> DebugData = std::vector<DebugRenderData>();

	void DrawBox(const GameEngineTransform& _Trans, const float4& _Color)
	{
		DrawBox(_Trans, GameEngineCore::GetCurLevel()->GetMainCamera(), _Color);
	}
	void DrawBox(const GameEngineTransform& _Trans, GameEngineCamera* _Camera, const float4& _Color)
	{
		static GameEngineTransform DebugTrans;

		DebugTrans.Copy(_Trans);
		DebugTrans.SetView(_Camera->GetView());
		DebugTrans.SetProjection(_Camera->GetProjectionMatrix());
		DebugTrans.CalculateWorldViewProjection();

		DebugData.push_back(DebugRenderData{ DebugInfo(DebugRenderType::Box, _Color) , DebugTrans.GetTransformData() });
	}

	void DrawSphere(const GameEngineTransform& _Trans, const float4& _Color)
	{
		DrawSphere(_Trans, GameEngineCore::GetCurLevel()->GetMainCamera(), _Color);
	}
	void DrawSphere(const GameEngineTransform& _Trans, GameEngineCamera* _Camera, const float4& _Color)
	{
		static GameEngineTransform DebugTrans;

		DebugTrans.Copy(_Trans);
		DebugTrans.SetView(_Camera->GetView());
		DebugTrans.SetProjection(_Camera->GetProjectionMatrix());
		DebugTrans.CalculateWorldViewProjection();

		DebugData.push_back(DebugRenderData{ DebugInfo(DebugRenderType::Sphere, _Color) , DebugTrans.GetTransformData() });
	}


	GameEngineShaderResourcesHelper DebugShaderResources;
	GameEngineRenderingPipeLine* DebugRenderingPipeLine;

	void Debug3DInitialize()
	{
		static bool IsOnce = false;

		if (true == IsOnce)
		{
			return;
		}


		DebugRenderingPipeLine = GameEngineRenderingPipeLine::Find("3DDebug");
		DebugShaderResources.ResourcesCheck(DebugRenderingPipeLine);

		IsOnce = true;
	}


	void Debug3DRender()
	{
		for (size_t i = 0; i < DebugData.size(); i++)
		{
			DebugShaderResources.SetConstantBufferLink("TransformData", DebugData[i].Data);
			DebugShaderResources.SetConstantBufferLink("DebugInfo", DebugData[i].Info);
			DebugShaderResources.AllResourcesSetting();
			DebugRenderingPipeLine->Rendering();
		}
		// DebugData.push_back(DebugRenderData());

		DebugData.clear();
		int a = 0;
	}

};