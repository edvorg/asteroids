#include "Asteroid.hpp"

#include "Misc.hpp"
#include "Graphics.hpp"

namespace test {

  void Asteroid::Init() {
	tail.Init();
  }

  void Asteroid::Update(double dt) {
	x += velX * dt;
	y += velY * dt;
	angle += velAngle * dt;
	tail.Update(dt);
	tail.SetOwnerX(x);
	tail.SetOwnerY(y);
	tail.SetOwnerVelX(velX);
	tail.SetOwnerVelY(velY);
	tail.SetOwnerSize(size);
	lifeTimer += dt;
  }

  void Asteroid::Draw() {
	DrawAsteroid(*this);
	tail.Draw();
  }

  void Asteroid::Release() {
	tail.Release();
  }

  Dimensions Asteroid::GetDimensions() const {
	return Dimensions(x, y, size);
  }

  Asteroid & Asteroid::operator =(const Asteroid & another) {
	x = another.x;
	y = another.y;
	angle = another.angle;
	size = another.size;
	velX = another.velX;
	velY = another.velY;
	velAngle = another.velAngle;
	dead = another.dead;
	lifeTimer = another.lifeTimer;
	return *this;
  }

}
