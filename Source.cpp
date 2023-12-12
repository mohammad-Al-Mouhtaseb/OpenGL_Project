#include <GL/glut.h>
#include<math.h>
#include<mmsystem.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

double tet = 6.28 + (3.14 / 2);
double ex = 0, ez = 0, ey = 0;
bool door1 = 1, door2 = 1, door3 = 1, door4 = 1, door5 = 1;//close
double d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0;
GLUquadricObj *a = gluNewQuadric();
int x = 0;

int tex[8];
int heet[20];

void SkyBoxCube()
{
	float P1[] = { 1, -0.2, 1 };
	float P2[] = { 1, -0.2, -1 };
	float P3[] = { -1, -0.2, -1 };
	float P4[] = { -1,-0.2, 1 };
	float P5[] = { 1, 0.3, 1 };
	float P6[] = { 1, 0.3, -1 };
	float P7[] = { -1, 0.3, -1 };
	float P8[] = { -1, 0.3, 1 };
	glColor3f(1, 2, 1);
	//bottom
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); glVertex3fv(P1);
	glTexCoord2f(0, 0); glVertex3fv(P2);
	glTexCoord2f(0, 1); glVertex3fv(P3);
	glTexCoord2f(1, 1); glVertex3fv(P4);
	glEnd();
	//top
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3fv(P6);
	glTexCoord2f(1, 1); glVertex3fv(P5);
	glTexCoord2f(1, 0); glVertex3fv(P8);
	glTexCoord2f(0, 0); glVertex3fv(P7);
	glEnd();
	//right
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1); glVertex3fv(P1);//1
	glTexCoord2f(1, 0); glVertex3fv(P5);//2
	glTexCoord2f(0, 0); glVertex3fv(P6);//6
	glTexCoord2f(0, 1); glVertex3fv(P2);//5
	glEnd();
	//back
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1); glVertex3fv(P2);//2
	glTexCoord2f(1, 0); glVertex3fv(P6);//3
	glTexCoord2f(0, 0); glVertex3fv(P7);//7
	glTexCoord2f(0, 1); glVertex3fv(P3);//6
	glEnd();
	//left
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1); glVertex3fv(P3);//3
	glTexCoord2f(1, 0); glVertex3fv(P7);//4
	glTexCoord2f(0, 0); glVertex3fv(P8);//8
	glTexCoord2f(0, 1); glVertex3fv(P4);//7
	glEnd();
	//front
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1); glVertex3fv(P4);//4
	glTexCoord2f(1, 0); glVertex3fv(P8);//1
	glTexCoord2f(0, 0); glVertex3fv(P5);//5
	glTexCoord2f(0, 1); glVertex3fv(P1);//8
	glEnd();
}

void SkyBoxFunc()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	SkyBoxCube();
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_LIGHTING);
}

GLuint LoadTexture(const char imagename[])
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping/filtering options (on the currently bound texture object)

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//GL_ADD, GL_MODULATE, GL_DECAL, GL_BLEND, GL_REPLACE.

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(imagename, &width, &height, &nrChannels, 0);
	if (data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

	}
	else
	{
		MessageBox(NULL, "Failed to load texture", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}
	stbi_image_free(data);


	return textureID;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE: /* Escape key */
		exit(0);
		break;

	case 'w':
		ey += 0.25;
		glutPostRedisplay();
		break;

	case 's':
		ey -= 0.25;
		glutPostRedisplay();
		break;
	case '1':
		if (door1) {
			door1 = 0;
			d1 = 0;
		}
		else {
			door1 = 1;
		}
		glutPostRedisplay();
		break;
	case '2':
		if (door2) {
			door2 = 0;
			d2 = 0;
		}
		else {
			door2 = 1;
		}
		glutPostRedisplay();
		break;
	case '3':
		if (door3) {
			door3 = 0;
			d3 = 0;
		}
		else {
			door3 = 1;
		}
		glutPostRedisplay();
		break;
	case '4':
		if (door4) {
			door4 = 0;
			d4 = 0;
		}
		else {
			door4 = 1;
		}
		glutPostRedisplay();
		break;
	case '5':
		if (door5) {
			door5 = 0;
			d5 = 0;
		}
		else {
			door5 = 1;
		}
		glutPostRedisplay();
		break;

	case 'r':
		ex = ex + ( 4 *cos(tet) );
		ez = ez + ( 4 * sin(tet));
		glutPostRedisplay();
		break;


	default:
		break;
	}
}

