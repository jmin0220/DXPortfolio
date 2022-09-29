#include "PreCompile.h"
#include "Drone.h"

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
}

void Drone::Update(float _DeltaTime)
{
	Move(_DeltaTime);
}

void Drone::Move(float _DeltaTime)
{
	// ���� �̵�
	MovedYPos_ += Ypos_ * _DeltaTime;	// �̵��� �Ÿ�

	// 10.0f�̻� �̵������� ���Ʒ� ����
	if (abs(MovedYPos_) > 25.0f)
	{
		Ypos_ *= -1.0f;
		MovedYPos_ = 0.0f;
	}

	// �¿��̵�
	float4 DestPos = 0.0f;
	float DroneDir = 0.0f;
	// ���⿡ ���� ��ġ�� ����
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

	PlayerPos_.x += DroneDir;
	PlayerPos_.y += 10.0f;

	// �̵��� X�� ����
	DestPos = float4::Lerp(this->GetTransform().GetWorldPosition(), PlayerPos_, GetAccTime());

	// �����̵�
	this->GetTransform().SetWorldPosition({ DestPos.x, DestPos.y, static_cast<float>(ZOrder::Player) });
	Renderer_->GetTransform().SetLocalMove({ 0.0f, Ypos_ * _DeltaTime, 0.0f });
	
	CheckNegativeX();
}

void Drone::CheckNegativeX()
{
	if (PlayerDir_.CompareInt3D(float4::LEFT))
	{
		// �¿����
		Renderer_->GetTransform().PixLocalNegativeX();
	}
	else
	{
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	Renderer_->SetPivot(PIVOTMODE::CENTER);
}