#include "CometTail.hpp"

#include <math.h>

#include "Misc.hpp"

namespace test {

  void CometTail::Init() {
	Super::Init();

	PushPeriod([] {
		return 0.001;
	  });

	PushPostSpawn([&] (DecorateStar & star) {
		// throw particles from back of owner orientation
        float angle = Rand<float>(0.0, M_PI * 2.0, 0.01);
        float rad = Rand<float>(0.0, ownerSize, 0.01);
		star.x = ownerX + cos(angle) * rad;
		star.y = ownerY + sin(angle) * rad;
		star.velX = - ownerVelX;
		star.velY = - ownerVelY;
	  });

	PushLife([] {
		return 0.5f;
	  });
  }

  void CometTail::Update(double dt) {
	Super::Update(dt);
  }

}
