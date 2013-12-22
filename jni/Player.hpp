#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <functional>

#include "Dimensions.hpp"
#include "ParticleSystem.hpp"
#include "CometTail.hpp"
#include "Bullets.hpp"

namespace test {

  class Player {
  public:
	template<class PARTICLE>
	using CollideBulletsCallback = std::function<void (PARTICLE &, Bullet &)>;
	template<class PARTICLE>
	using CollideCallback = std::function<void (PARTICLE &, Player &)>;

	void Init();
	void Update(double dt);
	void Draw();
	void Release();

	// try to kill player
	void Kill();

	// process touch
	void Touch(float newX, float newY);

	// collisions with particle systems
	template<class PARTICLE>
	void Collide(ParticleSystem<PARTICLE> & system, CollideCallback<PARTICLE> callback);
	// collisions with bullets
	template<class PARTICLE>
	void CollideBullets(ParticleSystem<PARTICLE> & system, CollideBulletsCallback<PARTICLE> callback);

	void Reset();

	Dimensions GetDimensions() const;
	inline bool IsSpawned() const { return spawned; }
	inline float GetX() const { return x; }
	inline float GetY() const { return y; }
	inline float GetAngle() const { return angle; }
	inline float GetSize() const { return size; }
	inline int GetLives() const { return lives; }
	inline int IsActive() const { return active; }
	inline void FieldSize(float w, float h) { bullets.FieldSize(w, h); }

  protected:
  private:
	const float respawnPeriod = 3.0f;
	const int livesInitial = 3;
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
	float respawnTimer = respawnPeriod + 1.0f;
	int lives = livesInitial;
	bool active = false;
	CometTail tail;
	Bullets bullets;
  };

  template<class PARTICLE>
  void Player::Collide(ParticleSystem<PARTICLE> & system, CollideCallback<PARTICLE> callback) {
	if (IsSpawned()) {
	  system.Collide(*this, callback);
	}
  }

  template<class PARTICLE>
  void Player::CollideBullets(ParticleSystem<PARTICLE> & system, CollideBulletsCallback<PARTICLE> callback) {
	system.template Collide<Bullet>(bullets, callback);
  }

}

#endif// PLAYER_HPP
