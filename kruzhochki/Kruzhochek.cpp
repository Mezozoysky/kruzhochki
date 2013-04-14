#include "Kruzhochek.h"
#include <math.h>

Kruzhochek::Kruzhochek(float x, float y, float r, float red, float green, float blue) :
  mX(x),
  mY(y),
  mR(r),
  mRed(red),
  mGreen(green),
  mBlue(blue)
{
  // Extra normalizing the radius. Just-in-case.
  if (mR > MAX_RADIUS)
  {
    mR = MAX_RADIUS;
  }
  if (mR < MIN_RADIUS)
  {
    mR = MIN_RADIUS;
  }
  // Calculating the value, reciprocal to radius.
  // It's always equas 1 for maximum radius and it increases while decreasing the radius.
  mValue = Kruzhochek::MAX_RADIUS / mR;
}

Kruzhochek::~Kruzhochek()
{
}

void Kruzhochek::draw(IGfxManager* gfx) const
{
  gfx->setColor(mRed, mGreen, mBlue);
  gfx->drawCircle(mX, mY, mR);
}

const float Kruzhochek::MIN_RADIUS = 20.0f;
const float Kruzhochek::MAX_RADIUS = 60.0f;

float Kruzhochek::getX() const
{
  return mX;
}

float Kruzhochek::getY() const
{
  return mY;
}

float Kruzhochek::getR() const
{
  return mR;
}

float Kruzhochek::getSpeed() const
{
  return mValue;
}

int Kruzhochek::getPoints() const
{
  // Poits are integer. The biggest (and cheapest) circle will cost 10 point
  // The smaller the raius, the grater value and points.
  return (int)(floor(mValue * 10 + 0.5));
}

void Kruzhochek::fall(DWORD deltaT)
{
  mY += deltaT / 10 * mValue; // sec * pixels/sec = pixels to fall.
}
