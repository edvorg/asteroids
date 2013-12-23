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
		a.SetSize(Rand<double>(1, 10, 1));
		a.SetPos(Rand<double>(0, GetFieldWidth(), 1),
				 Rand<float>(GetFieldHeight() + a.GetSize(),
							 GetFieldHeight() * 1.5, 0.1));
		a.SetAngle(0);
		a.SetVel(Rand<double>(0.1, 1.0, 0.1),
				 Rand<double>(-10, -30, -1));
		a.SetVelAngle(Rand<double>(-90.0, 90.0, 1.0));

		a.tail.FieldSize(GetFieldWidth(), GetFieldHeight());
		a.tail.FieldPos(0, 0);
	  });

	PushPreDestroy([this] (Asteroid & destroyed) {
		if (destroyed.GetSize() > minCrushSize) {
		  // crush asteroid in smaller parts

		  float awayAngle = rand() % 180 / 179.0f * M_PI * 2.0f;

		  for (unsigned int i = 0; i < crushPartsCount; ++i) {
			PushPostSpawn([&] (Asteroid & created) {
				float dirx = cosf(awayAngle);
				float diry = sinf(awayAngle);

				created.SetSize(destroyed.GetSize() / 3.0);
				created.SetPos(destroyed.GetPosX() + dirx * created.GetSize(),
							   destroyed.GetPosY() + diry * created.GetSize());

				dirx *= crushPartsAwayVel;
				diry *= crushPartsAwayVel;

				created.SetVel(destroyed.GetVelX() + dirx,
							   destroyed.GetVelY() + diry);

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
