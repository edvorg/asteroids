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
	for (unsigned int i = 0; i < used; ++i) {
	  asteroids[i].Update(dt);

	  if (asteroids[i].y < - 1.0 - asteroids[i].size) {
		Destroy(i);
	  }
	}
  }

  void Asteroids::Draw() {
	for (unsigned int i = 0; i < used; ++i) {
		asteroids[i].Draw();
	}
  }

  void Asteroids::Release() {
  }

  void Asteroids::Collide(const Dimensions & dimensions, std::function<void ()> callback) {
	bool collided = false;
	for (unsigned int i = 0; i < used; ++i) {
	  if (dimensions.Intersect(asteroids[i].GetDimensions())) {
		Destroy(i);
		collided = true;
	  }
	}

	if (collided) {
	  callback();
	}
  }

  void Asteroids::FieldSize(float newWidth, float newHeight) {
	params.fieldWidth = newWidth;
	params.fieldHeight = newHeight;

	for (unsigned int i = 0; i < used; ++i) {
	  asteroids[i].use = false;
	}
	used = 0;
  }

  void Asteroids::Spawn() {
	if (used < poolSize) {
	  asteroids[used].use = true;
	  asteroids[used].Respawn(params);
	  used++;
	}
  }

  void Asteroids::Destroy(unsigned int index) {
	if (index < used) {
	  asteroids[index].use = false;
	  used--;

	  if (asteroids[used].use) {
		asteroids[index] = asteroids[used];
		asteroids[used].use = false;
	  }
	}
  }
}
