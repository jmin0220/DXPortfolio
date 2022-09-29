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
		// ĳ���� �ִϸ��̼� �ε�
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
		// ���� �ִϸ��̼� �ε�
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


	// ����Ʈ �ִϸ��̼� �ε�
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

	// ������Ʈ �ִϸ��̼� �ε�
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

	// �������� �ε�
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

	// �������̽� �ε�
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

	// �������̽� �ε�(�ִϸ��̼�)
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

	// �����۾����� �ε�
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

	// ������ �ִϸ��̼� �ε�
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

	// ��Ʈ �ε�
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


	// ��� �ε�
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

	// ���� ����
	CreateLevel<StartLevel>(LEVEL_TITLE);
	CreateLevel<EndLevel>(LEVEL_END);
	CreateLevel<CharacterSelect>(LEVEL_SELECT);
	stage1Level_ = CreateLevel<Stage1Level>(LEVEL_STAGE1);
	CreateLevel<Stage2Level>(LEVEL_STAGE2);
	CreateLevel<TestLevel>("TestLevel");

	// �ʱ� ���� �̵�
	ChangeLevel(LEVEL_TITLE);
	// ChangeLevel("TestLevel");

	// IMGUI����
	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);

	// ����׿� Ű

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

	// TODO::�׽�Ʈ��
	int a = 0;
}

void RiskOfRain::End()
{
	// TODO::�׽�Ʈ��
	int a = 0;
}