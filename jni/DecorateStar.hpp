#ifndef DECORATESTAR_HPP
#define DECORATESTAR_HPP

#include "Dimensions.hpp"

namespace test {

  // DecorateStars particle system product
  class DecorateStar {

  public:
	float x = 0;
	float y = 0;
	float velX = 0;
	float velY = 0;
	float size = 1.0f;
	bool dead = false;
	float lifeTimer = 0.0f;

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
