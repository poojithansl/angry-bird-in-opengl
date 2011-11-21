#ifndef _OBJECT_H_
#define _OBJECT_H_

typedef struct point {
  GLint x;
  GLint y;
}GLPOINT;

class object {
private:
  GLPOINT lb;
  GLPOINT rt;
  bool flag;
public:
  object() {
    lb.x = 0;
    lb.y = 0;
    rt.x = 0;
    rt.y = 0;
    flag = false;
  }
  
  object(GLPOINT l, GLPOINT r) {
    lb = l;
    rt = r;
    flag = false;
  }
  
  void create_object() {
    if(!flag) {
      glColor3f(rand()%256/255.0, rand()%256/255.0, rand()%256/255.0);
      glRecti(lb.x, lb.y, rt.x, rt.y);
    }
  }
  
  void transform_object() {
    GLPOINT temp;
    GLint xref, yref, area;
    xref = ( (lb.x + rt.x) / 2);
    yref = ( (lb.y + rt.y) / 2);
    temp.x = xref;
    temp.y = yref;
    area = ((rt.x - lb.x) * (rt.y - lb.y));
    while(area > 1) {
      lb.x = (lb.x * 0.5) + (xref * (1 - 0.5));
      lb.y = (lb.y * 0.5) + (yref * (1 - 0.5));
      rt.x = (rt.x * 0.5) + (xref * (1 - 0.5));
      rt.y = (rt.y * 0.5) + (yref * (1 - 0.5));
      create_object();
      area = ((rt.x - lb.x) * (rt.y - lb.y));
      glutSwapBuffers();
      glFlush();
    }
  }
  
  void translate_object() {
      lb.y = lb.y - 150;
      rt.y = rt.y - 150;
      create_object();
      glutSwapBuffers();
  }
  
  int check_transform(GLPOINT temp) {
    if((temp.x + 20) > lb.x && (temp.x - 20) < rt.x && !flag) {
      if((temp.y + 20) > lb.y && (temp.y - 20) < rt.y) {
	transform_object();
	flag = true;
	return 1;
      }
    }
    return 0;
  }
  
  void check_translate(object tmp) { 
    if(tmp.flag && !flag) { 
      translate_object();
    }
  }
  
  bool check_flag() {
    if(flag) {
      return true;
    }
  }
  
  void back_to_initial(GLPOINT l, GLPOINT r) {
    lb = l;
    rt = r;
    flag = false;
  }
};

#endif