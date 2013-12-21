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
  };

}

#endif// ASTEROIDS_HPP
