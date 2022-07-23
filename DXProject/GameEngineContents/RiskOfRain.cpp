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
	// ���ҽ� �ε�
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
	Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
	Dir.Move(DIR_RESOURCE);
	Dir.Move(DIR_TEXTURE);

	std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

	for (auto& TmpDir : RecursiveDir)
	{
		GameEngineFolderTexture::Load(TmpDir.GetFullPath());
	}

	// ���� ����
	CreateLevel<StartLevel>(LEVEL_TITLE);
	CreateLevel<EndLevel>(LEVEL_END);
	CreateLevel<Stage1Level>(LEVEL_STAGE1);

	// �ʱ� ���� �̵�
	ChangeLevel(LEVEL_STAGE1);
}

void RiskOfRain::Update(float _DeltaTime)
{
	// TODO::�׽�Ʈ��
	int a = 0;
}

void RiskOfRain::End()
{
	// TODO::�׽�Ʈ��
	int a = 0;
}