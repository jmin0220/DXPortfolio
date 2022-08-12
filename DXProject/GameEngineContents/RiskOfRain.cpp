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
	}

	{
		// 몬스터 애니메이션 로딩
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
		Dir.Move(DIR_RESOURCE);
		Dir.Move(DIR_TEXTURE);
		Dir.Move(DIR_MONSTER);

		std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

		for (auto& TmpDir : RecursiveDir)
		{
			GameEngineFolderTexture::Load(TmpDir.GetFullPath());
		}
	}


	// 이펙트 애니메이션 로딩
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
		Dir.Move(DIR_RESOURCE);
		Dir.Move(DIR_TEXTURE);
		Dir.Move(DIR_EFFECT);

		std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

		for (auto& TmpDir : RecursiveDir)
		{
			GameEngineFolderTexture::Load(TmpDir.GetFullPath());
		}
	}

	// 오브젝트 애니메이션 로딩
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
		Dir.Move(DIR_RESOURCE);
		Dir.Move(DIR_TEXTURE);
		Dir.Move(DIR_OBJECT);

		std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

		for (auto& TmpDir : RecursiveDir)
		{
			GameEngineFolderTexture::Load(TmpDir.GetFullPath());
		}
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


	// 폰트 로딩
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
		Dir.Move(DIR_RESOURCE);
		Dir.Move(DIR_FONT);

		std::vector<GameEngineFile> Fonts = Dir.GetAllFile();

		for (size_t i = 0; i < Fonts.size(); i++)
		{
			GameEngineFont::Load(Fonts[i].GetFullPath());
		}


		GameEngineFont::Load("riskofrainfont");
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

	// 디버그용 키

	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}
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