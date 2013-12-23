#ifndef COMETTAIL_HPP
#define COMETTAIL_HPP

#include "ParticleSystem.hpp"
#include "DecorateStar.hpp"

namespace test {

  // represents small particle system throwed
  // e.g. from player's ship engine or from asteroid
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

	// pos x of owning object
	float ownerX = 0.0f;
	// pos y of owning object
	float ownerY = 0.0f;
	// vel x of owning object
	float ownerVelX = 0.0f;
	// vel y of owning object
	float ownerVelY = 0.0f;
	// size of owning object
	float ownerSize = 0.0f;
  };

}

#endif// COMETTAIL_HPP
