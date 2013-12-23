#ifndef SPLICEASTEROIDS_HPP
#define SPLICEASTEROIDS_HPP

#include "Asteroids.hpp"

namespace test {

  class SpliceAsteroids : public Asteroids {

  public:
	virtual void Init() override;
	virtual void Update(double dt) override;

	void SetLevel(unsigned int level);

  protected:
  private:
	const float velocity = 10.0f;
	const float spawnPeriodActiveInitial = 0.1f;
	const float spawnPeriodPassiveInitial = 10.0f;
	const float spawnPeriodActivePeriod = 1.0f;
	const float spawnPeriodPassivePeriod = 25.0f;
	float spawnPeriodActive = spawnPeriodActiveInitial;
	float spawnPeriodPassive = spawnPeriodPassiveInitial;
	bool active = false;
	bool leftToRight = false;
	float spawnPeriodActiveTimer = 0.0f;
	float spawnPeriodPassiveTimer = 0.0f;
	int level = 0;
  };

}

#endif// SPLICEASTEROIDS_HPP
