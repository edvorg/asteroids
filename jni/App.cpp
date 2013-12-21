#include "App.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <stdlib.h>
#include <math.h>

namespace test {

  void App::Init() {
  }

  void App::Update(double dt) {
  }

  void App::Draw() {
	GLfloat vertex[] = {
	  x + 0.0f, y + 0.0f,
	  x + 0.25f, y + 0.0f,
	  x + 0.25f, y + 0.25f
	};

	GLubyte indices[] = {
	  0, 1, 2
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertex);
	glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_BYTE, indices);
  }

  void App::Release() {
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
