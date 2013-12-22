#include "CometTail.hpp"

#include <math.h>

#include "Misc.hpp"

namespace test {

  void CometTail::Init() {
	Super::Init();
	Super::Resize(poolSize);

	PushPeriod([] {
		return 0.001;
	  });

	PushPostSpawn([&] (DecorateStar & star) {
        float angle = Rand<float>(0.0, M_PI * 2.0, 0.01);
        float rad = Rand<float>(0.0, ownerSize, 0.01);
		star.x = ownerX + cos(angle) * rad;
		star.y = ownerY + sin(angle) * rad;
		star.velX = - ownerVelX * 2;
		star.velY = - ownerVelY * 2;
	  });
  }

}
