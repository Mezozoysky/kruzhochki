#ifndef KRUZHOCHKI_IGFXMANAGER_H
#define KRUZHOCHKI_IGFXMANAGER_H

#include <Windows.h>
#include <string>

namespace kruz
{
  /// Graphics manager interface.
  /// Graphics manager can draw a circle or write a text.
  class IGfxManager
  {
  public:
    virtual ~IGfxManager()
    {
    }

    /// Set the current color.
    virtual void setColor(float r, float g, float b, float a = 1.0f) = 0;

    /// Draw the circle
    virtual void drawCircle(float x, float y, float r) = 0;
    /// Draw the text
    virtual void drawText(const std::string& text, unsigned short x, unsigned short y) = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IGFXMANAGER_H
