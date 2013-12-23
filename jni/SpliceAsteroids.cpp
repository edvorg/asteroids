#include "SpliceAsteroids.hpp"

#include <algorithm>
#include "Misc.hpp"

namespace test {

  void SpliceAsteroids::Init() {
	Asteroids::Init();

	auto topPostSpawn = TopPostSpawn();

	PushPeriod([this] {
		if (active) {
		  return spawnPeriodActive;
		}
		else {
		  return spawnPeriodPassive;
		}
	  });

	// use some generated data from Super and modify for our task

	PushPostSpawn([this, topPostSpawn] (Asteroid & created) {
		// call old callback

		topPostSpawn(created);

		// change some settings

		created.SetPos(Rand(- GetFieldWidth() * 0.5f, 0.0f, 0.1f),
					   Rand(GetFieldHeight() * 0.5f, GetFieldHeight() * 1.5f, 0.1f));
		created.SetVel(GetFieldWidth() * 0.25,
					   - GetFieldHeight() * 0.125);

		if (leftToRight) {
		  created.IncPosX(GetFieldWidth() * 2.0f);
		  created.DecVelX(- created.GetVelX());
		}
	  });
  }

  void SpliceAsteroids::Update(double dt) {
	Asteroids::Update(dt);

	if (active) {
	  spawnPeriodActiveTimer += dt;
	  if (spawnPeriodActiveTimer > spawnPeriodActivePeriod) {
		spawnPeriodActiveTimer = 0.0f;
		active = false;
	  }
	}
	else {
	  spawnPeriodPassiveTimer += dt;
	  if (spawnPeriodPassiveTimer > spawnPeriodPassivePeriod) {
		spawnPeriodPassiveTimer = 0.0f;
		active = true;
		leftToRight = rand() % 2;
	  }
	}
  }

  void SpliceAsteroids::SetLevel(unsigned int newLevel) {
	if (level != newLevel) {
	  level = newLevel;
	  auto l = level + 1;
	  spawnPeriodActive = spawnPeriodActiveInitial / l / l;
	  spawnPeriodPassive = spawnPeriodPassiveInitial / l / l;
	  spawnPeriodActiveTimer = 0.0f;
	  spawnPeriodPassiveTimer = 0.0f;
	}
  }

}
