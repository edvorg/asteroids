#include "App.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <stdlib.h>
#include <math.h>

namespace test {

  void App::Init() {
	player1.Init();
	player2.Init();
	asteroids.Init();
	spliceAsteroids.Init();
	bullets1.Init();
	bullets2.Init();
  }

  void App::Update(double dt) {
	player1.Update(dt);
	player2.Update(dt);
	asteroids.Update(dt);
	spliceAsteroids.Update(dt);
	bullets1.Update(dt);
	bullets2.Update(dt);

	bullets1.SetPos(player1.GetX(), player1.GetY());
	bullets1.SetAngle(player1.GetAngle());
	bullets1.SetSpawning(player1.IsSpawned());
	bullets2.SetPos(player2.GetX(), player2.GetY());
	bullets2.SetAngle(player2.GetAngle());
	bullets2.SetSpawning(player2.IsSpawned());

	if (player1.IsSpawned()) {
	  asteroids.Collide(player1.GetDimensions(), [this] () {
		  player1.Kill([this] () {
			  lives = std::max<int>(lives - 1, 0);
			  player1RespawnTimer = 0.0f;
			});
		});
	  spliceAsteroids.Collide(player1.GetDimensions(), [this] () {
		  player1.Kill([this] () {
			  lives = std::max<int>(lives - 1, 0);
			  player1RespawnTimer = 0.0f;
			});
		});
	}
	else {
	  player1RespawnTimer += dt;
	}

	if (player2.IsSpawned()) {
	  asteroids.Collide(player2.GetDimensions(), [this] () {
		  player2.Kill([this] () {
			  lives = std::max<int>(lives - 1, 0);
			  player2RespawnTimer = 0.0f;
			});
		});
	  spliceAsteroids.Collide(player2.GetDimensions(), [this] () {
		  player2.Kill([this] () {
			  lives = std::max<int>(lives - 1, 0);
			  player2RespawnTimer = 0.0f;
			});
		});
	}
	else {
	  player2RespawnTimer += dt;
	}

	asteroids.Collide(bullets1);
	asteroids.Collide(bullets2);
	spliceAsteroids.Collide(bullets1);
	spliceAsteroids.Collide(bullets2);
  }

  void App::Draw() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, fieldWidth, 0, fieldHeight, 1, -1);

	player1.Draw();
	player2.Draw();
	asteroids.Draw();
	spliceAsteroids.Draw();
	bullets1.Draw();
	bullets2.Draw();
  }

  void App::Release() {
	player1.Release();
	player2.Release();
	asteroids.Release();
	spliceAsteroids.Release();
	bullets1.Release();
	bullets2.Release();
  }

  void App::Touch(int player, float newX, float newY) {
	auto x = newX / screenWidth * fieldWidth;
	auto y = (1.0 - newY / screenHeight) * fieldHeight;

	if (player == 0) {
	  if (player1.IsSpawned()) {
		player1.Touch(x, y);
	  }
	  else if (player1RespawnTimer > playerRespawnPeriod && lives > 0) {
		player1.Touch(x, y);
		player1RespawnTimer = 0.0f;
	  }
	}
	else if (player == 1) {
	  if (player2.IsSpawned()) {
		player2.Touch(x, y);
	  }
	  else if (player2RespawnTimer > playerRespawnPeriod && lives > 0) {
		player2.Touch(x, y);
		player2RespawnTimer = 0.0f;
	  }
	}
  }

  void App::TouchEnd(int player, float newX, float newY) {
	if (player == 0) {
	  // player1.Kill([] {});
	}
	else if (player == 1) {
	  // player2.Kill([] {});
	}
  }

  void App::ScreenSize(float newWidth, float newHeight) {
	screenWidth = (newWidth > 0.1 ? newWidth : 1.0f);
	screenHeight = (newHeight > 0.1 ? newHeight : 1.0f);
	fieldHeight = fieldWidth * screenHeight / screenWidth;
	asteroids.FieldSize(fieldWidth, fieldHeight);
	spliceAsteroids.FieldSize(fieldWidth, fieldHeight);
	bullets1.FieldSize(fieldWidth, fieldHeight);
	bullets2.FieldSize(fieldWidth, fieldHeight);
  }

  int App::NearestPlayer(float coordX, float coordY) {
	int result = 0;

	if (player1.IsSpawned() && player2.IsSpawned()) {

	  float deltax1 = coordX - player1.GetX();
	  float deltay1 = coordY - player1.GetY();
	  float deltax2 = coordX - player2.GetX();
	  float deltay2 = coordY - player2.GetY();

	  if ((deltax1 * deltax1 + deltay1 * deltay1) >
		  (deltax2 * deltax2 + deltay2 * deltay2)) {
		result = 1;
	  }
	}

	return result;
  }

}
