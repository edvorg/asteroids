#include "Player.hpp"

#include <math.h>

#include "Misc.hpp"
#include "Graphics.hpp"

namespace test {

  void Player::Init() {
	tail.Init();
  }

  void Player::Update(double dt) {

	tail.Update(dt);
	tail.SetSpawning(IsSpawned());

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

	auto dirx = cos((angle + 90.0f) * M_PI / 180.0f) * 10.0f;
	auto diry = sin((angle + 90.0f) * M_PI / 180.0f) * 10.0f;

	tail.SetOwnerX(x - dirx);
	tail.SetOwnerY(y - diry);
	tail.SetOwnerSize(size * 0.5);
	tail.SetOwnerVelX(dirx);
	tail.SetOwnerVelY(diry);
	tail.FieldSize(size * 4, size * 4);
	tail.FieldPos(x - size * 2 - dirx, y - size * 2 - diry);
  }

  void Player::Draw() {
	DrawPlayer(*this);
	tail.Draw();
  }

  void Player::Release() {
	tail.Release();
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
