#ifndef _ANGRY_BIRD_H_
#define _ANGRY_BIRD_H_

const double TWO_PI = 6.2831853;

class angryobject {
private:
  GLPOINT centre;
  bool flag;
public:
  angryobject() {
    centre.x = 300;
    centre.y = 300;
    flag = false;
  }
  angryobject(int x, int y) {
    centre.x = x;
    centre.y = y;
    flag = false;
  }
  
  bool check_flag() {
    if(flag) 
      return true;
    else 
      return false;
  }
      
  void create_angry_bird() {
    glColor3f(1.0, 0.0, 0.0);
    int k;
    GLPOINT hexVertex;
    GLdouble hexTheta;
    glBegin(GL_POLYGON);
    for (k = 0; k < 20; k++) {
      hexTheta = TWO_PI * k/20;
      hexVertex.x = centre.x + 20 * cos(hexTheta);
      hexVertex.y = centre.y + 20 * sin(hexTheta);
      glVertex2i (hexVertex.x, hexVertex.y);
    }
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2i (centre.x + 10, centre.y + 10);
    glVertex2i (centre.x - 10, centre.y + 10);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i (centre.x, centre.y + 8);
    glVertex2i (centre.x - 5, centre.y);
    glVertex2i (centre.x + 5, centre.y);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i (centre.x - 10, centre.y - 3);
    glVertex2i (centre.x + 10, centre.y - 3);
    glVertex2i (centre.x, centre.y - 6);
    glEnd();
  }
  
  void change_flag() {
    if(flag) 
      flag = false;
    else
      flag = true;
  }
  
  void move_bird(int x, int y) {
    centre.x = x;
    centre.y = y;
  }
  
  void back_to_initial(int x, int y) {
    centre.x = x;
    centre.y = y;
    flag = false;
  }
};

#endif
  