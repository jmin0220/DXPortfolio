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
	// 5���¥�� ����
	int GoldFive = GoldValue / 5;
	// 1���¥�� ����
	int GoldOne = GoldValue % 5;
	float4 _RealPos = { _Pos.x, _Pos.y, static_cast<float>(ZOrder::Drops) };

	GameEngineRandom* Random = new GameEngineRandom();

	// 5��� ���
	for (int i = 0; i < GoldFive; i++)
	{
		// ��� ����
		Gold* tmpGold = _Level->CreateActor<Gold>();
		tmpGold->GetTransform().SetWorldPosition(_RealPos);
		tmpGold->SetGoldValue(5);
		tmpGold->UpdateGoldOption();

		// ��尡 �����ɶ� ������ ������ ����
		tmpGold->SetFlyDir({ Random->RandomFloat(-50.0, 50.0), 0.0f, 0.0f });
		tmpGold->GoldPop();

	}

	// 1��� ���
	for (int i = 0; i < GoldOne; i++)
	{
		// ��� ����
		Gold* tmpGold = _Level->CreateActor<Gold>();
		tmpGold->GetTransform().SetWorldPosition(_RealPos);
		tmpGold->SetGoldValue(1);
		tmpGold->UpdateGoldOption();

		// ��尡 �����ɶ� ������ ������ ����
		tmpGold->SetFlyDir({ Random->RandomFloat(-50.0, 50.0), 0.0f, 0.0f });
		tmpGold->GoldPop();
	}


	// ����ġ ����
	int ExpValue = _ExpValue;
	// 5����ġ¥�� ���� -> �������� ������
	int ExpFive = ExpValue / 5;
	// 1����ġ¥�� ����
	int ExpOne = ExpValue % 5;

	// 5����ġ ���
	for (int i = 0; i < ExpFive; i++)
	{
		// ����ġ ����
		Exp* tmpExp = _Level->CreateActor<Exp>();
		tmpExp->GetTransform().SetWorldPosition(_RealPos);
		tmpExp->SetExpValue(5);

		// ����ġ�� �����ɶ� ���� �̵���ġ�� ����
		tmpExp->SetDestPos({ Random->RandomFloat(-20.0, 20.0), Random->RandomFloat(-20.0, 20.0), 0.0f });
	}

	// 1����ġ ���
	for (int i = 0; i < ExpOne; i++)
	{
		// ����ġ ����
		Exp* tmpExp = _Level->CreateActor<Exp>();
		tmpExp->GetTransform().SetWorldPosition(_RealPos);
		tmpExp->SetExpValue(5);

		// ����ġ�� �����ɶ� ���� �̵���ġ�� ����
		tmpExp->SetDestPos({ Random->RandomFloat(-20.0, 20.0), Random->RandomFloat(-20.0, 20.0), 0.0f });
	}

	delete Random;
	Random = nullptr;
}
