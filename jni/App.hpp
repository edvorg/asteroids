#ifndef APP_HPP
#define APP_HPP

#include "Asteroids.hpp"
#include "Player.hpp"

namespace test {

  class App {

  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();

	// handle some parameters from device
	void Touch(float newX, float newY);
	void ScreenSize(float newWidth, float newHeight);

  protected:
  private:
	float x = 0.0f;
	float y = 0.0f;
	float screenWidth = 0.0f;
	float screenHeight = 0.0f;
	const float fieldWidth = 100.0;
	float fieldHeight = 100.0f;
	Asteroids asteroids;
	Player player1;
	unsigned int lives = 3;
  };

}

#endif
