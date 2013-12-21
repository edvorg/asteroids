#include "Asteroid.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <stdlib.h>
#include "math.h"
#include "Misc.hpp"

namespace test {

  void Asteroid::Update(double dt) {
	x += velX * dt;
	y += velY * dt;
	angle += velAngle * dt;
  }

  void Asteroid::Draw() {
	// TODO rewrite using vertex buffer and array objects
	static const int corners = 8;
	static GLfloat vertices[corners];
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
	glTranslatef(x, y, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(size, size, size);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawElements(GL_LINE_LOOP, corners, GL_UNSIGNED_BYTE, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
  }

  void Asteroid::Respawn() {
	size = Rand(0.04, 0.1, 0.01);
	x = Rand(- 1.0 + size, 1.0 - size, 0.01);
	y = 1.0f + size;
	angle = 0;
	velX = 0;
	velY = - Rand(0.1, 0.5, 0.01);
	velAngle = Rand(-90.0, 90.0, 1.0);
  }

}
