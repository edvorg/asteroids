#include "App.hpp"

#include <stdlib.h>
#include <math.h>

#include "Graphics.hpp"

namespace test {

  void App::Init() {
	asteroids.Init();
	spliceAsteroids.Init();
	progress.Init();
	stars.Init();

	for (int i = 0; i < maxPlayersCount; i++) {
	  players[i].Init();
	}
  }

  void App::Update(double dt) {
	progress.Update(dt);
	shaker.Update(dt);

	if (!progress.IsPaused()) {
	  asteroids.Update(dt);
	  spliceAsteroids.Update(dt);
	  stars.Update(dt);
	  asteroids.SetLevel(progress.GetLevel());

	  int livesTotal = 0;
	  int activeTotal = 0;

	  CollideAsteroids();

	  for (int i = 0; i < maxPlayersCount; i++) {
		players[i].Update(dt);
		CollidePlayer(players[i]);

		if (players[i].IsActive()) {
		  activeTotal++;
		  livesTotal += players[i].GetLives();
		}
	  }

	  if (livesTotal < 1 && activeTotal) {
		for (int i = 0; i < maxPlayersCount; i++) {
		  players[i].Reset();
		}
		progress.RestartGame();
		asteroids.Clean();
		spliceAsteroids.Clean();
		stars.Clean();
	  }
	}
  }

  void App::Draw() {
	SetProjection(fieldWidth, fieldHeight);

	if (!progress.IsPaused()) {
	  shaker.ApplyMatrix();
	  asteroids.Draw();
	  spliceAsteroids.Draw();
	  stars.Draw();
	  for (int i = 0; i < maxPlayersCount; i++) {
		players[i].Draw();
	  }
	}

	SetTranslate(0, 0);
	progress.Draw();
  }

  void App::Release() {
	asteroids.Release();
	spliceAsteroids.Release();
	progress.Release();
	stars.Release();
	for (int i = 0; i < maxPlayersCount; i++) {
	  players[i].Release();
	}
  }

  void App::Touch(int player, float newX, float newY) {
	auto x = newX / screenWidth * fieldWidth;
	auto y = (1.0 - newY / screenHeight) * fieldHeight;

	progress.Touch(newX, newY);

	if (!progress.IsPaused() &&
		players[player].GetLives() > 0 &&
		player < maxPlayersCount &&
		player >= 0) {
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
	asteroids.MarginLeft(10);
	asteroids.MarginRight(10);
	asteroids.MarginTop(fieldHeight * 0.5);
	asteroids.MarginBottom(10);

	spliceAsteroids.FieldSize(fieldWidth, fieldHeight);
	spliceAsteroids.MarginLeft(fieldWidth);
	spliceAsteroids.MarginRight(fieldWidth);
	spliceAsteroids.MarginTop(fieldHeight * 0);
	spliceAsteroids.MarginBottom(10);

	stars.FieldSize(fieldWidth, fieldHeight);
	stars.MarginLeft(10);
	stars.MarginRight(10);
	stars.MarginTop(10);
	stars.MarginBottom(10);

	progress.FieldSize(fieldWidth, fieldHeight);
	for (int i = 0; i < maxPlayersCount; i++) {
	  players[i].FieldSize(fieldWidth, fieldHeight);
	}
  }

  void App::CollideAsteroids() {
	  auto callback = [&] (Asteroid & a, Asteroid & b) {
		if (&a != &b) {
		  // TODO improve algo using absolute rigid body law
		  auto deltax = a.x - b.x;
		  auto deltay = a.y - b.y;
		  auto distance = sqrt(deltax * deltax + deltay * deltay);
		  deltax /= distance;
		  deltay /= distance;
		  a.velX += deltax * b.size;
		  a.velY += deltay * b.size;
		  b.velX -= deltax * a.size;
		  b.velY -= deltay * a.size;
		}
	  };

	  asteroids.Collide<Asteroid>(asteroids, callback);
	  asteroids.Collide<Asteroid>(spliceAsteroids, callback);
	  spliceAsteroids.Collide<Asteroid>(spliceAsteroids, callback);
  }

  void App::CollidePlayer(Player & player) {
	auto callback1 = [&] (Asteroid & a, Bullet & b) {
	  a.dead = true;
	  b.dead = true;
	};
	auto callback2 = [&] (Asteroid & a, Player & p) {
	  p.Kill();
	  shaker.Shake();
	  a.dead = true;
	};

	player.CollideBullets<Asteroid>(asteroids, callback1);
	player.CollideBullets<Asteroid>(spliceAsteroids, callback1);
	player.Collide<Asteroid>(asteroids, callback2);
	player.Collide<Asteroid>(spliceAsteroids, callback2);
  }

}
