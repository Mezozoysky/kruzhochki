#ifndef KRUZHOCHKI_KRUZHOCHEK_H
#define KRUZHOCHKI_KRUZHOCHEK_H

#include "Kruzhochki.h"

using namespace kruz;

class Kruzhochek
{
public:
  Kruzhochek(float x, float y, float r, float red, float green, float blue);
  ~Kruzhochek();

  static const float MIN_RADIUS;
  static const float MAX_RADIUS;

  float getX() const;
  float getY() const;
  float getR() const;

  /// Draw the kruzhochek on the window.
  void draw(IGfxManager* gfx) const;

  /// Get the spped of kruzhochek.
  /// We will assume that the speed is measured in pixels/sec.
  float getSpeed() const;
  /// Get the point, that a player gets for the killing kruzhochek.
  unsigned long getPoints() const;

  /// Test for the kruzhochek's circle contain the given point.
  bool contains(unsigned short x, unsigned short y) const;

  /// Chnage position according to the elapsed time.
  /// @param deltaT The elapsed time, msec.
  void fall(DWORD deltaT);

private:
  float mValue; ///< Calculated form radius, affects the hit points and falling speed.

  float mX; ///< Circle X-ccord.
  float mY; ///< Circle Y-ccord.
  float mR; ///< Circle radius.

  float mRed; ///< Circle color red component.
  float mGreen; ///< Circle color green component.
  float mBlue; ///< Circle color blue componnt.
};

#endif // KRUZHOCHKI_KRUZHOCHEK_H
