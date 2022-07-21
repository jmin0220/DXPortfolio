#include "PreCompile.h"
#include "RiskOfRain.h"
#include "GameEngineContents/StartLevel.h"
#include "GameEngineContents/EndLevel.h"
#include "GameEngineContents/Stage1Level.h"

#pragma comment(lib, "GameEngineBase.lib")

RiskOfRain::RiskOfRain()
{
}

RiskOfRain::~RiskOfRain() 
{
}

void RiskOfRain::Start()
{
	// 리소스 로드
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Player");
		Dir.Move("Bandit");
		Dir.Move("BanditIdle");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	/*{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Player");
		Dir.Move("Bandit");
		Dir.Move("BanditShoot1");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Player");
		Dir.Move("Bandit");
		Dir.Move("BanditShoot2");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}*/



	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("Resources");
	Dir.Move("Resources");

	std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

	for (auto& TmpDir : RecursiveDir)
	{
		GameEngineFolderTexture::Load(TmpDir.GetFullPath());
	}

	// 레벨 생성
	CreateLevel<StartLevel>("Title");
	CreateLevel<EndLevel>("End");
	CreateLevel<Stage1Level>("Stage1");
	// 초기 레벨 이동
	ChangeLevel("Stage1");
}

void RiskOfRain::Update(float _DeltaTime)
{
	// TODO::테스트용
	int a = 0;
}

void RiskOfRain::End()
{
	// TODO::테스트용
	int a = 0;
}