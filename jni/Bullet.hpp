#ifndef BULLET_HPP
#define BULLET_HPP

#include "Dimensions.hpp"
#include "Particle.hpp"

namespace test {

  // Bullets particle system product
  class Bullet : public Particle {

  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();
	Dimensions GetDimensions() const;

  protected:
  private:
  };

}

#endif// BULLET_HPP
