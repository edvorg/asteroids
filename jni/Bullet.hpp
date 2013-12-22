#ifndef BULLET_HPP
#define BULLET_HPP

#include "RandomizeParams.hpp"
#include "Dimensions.hpp"

namespace test {

  class Bullet {

  public:
	float x = 0;
	float y = 0;
	float angle = 0;
	float size = 0.1;
	float velX = 0;
	float velY = 0;
	float velAngle = 0;
	bool use = false;
	bool dead = false;

	void Init();
	void Update(double dt);
	void Draw();
	void Release();
	void Respawn(const RandomizeParams & params);
	Dimensions GetDimensions() const;

  protected:
  private:
  };

}

#endif// BULLET_HPP
