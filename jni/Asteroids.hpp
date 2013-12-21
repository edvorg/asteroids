#ifndef ASTEROIDS_HPP
#define ASTEROIDS_HPP

#include <memory>
#include <vector>
#include <functional>

#include "Asteroid.hpp"
#include "RandomizeParams.hpp"
#include "Dimensions.hpp"

namespace test {

  class Asteroids {

  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();

	void Collide(const Dimensions & dimensions, std::function<void ()> callback);

	// some application parameters
	void FieldSize(float newWidth, float newHeight);

  protected:
	void Spawn();
	void Destroy(unsigned int index);

  private:
	std::vector<Asteroid> asteroids;
	double spawnTimer = 0.0;
	double spawnPeriod = 1.0;
	int used = 0;
	int poolSize = 100;
	RandomizeParams params;
  };
}

#endif// ASTEROIDS_HPP
