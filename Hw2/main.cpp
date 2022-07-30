#include <stdlib.h>
#include <math.h>
#include "../GL/glut.h"


void init(void);//no need to modify this function
void display(void);
void reshape(int width, int height);//no need to modify this function
void keyboard(unsigned char key, int x, int y);//you can modify anything if you need
void idle(void);//no need to modify this function

void draw_PPAP(bool in_mirror);//in_mirror is TRUE if you draw mirror scene
//void drawpen(float l, float r);//no need to modify this function
void drawapple(float sz);//no need to modify this function
void drawbox(float xrot, float yrot, bool in_mirror);//no need to modify this function
//void draw_mirror_only();//you can modify anything if you need

float delta = 0.0;
float alpha = 2.0;
float box_xrot = 0.0f;
float box_yrot = 0.0f;
bool PPAP = false;
float camera_x = 0.0f;
float camera_z = 8.0f;
float camera_rot = 0.0f;
double mirror_pos[6][3] = {
	{ 0.0,3.0,0.0 },//up
	{ 0.0,-3.0,0.0 },//bottom
	{ 3.0,0.0,0.0 },//right
	{ 1.5,0.0,-3.5 },//right-front
	{ -1.5,0.0,-3.5 },//left-front
	{ -3.0,0.0,0.0 },//left
					 //{ 0.0,0.0,5.0 },//back
};
double mirror_rotate_axis[6][3] = {
	{ 1.0,0.0,0.0 },//up
	{ 1.0,0.0,0.0 },//bottom
	{ 0.0,1.0,0.0 },//right
	{ 0.0,1.0,0.0 },//right-front
	{ 0.0,1.0,0.0 },//left-front
	{ 0.0,1.0,0.0 },//left
					//{ 0.0,1.0,0.0 },//back
};
float mirror_color[6][4] = {
	{ 1.0,0.0,0.0,0.4 },//up
	{ 0.0,1.0,0.0,0.4 },//bottom
	{ 0.0,0.0,1.0,0.4 },//right
	{ 1.0,1.0,0.0,0.4 },//right-front
	{ 1.0,0.0,1.0,0.4 },//left-front
	{ 0.0,1.0,1.0,0.4 },//left
};

//-----------------------------------------------------------------------------

//PPAP_POS SCALE ANGLE 用來設定鏡子裡的PPAP的影像
double ppap_pos[6][3] = {
	{ 0.0,6.0,0.0 },//up
	{ 0.0,-6.0,0.0 },//bottom
	{ 6.0,0.0,0.0 },//right
	{ -2.0,0.0,-2.0 },//right-front
	{ 2.0,0.0,-2.0 },//left-front
	{ -6.0,0.0,0.0 },//left
					 //{ 0.0,0.0,5.0 },//back
};

float ppap_scale[6][3] = {
	{ 1.0,-1.0,1.0 },//up
	{ 1.0,-1.0,1.0 },//bottom
	{ -1.0,1.0,1.0 },//right
	{ -1.0,1.0,1.0 },//right-front
	{ -1.0,1.0,1.0 },//left-front
	{ -1.0,1.0,1.0 },//left
					 //{ 0.0,0.0,5.0 },//back
};
double ppap_rotate_angle[6] = { 0,-0,0,90,-90,-0 };
//-----------------------------------------------------------------------------

double mirror_rotate_angle[6] = { 90.0,-90.0,90.0,45.0,-45.0,-90 };
double mirror_size_x[6] = { 5.0,5.0,5.0,2.121,2.121,5.0 };
double mirror_size_y[6] = { 5.0,5.0,5.0,3.0,3.0,5.0 };


float MatAmb[] = { 1.0f, 1.0f, 1.0f, 1.0f };			// Material - Ambient Values
float MatDif[] = { 1.0f, 1.0f, 1.0f, 1.0f };			// PPAP Material - Diffuse Values
float MatSpc[] = { 0.0f, 0.0f, 0.0f, 1.0f };			// Material - Specular Values
float MatShn[] = { 0.1f };								// Material - Shininess



													//you can modify anything if you need

