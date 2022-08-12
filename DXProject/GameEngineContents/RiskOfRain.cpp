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


		GameEngineFont::Load("riskofrainfont");
	}


	// ���� ����
	CreateLevel<StartLevel>(LEVEL_TITLE);
	CreateLevel<EndLevel>(LEVEL_END);
	CreateLevel<CharacterSelect>(LEVEL_SELECT);
	CreateLevel<Stage1Level>(LEVEL_STAGE1);

	// �ʱ� ���� �̵�
	ChangeLevel(LEVEL_TITLE);

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
	// TODO::�׽�Ʈ��
	int a = 0;
}

void RiskOfRain::End()
{
	// TODO::�׽�Ʈ��
	int a = 0;
}