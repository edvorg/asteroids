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

	PushPostSpawn([this] (Asteroid & a) {
		a.size = Rand<double>(1, 10, 1);
		a.x = Rand<double>(0, GetFieldWidth(), 1);
		a.y = Rand<float>(GetFieldHeight() + a.size,
						  GetFieldHeight() * 1.5, 0.1);
		a.angle = 0;
		a.velX = Rand<double>(0.1, 1.0, 0.1);
		a.velY = Rand<double>(-10, -30, -1);
		a.velAngle = Rand<double>(-90.0, 90.0, 1.0);
		a.lifeTimer = 0.0f;
		a.tail.FieldSize(GetFieldWidth(), GetFieldHeight());
		a.tail.FieldPos(0, 0);
	  });

	PushPreDestroy([this] (Asteroid & destroyed) {
		if (destroyed.size > minCrushSize) {
		  // crush asteroid in smaller parts

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
