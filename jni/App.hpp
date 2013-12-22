#ifndef APP_HPP
#define APP_HPP

#include "Asteroids.hpp"
#include "SpliceAsteroids.hpp"
#include "Player.hpp"
#include "LevelProgress.hpp"
#include "DecorateStars.hpp"
#include "ScreenShaker.hpp"

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

  protected:
  private:
	void CollideAsteroids();
	void CollidePlayer(Player & player);

	const float fieldWidth = 100.0;
	static const int maxPlayersCount = 2;
	float fieldHeight = 100.0f;
	float screenWidth = 0.0f;
	float screenHeight = 0.0f;

	Asteroids asteroids;
	SpliceAsteroids spliceAsteroids;
 	DecorateStars stars;

	Player players[maxPlayersCount];
	int livesTotal = 0;
	float scoreTotal = 0.0f;

	LevelProgress progress;
	ScreenShaker shaker;
  };

}

#endif