void InitGL(void)
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.7f, 0.7f, 0.8f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	//PlaySound("g.wav", 0, SND_ASYNC | SND_LOOP);

	tex[0] = LoadTexture("Data/negy.jpg");
	tex[1] = LoadTexture("Data/posy.jpg");
	tex[2] = LoadTexture("Data/posx.jpg");
	tex[3] = LoadTexture("Data/posz.jpg");
	tex[4] = LoadTexture("Data/negx.jpg");
	tex[5] = LoadTexture("Data/negz.jpg");

	//الاشجار
	glNewList(1, GL_COMPILE);
	glPushMatrix();
	glColor3ub(10, 81, 36);
	gluQuadricDrawStyle(a, GLU_LINE);
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 0, -0.5 - 0.25);
	glutSolidCone(1, 2, 5, 5);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(0, 50, 5);
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 0, -0.5 - 0.25);
	glRotated(-18, 0, 0, 1);
	gluCylinder(a, 1.001, 0, 2.001, 5, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(0, 91, 46);
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 0, -0.25);
	glutSolidCone(1, 2, 5, 5);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(0, 50, 5);
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 0, -0.25);
	glRotated(-18, 0, 0, 1);
	gluCylinder(a, 1.001, 0, 2.001, 5, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(0, 91, 46);
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 0, 0.5 - 0.25);
	glutSolidCone(1, 2.3, 5, 5);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(0, 50, 5);
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 0, 0.5 - 0.25);
	glRotated(-18, 0, 0, 1);
	gluCylinder(a, 1.001, 0, 2.301, 5, 1);
	glPopMatrix();
	glPushMatrix();
	gluQuadricDrawStyle(a, GLU_FILL);
	glColor3ub(90, 48, 20);
	glRotated(90, 1, 0, 0);
	glTranslated(0, 0, 0.5 + 0.25);
	gluCylinder(a, 0.2, 0.25, 1.25, 30, 30);
	glPopMatrix();
	glEndList();
	//السور
	glNewList(2, GL_COMPILE);
	glPushMatrix();
	gluQuadricDrawStyle(a, GLU_FILL);
	glColor3ub(145, 145, 145);
	glTranslatef(0, -0.25, 0);
	glScalef(1, 1, 0.1);
	glutSolidCube(3.5);
	glPopMatrix();
	glPushMatrix();
	gluQuadricDrawStyle(a, GLU_FILL);
	glColor3ub(100, 100, 100);
	glTranslatef(2, 0, 0);
	glScalef(1, 8, 1);
	glutSolidCube(0.5);
	glPopMatrix();
	glEndList();
	//الرصيف
	glNewList(3, GL_COMPILE);
	glPushMatrix();
	glTranslated(0, -2 + 0.24, 0);
	glScalef(4, 0.3, 2);
	glColor3ub(107, 103, 99);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(1, -2 + 0.24, -1.25);
	glScalef(2, 0.3, 0.5);
	glColor3ub(190, 110, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1, -2 + 0.24, -1.25);
	glScalef(2, 0.3, 0.5);
	glColor3ub(190, 190, 190);
	glutSolidCube(1);
	glPopMatrix();
	glEndList();
	//الزجاج
	glNewList(4, GL_COMPILE);
	glPushMatrix();
	gluQuadricDrawStyle(a, GLU_LINE);
	glLineWidth(6);
	glTranslatef(-2.4, 0.625, 40);
	glScalef(3.4, 3.4, 0.05);
	glColor3ub(60, 60, 60);
	glRotatef(45, 0, 0, 1);
	gluCylinder(a, 1, 1, 1, 4, 50);
	glPopMatrix();
	glPushMatrix();
	gluQuadricDrawStyle(a, GLU_LINE);
	glLineWidth(6);
	glTranslatef(2.5, 0.625, 40);
	glScalef(3.45, 3.4, 0.05);
	glColor3ub(60, 60, 60);
	glRotatef(45, 0, 0, 1);
	gluCylinder(a, 1, 1, 1, 4, 50);
	glPopMatrix();
	glPushMatrix();
	glMaterialf(GL_FRONT, GL_SHININESS, 32);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(-2.4, 0.625, 40);
	glScalef(4.78, 4.75, 0.05);
	glColor4f(0, 0, 0.65, 0.25);
	glutSolidCube(1);
	glLineWidth(1);
	glPopMatrix();
	glEndList();
	//كنب
	glNewList(5, GL_COMPILE);
	glPushMatrix();
	glColor3ub(70, 58, 35);
	glTranslatef(0, -2 + 0.4, 0);
	glScalef(2, 0.8, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(90, 58, 35);
	glTranslatef(0.8, -1, 0);
	glScalef(0.4, 0.4, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.8, -1, 0);
	glScalef(0.4, 0.4, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(128, 0, 0);
	glTranslatef(0, -2 + 0.85, 0.5);
	glScalef(1.9, 1.8, 0.1);
	glutSolidCube(1);
	glPopMatrix();
	glEndList();
	//كرسي الطاولة
	glNewList(6, GL_COMPILE);
	glPushMatrix();
	gluQuadricDrawStyle(a, GLU_FILL);
	glColor3ub(0, 125, 40);
	glTranslatef(0, -2 + 0.75, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 0.75, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5, -2 + 0.75, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 0.75, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -2 + 1.5, 0.5);
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.5, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5, -2 + 1.5, 0.5);
	glRotatef(90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.5, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(200, 0, 0);
	glTranslatef(0.25, -1.325, 0.25);
	glScalef(0.56, 0.06, 0.56);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(80, 40, 200);
	glTranslatef(0.25, -0.75, 0.5);
	glScalef(0.58, 0.3, 0.06);
	glutSolidCube(1);
	glPopMatrix();
	glEndList();
	//مروحة
	glNewList(9, GL_COMPILE);
	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glRotated(90, 1, 0, 0);
	gluCylinder(a, 0.075, 0.075, 1.5+0.5, 30, 30);
	glPopMatrix();
	glEndList();
	//حيط مطبخ
	glNewList(7, GL_COMPILE);
	glPushMatrix();
	heet[0] = LoadTexture("Data/heeet.jpg");
	glBindTexture(GL_TEXTURE_2D, heet[0]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0,1);
	float P1[] = { 1, 1, -1 };
	float P2[] = { -1, 1, -1 };
	float P3[] = { -1, -1, -1 };
	float P4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(P1);
	glTexCoord2f(0, 0); glVertex3fv(P2);
	glTexCoord2f(0, 1); glVertex3fv(P3);
	glTexCoord2f(1, 1); glVertex3fv(P4);
	glEnd();
	glPopMatrix();
	glEndList();
	//ارضية النوم
	glNewList(8, GL_COMPILE);
	glPushMatrix();
	heet[1] = LoadTexture("Data/Marble.bmp");
	glBindTexture(GL_TEXTURE_2D, heet[1]);
	glBegin(GL_QUADS);
	//glColor4f(200, 0, 0, 1);
	float pP1[] = { 1, 1, -1 };
	float pP2[] = { -1, 1, -1 };
	float pP3[] = { -1, -1, -1 };
	float pP4[] = { 1, -1, -1 };
	glTexCoord2f(10, 0); glVertex3fv(pP1);
	glTexCoord2f(0, 0); glVertex3fv(pP2);
	glTexCoord2f(0, 9); glVertex3fv(pP3);
	glTexCoord2f(10, 9); glVertex3fv(pP4);
	glEnd();
	glPopMatrix();
	glEndList();
	//خزن المطبخ
	glNewList(10, GL_COMPILE);
	glPushMatrix();
	heet[2] = LoadTexture("Data/ff.jpg");
	glBindTexture(GL_TEXTURE_2D, heet[2]);
	glBegin(GL_QUADS);
	//glColor4f(200, 0, 0, 1);
	float qP1[] = { 1, 1, -1 };
	float qP2[] = { -1, 1, -1 };
	float qP3[] = { -1, -1, -1 };
	float qP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(qP1);
	glTexCoord2f(0, 0); glVertex3fv(qP2);
	glTexCoord2f(-1+0.035, 1); glVertex3fv(qP3);
	glTexCoord2f(0 + 0.035, 1); glVertex3fv(qP4);
	glEnd();
	glPopMatrix();
	glEndList();
	//خزن المطبخ2
	glNewList(11, GL_COMPILE);
	glPushMatrix();
	heet[3] = LoadTexture("Data/images (1).jfif");
	glBindTexture(GL_TEXTURE_2D, heet[3]);
	glBegin(GL_QUADS);
	//glColor4f(200, 0, 0, 1);
	float rP1[] = { 1, 1, -1 };
	float rP2[] = { -1, 1, -1 };
	float rP3[] = { -1, -1, -1 };
	float rP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(rP1);
	glTexCoord2f(0, 0); glVertex3fv(rP2);
	glTexCoord2f(-0.5, 1); glVertex3fv(rP3);
	glTexCoord2f(0.5, 1); glVertex3fv(rP4);
	glEnd();
	glPopMatrix();
	glEndList();
	//خزن نوم ص
	glNewList(12, GL_COMPILE);
	glPushMatrix();
	heet[4] = LoadTexture("Data/images (2).jfif");
	glBindTexture(GL_TEXTURE_2D, heet[4]);
	glBegin(GL_QUADS);
	//glColor4f(200, 0, 0, 1);
	float aP1[] = { 1, 1, -1 };
	float aP2[] = { -1, 1, -1 };
	float aP3[] = { -1, -1, -1 };
	float aP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(aP1);
	glTexCoord2f(0, 0); glVertex3fv(aP2);
	glTexCoord2f(-1 - 0.03, 1); glVertex3fv(aP3);
	glTexCoord2f(0 - 0.03, 1); glVertex3fv(aP4);
	glEnd();
	glPopMatrix();
	glEndList();
	// غسالة
	glNewList(13, GL_COMPILE);
	glPushMatrix();
	heet[5] = LoadTexture("Data/gas.png");
	glBindTexture(GL_TEXTURE_2D, heet[5]);
	glBegin(GL_QUADS);
	//glColor4f(200, 0, 0, 1);
	float wP1[] = { 1, 1, -1 };
	float wP2[] = { -1, 1, -1 };
	float wP3[] = { -1, -1, -1 };
	float wP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(wP1);
	glTexCoord2f(0, 0); glVertex3fv(wP2);
	glTexCoord2f(-1 + 0.085, 1); glVertex3fv(wP3);
	glTexCoord2f(0 + 0.085, 1); glVertex3fv(wP4);
	glEnd();
	glPopMatrix();
	glEndList();
	// خزانة كبيرة
	glNewList(14, GL_COMPILE);
	glPushMatrix();
	heet[6] = LoadTexture("Data/hhahs.jfif");
	glBindTexture(GL_TEXTURE_2D, heet[6]);
	glBegin(GL_QUADS);
	//glColor4f(200, 0, 0, 1);
	float yP1[] = { 1, 1, -1 };
	float yP2[] = { -1, 1, -1 };
	float yP3[] = { -1, -1, -1 };
	float yP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(yP1);
	glTexCoord2f(0, 0); glVertex3fv(yP2);
	glTexCoord2f(-0.37, 1); glVertex3fv(yP3);
	glTexCoord2f(0.63, 1); glVertex3fv(yP4);
	glEnd();
	glPopMatrix();
	glEndList();
	// غاز
	glNewList(15, GL_COMPILE);
	glPushMatrix();
	heet[7] = LoadTexture("Data/erttte.png");
	glBindTexture(GL_TEXTURE_2D, heet[7]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float oP1[] = { 1, 1, -1 };
	float oP2[] = { -1, 1, -1 };
	float oP3[] = { -1, -1, -1 };
	float oP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(oP1);
	glTexCoord2f(0, 0); glVertex3fv(oP2);
	glTexCoord2f(0, 1); glVertex3fv(oP3);
	glTexCoord2f(1, 1); glVertex3fv(oP4);
	glEnd();
	glPopMatrix();
	glEndList();
	// مجلى
	glNewList(16, GL_COMPILE);
	glPushMatrix();
	heet[8] = LoadTexture("Data/rerrrt.jpg");
	glBindTexture(GL_TEXTURE_2D, heet[8]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float zP1[] = { 1, 1, -1 };
	float zP2[] = { -1, 1, -1 };
	float zP3[] = { -1, -1, -1 };
	float zP4[] = { 1, -1, -1 };
	glTexCoord2f(0.5, 0); glVertex3fv(zP1);
	glTexCoord2f(-0.5, 0); glVertex3fv(zP2);
	glTexCoord2f(-0.66, 1); glVertex3fv(zP3);
	glTexCoord2f(0.34, 1); glVertex3fv(zP4);
	glEnd();
	glPopMatrix();
	glEndList();
	// باب
	glNewList(17, GL_COMPILE);
	glPushMatrix();
	heet[9] = LoadTexture("Data/Door.jpg");
	glBindTexture(GL_TEXTURE_2D, heet[9]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float xP1[] = { 1, 1, -1 };
	float xP2[] = { -1, 1, -1 };
	float xP3[] = { -1, -1, -1 };
	float xP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(xP1);
	glTexCoord2f(0, 0); glVertex3fv(xP2);
	glTexCoord2f(0, 1); glVertex3fv(xP3);
	glTexCoord2f(1, 1); glVertex3fv(xP4);
	glEnd();
	glPopMatrix();
	glEndList();
	// براد
	glNewList(18, GL_COMPILE);
	glPushMatrix();
	heet[10] = LoadTexture("Data/barad.png");
	glBindTexture(GL_TEXTURE_2D, heet[10]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float cP1[] = { 1, 1, -1 };
	float cP2[] = { -1, 1, -1 };
	float cP3[] = { -1, -1, -1 };
	float cP4[] = { 1, -1, -1 };
	glTexCoord2f(2, 0); glVertex3fv(cP1);
	glTexCoord2f(1, 0); glVertex3fv(cP2);
	glTexCoord2f(-0.28, 1); glVertex3fv(cP3);
	glTexCoord2f(0.72, 1); glVertex3fv(cP4);
	glEnd();
	glPopMatrix();
	glEndList();
	// تلفاز
	glNewList(19, GL_COMPILE);
	glPushMatrix();
	heet[11] = LoadTexture("Data/images.jfif");
	glBindTexture(GL_TEXTURE_2D, heet[11]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float ccP1[] = { 1, 1, -1 };
	float ccP2[] = { -1, 1, -1 };
	float ccP3[] = { -1, -1, -1 };
	float ccP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(ccP1);
	glTexCoord2f(0, 0); glVertex3fv(ccP2);
	glTexCoord2f(0, 1); glVertex3fv(ccP3);
	glTexCoord2f(1, 1); glVertex3fv(ccP4);
	glEnd();
	glPopMatrix();
	glEndList();
	//جدار
	glNewList(20, GL_COMPILE);
	glPushMatrix();
	heet[12] = LoadTexture("Data/123.jpg");
	glBindTexture(GL_TEXTURE_2D, heet[12]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float wcP1[] = { 1, 1, -1 };
	float wcP2[] = { -1, 1, -1 };
	float wcP3[] = { -1, -1, -1 };
	float wcP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(wcP1);
	glTexCoord2f(0, 0); glVertex3fv(wcP2);
	glTexCoord2f(0, 1); glVertex3fv(wcP3);
	glTexCoord2f(1, 1); glVertex3fv(wcP4);
	glEnd();
	glPopMatrix();
	glEndList();
	//خزانة
	glNewList(21, GL_COMPILE);
	glPushMatrix();
	heet[13] = LoadTexture("Data/Butterfly2.jpg");
	glBindTexture(GL_TEXTURE_2D, heet[13]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float bcP1[] = { 1, 1, -1 };
	float bcP2[] = { -1, 1, -1 };
	float bcP3[] = { -1, -1, -1 };
	float bcP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(bcP1);
	glTexCoord2f(0, 0); glVertex3fv(bcP2);
	glTexCoord2f(-0.455, 1); glVertex3fv(bcP3);
	glTexCoord2f(0.545, 1); glVertex3fv(bcP4);
	glEnd();
	glPopMatrix();
	glEndList();
	//طاولة الطعام
	glNewList(22, GL_COMPILE);
	glPushMatrix();
	heet[14] = LoadTexture("Data/tawla.png");
	glBindTexture(GL_TEXTURE_2D, heet[14]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float scP1[] = { 1, 1, -1 };
	float scP2[] = { -1, 1, -1 };
	float scP3[] = { -1, -1, -1 };
	float scP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(scP1);
	glTexCoord2f(0, 0); glVertex3fv(scP2);
	glTexCoord2f(0, 1); glVertex3fv(scP3);
	glTexCoord2f(1, 1); glVertex3fv(scP4);
	glEnd();
	glPopMatrix();
	glEndList();
	//سجادة 
	glNewList(23, GL_COMPILE);
	glPushMatrix();
	heet[15] = LoadTexture("Data/sss.jpg");
	glBindTexture(GL_TEXTURE_2D, heet[15]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float mcP1[] = { 1, 1, -1 };
	float mcP2[] = { -1, 1, -1 };
	float mcP3[] = { -1, -1, -1 };
	float mcP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(mcP1);
	glTexCoord2f(0, 0); glVertex3fv(mcP2);
	glTexCoord2f(0, 1); glVertex3fv(mcP3);
	glTexCoord2f(1, 1); glVertex3fv(mcP4);
	glEnd();
	glPopMatrix();
	glEndList();

	//للكنب1 
	glNewList(24, GL_COMPILE);
	glPushMatrix();
	heet[16] = LoadTexture("Data/Image2.bmp");
	glBindTexture(GL_TEXTURE_2D, heet[16]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float ucP1[] = { 1, 1, -1 };
	float ucP2[] = { -1, 1, -1 };
	float ucP3[] = { -1, -1, -1 };
	float ucP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(ucP1);
	glTexCoord2f(0, 0); glVertex3fv(ucP2);
	glTexCoord2f(0, 1); glVertex3fv(ucP3);
	glTexCoord2f(1, 1); glVertex3fv(ucP4);
	glEnd();
	glPopMatrix();
	glEndList();

	//2للكنب 
	glNewList(25, GL_COMPILE);
	glPushMatrix();
	heet[17] = LoadTexture("Data/Mask1.bmp");
	glBindTexture(GL_TEXTURE_2D, heet[17]);
	glBegin(GL_QUADS);
	glColor4f(200, 0, 0, 1);
	float zcP1[] = { 1, 1, -1 };
	float zcP2[] = { -1, 1, -1 };
	float zcP3[] = { -1, -1, -1 };
	float zcP4[] = { 1, -1, -1 };
	glTexCoord2f(1, 0); glVertex3fv(zcP1);
	glTexCoord2f(0, 0); glVertex3fv(zcP2);
	glTexCoord2f(0, 1); glVertex3fv(zcP3);
	glTexCoord2f(1, 1); glVertex3fv(zcP4);
	glEnd();
	glPopMatrix();
	glEndList();
}

void ReSizeGLScene(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 500.0f);
	//gluOrtho2D(0, 100, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void DrawGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	glRotatef(tet * 180 / 3.14, 0, 1, 0);
	SkyBoxFunc();
	glPopMatrix();


	gluLookAt(ex, ey, ez, ex + cos(tet), ey, ez + sin(tet), 0, 1, 0);



	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);




	//setting the color components for the light sourece
	//ambient is the scattered light component
	float am[] = { 0.2, 0.2, 0.2 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, am);

	//diffuse is the direct light color
	float di[] = { 0.2, 0.2, 0.2 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, di);

	//specular is the shininess color
	float sp[] = { 0, 0, 0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, sp);

	//enabling color material restores sets the color in glColor3f to the ambient & diffuse material components for the objects
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	//setting the specular color componenets for the materials and the shininess which contorls the size of the of highlight spot
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sp);

	float position[] = { 200, 200, -100, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);




	glBindTexture(GL_TEXTURE_2D, 0);
	glPushMatrix();
	////////////////////////->
	//الارض
	glTranslated(0, -2, 0);
	glScalef(400, 0, 400);
	glColor3ub(37, 33, 29);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//الرصيف الامامي
	glTranslatef(-100, 0, 9);
	for (int i = 0; i < 50; i++)
	{
		glTranslated(4, 0, 0);
		glCallList(3);
	}
	glPopMatrix();
	glPushMatrix();
	//الرصيف الخلفي
	glRotatef(180, 0, 1, 0);
	glTranslatef(-100 - 4, 0, 9);
	for (int i = 0; i < 50; i++)
	{
		glTranslated(4, 0, 0);
		glCallList(3);
	}
	glPopMatrix();
	glPushMatrix();
	//المنصف
	glTranslated(2, -1.999, 0);
	glScalef(200, 0, 0.2);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//الحيط الامامي يمين
	glTranslatef(-100, 0, 10);
	for (int i = 0; i < 24; i++)
	{
		glTranslated(4, 0, 0);
		glCallList(2);
	}
	glPopMatrix();
	glPushMatrix();
	//الحيط الامامي اليسار
	glRotatef(180, 0, 1, 0);
	glTranslatef(-100 - 4, 0, -10);
	for (int i = 0; i < 25; i++)
	{
		glTranslated(4, 0, 0);
		glCallList(2);
	}
	glPopMatrix();
	glPushMatrix();
	//الحيط يمين
	glRotatef(90, 0, 1, 0);
	glTranslatef(-100 + 8, 0, -50);
	for (int i = 0; i < 20; i++)
	{
		glTranslated(4, 0, 0);
		glCallList(2);
		glTranslated(0, 0, 4);
		glCallList(1);
		glTranslated(0, 0, -4);
	}
	glPopMatrix();
	glPushMatrix();
	//الحيط يسار
	glRotatef(90, 0, 1, 0);
	glTranslatef(-100 + 8, 0, 50);
	for (int i = 0; i < 20; i++)
	{
		glTranslated(4, 0, 0);
		glCallList(2);

		glTranslated(0, 0, -4);
		glCallList(1);
		glTranslated(0, 0, 4);
	}
	glPopMatrix();
	glPushMatrix();
	//الحيط الخلفي
	glTranslatef(-52, 0, 90);
	for (int i = 0; i < 25; i++)
	{
		glTranslated(4, 0, 0);
		glCallList(2);
		glTranslated(0, 0, -4);
		glCallList(1);
		glTranslated(0, 0, 4);
	}
	glPopMatrix();
	glPushMatrix();
	//الغشب
	glTranslated(0, -2 + 0.125, 50);
	glScalef(100, 0.25, 80);
	glColor3ub(37, 100, 29);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//الممر
	glTranslated(0, -2 + 0.13, 20);
	glScalef(4, 0.25, 20);
	glColor3ub(107, 103, 99);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//بعد الممر+ارضية ط 0
	glTranslatef(8, -2 + 0.13, 35);
	glScalef(45.2, 0.25, 10);
	glColor3ub(107, 103, 99);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//حيط بيت الخلفي
	glTranslatef(8, 4, 80);
	glScalef(45, 12, 0.25);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//حيط بيت يمين 
	glTranslatef(-14.5, 4, 60);
	glScalef(0.25, 12, 40);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//حيط بيت يسارسفلي
	glTranslatef(30.5, 1, 60);
	glScalef(0.25, 6, 40);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//حيط بيت يسار علوي
	glTranslatef(30.5, 7, 60);
	glScalef(0.25, 6, 40);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//البرندا
	glTranslatef(25, 4, 38);
	glScalef(11, 0.25, 4);
	glColor3ub(150, 150, 150);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(25 - 5.5, 5, 38);
	glScalef(0.4, 2, 4);
	glColor3ub(170, 170, 170);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(25 + 5.5, 5, 38);
	glScalef(0.4, 2, 4);
	glColor3ub(170, 170, 170);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(25, 5, 38 - 2);
	glScalef(11, 2, 0.4);
	glColor3ub(170, 170, 170);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//حيط فوف الباب
	glTranslatef(8 - 0.3, 3.75, 40);
	glScalef(45.2 - 0.6, 1, 0.25);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//ارضية الطابق اول
	glDisable(GL_LIGHT0);
	glTranslated(8, -2 + 0.13, 60);
	glColor3ub(150, 150, 150);
	glScalef(45, 0.25, 40);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//ارضية الطابق تاني
	glTranslated(8, -2 + 0.13 + 6, 60);
	glColor3ub(150, 150, 150);
	glScalef(45, 0.25, 40);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//سقف ط2
	glEnable(GL_LIGHT0);
	glTranslated(8, -2 + 0.13 + 12, 60);
	glColor3ub(150, 150, 150);
	glScalef(45, 0.25, 40);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//حيط اليمين
	glTranslatef(-9.737, 0.75, 40);
	glScalef(9.75, 5, 0.25);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//حيط الوسط
	glTranslatef(12.56, 0.75, 40);
	glScalef(15.25, 5, 0.25);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//حيط اليسار
	glTranslatef(30.3, 0.75 + 3.358, 40);
	glScalef(0.6, 12.2, 0.25);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//2حيط فوف الباب
	glTranslatef(8 - 0.3, 3.75 + 6, 40);
	glScalef(45.2 - 0.6, 1, 0.25);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	// فوق حيط الوسط
	glTranslatef(2.73, 0.75 + 6, 40);
	glScalef(34.7, 5, 0.25);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//الحيط يمين للمطبخ
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glTranslatef(-5.5, 4, 46);
	glScalef(0.25, 12, 12);
	glColor3ub(200, 200, 200);

	glutSolidCube(1);
	glTranslatef(0, -0.3, 0.5);
	glScalef(0.5, 0.4, 0.4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.5, 1, 56.4);
	glScalef(0.25, 6, 4);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.5, 3.4, 53.2);
	glScalef(0.25, 1.2, 2.4);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();

	//مطبخ حيط خلفي
	glColor3ub(200, 200, 200);
	glTranslatef(-10, 1, 58.5);
	glScalef(9, 6, 0.25);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();

	//الحيط يمين النوم
	glTranslatef(10, 4, 46);
	glScalef(0.25, 12, 12);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glTranslatef(0, -0.3, 0.5);
	glScalef(0.5, 0.4, 0.4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10, 1, 56.4);
	glScalef(0.25, 6, 4);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10, 3.4, 53.2);
	glScalef(0.25, 1.2, 2.4);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//حيط نوم خلفي
	glTranslatef(20.225, 1, 58.5);
	glScalef(20.5, 6, 0.25);
	glColor3ub(200, 200, 200);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//تخت
	glTranslatef(26, 0.4 - 2, 50);
	glScalef(9, 0.8, 7);
	glColor4f(0.317, 0.225, 0.146, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(30.3, 0.625 + 0.8 - 2, 50);
	glScalef(0.3, 1.25, 7);
	glColor4f(0.317, 0.215, 0.136, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//مخدات
	glColor4f(0.9, 0.9, 0.9, 1);
	glTranslatef(29, 0.2 - 2 + 0.7, 52);
	glScalef(1, 0.2, 2);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glColor4f(0.9, 0.9, 0.9, 1);
	glTranslatef(29, 0.2 - 2 + 0.7, 48);
	glScalef(1, 0.2, 2);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//.غرفة الجلوس
	//كنب

	glRotatef(90, 0, 1, 0);
	glTranslatef(-64.3, 0.75, 28.9);
	glScalef(1.5, 1.5, 1.5);
	glCallList(5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-69.3, 0.75, 28.9);
	glScalef(1.5, 1.5, 1.5);
	glCallList(5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-74.3, 0.75, 28.9);
	glScalef(1.5, 1.5, 1.5);
	glCallList(5);
	glPopMatrix();
	glPushMatrix();

	glRotatef(180, 0, 1, 0);
	glTranslatef(-26.3, 0.75, -59.9);
	glScalef(1.5, 1.5, 1.5);
	glCallList(5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-21.3, 0.75, -59.9);
	glScalef(1.5, 1.5, 1.5);
	glCallList(5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-16.3, 0.75, -59.9);
	glScalef(1.5, 1.5, 1.5);
	glCallList(5);
	glPopMatrix();
	glPushMatrix();
	//المسبح
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColor3ub(0, 0, 200);
	glTranslatef(-30.5, -1.7, 47);
	glScalef(24, 0.1, 34);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-30.5, 30, 1.7);
	glutSolidCone(6, 0.1, 50, 50);
	glPopMatrix();
	glPushMatrix();

	//طاولة الطعام
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glColor4f(0.357, 0.255, 0.176, 1);
	glTranslatef(-5, -0.55, 75);
	glScalef(8, 0.15, 4);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5 - 4 + 0.1, -1.35, 75 - 2 + 0.1);
	glScalef(0.2, 1.5, 0.2);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5 + 4 - 0.1, -1.35, 75 - 2 + 0.1);
	glScalef(0.2, 1.5, 0.2);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5 + 4 - 0.1, -1.35, 75 + 2 - 0.1);
	glScalef(0.2, 1.5, 0.2);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5 - 4 + 0.1, -1.35, 75 + 2 - 0.1);
	glScalef(0.2, 1.5, 0.2);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();

	//كراسي
	glTranslatef(-5.5, 0.9, 77);
	glScalef(1.7, 1.3, 1.7);
	glCallList(6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.5 + 2.5, 0.9, 77);
	glScalef(1.7, 1.3, 1.7);
	glCallList(6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5.5 - 2.5, 0.9, 77);
	glScalef(1.7, 1.3, 1.7);
	glCallList(6);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0),
		glTranslatef(5 + 2.5, 0.9, -77 + 4);
	glScalef(1.7, 1.3, 1.7);
	glCallList(6);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0),
		glTranslatef(5 - 2.5, 0.9, -77 + 4);
	glScalef(1.7, 1.3, 1.7);
	glCallList(6);
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0),
		glTranslatef(5, 0.9, -77 + 4);
	glScalef(1.7, 1.3, 1.7);
	glCallList(6);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0),
		glTranslatef(-77 + 1.5, 0.9, -2 + 0.75);
	glScalef(1.7, 1.3, 1.7);
	glCallList(6);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0),
		glTranslatef(77 - 2.25, 0.9, 8 + 0.75);
	glScalef(1.7, 1.3, 1.7);
	glCallList(6);
	glPopMatrix();
	glPushMatrix();
	//مروحة
	glTranslatef(21.3, 2 + 1 - 0.25, 70);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(x += 2.25, 0, 0, 1);
	for (float i = 0; i < 360; i += 72)
	{
		glPushMatrix();
		glRotatef(i, 0, 0, 1);
		glCallList(9);
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.5, 0.5, 32, 16);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotated(-90, 1, 0, 0);
	gluCylinder(a, 0.05, 0.05, 1.5, 30, 30);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	//طتولة نوم جسم
	glColor4f(0.4, 0.4, 0.4, 1);
	glTranslatef(11, 0.5 - 0.25, 43.5);
	glScalef(1.5, 4.5, 6);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(29.5, -1.2, 54.5);
	glScalef(1.5, 1.4, 1.2);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(29.5, -1.2, 45.5);
	glScalef(1.5, 1.4, 1.2);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//جدار خلفي
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 - 3, 1, 82.873);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 3, 1, 82.873);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 9, 1, 82.873);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 15, 1, 82.873);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 21, 1, 82.873);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 27, 1, 82.873);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 27 + 6, 1, 82.873);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 27 + 9, 1, 82.873);
	glScalef(3, 3, 3);
	glCallList(20);

	//جدار وسط
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 - 3, 1, 61.64);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5, 1, 61.64);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 21.5, 1, 61.63);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 27, 1, 61.63);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 27 + 6, 1, 61.63);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8.5 + 27 + 9, 1, 61.63);
	glScalef(3, 3, 3);
	glCallList(20);
	//جدار يمين
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-61.5, 1, -10);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-61.5 - 6, 1, -10);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-61.5 - 12, 1, -10);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-61.5 - 15.5, 1, -10.02);
	glScalef(3, 3, 3);
	glCallList(20);

	//جدار يسار
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-61.5, 1, 33);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-61.5 - 6, 1, 33);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-61.5 - 12, 1, 33);
	glScalef(3, 3, 3);
	glCallList(20);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-61.5 - 15.5, 1, 33 - 0.02);
	glScalef(3, 3, 3);
	glCallList(20);


	glPopMatrix();
	glPushMatrix();

	//خزانة

	glRotatef(-90, 0, 1, 0);
	glTranslatef(43.5, 0.3, -10.352);
	glScalef(2.8, 2, 1.4);
	glCallList(21);
	glPopMatrix();
	glPushMatrix();
	//طاولات النوم
	glRotatef(-90, 0, 1, 0);
	glTranslatef(54.5, -1.1, -28.14);
	glScalef(0.6, 0.6, 0.6);
	glCallList(12);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 12, 0);
	glTranslatef(45.5, -1.1, -28.14);
	glScalef(0.6, 0.6, 0.6);
	glCallList(12);
	glPopMatrix();
	glPushMatrix();
	//الحيط للمطبخ
	glRotatef(-90, 0, 1, 0);
	glTranslatef(43, 1, 6.66);
	glScalef(3, 3, 1);
	glCallList(7);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(49, 1, 6.66);
	glScalef(3, 3, 1);
	glCallList(7);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(43, 1, 15.3);
	glScalef(3, 3, 1);
	glCallList(7);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(49, 1, 15.3);
	glScalef(3, 3, 1);
	glCallList(7);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(55, 1, 15.3);
	glScalef(3, 3, 1);
	glCallList(7);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10, 1, 58);
	glScalef(4.4, 3, 1);
	glCallList(7);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10, 1, 42);
	glScalef(4.4, 3, 1);
	glCallList(7);
	//خزن المطبخ

	glPopMatrix();
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.5);
	glTranslatef(-13.76, -0.75, 49);
	glScalef(1.49, 2, 18);
	glutSolidCube(1);
	//فوق
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42, 3, 14);
	glCallList(10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 2, 3, 14);
	glCallList(10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 4, 3, 14);
	glCallList(10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 6, 3, 14);
	glCallList(10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 8, 3, 14);
	glCallList(10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 10, 3, 14);
	glCallList(10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 12, 3, 14);
	glCallList(10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 14, 3, 14);
	glCallList(10);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(-13.76, 3, 49.5);
	glScalef(1.49, 2, 18);
	glutSolidCube(1);
	//تحت
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42, -0.75, 14);
	glCallList(11);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 2, -0.75, 14);
	glCallList(11);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 4, -0.75, 14);
	glCallList(11);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 6, -0.75, 14);
	glCallList(11);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 8, -0.75, 14);
	glCallList(11);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 10, -0.75, 14);
	glCallList(11);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 12, -0.75, 14);
	glCallList(11);
	//غسالة
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(42 + 14, -0.75, 14);
	glCallList(13);
	glPopMatrix();
	glPushMatrix();
	//براد
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(-7, 0, 42);
	glScalef(2, 4, 2);
	glutSolidCube(1);
	//ارضية النوم
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(2 + 18.1, 49.1, 2.7);
	glScalef(10.2, 9, 1);
	glCallList(8);

	//باب مطبخ
	glPopMatrix();
	glPushMatrix();
	if (door5){
		glRotatef(90, 0, 1, 0);
		glTranslatef(-53.24, 0.515, -4.39);
		glScalef(1.23, 2.35, 1);
		glCallList(17);
	}

	else{
		glTranslatef(-4.4 - 2.46, 0.515, 53);
		glScalef(1.23, 2.35, 1);
		glCallList(17);
	}
	//باب نوم
	glPopMatrix();
	glPushMatrix();
	if (door4){
		glRotatef(90, 0, 1, 0);
		glTranslatef(-53.24, 0.515, 10.89);
		glScalef(1.23, 2.35, 1);
		glCallList(17);
	}
	else{
		glRotatef(180, 0, 1, 0);
		glTranslatef(-11.2, 0.515, -53.24 + 2.21);
		glScalef(1.23, 2.35, 1);
		glCallList(17);
	}

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-7, 0, 42+2.01);
	glScalef(1, 2, 1);
	glCallList(18);


	glPopMatrix();
	glPushMatrix();
	//الباب الرئيسي
	glTranslatef(-0.02, 0.1, 0);
	glScalef(1, 1.02, 1);
	glCallList(4);
	if (door2) {
		glTranslatef(2.5, 0.625, 40);
		glScalef(4.8, 4.75, 0.05);
		glColor4f(0.2, 0.2, 0.65, 0.25);
		glutSolidCube(1);
	}

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.02, 0.1, 0);
	glScalef(1, 1.02, 1);
	//الباب اليسار
	glTranslatef(25, 0, 0);
	glCallList(4);
	if (door1) {
		glTranslatef(2.5, 0.625, 40);
		glScalef(4.8, 4.75, 0.05);
		glColor4f(0.2, 0.2, 0.65, 0.25);
		glutSolidCube(1);
	}

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.02, -0.25, 0);
	glScalef(1, 1.02, 1);
	//الباب اليسار فوق
	glTranslatef(-0.02, 0.1, 0);
	glScalef(1, 1.02, 1);
	glTranslatef(25, 6, 0);
	glCallList(4);
	if (door3) {
		glTranslatef(2.5, 0.625, 40);
		glScalef(4.8, 4.75, 0.05);
		glColor4f(0.2, 0.2, 0.65, 0.25);
		glutSolidCube(1);
	}

	glPopMatrix();
	glPushMatrix();
	//فرن
	glRotatef(-90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(44, 12+1.62, 0.745);// z,x,y
	glScalef(1, 0.6, 1);
	glCallList(15);
	//مجلى
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(44+5, 12 + 1.62, 0.745);// z,x,y
	glScalef(2, 0.6, 1);
	glCallList(16);
	
	//تلفاز
	glPopMatrix();
	glPushMatrix();
	glTranslatef(21.3, 0.2, 79 + 0.48);
	glScalef(2, 2, 1);
	glCallList(19);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(21.3, 0.2, 79);
	glScalef(4, 4, 1);
	glutSolidCube(1);

	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-75, 5, 0.535);//z=-75 x>5 y
	glScalef(2, 4, 1);
	glCallList(22);
	//سجادة
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(21.3, 69.2, 2.7);
	glScalef(4.3, 7.3, 1);
	glCallList(23);


	/*
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.75, 1.448);
	glScalef(0.4, 0.4, 1);
	glCallList(24);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, 2.198);
	glScalef(0.6, 0.5, 1);
	glCallList(25);
	*/



	////////////////////////<-
	glPopMatrix();

	glFlush(); 
}
void animation(int) {
	glutTimerFunc(16, animation, 0);
	glutPostRedisplay();
}
void spesial(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		ex = ex + cos(tet);
		ez = ez + sin(tet);
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		ex = ex - cos(tet);
		ez = ez - sin(tet);
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		tet += 0.1;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		tet -= 0.1;
		glutPostRedisplay();
		break;

	case GLUT_KEY_HOME:
		ey += 0.25;
		glutPostRedisplay();
		break;

	case GLUT_KEY_END:
		ey -= 0.25;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE); // Use single display buffer.
	glutInitWindowSize(1280, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("EMPTY WINDOW");
	InitGL();
	glutReshapeFunc(ReSizeGLScene);
	glutDisplayFunc(DrawGLScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(spesial);
	animation(0);
	glutMainLoop();
	return 0;
}