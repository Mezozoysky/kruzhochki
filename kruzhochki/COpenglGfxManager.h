#ifndef KRUZHOCHKI_COPENGLGFXMANAGER_H
#define KRUZHOCHKI_COPENGLGFXMANAGER_H

#include "Kruzhochki.h"

namespace kruz
{

  class COpenglGfxManager :
    public IGfxManager
  {
  public:
    COpenglGfxManager(IRoot* root);
    virtual ~COpenglGfxManager();

    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);
    void drawCircle(GLfloat x, GLfloat y, GLfloat r);
    void drawPointsCounter(unsigned long points);
    // Wraps the root's glPrintText().
    void drawText(const std::string& text, unsigned short x, unsigned short y);

  private:
    IRoot* mRoot;
  };

} // namespace kruz

#endif // KRUZHOCHKI_COPENGLGFXMANAGER_H
