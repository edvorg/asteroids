#include "CometTail.hpp"

#include <math.h>

#include "Misc.hpp"

namespace test {

  void CometTail::Init() {
	Super::Init();
	Super::Resize(poolSize);

	PushPeriod([] {
		return 0.05;
	  });

	PushPostSpawn([this] (DecorateStar & star) {
		// throw particles from back of owner orientation
		star.SetSize(Rand<double>(0.5, 5, 1));
        float angle = Rand<float>(0.0, M_PI * 2.0, 0.01);
        float rad = Rand<float>(0.0, ownerSize, 0.01);
		star.SetPos(ownerX + cos(angle) * rad,
					ownerY + sin(angle) * rad);
		star.SetVel(- ownerVelX,
					- ownerVelY);
	  });

	PushLife([] {
		return 0.5f;
	  });
  }

}
