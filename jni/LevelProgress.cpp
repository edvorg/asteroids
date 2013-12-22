#include "LevelProgress.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

namespace test {

  void LevelProgress::Init() {
  }

  void LevelProgress::Update(double dt) {
	if (paused) {
	  startTimer += dt;
	  return;
	}

	levelTimer += dt;
	if (levelTimer > levelTime) {
	  levelTimer = 0.0f;
	  levelTime *= levelTimeExtendKoeff;
	  currentLevel++;
	}
  }

  void LevelProgress::Draw() {
	if (paused) {
	  // TODO rewrite using vertex buffer and array objects
	  static const int corners = 3;
	  static GLfloat vertices[corners * 2] = {
		0.0f, -1.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
	  };
	  static GLubyte indices[corners] = {
		0, 1, 2
	  };

	  GLfloat currentColor[4];
	  GLfloat width;
	  glGetFloatv(GL_CURRENT_COLOR,currentColor);
	  glGetFloatv(GL_LINE_WIDTH, &width);
	  glColor4f(0x34 / 255.0f, 0xbe / 255.0f, 0xda / 255.0f, 1.0f);
	  glLineWidth(playLineWidth);

	  // render
	  glMatrixMode(GL_MODELVIEW);
	  glPushMatrix();
	  glTranslatef(params.fieldWidth * 0.5f,
				   params.fieldHeight * 0.5f,
				   0);
	  glScalef(playButtonSize * params.fieldWidth,
			   playButtonSize * params.fieldWidth, 1);
	  glEnableClientState(GL_VERTEX_ARRAY);
	  glVertexPointer(2, GL_FLOAT, 0, vertices);
	  glDrawElements(GL_LINE_LOOP, corners, GL_UNSIGNED_BYTE, indices);
	  glDisableClientState(GL_VERTEX_ARRAY);
	  glPopMatrix();

	  glColor4f(currentColor[0],
				currentColor[1],
				currentColor[2],
				currentColor[3]);
	  glLineWidth(width);
	}
	else {
	  // TODO rewrite using vertex buffer and array objects
	  static const int corners = 2;
	  static GLfloat vertices[corners * 2] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
	  };
	  static GLubyte indices[corners] = {
		0, 1,
	  };

	  GLfloat currentColor[4];
	  GLfloat width;
	  glGetFloatv(GL_CURRENT_COLOR,currentColor);
	  glGetFloatv(GL_LINE_WIDTH, &width);
	  glColor4f(0x34 / 255.0f, 0xbe / 255.0f, 0xda / 255.0f, 1.0f);
	  glLineWidth(lineWidth);

	  // render
	  glMatrixMode(GL_MODELVIEW);
	  glPushMatrix();
	  glTranslatef(params.fieldWidth - lineWidth / params.fieldWidth,
				   0,
				   0);
	  glScalef(1, levelTimer / levelTime * params.fieldHeight, 1);
	  glEnableClientState(GL_VERTEX_ARRAY);
	  glVertexPointer(2, GL_FLOAT, 0, vertices);
	  glDrawElements(GL_LINE_LOOP, corners, GL_UNSIGNED_BYTE, indices);
	  glDisableClientState(GL_VERTEX_ARRAY);
	  glPopMatrix();

	  glColor4f(currentColor[0],
				currentColor[1],
				currentColor[2],
				currentColor[3]);
	  glLineWidth(width);
	}
  }

  void LevelProgress::Release() {
  }

  void LevelProgress::FieldSize(float width, float height) {
	params.fieldWidth = width;
	params.fieldHeight = height;
  }

  void LevelProgress::RestartLevel() {
	levelTimer = 0.0f;
  }

  void LevelProgress::RestartGame() {
	levelTimer = 0.0f;
	currentLevel = 1;
	levelTime = levelTimeInitial + 1.0;
	paused = true;
  }

  void LevelProgress::Touch(float x, float y) {
	if (startTimer > startTimerPeriod) {
	  paused = false;
	  startTimer = 0.0f;
	}
  }

}
