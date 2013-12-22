#ifndef APP_HPP
#define APP_HPP

#include "Asteroids.hpp"
#include "SpliceAsteroids.hpp"
#include "Player.hpp"
#include "Bullets.hpp"
#include "LevelProgress.hpp"
#include "DecorateStars.hpp"

namespace test {

  class App {

  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();

	// starts screen shake effect
	void ShakeScreen();

	// handle some parameters from device
	void Touch(int player, float newX, float newY);
	void TouchEnd(int player, float newX, float newY);
	void ScreenSize(float newWidth, float newHeight);

	// return nearest player id
	int NearestPlayer(float coordX, float coordY);

  protected:
  private:
	const float fieldWidth = 100.0;
	const float shakeTime = 1.0f;
	static const int maxPlayersCount = 2;
	float fieldHeight = 100.0f;
	float screenWidth = 0.0f;
	float screenHeight = 0.0f;
	float shakeTimer = 0.0f;
	bool shake = false;

	Asteroids asteroids;
	SpliceAsteroids spliceAsteroids;
 	DecorateStars stars;

	Player players[maxPlayersCount];
	Bullets bullets[maxPlayersCount];

	LevelProgress progress;
  };

}

#endif
