#ifndef BULLETS_HPP
#define BULLETS_HPP

#include "ParticleSystem.hpp"
#include "Bullet.hpp"

namespace test {

  class Bullets : public ParticleSystem<Bullet> {

  public:
	virtual void Init() override;

	// Emitter position
	void SetPos(float newX, float newY);
	// Emitter direction
	void SetAngle(float newAngle);

  protected:
  private:
	float period = 0.25f;
	float x = 0.0f;
	float y = 0.0f;
	float angle = 0.0f;
  };

}

#endif// BULLETS_HPP
