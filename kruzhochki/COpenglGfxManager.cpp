#include "COpenglGfxManager.h"
#include <math.h>
#include <GL\GL.h>

namespace kruz
{

  COpenglGfxManager::COpenglGfxManager(IRoot* root) :
    mRoot(root)
  {
  }


  COpenglGfxManager::~COpenglGfxManager()
  {
  }

  void COpenglGfxManager::setColor(float r, float g, float b, float a)
  {
    glColor4f(r, g, b, a);
  }

  void COpenglGfxManager::drawCircle(float x, float y, float r)
  {
    // Drawing the circle by 60 short lines connecting it's points.
    GLfloat angle;
    glPushMatrix();
    glLoadIdentity();
    glLineWidth(3.0f); // 3-pixels line width.
    glBegin(GL_LINE_LOOP);
      for (int i = 0; i < 60; ++i)
      {
        angle = (GLfloat)(i * 2 * 3.1415926 / 60);
        glVertex2f(x + (cos(angle) * r), y + (sin(angle) * r));
      }
    glEnd();
    glPopMatrix();
  }

  void COpenglGfxManager::drawText(const std::string& text, unsigned short x, unsigned short y)
  {
    mRoot->glPrintText(text, x, y);
  }

} // namespace kruz
