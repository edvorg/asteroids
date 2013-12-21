#ifndef ASTEROIDS_HPP
#define ASTEROIDS_HPP

#include <memory>
#include <vector>

namespace test {

  class Asteroids {

	class Asteroid {
	public:
	  float x = 0;
	  float y = 0;
	  float angle = 0;
	  float size = 0.1;
	  float velX = 0;
	  float velY = 0;
	  float velAngle = 0;
	  bool use = false;

	  void Update(double dt);
	  void Draw();
	  void Respawn();

	protected:
	private:
	};

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
