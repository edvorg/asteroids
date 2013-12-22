#ifndef LEVELPROGRESS_HPP
#define LEVELPROGRESS_HPP

#include "RandomizeParams.hpp"

namespace test {

  class LevelProgress {
  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();

	void FieldSize(float width, float height);
	void RestartLevel();
	void RestartGame();

  protected:
  private:
	const float levelTimeExtendKoeff = 1.5f;
	const float levelTimeInitial = 20.0f;
	float levelTime = levelTimeInitial;
	float levelTimer = 0.0f;
	RandomizeParams params;
	int currentLevel = 1;
	const float lineWidth = 16.0f;
  };

}

#endif// LEVELPROGRESS_HPP
