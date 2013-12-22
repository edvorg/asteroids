#ifndef SCREENSHAKER_HPP
#define SCREENSHAKER_HPP

namespace test {

  class ScreenShaker {
  public:
	// starts screen shake effect
	void Shake();

	void Update(double dt);
	void ApplyMatrix();

  protected:
  private:
	const float shakeTime = 1.0f;
	float shakeTimer = 0.0f;
	bool shake = false;
  };

}

#endif// SCREENSHAKER_HPP
