#ifndef KRUZHOCHKI_IGFXMANAGER_H
#define KRUZHOCHKI_IGFXMANAGER_H

#include <Windows.h>
#include <gl\GL.h>
#include <string>

namespace kruz
{

  class IGfxManager
  {
  public:
    virtual ~IGfxManager()
    {
    }

    virtual void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f) = 0;

    virtual void drawCircle(GLfloat x, GLfloat y, GLfloat r) = 0;
    virtual void drawPointsCounter(unsigned long points) = 0;

    virtual void drawText(const std::string& text, unsigned short x, unsigned short y) = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IGFXMANAGER_H
