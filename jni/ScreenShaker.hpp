#ifndef SCREENSHAKER_HPP
#define SCREENSHAKER_HPP

namespace test {

  // screen shake effect used in by e.g. explosions
  class ScreenShaker {
  public:
	// starts screen shake effect
	void Shake();

	void Update(double dt);
	// apply transformation matrix of shake effect
	void ApplyMatrix();

  protected:
  private:
	const float shakeTime = 1.0f;
	float shakeTimer = 0.0f;
	bool shake = false;
  };

}

#endif// SCREENSHAKER_HPP
