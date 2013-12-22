#ifndef GRAPHICS
#define GRAPHICS

namespace test {

  class Player;
  class Asteroid;
  class DecorateStar;
  class Bullet;
  class LevelProgress;

  void DrawPlayer(const Player & player);
  void DrawAsteroid(const Asteroid & asteroid);
  void DrawDecorateStar(const DecorateStar & star);
  void DrawBullet(const Bullet & bullet);
  void DrawProgress(const LevelProgress & progress);

}

#endif// GRAPHICS
