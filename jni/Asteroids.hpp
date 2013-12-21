#ifndef ASTEROIDS_HPP
#define ASTEROIDS_HPP

#include <memory>
#include <vector>

#include "Asteroid.hpp"

namespace test {

  class Asteroids {

  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();

  protected:
	void Spawn();

  private:
	std::vector<Asteroid> asteroids;
	double spawnTimer = 0.0;
	double spawnPeriod = 1.0;
	int used = 0;
	int poolSize = 100;
  };
}

#endif ASTEROIDS_HPP
