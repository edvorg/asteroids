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

  Dimensions Bullet::GetDimensions() const {
	return Dimensions(x, y, size);
  }

}
