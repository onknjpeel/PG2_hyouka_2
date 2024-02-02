#pragma once
#include "Object.h"
class Enemy : public Object
{
private:
	int appearTime_;
	bool isExplode_;
	bool isHit_;
	int coolTime_;
public:
	Enemy(Vector2 pos, Vector2 speed, float radius, int lifes, bool isAlive, bool isExplode, bool isHit);
	~Enemy();
	void ColorSet(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);
	void Explode();
	void Move();
	void Draw();
	unsigned int GetAlpha() { return alpha_; }
	Vector2 GetPos() { return pos_; }
	float GetRadius() { return radius_; }
	int GetLifes() { return lifes_; }
	void Reset(Vector2 pos, float radius, int lifes, bool isAlive, bool isExplode, bool isHit, unsigned int alpha);
	void Collision(Vector2 pos, float radius);
	void Update();
};

