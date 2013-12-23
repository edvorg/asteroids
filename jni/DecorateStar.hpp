#ifndef DECORATESTAR_HPP
#define DECORATESTAR_HPP

#include "Dimensions.hpp"
#include "Particle.hpp"

namespace test {

  // DecorateStars particle system product
  class DecorateStar : public Particle {

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

#endif// DECORATESTAR_HPP
