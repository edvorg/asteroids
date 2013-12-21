#ifndef ASTEROIDS_HPP
#define ASTEROIDS_HPP

#include <memory>
#include <vector>

#include "Asteroid.hpp"
#include "RandomizeParams.hpp"

namespace test {

  class Asteroids {

  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();

	// some application parameters
	void FieldSize(float newWidth, float newHeight);

  protected:
	void Spawn();

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
