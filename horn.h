#ifndef _HORN_H_
#define _HORN_H_

class horn {
private:
  GLPOINT l;
  bool lside;
public:
  horn(bool s) {
    l.x = 1200;
    l.y = 400;
    lside = s;
  }
  
  horn(GLPOINT p, bool s) {
    l = p;
    lside = s;
  }
  
  void create_object() {
    if(lside) {
      glColor3f(0.12, 5.9, 0.14);
      glBegin(GL_TRIANGLES);
	glVertex2i(l.x, l.y);
	glVertex2i(l.x + 20, 200);
	glVertex2i(l.x, 200);
      glEnd();
    }
    else {
      glColor3f(0.12, 5.9, 0.14);
      glBegin(GL_TRIANGLES);
	glVertex2i(l.x, l.y);
	glVertex2i(l.x - 20, 200);
	glVertex2i(l.x, 200);
      glEnd();
    }
  }
  
  void transform_horn(GLPOINT temp) {
    l.y = temp.y;
    create_object();
  }
    
  void check_transform(GLPOINT temp) {
    if((temp.y - 20) < l.y && (temp.y + 20) > 200) {
      if(lside) {
	if((temp.x + 20) > (l.x - 20) && (temp.x - 20) < l.x) {
	  transform_horn(temp);
	}
      }
      else {
	if((temp.x - 20) < l.x && (temp.x + 20) > (l.x - 20)) {
	  transform_horn(temp);
	}
      }
    }
  }
  
  void back_to_initial(GLPOINT p, bool s) {
    l = p;
    lside = s;
  }
  
};
  
  

  
#endif