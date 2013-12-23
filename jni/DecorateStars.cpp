#include "DecorateStars.hpp"

namespace test {

  void DecorateStars::Init() {
	Super::Init();
	Super::Resize(poolSize);

	PushPostSpawn([this] (DecorateStar & star) {
		star.size = Rand<double>(0.5, 5, 1);
		star.x = Rand<double>(0, GetFieldWidth(), 1);
		star.y = GetFieldHeight() + star.size;
		star.velX = Rand<double>(0.1, 1.0, 0.1);
		star.velY = Rand<double>(-10, -40, -1) * star.size;
		star.lifeTimer = 0.0f;
	  });

	PushPeriod([] {
		return 0.01;
	  });
  }

}
