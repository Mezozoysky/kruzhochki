#ifndef KRUZHOCHKI_IGFXMANAGER_H
#define KRUZHOCHKI_IGFXMANAGER_H

#include <Windows.h>
#include <gl\GL.h>

namespace kruz
{

  class IGfxManager
  {
  public:
    virtual ~IGfxManager()
    {
    }

    virtual void drawCircle(GLfloat x, GLfloat y, GLfloat r) = 0;
    virtual void drawPointsCounter(unsigned long points) = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IGFXMANAGER_H
