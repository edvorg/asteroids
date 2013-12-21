#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>
#include <functional>

#include "RandomizeParams.hpp"
#include "Misc.hpp"

namespace test {

  template<class PARTICLE>
  class ParticleSystem {

  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();

	void Collide(const Dimensions & dimensions, std::function<void ()> callback);

	// some application parameters
	void FieldSize(float newWidth, float newHeight);

  protected:
  private:
	void Spawn();
	void Destroy(unsigned int index);

	std::vector<PARTICLE> pool;
	int poolSize = 100;
	double spawnTimer = 0.0;
	double spawnPeriod = 1.0;
	int used = 0;
	RandomizeParams params;
  };

  template <class PARTICLE> void ParticleSystem<PARTICLE>::Init() {
	pool.resize(poolSize);
  }

  template <class PARTICLE> void ParticleSystem<PARTICLE>::Update(double dt) {
	// spawn new pool on field
	spawnTimer += dt;
	if (spawnTimer > spawnPeriod && used < poolSize) {
	  Spawn();
	  spawnTimer = 0;
	  spawnPeriod = Rand(0.25, 1.0, 0.01);
	}

	// update active pool
	for (unsigned int i = 0; i < used; ++i) {
	  pool[i].Update(dt);

	  if (pool[i].y < - 1.0 - pool[i].size) {
		Destroy(i);
	  }
	}
  }

  template <class PARTICLE> void ParticleSystem<PARTICLE>::Draw() {
	for (unsigned int i = 0; i < used; ++i) {
		pool[i].Draw();
	}
  }

  template <class PARTICLE> void ParticleSystem<PARTICLE>::Release() {
  }

  template <class PARTICLE> void ParticleSystem<PARTICLE>::Collide(const Dimensions & dimensions, std::function<void ()> callback) {
	bool collided = false;
	for (unsigned int i = 0; i < used; ++i) {
	  if (dimensions.Intersect(pool[i].GetDimensions())) {
		Destroy(i);
		collided = true;
	  }
	}

	if (collided) {
	  callback();
	}
  }

  template <class PARTICLE> void ParticleSystem<PARTICLE>::FieldSize(float newWidth, float newHeight) {
	params.fieldWidth = newWidth;
	params.fieldHeight = newHeight;

	for (unsigned int i = 0; i < used; ++i) {
	  pool[i].use = false;
	}
	used = 0;
  }

  template <class PARTICLE> void ParticleSystem<PARTICLE>::Spawn() {
	if (used < poolSize) {
	  pool[used].use = true;
	  pool[used].Respawn(params);
	  used++;
	}
  }

  template <class PARTICLE> void ParticleSystem<PARTICLE>::Destroy(unsigned int index) {
	if (index < used) {
	  pool[index].use = false;
	  used--;

	  if (pool[used].use) {
		pool[index] = pool[used];
		pool[used].use = false;
	  }
	}
  }
}

#endif// PARTICLESYSTEM_HPP
