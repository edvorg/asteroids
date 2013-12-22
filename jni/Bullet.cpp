#include "Bullet.hpp"

#include <stdlib.h>

#include "Misc.hpp"
#include "Graphics.hpp"

namespace test  {

  void Bullet::Init() {

  }

  void Bullet::Update(double dt) {
	x += velX * dt;
	y += velY * dt;
	angle += velAngle * dt;
	lifeTimer += dt;
  }

  void Bullet::Draw() {
	DrawBullet(*this);
  }

  void Bullet::Release() {

  }

  void Bullet::Respawn(const RandomizeParams & params) {
	// TODO load params from xml/json
	size = Rand<double>(1, 10, 1);
	x = Rand<double>(0, params.fieldWidth, 1);
	y = params.fieldHeight + size;
	angle = 0;
	velX = Rand<double>(0.1, 1.0, 0.1);
	velY = Rand<double>(-5, -20, -1);
	velAngle = Rand<double>(-90.0, 90.0, 1.0);
	lifeTimer = 0.0f;
  }

  Dimensions Bullet::GetDimensions() const {
	return Dimensions(x, y, size);
  }

}
