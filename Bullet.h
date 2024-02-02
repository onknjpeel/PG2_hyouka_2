#pragma once
#include "Vector2.h"
class Bullet
{
private:
	Vector2 pos_;
	float speed_;
	float radius_;
	bool isShot_;
public:
	Bullet(Vector2 pos, float speed, float radius, bool isShot);
	~Bullet();
	void Move();
	void Draw();
	bool GetFlag() { return isShot_; }
	Vector2 GetPos() { return pos_; }
	float GetRadius() { return radius_; }
	void SetFlag(bool isShot);
	void SetPos(Vector2 pos);
	void Reset(Vector2 pos, bool isShot);
	void Collision(Vector2 pos, float radius);
};

