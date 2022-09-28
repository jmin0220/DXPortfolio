#pragma once

// Ό³Έν :
class MissileExplosion
{
public:
	// constrcuter destructer
	MissileExplosion();
	~MissileExplosion();

	// delete Function
	MissileExplosion(const MissileExplosion& _Other) = delete;
	MissileExplosion(MissileExplosion&& _Other) noexcept = delete;
	MissileExplosion& operator=(const MissileExplosion& _Other) = delete;
	MissileExplosion& operator=(MissileExplosion&& _Other) noexcept = delete;

protected:

private:

};

