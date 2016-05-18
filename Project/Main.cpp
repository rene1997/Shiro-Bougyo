#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <ApplicationServices/ApplicationServices.h>
#include <cstdlib>

#else
#include <windows.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include "GL\freeglut.h"
#endif

#include "GameStateManager.h"

GameStateManager gameManager;
int width, height;
bool keys[255];
struct Camera
{
	float posX = 0;
	float posY = -4;
	float rotX = 0;
	float rotY = 0;
} camera;

void onDisplay() {
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width / height, 0.1, 30);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, 0, camera.posY);


	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-15, -1, -15);
	glVertex3f(15, -1, -15);
	glVertex3f(15, -1, 15);
	glVertex3f(-15, -1, 15);
	glEnd();
	glPopMatrix();
	
	glColor3f(1.0f, 1.0f, 1.0f);
	gameManager.Draw();


	glFlush();
	glutSwapBuffers();

}

void onIdle() {
	//do nothing
}

void onTimer(int id){
	gameManager.Update();
	glutPostRedisplay();
	glutTimerFunc(1000/60,onTimer, 1);
}

void onKeyboard(unsigned char key, int, int) {
	switch (key)
	{
		case 27:             // ESCAPE key
			exit (0);
		case '[':
			gameManager.previousState();
			break;
		case ']':
			gameManager.nextState();
			break;
		default:
			//just to please CLion.
			break;
	}
	keys[key] = true;
}

void onKeyboardUp(unsigned char key, int, int) {
	keys[key] = false;
}

void mousePassiveMotion(int x, int y) {


	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		glutWarpPointer(width / 2, height / 2);
	}
}

int main(int argc, char* argv[]) {
	
	gameManager.Init();

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(1920,1080);
	glutCreateWindow("Shiro Bougyo");

	glEnable(GL_DEPTH_TEST);
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
#if __APPLE__
    CGSetLocalEventsSuppressionInterval(0.0);
#endif
	glutIdleFunc(onIdle);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(onKeyboard);
	glutTimerFunc(1000/60,onTimer, 1);
	glutKeyboardUpFunc(onKeyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(width / 2, height / 2);

	memset(keys, 0, sizeof(keys));

	glutMainLoop();
}
