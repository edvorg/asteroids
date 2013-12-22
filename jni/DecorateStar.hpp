#ifndef DECORATESTAR_HPP
#define DECORATESTAR_HPP

#include "Dimensions.hpp"

namespace test {

  class RandomizeParams;

  class DecorateStar {

  public:
	float x = 0;
	float y = 0;
	float velX = 0;
	float velY = 0;
	float size = 1.0f;
	bool use = false;
	bool dead = false;

	void Init();
	void Update(double dt);
	void Draw();
	void Release();
	void Respawn(const RandomizeParams & params);
	Dimensions GetDimensions() const;

  protected:
  private:
  };

}

#endif// DECORATESTAR_HPP