void display(void)
{


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camera_x, 0.0, camera_z, /* Eye pos XYZ */
		camera_x + 1.0f*sin(camera_rot), 0.0, camera_z - 1.0f*cos(camera_rot), /* Target pos XYZ */
		0.0, 1.0, 0.0); /* Up vector */


	box_xrot += 0.5f;
	box_yrot += 0.5f;
	if (PPAP)
	{
		alpha = alpha > 0 ? alpha - 0.1 : 0;
		delta = 90.0;
	}
	else
	{
		alpha = 2.0;
		delta += 0.2;
	}



	//draw_mirror_only();

	draw_PPAP(false);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//you can modify anything if you need
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
	{
		camera_z -= 0.5*cos(camera_rot);
		camera_x += 0.5*sin(camera_rot);
		break;
	}
	case 's':
	{
		camera_z += 0.5*cos(camera_rot);
		camera_x -= 0.5*sin(camera_rot);
		break;
	}
	case 'a':
	{
		camera_z -= 0.5*sin(camera_rot);
		camera_x -= 0.5*cos(camera_rot);
		break;
	}
	case 'd':
	{
		camera_z += 0.5*sin(camera_rot);
		camera_x += 0.5*cos(camera_rot);
		break;
	}
	case 'q':
	{
		camera_rot -= 0.03f;
		break;
	}
	case 'e':
	{
		camera_rot += 0.03f;
		break;
	}
	case 13:
	{   //enter
		PPAP = !PPAP;
		break;
	}
	case 27:
	{   //ESC
		exit(0);
		break;
	}
	default:
	{
		break;
	}
	}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//no need to modify this function
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutCreateWindow("OpenGL Assignment 2-0556101"); //SUDO
	glutReshapeWindow(512, 512);

	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}

//no need to modify this function
void init(void) {

	GLfloat position[] = { 1.0, 1.0, 5.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmb);			// Set Material Ambience
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDif);			// Set Material Diffuse
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpc);		// Set Material Specular
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShn);		// Set Material Shininess
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Set The Blending Function For Translucency

}

//no need to modify this function
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	//glOrtho(-5.0,5.0,-5.0,5.0,0.0,200.0);
}

//no need to modify this function
void idle(void)
{
	glutPostRedisplay();
}

//in_mirror is TRUE if you draw mirror scene
void draw_PPAP(bool in_mirror)
{
	drawbox(box_xrot, box_yrot, in_mirror);
	glDisable(GL_BLEND);
	glPushMatrix();
	glTranslatef(-alpha, 0.0, 0.0);
	if (PPAP)
	{
		glRotatef(-90, 0.0, 0.0, 1.0);
	}
	else
	{
		glRotatef(delta, 0.0, 1.0, 0.0);
		glRotatef(10, 0.0, 0.0, 1.0);
	}
	//drawpen(2.0, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(alpha, 0.0, 0.0);
	glRotatef(delta, 0.0, 1.0, 0.0);
	drawapple(0.8);
	glPopMatrix();
	glEnable(GL_BLEND);
	
}

//no need to modify this function
void drawapple(float sz)
{
	glEnable(GL_ALPHA_TEST);
	glColor4f(1, 0, 0, 0);
	glEnable(GL_BLEND);
	//glStencilFunc(GL_NEVER, 1, 0);
	glPushMatrix();
	glutSolidSphere(sz, 32, 32);
	glTranslatef(0.0, sz, 0.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(sz * 0.15, sz * 0.6, 32, 32);
	glPopMatrix();

	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, 0.0, -sz * 0.4);
	//glutSolidCone(sz * 0.05, sz * 0.4, 32, 32);
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	}

//no need to modify this function
void drawbox(float xrot, float yrot, bool in_mirror)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//glDisable(GL_DEPTH_TEST);
	if (!in_mirror) glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);



	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	glColor3d(1, 0, 1);
	glutSolidCube(2.2);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_EQUAL, 1, 255);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	if (!in_mirror) glDisable(GL_BLEND);
}