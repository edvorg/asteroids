#include "App.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <stdlib.h>
#include <math.h>

namespace test {

  void App::Init() {
	asteroids.Init();
	spliceAsteroids.Init();
	progress.Init();
	stars.Init();

	for (int i = 0; i < maxPlayersCount; i++) {
	  players[i].Init();
	  bullets[i].Init();
	}
  }

  void App::Update(double dt) {
	progress.Update(dt);

	if (!progress.IsPaused()) {
	  asteroids.Update(dt);
	  spliceAsteroids.Update(dt);
	  stars.Update(dt);

	  int livesTotal = 0;
	  int activeTotal = 0;

	  for (int i = 0; i < maxPlayersCount; i++) {
		players[i].Update(dt);
		bullets[i].Update(dt);
		bullets[i].SetPos(players[i].GetX(), players[i].GetY());
		bullets[i].SetAngle(players[i].GetAngle());
		bullets[i].SetSpawning(players[i].IsSpawned());

		asteroids.Collide(bullets[i]);
		spliceAsteroids.Collide(bullets[i]);

		players[i].Collide(asteroids, [&] { players[i].Kill(); });
		players[i].Collide(spliceAsteroids, [&] { players[i].Kill(); });

		if (players[i].IsActive()) {
		  activeTotal++;
		  livesTotal += players[i].GetLives();
		}
	  }

	  if (livesTotal < 1 && activeTotal) {
		for (int i = 0; i < maxPlayersCount; i++) {
		  players[i].Reset();
		  bullets[i].Clean();
		}
		progress.RestartGame();
		asteroids.Clean();
		spliceAsteroids.Clean();
		stars.Clean();
	  }
	}
  }

  void App::Draw() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, fieldWidth, 0, fieldHeight, 1, -1);

	if (!progress.IsPaused()) {
	  asteroids.Draw();
	  spliceAsteroids.Draw();
	  stars.Draw();
	  for (int i = 0; i < maxPlayersCount; i++) {
		players[i].Draw();
		bullets[i].Draw();
	  }
	}

	progress.Draw();
  }

  void App::Release() {
	asteroids.Release();
	spliceAsteroids.Release();
	progress.Release();
	stars.Release();
	for (int i = 0; i < maxPlayersCount; i++) {
	  players[i].Release();
	  bullets[i].Release();
	}
  }

  void App::Touch(int player, float newX, float newY) {
	auto x = newX / screenWidth * fieldWidth;
	auto y = (1.0 - newY / screenHeight) * fieldHeight;

	progress.Touch(newX, newY);

	if (!progress.IsPaused() && players[player].GetLives() > 0) {
	  players[player].Touch(x, y);
	}
  }

  void App::TouchEnd(int player, float newX, float newY) {
  }

  void App::ScreenSize(float newWidth, float newHeight) {
	screenWidth = (newWidth > 0.1 ? newWidth : 1.0f);
	screenHeight = (newHeight > 0.1 ? newHeight : 1.0f);
	fieldHeight = fieldWidth * screenHeight / screenWidth;
	asteroids.FieldSize(fieldWidth, fieldHeight);
	spliceAsteroids.FieldSize(fieldWidth, fieldHeight);
	progress.FieldSize(fieldWidth, fieldHeight);
	stars.FieldSize(fieldWidth, fieldHeight);
	for (int i = 0; i < maxPlayersCount; i++) {
	  bullets[i].FieldSize(fieldWidth, fieldHeight);
	}
  }

}
