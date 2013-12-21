#ifndef ASTEROIDS_HPP
#define ASTEROIDS_HPP

#include <memory>
#include <vector>
#include <functional>

#include "Asteroid.hpp"
#include "RandomizeParams.hpp"
#include "Dimensions.hpp"
#include "ParticleSystem.hpp"

namespace test {

  class Asteroids : public ParticleSystem<Asteroid> {

  public:
	virtual void Init() override;

  protected:
  private:
	// minimum size of asteroid to crush in small parts
	float minCrushSize = 5.0f;
	int crushPartsCount = 3;
	int crushPartsAwayVel = 10.0f;
  };

}

#endif// ASTEROIDS_HPP
