#include "Player.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <float.h>

#include <Misc.hpp>

namespace test {

  void Player::Init() {

  }

  void Player::Update(double dt) {
	float deltaX = targetX - x;
	float deltaY = targetY - y;
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	if (distance > 0.1f) {
	  if (distance > 15.0f) { // acceleration
		velX += acceleration;
		velY += acceleration;
	  }
	  else { // deceleration
		velX /= deceleration;
		velY /= deceleration;
	  }

	  x += deltaX * velX;
	  y += deltaY * velY;

	  // look in direction of finger

	  deltaX /= distance;
	  angle = acos(deltaX) / M_PI * 180.0f;
	  if (deltaY < 0.0) {
		angle *= - 1.0f;
	  }
	  angle -= 90.0f;
	}

	x += velX;
	y += velY;
  }

  void Player::Draw() {
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

	if (spawned) {
	  // render
	  glMatrixMode(GL_MODELVIEW);
	  glPushMatrix();
	  glTranslatef(x, y, 0);
	  glRotatef(angle, 0, 0, 1);
	  glScalef(size, size, 1);
	  glEnableClientState(GL_VERTEX_ARRAY);
	  glVertexPointer(2, GL_FLOAT, 0, vertices);
	  glDrawElements(GL_LINE_LOOP, corners, GL_UNSIGNED_BYTE, indices);
	  glDisableClientState(GL_VERTEX_ARRAY);
	  glPopMatrix();
	}
  }

  void Player::Release() {
  }

  void Player::Kill(std::function<void ()> callback) {
	spawned = false;
	callback();
  }

  void Player::Touch(float newX, float newY) {

	if (!spawned) {
	  spawned = true;
	  x = newX;
	  y = newY;
	  angle = 0.0f;
	  velX = 0.0f;
	  velY = 0.0f;
	  targetX = newX;
	  targetY = newY;
	  size = 7.0f;
	}
	else {
	  targetX = newX;
	  targetY = newY;
	}
  }

  Dimensions Player::GetDimensions() const {
	return Dimensions(x, y, size);
  }

}
