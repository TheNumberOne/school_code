
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 2);
	glVertex3f(0, 30.f, 2);
	glVertex3f(-30.f, 30.f, 2);
	glVertex3f(-30.f, 0, 2);
	glEnd();


	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
    glVertex3d(0, -20, 0);
    glVertex3d(20, -20, 0);
    glVertex3d(20, 0, 0);
    glEnd();
    glDisable(GL_DEPTH_TEST);

	glFlush();
}

// Initialization routine.
void setup()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	std::cout << w << " " << h << std::endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-30.*w/h, 30.*w/h, -30, 30, 5, 20);
	glTranslatef(0, 0, 1);
	glRotatef(-5, 1, 1, 0);
	glTranslatef(0, 0, -10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
	default:
		break;
	}
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	
	glutInitWindowSize(850, 600);
	glutInitWindowPosition(0, 0);
	
	glutCreateWindow("square.cpp");
	
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}