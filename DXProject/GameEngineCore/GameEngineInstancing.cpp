#include "PreCompile.h"
#include "GameEngineInstancing.h"

// �ּ� 2���̻��� �𿩾� �ν��Ͻ��� �����ϰڴ�.
int GameEngineInstancing::MinInstancingCount = 1;

// �ϴ� �����ߴٸ� 100���� �Ҽ� �ִٴ� �����Ͽ� �̰� �ϰڴ�.
int GameEngineInstancing::StartInstancingCount = 100;

GameEngineInstancing::GameEngineInstancing()
	: Buffer(nullptr)
	, Count(0)
	, DataInsert(0)

{
}

GameEngineInstancing::~GameEngineInstancing()
{
}

