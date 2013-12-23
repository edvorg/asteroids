#include "LevelProgress.hpp"

#include "Graphics.hpp"

namespace test {

  void LevelProgress::Init() {
  }

  void LevelProgress::Update(double dt) {
	// wait some time before we can start game
	if (paused) {
	  startTimer += dt;
	  return;
	}

	// if we played enough go to next level
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
	// reset to first level
	levelTimer = 0.0f;
	level = 0;
	levelTime = levelTimeInitial + 1.0;
	paused = true;
  }

  void LevelProgress::Touch(float x, float y) {
	// try to start game
	if (startTimer > startTimerPeriod) {
	  paused = false;
	  startTimer = 0.0f;
	}
  }

}
