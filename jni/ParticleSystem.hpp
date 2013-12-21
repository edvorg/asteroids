#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>
#include <functional>

#include "RandomizeParams.hpp"
#include "Misc.hpp"
#include "Dimensions.hpp"

namespace test {

  template<class PARTICLE>
  class ParticleSystem {

  public:
	using PostSpawn = std::function<void (PARTICLE &)>;
	using Period = std::function<float ()>;

	ParticleSystem() = default;
	virtual ~ParticleSystem() = default;

	virtual void Init();
	virtual void Update(double dt);
	virtual void Draw();
	virtual void Release();

	void Collide(const Dimensions & dimensions, std::function<void ()> callback);
	template<class ANOTHER>
	void Collide(ParticleSystem<ANOTHER> & another);

	// some application parameters
	void FieldSize(float newWidth, float newHeight);
	void SetPeriod(Period newPeriod);
	void SetPostSpawn(PostSpawn newPostSpawn);
	void SetSpawning(bool enable);

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
	bool spawning = true;

	// customization functions
	// must return particles spawn period
	Period period = [] { return 1.0f; };
	// optional particle post process after creation
	PostSpawn postSpawn = [] (PARTICLE &) {};
  };

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Init() {
	pool.resize(poolSize);
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Update(double dt) {
	// spawn new pool on field
	if (spawning) {
	  spawnTimer += dt;
	  if (spawnTimer > spawnPeriod && used < poolSize) {
		Spawn();
		spawnTimer = 0;
		spawnPeriod = period();
	  }
	}

	// update active pool
	for (unsigned int i = 0; i < used; ++i) {
	  pool[i].Update(dt);

	  if (pool[i].y < - pool[i].size ||
		  pool[i].y > params.fieldHeight + pool[i].size ||
		  pool[i].x < - pool[i].size ||
		  pool[i].x > params.fieldWidth + pool[i].size) {
		Destroy(i);
	  }
	}
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Draw() {
	for (unsigned int i = 0; i < used; ++i) {
	  pool[i].Draw();
	}
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Release() {
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Collide(const Dimensions & dimensions, std::function<void ()> callback) {
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

  template<class PARTICLE>
  template <class ANOTHER>
  void ParticleSystem<PARTICLE>::Collide(ParticleSystem<ANOTHER> & another) {
	// TODO optimize this. complexity n^2 now, use aabb or something else

	unsigned int i = 0;
	auto callback = [&] {
	  Destroy(i);
	};

	for (; i < used; ++i) {
	  another.Collide(pool[i].GetDimensions(), callback);
	}
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::FieldSize(float newWidth, float newHeight) {
	params.fieldWidth = newWidth;
	params.fieldHeight = newHeight;

	for (unsigned int i = 0; i < used; ++i) {
	  pool[i].use = false;
	}
	used = 0;
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::SetPeriod(Period newPeriod) {
	period = newPeriod;
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::SetPostSpawn(PostSpawn newPostSpawn) {
	postSpawn = newPostSpawn;
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::SetSpawning(bool enable) {
	spawning = enable;
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Spawn() {
	if (used < poolSize) {
	  auto index = used;
	  used++;
	  pool[index].use = true;
	  pool[index].Respawn(params);

	  postSpawn(pool[index]);
	}
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Destroy(unsigned int index) {
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
