#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <functional>

#include "Dimensions.hpp"

namespace test {

  class Player {
  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();

	// try to kill player
	void Kill(std::function<void ()> callback);

	// process touch
	void Touch(float newX, float newY);

	Dimensions GetDimensions() const;
	inline bool IsSpawned() const { return spawned; }
	inline float GetX() const { return x; }
	inline float GetY() const { return y; }
	inline float GetAngle() const { return angle; }

  protected:
  private:
	bool spawned = false;
	float x = 0.0f;
	float y = 0.0f;
	float angle = 0.0f;
	float velX = 0.0f;
	float velY = 0.0f;
	float targetX = 0.0f;
	float targetY = 0.0f;
	float size = 7.0f;
	float acceleration = 0.005;
	float deceleration = 3;
  };

}

#endif// PLAYER_HPP
