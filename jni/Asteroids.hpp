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
	using Super = ParticleSystem<Asteroid>;

	virtual void Init() override;
	virtual void Update(double dt) override;

	void SetLevel(unsigned int level);

  protected:
  private:
	const float periodMinInitial = 1.0f;
	const float periodMaxInitial = 2.0f;
	// minimum size of asteroid to crush in small parts
	float minCrushSize = 5.0f;
	int crushPartsCount = 3;
	int crushPartsAwayVel = 10.0f;
	float periodMin = periodMinInitial;
	float periodMax = periodMaxInitial;
  };

}

#endif// ASTEROIDS_HPP
