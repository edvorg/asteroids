#ifndef SPLICEASTEROIDS_HPP
#define SPLICEASTEROIDS_HPP

#include "Asteroids.hpp"

namespace test {

  class SpliceAsteroids : public Asteroids {

  public:
	virtual void Init() override;
	virtual void Update(double dt) override;

  protected:
  private:
	const float velocity = 10.0f;
	bool active = false;
	bool leftToRight = false;
	const float spawnPeriodActive = 0.1f;
	const float spawnPeriodPassive = 10.0f;
	float spawnPeriodActiveTimer = 0.0f;
	float spawnPeriodPassiveTimer = 0.0f;
	const float spawnPeriodActivePeriod = 1.0f;
	const float spawnPeriodPassivePeriod = 25.0f;
  };

}

#endif// SPLICEASTEROIDS_HPP
