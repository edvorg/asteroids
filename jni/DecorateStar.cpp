#include "DecorateStar.hpp"

#include "Misc.hpp"
#include "RandomizeParams.hpp"
#include "Graphics.hpp"

namespace test {

  void DecorateStar::Init() {

  }

  void DecorateStar::Update(double dt) {
	x += velX * dt;
	y += velY * dt;
	lifeTimer += dt;
  }

  void DecorateStar::Draw() {
	DrawDecorateStar(*this);
  }

  void DecorateStar::Release() {

  }

  void DecorateStar::Respawn(const test::RandomizeParams &params) {
	size = Rand<double>(0.5, 5, 1);
	x = Rand<double>(0, params.fieldWidth, 1);
	y = params.fieldHeight + size;
	velX = Rand<double>(0.1, 1.0, 0.1);
	velY = Rand<double>(-10, -40, -1) * size;
	lifeTimer = 0.0f;
  }

  Dimensions DecorateStar::GetDimensions() const {
	return Dimensions(x, y, size);
  }

}
