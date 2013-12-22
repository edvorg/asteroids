#include "LevelProgress.hpp"

#include "Graphics.hpp"

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
	  level++;
	}
  }

  void LevelProgress::Draw() {
	DrawProgress(*this);
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
	level = 0;
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
