#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Dimensions.hpp"
#include "CometTail.hpp"

namespace test {

  // Asteroids particle system product
  class Asteroid {

  public:
	float x = 0;
	float y = 0;
	float angle = 0;
	float size = 0.1;
	float velX = 0;
	float velY = 0;
	float velAngle = 0;
	bool dead = false;
	CometTail tail;
	float lifeTimer = 0.0f;

	void Init();
	void Update(double dt);
	void Draw();
	void Release();
	Dimensions GetDimensions() const;

	Asteroid & operator =(const Asteroid & another);

  protected:
  private:
  };

}

#endif// ASTEROID_HPP
