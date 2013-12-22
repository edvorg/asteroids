#include "DecorateStar.hpp"

#include <math.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <algorithm>

#include "Misc.hpp"
#include "RandomizeParams.hpp"

namespace test {

  void DecorateStar::Update(double dt) {
	x += velX * dt;
	y += velY * dt;
  }

  void DecorateStar::Draw() {
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

	glPointSize(size);
    glColor4f(0, 0, 0, std::abs(velY) / 20.0f  * 0.4f);
    // glColor4f(0, 0, 0, 0.5);

	// render
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);
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

  void DecorateStar::Respawn(const test::RandomizeParams &params) {
	size = Rand<double>(0.5, 5, 1);
	x = Rand<double>(0, params.fieldWidth, 1);
	y = params.fieldHeight + size;
	velX = Rand<double>(0.1, 1.0, 0.1);
	velY = Rand<double>(-10, -40, -1) * size;
  }

  Dimensions DecorateStar::GetDimensions() const {
	return Dimensions(x, y, size);
  }

}
