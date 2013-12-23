#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Dimensions.hpp"
#include "CometTail.hpp"

#include "Particle.hpp"

namespace test {

  // Asteroids particle system product
  class Asteroid : public Particle {

  public:
	CometTail tail;

	void Init();
	void Update(double dt);
	void Draw();
	void Release();
	Dimensions GetDimensions() const;

	Asteroid & operator = (const Asteroid & another);

  protected:
  private:
  };

}

#endif// ASTEROID_HPP
