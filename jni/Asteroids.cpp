#include "Asteroids.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <algorithm>
#include "Misc.hpp"

namespace test {

  void Asteroids::Asteroid::Update(double dt) {
	x += velX * dt;
	y += velY * dt;
	angle += velAngle * dt;
  }

  void Asteroids::Asteroid::Draw() {
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

  void Asteroids::Asteroid::Respawn() {
	size = Rand(0.01, 0.1, 0.01);
	x = Rand(- 1.0 + size, 1.0 - size, 0.01);
	y = 1.0f + size;
	angle = 0;
	velX = 0;
	velY = - Rand(0.1, 0.5, 0.01);
	velAngle = Rand(-90.0, 90.0, 1.0);
  }

  void Asteroids::Init() {
	asteroids.resize(poolSize);
  }

  void Asteroids::Update(double dt) {
	// spawn new asteroids on field
	spawnTimer += dt;
	if (spawnTimer > spawnPeriod && used < poolSize) {
	  Spawn();
	  spawnTimer = 0;
	  spawnPeriod = Rand(0.25, 1.0, 0.01);
	}

	// update active asteroids
	for (unsigned int i = 0; i < used; i++) {
	  asteroids[i].Update(dt);

	  if (asteroids[i].y < - 1.0 - asteroids[i].size) {
		asteroids[i].use = false;
		used--;

		if (asteroids[used].use) {
		  asteroids[i] = asteroids[used];
		  asteroids[used].use = false;
		}
	  }
	}
  }

  void Asteroids::Draw() {
	for (unsigned int i = 0; i < used; i++) {
		asteroids[i].Draw();
	}
  }

  void Asteroids::Release() {
  }

  void Asteroids::Spawn() {
	if (used < poolSize) {
	  asteroids[used].use = true;
	  asteroids[used].Respawn();
	  used++;
	}
  }
}
