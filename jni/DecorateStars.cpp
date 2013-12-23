#include "DecorateStars.hpp"

namespace test {

  void DecorateStars::Init() {
	Super::Init();
	Super::Resize(poolSize);

	PushPostSpawn([this] (DecorateStar & star) {
		star.SetSize(Rand<double>(0.5, 5, 1));
		star.SetPos(Rand<double>(0, GetFieldWidth(), 1),
					GetFieldHeight() + star.GetSize());
		star.SetVel(Rand<double>(0.1, 1.0, 0.1),
					Rand<double>(-10, -40, -1) * star.GetSize());
	  });

	PushPeriod([] {
		return 0.01;
	  });
  }

}
