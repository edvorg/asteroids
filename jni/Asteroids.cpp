#include "Asteroids.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <algorithm>
#include "Misc.hpp"

namespace test {

  void Asteroids::Init() {
	asteroids.resize(poolSize);
  }

  void Asteroids::Update(double dt) {
	// spawn new asteroids on field
	spawnTimer += dt;
	if (spawnTimer > spawnPeriod && used < poolSize) {
	  Spawn();
	  spawnTimer = 0;
	  spawnPeriod = Rand(0.25, 1.0, 0.01);
	}

	// update active asteroids
	for (unsigned int i = 0; i < used; i++) {
	  asteroids[i].Update(dt);

	  if (asteroids[i].y < - 1.0 - asteroids[i].size) {
		asteroids[i].use = false;
		used--;

		if (asteroids[used].use) {
		  asteroids[i] = asteroids[used];
		  asteroids[used].use = false;
		}
	  }
	}
  }

  void Asteroids::Draw() {
	for (unsigned int i = 0; i < used; i++) {
		asteroids[i].Draw();
	}
  }

  void Asteroids::Release() {
  }

  void Asteroids::Spawn() {
	if (used < poolSize) {
	  asteroids[used].use = true;
	  asteroids[used].Respawn();
	  used++;
	}
  }
}
