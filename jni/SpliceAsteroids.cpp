#include "SpliceAsteroids.hpp"

#include <algorithm>
#include "Misc.hpp"

namespace test {

  void SpliceAsteroids::Init() {
	Asteroids::Init();

	PushPeriod([this] {
		if (active) {
		  return spawnPeriodActive;
		}
		else {
		  return spawnPeriodPassive;
		}
	  });

	PushPostSpawn([&] (Asteroid & created) {
		created.x = Rand(- GetFieldWidth() * 0.5f,
						 0.0f,
						 0.1f);
		created.y = Rand(GetFieldHeight() * 0.5f,
						 GetFieldHeight() * 1.5f,
						 0.1f);
		created.velX = GetFieldWidth() * 0.25;
		created.velY = - GetFieldHeight() * 0.125;

		if (leftToRight) {
		  created.x += GetFieldWidth() * 2.0f;
		  created.velX = - created.velX;
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
