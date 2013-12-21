#include "App.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <stdlib.h>
#include <math.h>

namespace test {

  void App::Init() {
	asteroids.Init();
  }

  void App::Update(double dt) {
	asteroids.Update(dt);
  }

  void App::Draw() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, fieldWidth, 0, fieldHeight, 1, -1);

	asteroids.Draw();
  }

  void App::Release() {
	asteroids.Release();
  }

  void App::Touch(float newX, float newY) {
	x =   (newX / screenWidth) * fieldWidth;
	y = - (newY / screenHeight) * fieldHeight;
  }

  void App::ScreenSize(float newWidth, float newHeight) {
	screenWidth = newWidth;
	screenHeight = newHeight;
	fieldHeight = fieldWidth * screenHeight / (screenWidth ? screenWidth : 1.0f);
	asteroids.FieldSize(fieldWidth, fieldHeight);
  }

}
