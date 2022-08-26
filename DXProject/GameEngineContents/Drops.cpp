#include "PreCompile.h"
#include "Drops.h"
#include "Gold.h"
#include "Exp.h"
#include <GameEngineBase/GameEngineRandom.h>

float4 Drops::PlayerPos_ = float4::ZERO;

Drops::Drops() 
	: PlayerChaseTimer_(0.0f)
{
}

Drops::~Drops() 
{
}

void Drops::CreateCoinsAndExp(int _GoldValue, int _ExpValue, float4 _Pos, GameEngineLevel* _Level)
{
	int GoldValue = _GoldValue;
	// 5골드짜리 갯수
	int GoldFive = GoldValue / 5;
	// 1골드짜리 갯수
	int GoldOne = GoldValue % 5;

	GameEngineRandom* Random = new GameEngineRandom();

	// 5골드 출력
	for (int i = 0; i < GoldFive; i++)
	{
		// 골드 생성
		Gold* tmpGold = _Level->CreateActor<Gold>();
		tmpGold->GetTransform().SetWorldPosition(_Pos);
		tmpGold->SetGoldValue(5);
		tmpGold->UpdateGoldOption();

		// 골드가 생성될때 떨어질 각도를 설정
		tmpGold->SetFlyDir({ Random->RandomFloat(-50.0, 50.0), 0.0f, 0.0f });
		tmpGold->GoldPop();

	}

	// 1골드 출력
	for (int i = 0; i < GoldOne; i++)
	{
		// 골드 생성
		Gold* tmpGold = _Level->CreateActor<Gold>();
		tmpGold->GetTransform().SetWorldPosition(_Pos);
		tmpGold->SetGoldValue(1);
		tmpGold->UpdateGoldOption();

		// 골드가 생성될때 떨어질 각도를 설정
		tmpGold->SetFlyDir({ Random->RandomFloat(-50.0, 50.0), 0.0f, 0.0f });
		tmpGold->GoldPop();
	}


	// 경험치 생성
	int ExpValue = _ExpValue;
	// 5경험치짜리 갯수 -> 렌더러는 동일함
	int ExpFive = ExpValue / 5;
	// 1경험치짜리 갯수
	int ExpOne = ExpValue % 5;

	// 5경험치 출력
	for (int i = 0; i < ExpFive; i++)
	{
		// 경험치 생성
		Exp* tmpExp = _Level->CreateActor<Exp>();
		tmpExp->GetTransform().SetWorldPosition(_Pos);
		tmpExp->SetExpValue(5);

		// 경험치가 생성될때 최종 이동위치를 설정
		tmpExp->SetDestPos({ Random->RandomFloat(-15.0, 15.0), Random->RandomFloat(-15.0, 15.0), 0.0f });
	}

	// 1경험치 출력
	for (int i = 0; i < ExpOne; i++)
	{
		// 경험치 생성
		Exp* tmpExp = _Level->CreateActor<Exp>();
		tmpExp->GetTransform().SetWorldPosition(_Pos);
		tmpExp->SetExpValue(5);

		// 경험치가 생성될때 최종 이동위치를 설정
		tmpExp->SetDestPos({ Random->RandomFloat(-15.0, 15.0), Random->RandomFloat(-15.0, 15.0), 0.0f });
	}

	delete Random;
	Random = nullptr;
}
