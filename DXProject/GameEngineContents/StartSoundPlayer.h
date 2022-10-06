#pragma once

// Ό³Έν :
class StartSoundPlayer
{
public:
	// constrcuter destructer
	StartSoundPlayer();
	~StartSoundPlayer();

	// delete Function
	StartSoundPlayer(const StartSoundPlayer& _Other) = delete;
	StartSoundPlayer(StartSoundPlayer&& _Other) noexcept = delete;
	StartSoundPlayer& operator=(const StartSoundPlayer& _Other) = delete;
	StartSoundPlayer& operator=(StartSoundPlayer&& _Other) noexcept = delete;

	static GameEngineSoundPlayer SoundPlayer_;
};

