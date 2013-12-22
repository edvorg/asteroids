#include "Asteroid.hpp"

#include "Misc.hpp"
#include "Graphics.hpp"

namespace test {

  void Asteroid::Update(double dt) {
	x += velX * dt;
	y += velY * dt;
	angle += velAngle * dt;
  }

  void Asteroid::Draw() {
	DrawAsteroid(*this);
  }

  void Asteroid::Respawn(const RandomizeParams & params) {
	size = Rand<double>(1, 10, 1);
	x = Rand<double>(0, params.fieldWidth, 1);
	y = params.fieldHeight + size;
	angle = 0;
	velX = Rand<double>(0.1, 1.0, 0.1);
	velY = Rand<double>(-10, -30, -1);
	velAngle = Rand<double>(-90.0, 90.0, 1.0);
  }

  Dimensions Asteroid::GetDimensions() const {
	return Dimensions(x, y, size);
  }

}
