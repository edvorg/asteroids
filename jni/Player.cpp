#include "Player.hpp"

#include <math.h>

#include "Misc.hpp"
#include "Graphics.hpp"

namespace test {

  void Player::Init() {

  }

  void Player::Update(double dt) {

	if (!IsSpawned()) {
	  respawnTimer += dt;
	  return;
	}

	float deltaX = targetX - x;
	float deltaY = targetY - y;
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	if (distance > 0.1f) {
	  if (distance > 15.0f) { // acceleration
		velX += acceleration;
		velY += acceleration;
	  }
	  else { // deceleration
		velX /= deceleration;
		velY /= deceleration;
	  }

	  x += deltaX * velX;
	  y += deltaY * velY;

	  // look in direction of finger

	  deltaX /= distance;
	  angle = acos(deltaX) / M_PI * 180.0f;
	  if (deltaY < 0.0) {
		angle *= - 1.0f;
	  }
	  angle -= 90.0f;
	}

	x += velX;
	y += velY;
  }

  void Player::Draw() {
	DrawPlayer(*this);
  }

  void Player::Release() {
  }

  void Player::Kill() {
	if (spawned) {
	  spawned = false;
	  lives = std::max<int>(lives - 1, 0);
	  respawnTimer = 0.0f;
	}
  }

  void Player::Touch(float newX, float newY) {

	if (!spawned && respawnTimer > respawnPeriod) {
	  spawned = true;
	  x = newX;
	  y = newY;
	  angle = 0.0f;
	  velX = 0.0f;
	  velY = 0.0f;
	  targetX = newX;
	  targetY = newY;
	  size = 7.0f;
	  respawnTimer = 0.0f;
	  active = true;
	}
	else {
	  targetX = newX;
	  targetY = newY;
	}
  }

  void Player::Reset() {
	lives = livesInitial;
	active = false;
	respawnTimer = respawnPeriod + 1.0f;
  }

  Dimensions Player::GetDimensions() const {
	return Dimensions(x, y, size * 0.5);
  }

}
