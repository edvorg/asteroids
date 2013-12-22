#include "ScreenShaker.hpp"

#include <math.h>

#include "Graphics.hpp"

namespace test {

  void ScreenShaker::Shake() {
	shake = true;
  }

  void ScreenShaker::Update(double dt) {
	if (shake) {
	  shakeTimer += dt;
	  if (shakeTimer > shakeTime) {
		shake = false;
		SetTranslate(0, 0);
		shakeTimer = 0.0f;
	  }
	  else {
		auto amplitude = (1.0 - shakeTimer / shakeTime) * 5.0;
		auto angle = shakeTimer / shakeTime * M_PI * 2.0f * 10.0f;
		SetTranslate(amplitude * sin(angle), 0);
	  }
	}
  }

  void ScreenShaker::ApplyMatrix() {
	if (shake) {
	  auto amplitude = (1.0 - shakeTimer / shakeTime) * 1.0;
	  auto angle = shakeTimer / shakeTime * M_PI * 2.0f * 10.0f;
	  SetTranslate(amplitude * sin(angle), 0);
	}
	else {
	  SetTranslate(0, 0);
	}
  }

}
