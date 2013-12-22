#ifndef GRAPHICS
#define GRAPHICS

namespace test {

  class Player;
  class Asteroid;
  class DecorateStar;
  class Bullet;
  class LevelProgress;

  void SetTranslate(float x, float y);
  void SetProjection(float fieldWidth, float fieldHeight);
  void DrawNumber(bool fromLeft, float x, float y, float sizex, float sizey, unsigned int number);
  void DrawDigit(float x, float y, float sizex, float sizey, unsigned int digit);
  void DrawPlayer(const Player & player);
  void DrawAsteroid(const Asteroid & asteroid);
  void DrawDecorateStar(const DecorateStar & star);
  void DrawBullet(const Bullet & bullet);
  void DrawProgress(const LevelProgress & progress);

}

#endif// GRAPHICS
