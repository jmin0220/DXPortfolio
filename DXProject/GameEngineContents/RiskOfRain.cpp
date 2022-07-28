#include "PreCompile.h"
#include "RiskOfRain.h"
#include "GameEngineContents/StartLevel.h"
#include "GameEngineContents/EndLevel.h"
#include "GameEngineContents/CharacterSelect.h"
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
	// 캐릭터 애니메이션 로딩
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
	Dir.Move(DIR_RESOURCE);
	Dir.Move(DIR_TEXTURE);
	Dir.Move(DIR_CHARACTERS);

	std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

	for (auto& TmpDir : RecursiveDir)
	{
		GameEngineFolderTexture::Load(TmpDir.GetFullPath());
	}

	// 스테이지 로딩
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
		Dir.Move(DIR_RESOURCE);
		Dir.Move(DIR_TEXTURE);
		Dir.Move(DIR_STAGE);

		std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

		for (auto& TmpDir : RecursiveDir)
		{
			std::vector<GameEngineFile> Shaders = TmpDir.GetAllFile();

			for (size_t i = 0; i < Shaders.size(); i++)
			{
				GameEngineTexture::Load(Shaders[i].GetFullPath());
			}
		}
	}

	// 인터페이스 로딩
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
		Dir.Move(DIR_RESOURCE);
		Dir.Move(DIR_TEXTURE);
		Dir.Move(DIR_INTERFACE);

		std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

		for (auto& TmpDir : RecursiveDir)
		{
			std::vector<GameEngineFile> Shaders = TmpDir.GetAllFile();

			for (size_t i = 0; i < Shaders.size(); i++)
			{
				GameEngineTexture::Load(Shaders[i].GetFullPath());
			}
		}
	}

	// 레벨 생성
	CreateLevel<StartLevel>(LEVEL_TITLE);
	CreateLevel<EndLevel>(LEVEL_END);
	CreateLevel<CharacterSelect>(LEVEL_SELECT);
	CreateLevel<Stage1Level>(LEVEL_STAGE1);

	// 초기 레벨 이동
	ChangeLevel(LEVEL_TITLE);

	// IMGUI생성
	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
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