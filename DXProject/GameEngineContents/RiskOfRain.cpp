#include "PreCompile.h"
#include "RiskOfRain.h"
#include "GameEngineContents/StartLevel.h"
#include "GameEngineContents/EndLevel.h"
#include "GameEngineContents/CharacterSelect.h"
#include "GameEngineContents/Stage1Level.h"
#include "GameEngineContents/Stage2Level.h"
#include "GameEngineContents/TestLevel.h"

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

	// 인터페이스 로딩(애니메이션)
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
		Dir.Move(DIR_RESOURCE);
		Dir.Move(DIR_TEXTURE);
		Dir.Move(DIR_INTERFACE);

		std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

		for (auto& TmpDir : RecursiveDir)
		{
			GameEngineFolderTexture::Load(TmpDir.GetFullPath());
		}
	}

	// 아이템아이콘 로딩
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
		Dir.Move(DIR_RESOURCE);
		Dir.Move(DIR_TEXTURE);
		Dir.Move(DIR_ITEM);

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

	// 아이템 애니메이션 로딩
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
		Dir.Move(DIR_RESOURCE);
		Dir.Move(DIR_TEXTURE);
		Dir.Move(DIR_ITEMANIMATION);

		std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

		for (auto& TmpDir : RecursiveDir)
		{
			GameEngineFolderTexture::Load(TmpDir.GetFullPath());
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


		GameEngineFont::Load(FONT_RISKOFRAIN);
	}


	// 드론 로딩
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCE);
		Dir.Move(DIR_RESOURCE);
		Dir.Move(DIR_TEXTURE);
		Dir.Move(DIR_DRONE);

		std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

		for (auto& TmpDir : RecursiveDir)
		{
			GameEngineFolderTexture::Load(TmpDir.GetFullPath());
		}
	}

	// 레벨 생성
	CreateLevel<StartLevel>(LEVEL_TITLE);
	CreateLevel<EndLevel>(LEVEL_END);
	CreateLevel<CharacterSelect>(LEVEL_SELECT);
	stage1Level_ = CreateLevel<Stage1Level>(LEVEL_STAGE1);
	CreateLevel<Stage2Level>(LEVEL_STAGE2);
	CreateLevel<TestLevel>("TestLevel");

	// 초기 레벨 이동
	ChangeLevel(LEVEL_TITLE);
	// ChangeLevel("TestLevel");

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
	if (stage1Level_ == nullptr)
	{
		stage1Level_ = CreateLevel<Stage1Level>(LEVEL_STAGE1);
	}

	// TODO::테스트용
	int a = 0;
}

void RiskOfRain::End()
{
	// TODO::테스트용
	int a = 0;
}