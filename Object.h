#pragma once
#include "Vector2.h"
class Object
{
protected:
	Vector2 pos_;
	Vector2 speed_;
	float radius_;
	int lifes_;
	bool isAlive_;
	unsigned int red_;
	unsigned int green_;
	unsigned int blue_;
	unsigned int alpha_;
public:
	virtual void Move();
	virtual void Draw();
};

