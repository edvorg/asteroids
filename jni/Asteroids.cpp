#include "Asteroids.hpp"

#include <algorithm>
#include "Misc.hpp"
#include <math.h>

namespace test {

  void Asteroids::Init() {
	Super::Init();

	PushPeriod([this] {
		return Rand<float>(periodMin, periodMax, 0.01);
	  });

	PushPreDestroy([&] (Asteroid & destroyed) {
		if (destroyed.size > minCrushSize) {
		  float awayAngle = rand() % 180 / 179.0f * M_PI * 2.0f;

		  for (unsigned int i = 0; i < crushPartsCount; ++i) {
			PushPostSpawn([&] (Asteroid & created) {
				float dirx = cosf(awayAngle);
				float diry = sinf(awayAngle);

				created.size = destroyed.size / 3.0;
				created.x = destroyed.x + dirx * created.size;
				created.y = destroyed.y + diry * created.size;

				dirx *= crushPartsAwayVel;
				diry *= crushPartsAwayVel;

				created.velX = destroyed.velX + dirx;
				created.velY = destroyed.velY + diry;

				awayAngle += M_PI * 2.0f / 3.0f;
			  });
			Spawn();
			PopPostSpawn();
		  }
		}
	  });
  }

  void Asteroids::Update(double dt) {
	Super::Update(dt);
  }

  void Asteroids::SetLevel(unsigned int level) {
	auto l = level + 1;
	periodMin = periodMinInitial / l / l;
	periodMax = periodMaxInitial / l;
  }

}
