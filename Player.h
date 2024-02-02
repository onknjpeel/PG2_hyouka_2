#pragma once
#include "Vector2.h"
#include "Bullet.h"
class Player
{
private:
	Vector2 pos_;
	float speed_;
	float radius_;
	int lifes_;
	bool isAlive_;
	bool isExplode_;
	bool isHit_;
	int coolTime_;
public:
	Bullet* bullet_[20];
public:
	Player(Vector2 pos, float speed, float radius, int lifes, bool isAlive, bool isExplode,bool isHit);
	~Player();
	void Move(const char* keys);
	void Draw();
	Vector2 GetPos() { return pos_; }
	float GetRadius() { return radius_; }
	int GetLifes() { return lifes_; }
	void Reset(Vector2 pos, float radius, int lifes, bool isAlive, bool isExplode,bool isHit);
	void Collision(Vector2 pos, float radius);
	void Explode();
	void Update();
};

