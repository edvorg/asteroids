#include "Graphics.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <math.h>
#include <algorithm>

#include "Bullet.hpp"
#include "DecorateStar.hpp"
#include "Asteroid.hpp"
#include "Player.hpp"
#include "LevelProgress.hpp"

namespace test {

  void DrawPlayer(const Player & player) {
	// TODO rewrite using vertex buffer and array objects
	static const int corners = 3;
	static GLfloat vertices[corners * 2] = {
	  0.75, -1.0,
	  0.0, 1.0,
	  -0.75, -1.0,
	};
	static GLubyte indices[corners] = {
	  0, 1, 2
	};

	if (player.IsSpawned()) {
	  // render
	  glMatrixMode(GL_MODELVIEW);
	  glPushMatrix();
	  glTranslatef(player.GetX(), player.GetY(), 0);
	  glRotatef(player.GetAngle(), 0, 0, 1);
	  glScalef(player.GetSize(), player.GetSize(), 1);
	  glEnableClientState(GL_VERTEX_ARRAY);
	  glVertexPointer(2, GL_FLOAT, 0, vertices);
	  glDrawElements(GL_LINE_LOOP, corners, GL_UNSIGNED_BYTE, indices);
	  glDisableClientState(GL_VERTEX_ARRAY);
	  glPopMatrix();
	}
  }
  void DrawAsteroid(const Asteroid & asteroid) {
	// TODO rewrite using vertex buffer and array objects
	static const int corners = 8;
	static GLfloat vertices[corners * 2];
	static GLubyte indices[corners];
	static bool verticesInited = false;

	if (!verticesInited) {
	  float angle = 0;
	  for (unsigned int i = 0; i < corners; i++) {
		vertices[i * 2] = cos(angle);
		vertices[i * 2 + 1] = sin(angle);
		indices[i] = i;
		angle += 2.0 * M_PI / corners;
	  }
	  verticesInited = true;
	}

	// render
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(asteroid.x, asteroid.y, 0);
	glRotatef(asteroid.angle, 0, 0, 1);
	glScalef(asteroid.size, asteroid.size, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawElements(GL_LINE_LOOP, corners, GL_UNSIGNED_BYTE, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
  }
  void DrawDecorateStar(const DecorateStar & star) {
	// TODO rewrite using vertex buffer and array objects
	static const int corners = 1;
	static GLfloat vertices[corners * 2] = {
	  0.0f, 0.0f,
	};
	static GLubyte indices[corners] = {
	  0,
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat currentColor[4];
	GLfloat oldSize;
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glGetFloatv(GL_POINT_SIZE, &oldSize);

	glPointSize(star.size);
    glColor4f(0, 0, 0, std::abs(star.velY) / 20.0f  * 0.4f);
    // glColor4f(0, 0, 0, 0.5);

	// render
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(star.x, star.y, 0);
	glScalef(star.size, star.size, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawElements(GL_POINTS, corners, GL_UNSIGNED_BYTE, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();

	glPointSize(oldSize);
	glColor4f(currentColor[0],
			  currentColor[1],
			  currentColor[2],
			  currentColor[3]);

	glDisable(GL_BLEND);
  }
  void DrawBullet(const Bullet & bullet) {
	// TODO rewrite using vertex buffer and array objects
	static const int corners = 8;
	static GLfloat vertices[corners * 2];
	static GLubyte indices[corners];
	static bool verticesInited = false;

	if (!verticesInited) {
	  float angle = 0;
	  for (unsigned int i = 0; i < corners; i++) {
		vertices[i * 2] = cos(angle);
		vertices[i * 2 + 1] = sin(angle);
		indices[i] = i;
		angle += 2.0 * M_PI / corners;
	  }
	  verticesInited = true;
	}

	// render
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(bullet.x, bullet.y, 0);
	glRotatef(bullet.angle, 0, 0, 1);
	glScalef(bullet.size, bullet.size, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawElements(GL_LINE_LOOP, corners, GL_UNSIGNED_BYTE, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
  }

  void DrawProgress(const LevelProgress & progress) {
	if (progress.IsPaused()) {
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
	  glLineWidth(progress.playLineWidth);

	  // render
	  glMatrixMode(GL_MODELVIEW);
	  glPushMatrix();
	  glTranslatef(progress.GetParams().fieldWidth * 0.5f,
				   progress.GetParams().fieldHeight * 0.5f,
				   0);
	  glScalef(progress.playButtonSize * progress.GetParams().fieldWidth,
			   progress.playButtonSize * progress.GetParams().fieldWidth, 1);
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
	  glLineWidth(progress.lineWidth);

	  // render
	  glMatrixMode(GL_MODELVIEW);
	  glPushMatrix();
	  glTranslatef(progress.GetParams().fieldWidth - progress.lineWidth / progress.GetParams().fieldWidth,
				   0,
				   0);
	  glScalef(1, progress.GetLevelTimer() / progress.GetLevelTime() * progress.GetParams().fieldHeight, 1);
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

}
