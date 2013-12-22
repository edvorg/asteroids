#include "DecorateStars.hpp"

namespace test {

  void DecorateStars::Init() {
	Super::Init();

	PushPeriod([] {
		return 0.1;
	  });
  }

}
