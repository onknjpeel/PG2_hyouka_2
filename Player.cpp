#include "Player.h"
#include "Novice.h"
#include <cmath>

Player::Player(Vector2 pos, float speed, float radius, int lifes, bool isAlive, bool isExplode, bool isHit)
{
	pos_ = pos;
	speed_ = speed;
	radius_ = radius;
	lifes_ = lifes;
	isAlive_ = isAlive;
	isExplode_ = isExplode;
	isHit_ = isHit;
	for (int i = 0; i < 20; i++) {
		bullet_[i] = new Bullet({ -100,-100 }, 10, 10, false);
	}
}

Player::~Player()
{
}

void Player::Move(const char* keys)
{
	if (isAlive_) {
		if (keys[DIK_W]) {
			pos_.y -= speed_;
		}
		if (keys[DIK_S]) {
			pos_.y += speed_;
		}
		if (keys[DIK_A]) {
			pos_.x -= speed_;
		}
		if (keys[DIK_D]) {
			pos_.x += speed_;
		}
	}
}

void Player::Draw()
{
	if (isAlive_) {
		Novice::DrawEllipse(int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, GREEN, kFillModeSolid);
	}
}

void Player::Reset(Vector2 pos, float radius, int lifes, bool isAlive, bool isExplode, bool isHit)
{
	pos_ = pos;
	radius_ = radius;
	lifes_ = lifes;
	isAlive_ = isAlive;
	isExplode_ = isExplode;
	isHit_ = isHit;
}

void Player::Collision(Vector2 pos, float radius)
{
	float distance = float(std::sqrt(std::pow(pos.x - pos_.x, 2) + std::pow(pos.y - pos_.y, 2)));
	if (distance < (radius_ + radius)) {
		if (!isHit_) {
			isHit_ = true;
			lifes_ -= 1;
		}
	}
}

void Player::Explode()
{
	if (lifes_ <= 0) {
		isAlive_ = false;
		isExplode_ = true;
	}
	if (isExplode_) {
		if (radius_ != 0) {
			radius_ -= 1;
		}
	}
}

void Player::Update()
{
	if (isHit_) {
		coolTime_--;
		if (coolTime_ <= 0) {
			isHit_ = false;
		}
	}
	else {
		coolTime_ = 60;
	}
}
