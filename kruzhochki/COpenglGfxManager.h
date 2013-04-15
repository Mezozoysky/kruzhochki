#ifndef KRUZHOCHKI_COPENGLGFXMANAGER_H
#define KRUZHOCHKI_COPENGLGFXMANAGER_H

#include "Kruzhochki.h"

namespace kruz
{
  /// Cross-platform OpenGL-based graphics manager implementation.
  class COpenglGfxManager :
    public IGfxManager
  {
  public:
    COpenglGfxManager(IRoot* root);
    virtual ~COpenglGfxManager();

    void setColor(float r, float g, float b, float a = 1.0f);
    void drawCircle(float x, float y, float r);
    // Wraps the root's glPrintText method.
    void drawText(const std::string& text, unsigned short x, unsigned short y);

  private:
    IRoot* mRoot;
  };

} // namespace kruz

#endif // KRUZHOCHKI_COPENGLGFXMANAGER_H
