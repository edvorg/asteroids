#ifndef PLAYER_HPP
#define PLAYER_HPP

namespace test {

  class Player {
  public:
	void Init();
	void Update(double dt);
	void Draw();
	void Release();

	// some data to handle from app
	void Touch(float newX, float newY);

  protected:
  private:
	bool spawned = false;
	float x = 0.0f;
	float y = 0.0f;
	float angle = 0.0f;
	float velX = 0.0f;
	float velY = 0.0f;
	float targetX = 0.0f;
	float targetY = 0.0f;
	float size = 7.0f;
	float acceleration = 0.005;
	float deceleration = 3;
  };

}

#endif// PLAYER_HPP
