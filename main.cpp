#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "object.h"
#include "angryobject.h"
#include "catapult.h"
#include "pig.h"
#include "horn.h"

GLPOINT assign_point(GLint x, GLint y) {
  GLPOINT temp;
  temp.x = x;
  temp.y = y;
  return temp;
}

const float u = 100.0;
int num_point = 0, score = 0;
bool final = false;
GLPOINT start, prev, curr, star;
GLPOINT l1 = assign_point(850, 200);
GLPOINT r1 = assign_point(1000, 350);
GLPOINT l2 = assign_point(1000, 200);
GLPOINT r2 = assign_point(1150, 350);
GLPOINT l3 = assign_point(850, 350);
GLPOINT r3 = assign_point(1000, 500);
GLPOINT l4 = assign_point(1000, 350);
GLPOINT r4 = assign_point(1150, 500);
GLPOINT h = assign_point(1300, 400);
GLPOINT hh = assign_point(1200, 400);
GLPOINT p = assign_point(1250, 250);
object obj1(l1, r1);
object obj2(l2, r2);
object obj3(l3, r3);
object obj4(l4, r4);
angryobject a1;
angryobject a2(350, 220);
angryobject a3(400, 220);
catapult c1;
pig p1;
pig p2(p);
horn h1(true);
horn h2(h, false);

  
void orig_screen() { 
  int i;
  glColor3f(0.43, 0.25, 0.22);
  glRecti(0, 0, 1600, 200);
  glColor3f(0.2, 0.2, 0.2);
  glBegin(GL_LINES);
  for (i = 0; i <= 1600; i += 50) {
    glVertex2i(i * 1.15, 200);
    glVertex2f(i, 0);
  }
  for (i = 0; i <= 200; i += 30) {
    glVertex2i(0, i);
    glVertex2f(1600, i);
  }
  glEnd();
  
  obj1.create_object();
  obj2.create_object();
  obj3.create_object();
  obj4.create_object();
  if(!a1.check_flag()) {
    a1.create_angry_bird();
  }
  if(!a2.check_flag()) {
    a2.create_angry_bird();
  }
  if(!a3.check_flag()) {
    a3.create_angry_bird();
  }
  c1.create_catapult();
  p1.create_pig();
  p2.create_pig();
  h1.create_object();
  h2.create_object();
}

void myInit(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(1.0f, 0.0f, 0.0f);
  glPointSize(4.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 1600.0, 0.0, 900.0); 
}

void myDisplay(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  orig_screen();
  glBegin(GL_POINTS);
  glVertex2i(300, 300);
  glutSwapBuffers();
  glEnd();
  glFlush();
}

void calc(int x, int y) {
  bool temp;
  start.x = 300, start.y = 300;
  prev = start;
  float sine, cose, time_flight;
  int i, o1 = 0, o2 = 0, o3 = 0, o4 = 0;
     glClear(GL_COLOR_BUFFER_BIT);
  
  // Calculate the sine and cosine values.
  sine = ((start.y - y)) / ( sqrt( pow((start.x - x), 2) + pow((start.y - y), 2) ) );
  cose = ((start.x - x)) / ( sqrt( pow((start.x - x), 2) + pow((start.y - y), 2) ) );
  
  //Calculating the time of flight
  time_flight = 2.0 * u * sine / 9.8;
  //Calulating the horizontal and vertical displacement
  for(i = 0; ((i < time_flight) || (curr.y > 300)); i++) {
    glClear(GL_COLOR_BUFFER_BIT);
    curr.x = start.x + (u * i * cose);
    curr.y = start.y + ((u * i * sine) - (0.5 * 9.8 * pow(i, 2)));
    if(curr.y < 300) {
      curr.y = 220;
    }
    if(!a1.check_flag()) {
      a1.move_bird(curr.x, curr.y);
    }
    else if(!a2.check_flag()) {
      a2.move_bird(curr.x, curr.y);
    }
   else if(!a3.check_flag()) {
      a3.move_bird(curr.x, curr.y);
    }
    orig_screen();
    o1 = obj1.check_transform(curr);
    o2 = obj2.check_transform(curr);
    o3 = obj3.check_transform(curr);
    o4 = obj4.check_transform(curr);
    if(o1 == 1) {
      score += 1500;
      obj3.check_translate(obj1);
    }
    if(o2 == 1) {
      score += 1500;
      obj4.check_translate(obj2);
    }
    if(o3 == 1) {
      score += 1000;
    }
    if(o4 == 1) {
      score += 1000;
    }
    h1.check_transform(curr);
    h2.check_transform(curr);
    temp = p1.check_transform(curr, num_point, score, p2, final);
    p1.translate_pig(obj2, obj4, num_point, score, p2, final);
    temp = p2.check_transform(curr, num_point, score, p1, final);
    if(p1.check_game_over(p2)) {
      break;
    }
    glutSwapBuffers();
  }
  glFlush();
}
void back_to_start() {
  p1.back_to_initial(1100, 550);
  p2.back_to_initial(1250, 250);
  obj1.back_to_initial(l1, r1);
  obj2.back_to_initial(l2, r2);
  obj3.back_to_initial(l3, r3);
  obj4.back_to_initial(l4, r4);
  a1.back_to_initial(300, 300);
  a2.back_to_initial(350, 220);
  a3.back_to_initial(400, 220);
  h1.back_to_initial(hh, true);
  h2.back_to_initial(h, false);
  final = false;
  glutSwapBuffers();
}
void myKeyboard(unsigned char key, int mouseX, int mouseY) {
  switch(key) {
    case 'r': num_point = 0;
	      glClear(GL_COLOR_BUFFER_BIT);
	      back_to_start();
	      orig_screen();
	      glutSwapBuffers();
	      break;
    case 'e': exit(-1);
    default: break;
  }
}

void myMouse(int button, int state, int x, int y) {
  int x1, y1;
  if(button == GLUT_LEFT_BUTTON) {
    if(state == GLUT_DOWN && !p1.check_game_over(p2)) {
	glClear(GL_COLOR_BUFFER_BIT);
	x1 = x;
	y1 = 900 - y;
	switch(num_point) {
	  case 0 : a2.move_bird(300, 300);
		   a2.create_angry_bird();
		   break;
	  case 1 : a3.move_bird(300, 300);
		   a3.create_angry_bird();
		   break;
	}
	glFlush();
    }
  }
  if(button == GLUT_LEFT_BUTTON) {
    if(state == GLUT_UP) {
      if(num_point < 3 && !p1.check_game_over(p2)) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	x1 = x;
	y1 = 900 - y;
	if(!a1.check_flag()) {
	  a1.move_bird(x1, y1);
	  a1.create_angry_bird();
	}
	else if(!a2.check_flag()) {
	  a2.move_bird(x1, y1);
	  a2.create_angry_bird();
	}
	else if(!a3.check_flag()) {
	  a3.move_bird(x1, y1);
	  a3.create_angry_bird();
	}
	calc(x1, y1);
	switch(num_point) {
	  case 0 : a1.change_flag();
		   break;
	  case 1 : a2.change_flag();
		   break;
	  case 2 : a3.change_flag();
		   if(!(p1.check_game_over(p2))) {
		     final = true;
		     p1.transform_pig(num_point, score, p2, final);
		   }
		    break;
	}
	num_point++;
	glEnd();
	glFlush();
      }
    }
  }
}
    
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Angry Birds");
	myInit();
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutMainLoop();
	return 0;
}