#include "EnemyA.h"
#include "Novice.h"
#include "GetColor.h"
#include <cmath>

Enemy::Enemy(Vector2 pos, Vector2 speed, float radius, int lifes, bool isAlive, bool isExplode, bool isHit)
{
	pos_ = pos;
	speed_ = speed;
	radius_ = radius;
	lifes_ = lifes;
	isAlive_ = isAlive;
	isExplode_ = isExplode;
	isHit_ = isHit;
}

Enemy::~Enemy()
{
}

void Enemy::ColorSet(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
{
	red_ = red;
	green_ = green;
	blue_ = blue;
	alpha_ = alpha;
}

void Enemy::Explode()
{
	if (lifes_ <= 0) {
		isAlive_ = false;
		isExplode_ = true;
	}
	if (isExplode_) {
		if (alpha_ != 0) {
			alpha_ -= 5;
			radius_ += 5;
		}
	}
}

void Enemy::Move()
{
	if (isAlive_) {
		if (pos_.x > 1180) {
			pos_.x -= speed_.x;
		}
		else {
			pos_.y += speed_.y;
			if (pos_.y + radius_ > 720 || pos_.y - radius_ < 0) {
				speed_.y *= -1;
			}
		}
	}
}

void Enemy::Draw()
{
	if (alpha_ != 0) {
		Novice::DrawEllipse(
			int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f,
			GetColor(red_, green_, blue_, alpha_), kFillModeSolid);
	}
}

void Enemy::Reset(Vector2 pos, float radius, int lifes, bool isAlive, bool isExplode, bool isHit, unsigned int alpha)
{
	pos_ = pos;
	radius_ = radius;
	lifes_ = lifes;
	isAlive_ = isAlive;
	isExplode_ = isExplode;
	isHit_ = isHit;
	alpha_ = alpha;
}

void Enemy::Collision(Vector2 pos, float radius)
{
	if (isAlive_) {
		float distance = float(std::sqrt(std::pow(pos.x - pos_.x, 2) + std::pow(pos.y - pos_.y, 2)));
		if (distance < (radius_ + radius)) {
			if (!isHit_) {
				isHit_ = true;
				lifes_--;
			}
		}
	}
}

void Enemy::Update()
{
	if (isHit_) {
		coolTime_--;
		if (coolTime_ <= 0) {
			isHit_ = false;
		}
	}
	else {
		coolTime_ = 10;
	}
}