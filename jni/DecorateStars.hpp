#ifndef DECORATESTARS_HPP
#define DECORATESTARS_HPP

#include "ParticleSystem.hpp"
#include "DecorateStar.hpp"

namespace test {

  class DecorateStars : public ParticleSystem<DecorateStar> {

  public:
	using Super = ParticleSystem<DecorateStar>;

	virtual void Init() override;

  protected:
  private:
	const int poolSize = 500;
  };

}

#endif// DECORATESTARS_HPP
