#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>
#include <functional>
#include <stack>

#include "RandomizeParams.hpp"
#include "Misc.hpp"
#include "Dimensions.hpp"

namespace test {

  template<class PARTICLE>
  class ParticleSystem {

  public:
	using Period = std::function<float ()>;
	using PostSpawn = std::function<void (PARTICLE &)>;
	using PreDestroy = std::function<void (PARTICLE &)>;

	ParticleSystem() = default;
	virtual ~ParticleSystem() = default;

	virtual void Init();
	virtual void Update(double dt);
	virtual void Draw();
	virtual void Release();
	virtual void Clean();
	virtual void Resize(int newSize);

	template<class ANOTHER>
	void Collide(ANOTHER & another, std::function<void (PARTICLE &, ANOTHER &)> callback);
	template<class ANOTHER>
	void Collide(ParticleSystem<ANOTHER> & another, std::function<void (PARTICLE &, ANOTHER &)> callback);

	// some application parameters
	void FieldSize(float newWidth, float newHeight);
	void PushPeriod(Period newPeriod);
	void PopPeriod();
	void PushPostSpawn(PostSpawn newPostSpawn);
	void PopPostSpawn();
	void PushPreDestroy(PreDestroy newPreDestroy);
	void PopPreDestroy();
	void SetSpawning(bool enable);

	inline float GetFieldWidth() const { return params.fieldWidth; }
	inline float GetFieldHeight() const { return params.fieldHeight; }

  protected:
	void Spawn();
	void Destroy(unsigned int index);

  private:
	std::vector<PARTICLE> pool;
	int poolSize = 100;
	double spawnTimer = 0.0;
	double spawnPeriod = 1.0;
	int used = 0;
	RandomizeParams params;
	bool spawning = true;

	// customization functions
	// must return particles spawn period
	std::stack<Period> periods;
	// optional particle post process after creation
	std::stack<PostSpawn> postSpawns;
	// optional particle pre process after destroy
	std::stack<PreDestroy> preDestroys;
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
	  if (periods.size()) {
		spawnPeriod = periods.top()();
	  }
	  if (spawnTimer > spawnPeriod && used < poolSize) {
		Spawn();
		spawnTimer = 0;
	  }
	}

	// update active pool
	for (unsigned int i = 0; i < used; ++i) {
	  pool[i].Update(dt);

	  if (pool[i].dead ||
		  pool[i].y < - params.fieldHeight ||
		  pool[i].y > params.fieldHeight * 2.0f ||
		  pool[i].x < - params.fieldWidth ||
		  pool[i].x > params.fieldWidth * 2.0f) {
		pool[i].dead = false;
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
  void ParticleSystem<PARTICLE>::Clean() {
	for (unsigned int i = 0; i < used; ++i) {
	  pool[i].use = false;
	}
	used = 0;
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Resize(int newSize) {
	pool.resize(newSize);
	poolSize = newSize;
	for (unsigned int i = 0; i < used; ++i) {
	  pool[i].use = false;
	}
	used = 0;
  }

  template<class PARTICLE>
  template <class ANOTHER>
  void ParticleSystem<PARTICLE>::Collide(ANOTHER & another, std::function<void (PARTICLE &, ANOTHER &)> callback) {
	for (unsigned int i = 0; i < used; ++i) {
	  if (another.GetDimensions().Intersect(pool[i].GetDimensions())) {
		callback(pool[i], another);
	  }
	}
  }

  template<class PARTICLE>
  template <class ANOTHER>
  void ParticleSystem<PARTICLE>::Collide(ParticleSystem<ANOTHER> & another, std::function<void (PARTICLE &, ANOTHER &)> callback) {
	// TODO optimize this. complexity n^2 now, use aabb or something else
	auto reversed = [&] (ANOTHER & a, PARTICLE & p) {
	  callback(p, a);
	};
	for (unsigned i = 0; i < used; i++) {
	  another.template Collide<PARTICLE>(pool[i], reversed);
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
  void ParticleSystem<PARTICLE>::PushPeriod(Period newPeriod) {
	periods.push(newPeriod);
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::PopPeriod() {
	if (periods.size()) {
	  periods.pop();
	}
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::PushPostSpawn(PostSpawn newPostSpawn) {
	postSpawns.push(newPostSpawn);
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::PopPostSpawn() {
	if (postSpawns.size()) {
	  postSpawns.pop();
	}
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::PushPreDestroy(PreDestroy newPreDestroy) {
	preDestroys.push(newPreDestroy);
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::PopPreDestroy() {
	if (preDestroys.size()) {
	  preDestroys.pop();
	}
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
	  if (postSpawns.size()) {
		postSpawns.top()(pool[index]);
	  }
	}
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Destroy(unsigned int index) {
	if (index < used) {
	  if (preDestroys.size()) {
		preDestroys.top()(pool[index]);
	  }
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
