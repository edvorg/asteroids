#include "DecorateStars.hpp"

namespace test {

  void DecorateStars::Init() {
	Super::Init();
	Super::Resize(poolSize);

	PushPeriod([] {
		return 0.01;
	  });
  }

}
