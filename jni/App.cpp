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
	glOrthof(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f);

	asteroids.Draw();
  }

  void App::Release() {
	asteroids.Release();
  }

  void App::Touch(float newX, float newY) {
	x = (newX / width - 0.5f) * 2.0f;
	y = (- newY / height + 0.5f) * 2.0;
  }

  void App::ScreenSize(float newWidth, float newHeight) {
	width = newWidth;
	height = newHeight;
  }

}
