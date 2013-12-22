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
	tail.FieldSize(10 * size, 10 * size);
	tail.FieldPos(x - 5 * size, y - 5 * size);
  }

  void Asteroid::Draw() {
	DrawAsteroid(*this);
	tail.Draw();
  }

  void Asteroid::Release() {
	tail.Release();
  }

  void Asteroid::Respawn(const RandomizeParams & params) {
	size = Rand<double>(1, 10, 1);
	x = Rand<double>(0, params.fieldWidth, 1);
	y = Rand<float>(params.fieldHeight + size, params.fieldHeight * 1.5, 0.1);
	angle = 0;
	velX = Rand<double>(0.1, 1.0, 0.1);
	velY = Rand<double>(-10, -30, -1);
	velAngle = Rand<double>(-90.0, 90.0, 1.0);
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
	return *this;
  }

}
