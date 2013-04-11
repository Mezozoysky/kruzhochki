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

    virtual void drawCircle() = 0;
    virtual void drawCounter() = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IGFXMANAGER_H
