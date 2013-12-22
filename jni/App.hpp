#ifndef APP_HPP
#define APP_HPP

#include "Asteroids.hpp"
#include "SpliceAsteroids.hpp"
#include "Player.hpp"
#include "Bullets.hpp"

namespace test {

  class App {

  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();

	// handle some parameters from device
	void Touch(int player, float newX, float newY);
	void TouchEnd(int player, float newX, float newY);
	void ScreenSize(float newWidth, float newHeight);

	// return nearest player id
	int NearestPlayer(float coordX, float coordY);

  protected:
  private:
	float x = 0.0f;
	float y = 0.0f;
	float screenWidth = 0.0f;
	float screenHeight = 0.0f;
	const float fieldWidth = 100.0;
	float fieldHeight = 100.0f;
	Asteroids asteroids;
	SpliceAsteroids spliceAsteroids;
	Player player1;
	Player player2;
	Bullets bullets1;
	Bullets bullets2;
	int lives = 3;
  };

}

#endif
