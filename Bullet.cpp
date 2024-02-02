#include "Bullet.h"
#include "Novice.h"
#include <cmath>

Bullet::Bullet(Vector2 pos, float speed, float radius, bool isShot)
{
	pos_ = pos;
	speed_ = speed;
	radius_ = radius;
	isShot_ = isShot;
}

Bullet::~Bullet()
{
}

void Bullet::Move()
{
	if (isShot_) {
		pos_.x += speed_;
	}
	if (pos_.x - radius_ > 1280) {
		isShot_ = false;
		pos_ = { -100,-100 };
	}
}

void Bullet::Draw()
{
	if (isShot_) {
		Novice::DrawEllipse(int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, WHITE, kFillModeSolid);
	}
}

void Bullet::SetFlag(bool isShot)
{
	isShot_ = isShot;
}

void Bullet::SetPos(Vector2 pos)
{
	pos_ = pos;
}

void Bullet::Reset(Vector2 pos, bool isShot)
{
	pos_ = pos;
	isShot_ = isShot;
}

void Bullet::Collision(Vector2 pos, float radius)
{
	if (isShot_) {
		float distance = float(std::sqrt(std::pow(pos.x - pos_.x, 2) + std::pow(pos.y - pos_.y, 2)));
		if (distance < (radius_ + radius)) {
			isShot_ = false;
		}
	}
}
