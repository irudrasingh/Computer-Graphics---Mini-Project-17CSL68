#include<stdlib.h>
#include <GL/glut.h>
#include <algorithm>
#include<math.h>

using namespace std;

GLfloat cameraDistance = 12, cameraAngle = 0;

int arm_angles[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
enum { Palm_y, Palm_z, Last_b, Last_m, Last_t, Ring_b, Ring_m, Ring_t, Middle_b, Middle_m, Middle_t, Index_b, Index_m, Index_t, Thumb_b, Thumb_t };

int handShape = 0;
int showControls = 0;
int scene = 0;


void change_angle(int angle, int delta, int minimum = 0, int maximum = 180) {
	int tempAngle = (arm_angles[angle] + delta) % 360;
	if (tempAngle >= minimum && tempAngle <= maximum)
		arm_angles[angle] = tempAngle;
}


void drawstring(float x, float y, float z, const char *s) {
	unsigned int i;
	glRasterPos3f(x, y, z);

	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}
void drawstring2(float x, float y, float z, const char *s) {
	unsigned int i;
	glRasterPos2f(x, y);

	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}
void FrontPage() {
	float temp = 10;
	//glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0.0, 20, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/////Dark-grey Background/////
	glColor3f(0.117, 0.117, 0.117);
	glBegin(GL_POLYGON);
	glVertex2f(-15, -15);
	glVertex2f(-15, 15);
	glVertex2f(15, 15);
	glVertex2f(15, -15);
	glEnd();

	/////Light-grey Strip/////
	glColor3f(0.360, 0.376, 0.380);
	glBegin(GL_POLYGON);
	glVertex2f(-15, 15);
	glVertex2f(-15, 9);
	glVertex2f(15, 9);
	glVertex2f(15, 15);
	glEnd();

	/////Green Strip/////
	glColor3f(0.207, 0.690, 0.427);
	glBegin(GL_POLYGON);
	glVertex2f(-15, 5);
	glVertex2f(-15, 9);
	glVertex2f(15, 9);
	glVertex2f(15, 5);
	glEnd();

	/////Light-grey Bottom/////
	glColor3f(0.360, 0.376, 0.380);
	glBegin(GL_POLYGON);
	glVertex2f(-15, -15);
	glVertex2f(-15, -10);
	glVertex2f(15, -10);
	glVertex2f(15, -15);
	glEnd();

	/////Text part/////
	{
		glColor3f(0.117, 0.117, 0.117);
		//glColor3f(0.207, 0.690, 0.427);
		drawstring(-4, 10.8, 0.0, "ACS College of Engineering");
		glColor3f(0.117, 0.117, 0.117);
		drawstring(-4.5, 6.8, 0.0, "HAND SIMULATOR");

		glColor3f(0.360, 0.376, 0.380);
		drawstring(-8, 3, 0, "Project by :");

		glColor3f(0.207, 0.890, 0.627);
		drawstring2(-8, 2, 0, "     RUDRA PRATAP SINGH");
		drawstring2(-4, 2, 0, "                                   1AH17CS059");
		drawstring2(-8, 1, 0, "     SAHIL BHATT ");
		drawstring2(-4, 1, 0, "                                   1AH17CS062");
		drawstring2(-8, 0, 0, "     SURAJ KUMAR ");
		drawstring2(-4, 0, 0, "                                   1AH17CS076");

		glColor3f(0.360, 0.376, 0.380);
		drawstring(-8, -2, 0, "Under the guidance of :");

		glColor3f(0.207, 0.690, 0.427);
		drawstring2(-8, -3, 0, "     DR.JYOTI MEHTAN");
		drawstring2(-8, -4, 0, "     Professor,");
		drawstring2(-8, -5, 0, "     CSE dept");

		glColor3f(0.117, 0.117, 0.117);
		drawstring(-5.5, -12, 0.0, "PRESS ENTER TO START");
	}
	glutSwapBuffers();

}

void createSphere() {
	glutWireSphere(0.5f, 10, 10);
}
void controls() {
	glColor3f(1, 1, 1);


	/////last/////
	drawstring(6.5, 0, 1.7, "Q");
	drawstring(5, 0, 1.7, "A");
	drawstring(3, 0, 1.7, "Z");
	/////ring/////
	drawstring(6.5, 0, 0.7, "W");
	drawstring(5, 0, 0.7, "S");
	drawstring(3, 0, 0.7, "X");
	/////middle/////
	drawstring(6.5, 0, -0.3, "E");
	drawstring(5, 0, -0.3, "D");
	drawstring(3, 0, -0.3, "C");
	/////index/////
	drawstring(6.5, 0, -1.3, "R");
	drawstring(5, 0, -1.3, "F");
	drawstring(3, 0, -1.3, "V");
	/////thumb/////
	drawstring(0.8, 0, -2.8, "G");
	drawstring(0.8, 0, -4.8, "B");
}
void drawControl(float x, float y, float z, const char *s) {
	unsigned int i;
	glRasterPos3f(x, y, z);

	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
}
void controlDisplay(const char *str) {
	glColor3f(1, 1, 1);
	drawControl(0, 0, 0, str);
}
void MainScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	GLfloat x = cameraDistance * sin(cameraAngle);
	GLfloat z = cameraDistance * cos(cameraAngle);
	gluLookAt(x, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	{
		glPushMatrix();

		/*if (showControls == 1)
		controls();*/

		glRotatef((GLfloat)arm_angles[Palm_y], 0., 1., 0.);						//For palm rotation
		glRotatef((GLfloat)arm_angles[Palm_z], 0., 0., 1.);						//For palm rotation
		glTranslatef(1., 0., 0.);

		/*if (showControls == 1)
		controls();*/

		/////PALM/////
		glPushMatrix();
		if (handShape == 1)											/////SHAPE CHECK/////
			glScalef(4, 1, 4);
		else
			glScalef(4.0, 0.4, 4.0);
		glColor3f(1.0f, 1.0f, 1.0f);

		if (handShape == 1)											/////SHAPE CHECK/////
			glutWireSphere(0.5f, 20, 6);
		else
			glutWireCube(1.);
		glPopMatrix();

		{/////LAST FINGER/////
			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glTranslatef(1.5, 0., 1.5);
			else
				glTranslatef(2., 0., 1.5);
			glRotatef((GLfloat)arm_angles[Last_b], 0., 0., 1.);					//rotate bottom part of last finger
			glTranslatef(1., 0., 0.);

			if (showControls == 1) {
				controlDisplay("Z");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(2, 1, 1);
			else
				glScalef(2.0, 0.4, 1.0);
			glColor3f(1, 1, 0);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glTranslatef(1., 0., 0.);
			glRotatef((GLfloat)arm_angles[Last_m], 0., 0., 1.);					//rotate middle part of last finger
			glTranslatef(1., 0., 0.);

			if (showControls == 1) {
				controlDisplay("A");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(2, 1, 1);
			else
				glScalef(2.0, 0.4, 1.0);
			glColor3f(1, 0.75, 0);
			if (handShape == 1)										/////SHAPE CHECK/////	
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glTranslatef(0.85, 0., 0.);
			glRotatef((GLfloat)arm_angles[Last_t], 0., 0., 1.);					//rotate top part of last finger
			glTranslatef(0.85, 0., 0.);

			if (showControls == 1) {
				controlDisplay("Q");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(1.5, 1, 1);
			else
				glScalef(1.5, 0.4, 1.0);
			glColor3f(1, 0.75, 0.2);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glPopMatrix();
		}

		{/////RING FINGER/////
			glPushMatrix();

			glTranslatef(2., 0., 0.5);
			glRotatef((GLfloat)arm_angles[Ring_b], 0., 0., 1.);					//rotate bottom part of ring finger
			glTranslatef(1., 0., 0.);

			if (showControls == 1) {
				controlDisplay("X");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(2, 1, 1);
			else
				glScalef(2.0, 0.4, 1.0);
			glColor3f(0, 1, 1);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glTranslatef(1., 0., 0.);
			glRotatef((GLfloat)arm_angles[Ring_m], 0., 0., 1.);					//rotate middle part of ring finger
			glTranslatef(1., 0., 0.);

			if (showControls == 1) {
				controlDisplay("S");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(2, 1, 1);
			else
				glScalef(2.0, 0.4, 1.0);
			glColor3f(0, 1, 0.75);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glTranslatef(0.85, 0., 0.);
			glRotatef((GLfloat)arm_angles[Ring_t], 0., 0., 1.);					//rotate top part of ring finger
			glTranslatef(0.85, 0., 0.);

			if (showControls == 1) {
				controlDisplay("W");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(1.5, 1, 1);
			else
				glScalef(1.5, 0.4, 1.0);
			glColor3f(0.2, 1, 0.75);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glPopMatrix();
		}

		{/////MIDDLE FINGER/////
			glPushMatrix();

			glTranslatef(2., 0., -0.5);
			glRotatef((GLfloat)arm_angles[Middle_b], 0., 0., 1.);				//rotate bottom part of middle finger
			glTranslatef(1., 0., 0.);

			if (showControls == 1) {
				controlDisplay("C");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(2, 1, 1);
			else
				glScalef(2.0, 0.4, 1.0);
			glColor3f(1, 0, 1);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glTranslatef(1., 0., 0.);
			glRotatef((GLfloat)arm_angles[Middle_m], 0., 0., 1.);				//rotate middle part of middle finger
			glTranslatef(1., 0., 0.);

			if (showControls == 1) {
				controlDisplay("D");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(2, 1, 1);
			else
				glScalef(2.0, 0.4, 1.0);
			glColor3f(0.75, 0, 1);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glTranslatef(0.85, 0., 0.);
			glRotatef((GLfloat)arm_angles[Middle_t], 0., 0., 1.);				//rotate top part of middle finger
			glTranslatef(0.85, 0., 0.);

			if (showControls == 1) {
				controlDisplay("E");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(1.5, 1, 1);
			else
				glScalef(1.5, 0.4, 1.0);
			glColor3f(0.75, 0.2, 1);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glPopMatrix();
		}

		{/////INDEX FINGER/////
			glPushMatrix();

			if (handShape == 1)										/////SHAPE CHECK/////
				glTranslatef(1.5, 0., -1.5);
			else
				glTranslatef(2., 0., -1.5);
			glRotatef((GLfloat)arm_angles[Index_b], 0., 0., 1.);				//rotate bottom part of index finger
			glTranslatef(1., 0., 0.);

			if (showControls == 1) {
				controlDisplay("V");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(2, 1, 1);
			else
				glScalef(2.0, 0.4, 1.0);
			glColor3f(0.2, 0, 1);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glTranslatef(1., 0., 0.);
			glRotatef((GLfloat)arm_angles[Index_m], 0., 0., 1.);				//rotate middle part of index finger
			glTranslatef(1., 0., 0.);

			if (showControls == 1) {
				controlDisplay("F");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(2, 1, 1);
			else
				glScalef(2.0, 0.4, 1.0);
			glColor3f(0, 0.2, 1);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glTranslatef(0.85, 0., 0.);
			glRotatef((GLfloat)arm_angles[Index_t], 0., 0., 1.);				//rotate top part of index finger
			glTranslatef(0.85, 0., 0.);

			if (showControls == 1) {
				controlDisplay("R");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(1.5, 1, 1);
			else
				glScalef(1.5, 0.4, 1.0);
			glColor3f(0.2, 0.2, 1);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glPopMatrix();
		}

		{/////THUMB/////
			glPushMatrix();

			if (handShape == 1) {									/////SHAPE CHECK/////
				glTranslatef(0, 0, -1.8);
				glRotatef(60, 0, 1, 0);
				glRotatef((GLfloat)arm_angles[Thumb_b], 0.5, 0., 1.);				//rotate bottom part of thumb
			}
			else {
				glTranslatef(1, 0., -2.);
				glRotatef(90., 0., 1., 0.);
				glRotatef((GLfloat)arm_angles[Thumb_b], 0., 0., 1.);
			}

			glTranslatef(1., 0., 0.);

			if (showControls == 1) {
				controlDisplay("B");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(1.5, 1, 1);
			else
				glScalef(2.0, 0.4, 1.0);
			glColor3f(1, 0, 0.2);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();
			if (handShape == 1) {
				glTranslatef(0.5, 0., 0.);
				glRotatef((GLfloat)arm_angles[Thumb_t], 0.5, 0., 1.);				//rotate top part of thumb
			}
			else {
				glTranslatef(1., 0., 0.);
				glRotatef((GLfloat)arm_angles[Thumb_t], 0., 0., 1.);				//rotate top part of thumb
			}
			glTranslatef(1., 0., 0.);

			if (showControls == 1) {
				controlDisplay("G");
			}

			glPushMatrix();
			if (handShape == 1)										/////SHAPE CHECK/////
				glScalef(1.5, 1, 1);
			else
				glScalef(2.0, 0.4, 1.0);
			glColor3f(1, 0.2, 0);
			if (handShape == 1)										/////SHAPE CHECK/////
				createSphere();
			else
				glutWireCube(1.);
			glPopMatrix();

			glPopMatrix();
		}

		glPopMatrix();
	}

	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 300.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display() {
	if (scene == 0)
		FrontPage();
	else {
		MainScene();

	}
}

void specialKeys(int key, int x, int y) {
	GLfloat distanceDelta = 1.0, angleDelta = 5 * 3.14159 / 180.0;
	if (key == GLUT_KEY_UP) {
		cameraDistance -= distanceDelta;
		cameraDistance = max((GLfloat)2.0, cameraDistance);
	}
	if (key == GLUT_KEY_DOWN) {
		cameraDistance += distanceDelta;
	}
	if (key == GLUT_KEY_LEFT) {
		cameraAngle -= angleDelta;
	}
	if (key == GLUT_KEY_RIGHT) {
		cameraAngle += angleDelta;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	int delta = 5;

	switch (key) {

		/////PALM/////
	case 'l':
		change_angle(Palm_y, delta, -180, 0);
		break;
	case 'j':
		change_angle(Palm_y, -delta, -180, 0);
		break;
	case 'i':
		change_angle(Palm_z, delta, -90, 90);
		break;
	case 'k':
		change_angle(Palm_z, -delta, -90, 90);
		break;

		/////LAST FINGER/////
	case 'z':
		change_angle(Last_b, delta, 0, 90);
		break;
	case 'a':
		change_angle(Last_m, delta, 0, 100);
		break;
	case 'q':
		change_angle(Last_t, delta, 0, 80);
		break;
	case '1':
		arm_angles[Last_b] = 0;
		arm_angles[Last_m] = 0;
		arm_angles[Last_t] = 0;
		break;

		/////RING FINGER/////
	case 'x':
		change_angle(Ring_b, delta, 0, 90);
		break;
	case 's':
		change_angle(Ring_m, delta, 0, 100);
		break;
	case 'w':
		change_angle(Ring_t, delta, 0, 80);
		break;
	case '2':
		arm_angles[Ring_b] = 0;
		arm_angles[Ring_m] = 0;
		arm_angles[Ring_t] = 0;
		break;

		/////MIDDLE FINGER/////
	case 'c':
		change_angle(Middle_b, delta, 0, 90);
		break;
	case 'd':
		change_angle(Middle_m, delta, 0, 100);
		break;
	case 'e':
		change_angle(Middle_t, delta, 0, 80);
		break;
	case '3':
		arm_angles[Middle_b] = 0;
		arm_angles[Middle_m] = 0;
		arm_angles[Middle_t] = 0;
		break;

		/////INDEX FINGER/////
	case 'v':
		change_angle(Index_b, delta, 0, 90);
		break;
	case 'f':
		change_angle(Index_m, delta, 0, 100);
		break;
	case 'r':
		change_angle(Index_t, delta, 0, 80);
		break;
	case '4':
		arm_angles[Index_b] = 0;
		arm_angles[Index_m] = 0;
		arm_angles[Index_t] = 0;
		break;

		/////THUMB/////
	case 'b':
		change_angle(Thumb_b, delta, 0, 90);
		break;
	case 'g':
		change_angle(Thumb_t, delta, 0, 100);
		break;
	case '5':
		arm_angles[Thumb_b] = 0;
		arm_angles[Thumb_t] = 0;
		break;

		//////////////////Change Scene//////////////////
	case 13:
		scene = 1;
		break;


		//////////////////Show Controls//////////////////
	case 32:
		if (showControls == 0)
			showControls = 1;
		else
			showControls = 0;
		break;

		//////////////////Hand Gestures//////////////////
	case '0':									/////Gesture 1: NaN/////
		arm_angles[Last_b] = 5;
		arm_angles[Last_m] = 10;
		arm_angles[Last_t] = 5;

		arm_angles[Ring_b] = 80;
		arm_angles[Ring_m] = 90;
		arm_angles[Ring_t] = 60;

		arm_angles[Middle_b] = 80;
		arm_angles[Middle_m] = 90;
		arm_angles[Middle_t] = 60;

		arm_angles[Index_b] = 5;
		arm_angles[Index_m] = 10;
		arm_angles[Index_t] = 5;

		arm_angles[Thumb_b] = 80;
		arm_angles[Thumb_t] = 80;
		break;

	case '7':									/////Gesture 2: ROCK/////
		arm_angles[Last_b] = 90;
		arm_angles[Last_m] = 100;
		arm_angles[Last_t] = 80;

		arm_angles[Ring_b] = 90;
		arm_angles[Ring_m] = 100;
		arm_angles[Ring_t] = 80;

		arm_angles[Middle_b] = 90;
		arm_angles[Middle_m] = 100;
		arm_angles[Middle_t] = 80;

		arm_angles[Index_b] = 90;
		arm_angles[Index_m] = 100;
		arm_angles[Index_t] = 80;

		arm_angles[Thumb_b] = 60;
		arm_angles[Thumb_t] = 100;
		break;

	case '8':									/////Gesture 2: PAPER/////
		arm_angles[Last_b] = 0;
		arm_angles[Last_m] = 0;
		arm_angles[Last_t] = 0;

		arm_angles[Ring_b] = 0;
		arm_angles[Ring_m] = 0;
		arm_angles[Ring_t] = 0;

		arm_angles[Middle_b] = 0;
		arm_angles[Middle_m] = 0;
		arm_angles[Middle_t] = 0;

		arm_angles[Index_b] = 0;
		arm_angles[Index_m] = 0;
		arm_angles[Index_t] = 0;

		arm_angles[Thumb_b] = 0;
		arm_angles[Thumb_t] = 0;
		break;

	case '9':									/////Gesture 2: SCISSOR/////
		arm_angles[Last_b] = 60;
		arm_angles[Last_m] = 90;
		arm_angles[Last_t] = 80;

		arm_angles[Ring_b] = 60;
		arm_angles[Ring_m] = 90;
		arm_angles[Ring_t] = 80;

		arm_angles[Middle_b] = 5;
		arm_angles[Middle_m] = 0;
		arm_angles[Middle_t] = 0;

		arm_angles[Index_b] = 5;
		arm_angles[Index_m] = 0;
		arm_angles[Index_t] = 0;

		arm_angles[Thumb_b] = 80;
		arm_angles[Thumb_t] = 100;
		break;
	}

	glutPostRedisplay();
}



void Menu(int value) {
	switch (value) {
	case 1:
		handShape = 0;
		break;
	case 2:
		handShape = 1;
		break;

	case 3:
		exit(0);
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(790, 790);
	glutCreateWindow("Hand Simulation");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);

	int sub1 = glutCreateMenu(Menu);
	glutAddMenuEntry("Cuboidal", 1);
	glutAddMenuEntry("Spherical", 2);
	glutCreateMenu(Menu);
	glutAddSubMenu("Shape", sub1);

	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutMainLoop();
}
