#include "PreCompile.h"
#include "Drone.h"
#include "Option.h"

float4 Drone::PlayerPos_ = float4::ZERO;
float4 Drone::PlayerDir_ = float4::ZERO;

Drone::Drone() 
	: Speed_(Player_MOVE_SPEED)
	, MovedYPos_(0.0f)
	, Ypos_(30.0f)
{
}

Drone::~Drone() 
{
}

void Drone::Start()
{
	AnimInit();

	StateInit();
}

void Drone::Update(float _DeltaTime)
{
	Move(_DeltaTime);

	// 스테이트 업데이트
	StateManager_.Update(_DeltaTime);

	if (true == Option::DestroyDrone_)
	{
		this->Death();
	}
}

void Drone::LevelEndEvent()
{
	this->SetLevelOverOn();
}

void Drone::Move(float _DeltaTime)
{
	// 상하 이동
	MovedYPos_ += Ypos_ * _DeltaTime;	// 이동한 거리

	// 10.0f이상 이동했으면 위아래 반전
	if (abs(MovedYPos_) > 25.0f)
	{
		Ypos_ *= -1.0f;
		MovedYPos_ = 0.0f;
	}

	// 좌우이동
	float4 DestPos = 0.0f;
	float DroneDir = 0.0f;
	// 방향에 따라 위치를 조정
	if (PlayerDir_.CompareInt2D(float4::RIGHT))
	{
		DroneDir = -25.0f;
		
	}
	else
	{
		DroneDir = 25.0f;
	}

	if (GetAccTime() >= 1.0f)
	{
		ReSetAccTime();
	}


	float4 tmpPlayerPos = { PlayerPos_.x + DroneDir, PlayerPos_.y + 10.0f, PlayerPos_.z};
	tmpPlayerPos.x += 5.0f;
	tmpPlayerPos.y += 5.0f;


	// 이동할 X값 결정
	DestPos = float4::Lerp(this->GetTransform().GetWorldPosition(), tmpPlayerPos, GetAccTime());

	// 최종이동
	this->GetTransform().SetWorldPosition({ DestPos.x, DestPos.y, static_cast<float>(ZOrder::Player) });
	Renderer_->GetTransform().SetLocalMove({ 0.0f, Ypos_ * _DeltaTime, 0.0f });
	
	CheckNegativeX();
}

void Drone::CheckNegativeX()
{
	if (PlayerDir_.CompareInt3D(float4::LEFT))
	{
		// 좌우반전
		Renderer_->GetTransform().PixLocalNegativeX();
	}
	else
	{
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	Renderer_->SetPivot(PIVOTMODE::CENTER);
}