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

	// handle some parameters from device
	void Touch(int player, float newX, float newY);
	void TouchEnd(int player, float newX, float newY);
	void ScreenSize(float newWidth, float newHeight);

	// return nearest player id
	int NearestPlayer(float coordX, float coordY);

  protected:
  private:
	const float fieldWidth = 100.0;
	static const int maxPlayersCount = 2;
	float fieldHeight = 100.0f;
	float screenWidth = 0.0f;
	float screenHeight = 0.0f;

	Asteroids asteroids;
	SpliceAsteroids spliceAsteroids;
 	DecorateStars stars;

	Player players[maxPlayersCount];
	Bullets bullets[maxPlayersCount];

	LevelProgress progress;
  };

}

#endif
