#include "PreCompile.h"
#include "CharacterSelect.h"
#include "CharacterSelecter.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Stage1Level.h"

CharacterSelect::CharacterSelect() 
{
}

CharacterSelect::~CharacterSelect() 
{
}

void CharacterSelect::Start()
{
	CharacterSelecter_ = CreateActor<CharacterSelecter>();	


	if (false == GameEngineInput::GetInst()->IsKey(CHANGE_LEVEL_STAGE1))
	{
		GameEngineInput::GetInst()->CreateKey(CHANGE_LEVEL_STAGE1, VK_RETURN);
	}
}

void CharacterSelect::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown(CHANGE_LEVEL_CHRACTER_SELECT))
	{
		GEngine::ChangeLevel(LEVEL_STAGE1);
	}
}

void CharacterSelect::End()
{

}

void CharacterSelect::LevelEndEvent()
{
	SoundPlayer_.SoundPlayer_.Stop();
}
