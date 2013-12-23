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

  Dimensions DecorateStar::GetDimensions() const {
	return Dimensions(x, y, size);
  }

}
