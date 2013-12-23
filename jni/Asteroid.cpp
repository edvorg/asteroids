#include "Asteroid.hpp"

#include "Misc.hpp"
#include "Graphics.hpp"

namespace test {

  void Asteroid::Init() {
	tail.Init();
  }

  void Asteroid::Update(double dt) {
	tail.Update(dt);
	tail.SetOwnerX(GetPosX());
	tail.SetOwnerY(GetPosY());
	tail.SetOwnerVelX(GetVelX());
	tail.SetOwnerVelY(GetVelY());
	tail.SetOwnerSize(GetSize());
  }

  void Asteroid::Draw() {
	DrawAsteroid(*this);
	tail.Draw();
  }

  void Asteroid::Release() {
	tail.Release();
  }

  Dimensions Asteroid::GetDimensions() const {
	return Dimensions(GetPosX(), GetPosY(), GetSize());
  }

  Asteroid & Asteroid::operator = (const Asteroid & another) {
	Particle::operator=(another);
	return *this;
  }

}
