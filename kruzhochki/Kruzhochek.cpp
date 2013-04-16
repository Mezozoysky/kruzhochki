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

unsigned long Kruzhochek::getPoints() const
{
  // Poits are integer. The biggest (and cheapest) circle will cost 10 point
  // The smaller the raius, the grater value and points.
  return (unsigned long)(floor(mValue * 10 + 0.5));
}

bool Kruzhochek::contains(unsigned short x, unsigned short y) const
{
  // Geometry.
  float dX; // Horizontal distance between point and circle center.
  float dY; // Vertical distance between point and circle center.

  if (x > mX)
  {
    dX = x - mX;
  }
  else
  {
    dX = mX - x;
  }
  if (y > mY)
  {
    dY = y - mY;
  }
  else
  {
    dY = mY - y;
  }

  // Return true if absolute distance less then raduis.
  return sqrtf(dX * dX + dY * dY) < mR;
}

void Kruzhochek::fall(DWORD deltaT)
{
  mY += (deltaT / 10.0f) * (mValue + 0.2f); // time * speed = pixels to fall.
}
