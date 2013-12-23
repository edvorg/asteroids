#include "Bullets.hpp"

#include <math.h>

namespace test {

  void Bullets::Init() {
	ParticleSystem<Bullet>::Init();

	PushPeriod([this] {
		return period;
	  });

	PushPostSpawn([this] (Bullet & bullet) {
		// throw bullets in front of owner orientation
		bullet.x = x;
		bullet.y = y;
		bullet.velX = cos((angle + 90.0f) / 180.0f * M_PI) * 100.0f;
		bullet.velY = sin((angle + 90.0f) / 180.0f * M_PI) * 100.0f;
		bullet.size = 1.0f;
	  });
  }

  void Bullets::SetPos(float newX, float newY) {
	x = newX;
	y = newY;
  }

  void Bullets::SetAngle(float newAngle) {
	angle = newAngle;
  }

}
