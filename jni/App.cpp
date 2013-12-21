#include "App.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <stdlib.h>
#include <math.h>

namespace test {

  void App::Init() {
	player1.Init();
	asteroids.Init();
  }

  void App::Update(double dt) {
	player1.Update(dt);
	asteroids.Update(dt);
  }

  void App::Draw() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, fieldWidth, 0, fieldHeight, 1, -1);

	player1.Draw();
	asteroids.Draw();
  }

  void App::Release() {
	player1.Release();
	asteroids.Release();
  }

  void App::Touch(float newX, float newY) {
	x = newX / screenWidth * fieldWidth;
	y = (1.0 - newY / screenHeight) * fieldHeight;
	player1.Touch(x, y);
  }

  void App::ScreenSize(float newWidth, float newHeight) {
	screenWidth = (newWidth > 0.1 ? newWidth : 1.0f);
	screenHeight = (newHeight > 0.1 ? newHeight : 1.0f);
	fieldHeight = fieldWidth * screenHeight / screenWidth;
	asteroids.FieldSize(fieldWidth, fieldHeight);
  }

}
