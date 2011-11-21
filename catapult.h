#ifndef _CATAPULT_H_
#define _CATAPULT_H_

class catapult {
private:
  GLPOINT start;
public:
  catapult() {
    start.x = 300;
    start.y = 260;
  }
  void create_catapult() {
    glColor3f(0.42, 0.28, 0.11);
    glLineWidth(5.0);
    glBegin(GL_LINES);
      glVertex2i(start.x, start.y);
      glVertex2i(start.x, start.y - 60);
    glEnd();
    glLineWidth(3.0);
    glBegin(GL_LINES);
      glVertex2i(start.x, start.y);
      glVertex2i(start.x - 20, start.y + 45);
    glEnd();
    glBegin(GL_LINES);
      glVertex2i(start.x, start.y);
      glVertex2i(start.x + 20, start.y + 45);
    glEnd();
  }
};


#endif