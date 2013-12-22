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
	void Touch(float x, float y);

	inline bool IsPaused() const { return paused; }
	inline RandomizeParams GetParams() const { return params; }
	inline float GetLevelTime() const { return levelTime; }
	inline float GetLevelTimer() const { return levelTimer; }

	const float levelTimeExtendKoeff = 1.5f;
	const float levelTimeInitial = 20.0f;
	const float lineWidth = 16.0f;
	const float playLineWidth = 8.0f;
	const float playButtonSize = 0.1f;
	const float startTimerPeriod = 1.0f;

  protected:
  private:
	float levelTime = levelTimeInitial;
	float levelTimer = 0.0f;
	RandomizeParams params;
	int currentLevel = 1;
	bool paused = true;
	float startTimer = startTimerPeriod + 1.0;
  };

}

#endif// LEVELPROGRESS_HPP
