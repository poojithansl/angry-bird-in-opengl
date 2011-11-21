#ifndef _PIG_H_
#define _PIG_H_

class pig {
private:
  GLPOINT centre;
  bool flag;
public:
  pig() {
    centre.x = 1100;
    centre.y = 550;
    flag = false;
  }
  
  pig(GLPOINT temp) {
    centre = temp;
    flag = false;
  }
  
  void change_flag() {
    flag = false;
  }
  
  bool check_game_over(pig tmp) {
    if(tmp.flag && flag) {
      return true;
    }
    else {
      return false;
    }
  }
  
  void create_pig() {
    glColor3f(0.0, 0.0, 1.0);
    int k;
    GLPOINT hexVertex;
    GLdouble hexTheta;
    glBegin(GL_POLYGON);
    for (k = 0; k < 50; k++) {
      hexTheta = TWO_PI * k/50;
      hexVertex.x = centre.x + 50 * cos(hexTheta);
      hexVertex.y = centre.y + 50 * sin(hexTheta);
      glVertex2i (hexVertex.x, hexVertex.y);
    }
    glEnd();
    
    //RIGHT Eye
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (k = 0; k < 50; k++) {
      hexTheta = TWO_PI * k/50;
      hexVertex.x = centre.x + 20 + 5 * cos(hexTheta);
      hexVertex.y = centre.y + 15 + 5 * sin(hexTheta);
      glVertex2i (hexVertex.x, hexVertex.y);
    }
    glEnd();
    
    //LEFT Eye
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (k = 0; k < 50; k++) {
      hexTheta = TWO_PI * k/50;
      hexVertex.x = centre.x - 20 + 5 * cos(hexTheta);
      hexVertex.y = centre.y + 15 + 5 * sin(hexTheta);
      glVertex2i (hexVertex.x, hexVertex.y);
    }
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i (centre.x, centre.y + 10);
    glVertex2i (centre.x - 10, centre.y);
    glVertex2i (centre.x + 10, centre.y);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i (centre.x - 30, centre.y - 20);
    glVertex2i (centre.x + 30, centre.y - 20);
    glVertex2i (centre.x, centre.y - 30);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2i (centre.x - 10, centre.y - 22);
    glVertex2i (centre.x + 10, centre.y - 22);
    glVertex2i (centre.x, centre.y - 45);
    glEnd();
    glLineWidth(4.0);
    glBegin(GL_LINES);
      glVertex2i(centre.x, centre.y + 50);
      glVertex2i(centre.x - 20, centre.y + 65);
    glEnd();
    glBegin(GL_LINES);
      glVertex2i(centre.x, centre.y + 50);
      glVertex2i(centre.x + 20, centre.y + 65);
    glEnd();
  }
  
  bool check_transform(GLPOINT tmp, int num, int score, pig p2, bool final) {
    if(((tmp.x + 20) > (centre.x - 50)) && ((tmp.x - 20) < (centre.x + 50)) && !flag) {
      if(((tmp.y + 20) > (centre.y - 50)) && ((tmp.y - 20) < (centre.y + 50))) {
	flag = true;
	transform_pig(num, score, p2, final);
	return true;
      }
    }
  }
  
  void transform_pig(int num, int score, pig tmp, bool final) {
    char str[] = "CONGRATULATIONS, YOU WON THE GAME";
    char str2[] = "SORRY, GOOD LUCK NEXT TIME";
    char str1[] = "Your Score is - ";
    int sco[10], i, temp, j = 0, count = 0;
    bool show_score = false;
    GLPOINT star;
    GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;
    score += 14000 + ((3 - num) * 10000);
    temp = score;
    while(score) {
      sco[j++] = score % 10;
      score /= 10;
      count++;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    for(i = 0; i < 100; i++) {
	star.x = rand()%1600/1;
	star.y = rand()%900/1;
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(rand()%2/1);
	glBegin(GL_POINTS);
	glVertex2i(star.x, star.y);
	glEnd();
      }
      if(flag) {
	centre.x = -500;
	centre.y = -500;
	create_pig();
      }
    if(check_game_over(tmp)) {
      show_score = true;
      glRasterPos3f (500.0, 650.0, 0.0);
      for(i = 0; i < strlen(str); i++) {
	glutBitmapCharacter(font_style1, (int)str[i]);
      }
      glRasterPos3f (500.0, 600.0, 0.0);
      for(i = 0; i < strlen(str1); i++) {
	glutBitmapCharacter(font_style1, (int)str1[i]);
      }
      glutSwapBuffers();
    }
    else if(final) {
      if(num == 2){
	show_score = true;
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f (500.0, 650.0, 0.0);
	for(i = 0; i < strlen(str2); i++) {
	  glutBitmapCharacter(font_style1, (int)str2[i]);
	}
	glRasterPos3f (500.0, 600.0, 0.0);
	for(i = 0; i < strlen(str1); i++) {
	  glutBitmapCharacter(font_style1, (int)str1[i]);
	}
	glutSwapBuffers();
      }
    }
    if(show_score) {
      for(i = count - 1; i >= 0; i--) {
	switch(sco[i]) {
	  case 0 : glutBitmapCharacter(font_style1, '0');
		    break;
	  case 1 : glutBitmapCharacter(font_style1, '1');
		    break;
	  case 2 : glutBitmapCharacter(font_style1, '2');
		    break;
	  case 3 : glutBitmapCharacter(font_style1, '3');
		    break;
	  case 4 : glutBitmapCharacter(font_style1, '4');
		    break;
	  case 5 : glutBitmapCharacter(font_style1, '5');
		    break;
	  case 6 : glutBitmapCharacter(font_style1, '6');
		    break;
	  case 7 : glutBitmapCharacter(font_style1, '7');
		    break;
	  case 8 : glutBitmapCharacter(font_style1, '8');
		    break;
	  case 9 : glutBitmapCharacter(font_style1, '9');
		    break;
	 }
      }
      glutSwapBuffers();
    }
    glFlush();
  }
  
  void translate_pig(object tmp1, object tmp2, int num, int score, pig p2, bool final) {
    if(tmp1.check_flag() && tmp2.check_flag()) {
      centre.y = 250;
      create_pig();
      flag = true;
      transform_pig(num, score, p2, final);
    }
    else if(tmp2.check_flag() || tmp1.check_flag()) {
      centre.y = 400;
      create_pig();
      if(num == 3) {
	transform_pig(num, score, p2, final);
      }
    }
    else {
      if(num == 3) {
	transform_pig(num, score, p2, final);
      }
    }
    glutSwapBuffers();
  }
  
  void back_to_initial(int p, int q) {
    centre.x = p;
    centre.y = q;
    flag = false;
  }
};

#endif