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
	void FieldPos(float newX, float newY);
	inline void MarginLeft(float left) { marginLeft = left; }
	inline void MarginTop(float top) { marginTop = top; }
	inline void MarginRight(float right) { marginRight = right; }
	inline void MarginBottom(float bottom) { marginBottom = bottom; }
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
	float x = 0.0f;
	float y = 0.0f;
	float marginLeft = 0.0f;
	float marginRight = 0.0f;
	float marginTop = 0.0f;
	float marginBottom = 0.0f;

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
	for (unsigned int i = 0; i < poolSize; i++) {
	  pool[i].Init();
	}
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
	  	  pool[i].y < y - marginBottom ||
	  	  pool[i].y > y + params.fieldHeight + marginTop ||
	  	  pool[i].x < x - marginLeft ||
	  	  pool[i].x > x + params.fieldWidth + marginRight) {
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
	for (unsigned int i = 0; i < poolSize; i++) {
	  pool[i].Release();
	}
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Clean() {
	used = 0;
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::Resize(int newSize) {
	pool.resize(newSize);
	poolSize = newSize;
	used = 0;
  }

  template<class PARTICLE>
  template <class ANOTHER>
  void ParticleSystem<PARTICLE>::Collide(ANOTHER & another, std::function<void (PARTICLE &, ANOTHER &)> callback) {
	// TODO optimize this. complexity n now, use aabb or something else
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
  }

  template<class PARTICLE>
  void ParticleSystem<PARTICLE>::FieldPos(float newX, float newY) {
	x = newX;
	y = newY;
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
	  used--;

	  if (index < used) {
		pool[index] = pool[used];
	  }
	}
  }
}

#endif// PARTICLESYSTEM_HPP
