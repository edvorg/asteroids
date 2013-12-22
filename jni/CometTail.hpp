#ifndef COMETTAIL_HPP
#define COMETTAIL_HPP

#include "ParticleSystem.hpp"
#include "DecorateStar.hpp"

namespace test {

  class CometTail : public ParticleSystem<DecorateStar> {

  public:
	using Super = ParticleSystem<DecorateStar>;

	virtual void Init() override;
	virtual void Update(double dt) override;

	inline void SetOwnerX(float x) { ownerX = x; }
	inline void SetOwnerY(float y) { ownerY = y; }
	inline void SetOwnerVelX(float velX) { ownerVelX = velX; }
	inline void SetOwnerVelY(float velY) { ownerVelY = velY; }
	inline void SetOwnerSize(float size) { ownerSize = size; }

  protected:
  private:
	const int poolSize = 100;
	float ownerX = 0.0f;
	float ownerY = 0.0f;
	float ownerVelX = 0.0f;
	float ownerVelY = 0.0f;
	float ownerSize = 0.0f;
  };

}

#endif// COMETTAIL_HPP
