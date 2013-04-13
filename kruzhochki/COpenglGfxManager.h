#ifndef KRUZHOCHKI_COPENGLGFXMANAGER_H
#define KRUZHOCHKI_COPENGLGFXMANAGER_H

#include "Kruzhochki.h"

namespace kruz
{

  class COpenglGfxManager :
    public IGfxManager
  {
  public:
    COpenglGfxManager();
    virtual ~COpenglGfxManager();
    void drawCircle(GLfloat x, GLfloat y, GLfloat r);
    void drawPointsCounter(unsigned long points);
  };

} // namespace kruz

#endif // KRUZHOCHKI_COPENGLGFXMANAGER_H
