#include "CometTail.hpp"

#include <math.h>

#include "Misc.hpp"

namespace test {

  void CometTail::Init() {
	Super::Init();

	PushPeriod([] {
		return 0.001;
	  });

	PushPostSpawn([this] (DecorateStar & star) {
		// throw particles from back of owner orientation
		star.size = Rand<double>(0.5, 5, 1);
        float angle = Rand<float>(0.0, M_PI * 2.0, 0.01);
        float rad = Rand<float>(0.0, ownerSize, 0.01);
		star.x = ownerX + cos(angle) * rad;
		star.y = ownerY + sin(angle) * rad;
		star.velX = - ownerVelX;
		star.velY = - ownerVelY;
		star.lifeTimer = 0.0f;
	  });

	PushLife([] {
		return 0.5f;
	  });
  }

}
