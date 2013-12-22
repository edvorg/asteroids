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

	  int livesTotal = 0;
	  int activeTotal = 0;

	  for (int i = 0; i < maxPlayersCount; i++) {
		players[i].Update(dt);

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

		players[i].CollideBullets<Asteroid>(asteroids, [&] (Asteroid & a, Bullet & b) {
			a.dead = true;
			b.dead = true;
		  });
		players[i].CollideBullets<Asteroid>(spliceAsteroids, [&] (Asteroid & a, Bullet & b) {
			a.dead = true;
			b.dead = true;
		  });
		players[i].Collide<Asteroid>(asteroids, [&] (Asteroid & a, Player & p) {
			p.Kill();
			shaker.Shake();
			a.dead = true;
		  });
		players[i].Collide<Asteroid>(spliceAsteroids, [&] (Asteroid & a, Player & p) {
			p.Kill();
			shaker.Shake();
			a.dead = true;
		  });

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

}
