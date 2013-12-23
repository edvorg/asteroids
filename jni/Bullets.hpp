#ifndef BULLETS_HPP
#define BULLETS_HPP

#include "ParticleSystem.hpp"
#include "Bullet.hpp"

namespace test {

  // represents bullets field throwed by player
  class Bullets : public ParticleSystem<Bullet> {

  public:
	virtual void Init() override;

	void SetPos(float newX, float newY);
	void SetAngle(float newAngle);

  protected:
  private:
	float period = 0.25f;
	// owner position x
	float x = 0.0f;
	// owner position y
	float y = 0.0f;
	// owner orientation
	float angle = 0.0f;
  };

}

#endif// BULLETS_HPP
