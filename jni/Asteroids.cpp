#include "Asteroids.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <algorithm>
#include "Misc.hpp"

namespace test {

  void Asteroids::Init() {
	ParticleSystem<Asteroid>::Init();

	SetPeriod([] {
		return Rand(0.25, 1.0, 0.01);
	  });
  }
}
