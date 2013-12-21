#include "App.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <stdlib.h>
#include <math.h>

namespace test {

  void App::Init() {
	player1.Init();
	asteroids.Init();
	bullets1.Init();
  }

  void App::Update(double dt) {
	player1.Update(dt);
	asteroids.Update(dt);
	bullets1.Update(dt);

	bullets1.SetPos(player1.GetX(), player1.GetY());
	bullets1.SetAngle(player1.GetAngle());
	bullets1.SetSpawning(player1.IsSpawned());

	if (player1.IsSpawned()) {
	  asteroids.Collide(player1.GetDimensions(), [this] () {
		  player1.Kill([this] () {
			  lives--;
			});
		});
	}

	asteroids.Collide(bullets1);
  }

  void App::Draw() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, fieldWidth, 0, fieldHeight, 1, -1);

	player1.Draw();
	asteroids.Draw();
	bullets1.Draw();
  }

  void App::Release() {
	player1.Release();
	asteroids.Release();
	bullets1.Release();
  }

  void App::Touch(float newX, float newY) {
	x = newX / screenWidth * fieldWidth;
	y = (1.0 - newY / screenHeight) * fieldHeight;

	if (lives) {
	  player1.Touch(x, y);
	}
  }

  void App::ScreenSize(float newWidth, float newHeight) {
	screenWidth = (newWidth > 0.1 ? newWidth : 1.0f);
	screenHeight = (newHeight > 0.1 ? newHeight : 1.0f);
	fieldHeight = fieldWidth * screenHeight / screenWidth;
	asteroids.FieldSize(fieldWidth, fieldHeight);
	bullets1.FieldSize(fieldWidth, fieldHeight);
  }

}
