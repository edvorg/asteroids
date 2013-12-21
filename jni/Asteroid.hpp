#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "RandomizeParams.hpp"

namespace test {

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
	  void Respawn(const RandomizeParams & params);

	protected:
	private:
	};

}

#endif// ASTEROID_HPP
