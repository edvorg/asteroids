#include "SpliceAsteroids.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

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
		created.x -= GetFieldWidth();
		created.velX = 55;
		created.velY = -35;

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
}
