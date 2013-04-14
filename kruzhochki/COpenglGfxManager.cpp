#include "COpenglGfxManager.h"
#include <math.h>

namespace kruz
{

  COpenglGfxManager::COpenglGfxManager(IRoot* root) :
    mRoot(root)
  {
  }


  COpenglGfxManager::~COpenglGfxManager()
  {
  }

  void COpenglGfxManager::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    glColor4f(r, g, b, a);
  }

  void COpenglGfxManager::drawCircle(GLfloat x, GLfloat y, GLfloat r)
  {
    GLfloat angle;
    glPushMatrix();
    glLoadIdentity();
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
      for (int i = 0; i < 60; ++i)
      {
        angle = (GLfloat)(i * 2 * 3.1415926 / 60);
        glVertex2f(x + (cos(angle) * r), y + (sin(angle) * r));
      }
    glEnd();
    glPopMatrix();
  }

  void COpenglGfxManager::drawPointsCounter(unsigned long points)
  {
  }

  void COpenglGfxManager::drawText(const std::string& text, unsigned short x, unsigned short y)
  {
    mRoot->glPrintText(text, x, y);
  }

} // namespace kruz
