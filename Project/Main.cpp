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
#include "SerialHandler.h"
#include "Camera.h"

#include "PlayingState.h"

#include "WiiHandler.h"

#define COMMPORT 5
#define DELTATIME_MODIFIER 10;

#include "sdl_audio.h"

GameStateManager gameManager;
SerialHandler serial = SerialHandler(COMMPORT, &gameManager);
bool keys[255];
void* wiiFunc(void * argument);
void* musicFunc(void * argument);
//Camera camera;

WiiHandler wiiHandler;
int buttonPressed = 0;
int WindowWidth = 1920;
int WindowHeight = 1080;

int oldTimeSinceStart = 0;

void onDisplay() {
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	gameManager.Draw();



    glFlush();
    glutSwapBuffers();
}

void initializeThreads(){
	std::thread wiiThread(&wiiFunc,nullptr); //WiiMote Thread
	wiiThread.detach();
	std::thread musicThread(&SDL_Audio::playTheme, SDL_Audio()); //Play theme sound
	musicThread.detach();
	std::thread serialThread(&SerialHandler::receiveThread, &serial); //Serialthread
	serialThread.detach();
}

void onIdle() {
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME); //This has to be the first line in this method.
	if (keys[27]) exit(0);
	if (keys['m']) { //Scale powerup.
		GameState* currentState = gameManager.getCurrentState();
		PlayingState *playState = dynamic_cast<PlayingState*>(currentState);
		if (playState)
			playState->ScalePowerUp();
	}
	if (keys['n']) { //
		GameState* currentState = gameManager.getCurrentState();
		PlayingState *playState = dynamic_cast<PlayingState*>(currentState);
		if (playState)
			playState->DestoryPowerUp();
	}

	//for testing remove keys for final release:
	float deltatime = (float)(timeSinceStart - oldTimeSinceStart) / DELTATIME_MODIFIER;
	//TODO: for testing remove keys for final release:
	gameManager.Update(deltatime, keys);
	oldTimeSinceStart = timeSinceStart;
	//gameManager.Update(deltatime);

	oldTimeSinceStart = timeSinceStart;
	glutPostRedisplay();
}

void onKeyboard(unsigned char key, int, int) {
	switch (key)
	{
	case 27:             // ESCAPE key
		exit(0);
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

void* wiiFunc(void * argument) {
	wiiHandler.wiiMoteLoop();
	return 0;
}

void onKeyboardUp(unsigned char key, int, int) {
	keys[key] = false;
}

void mousePassiveMotion(int x, int y) {
		int dx = x - WindowWidth / 2;
		int dy = y - WindowHeight / 2;
		if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
		{
			gameManager.GetPlayers().at(0)->getCamera()->rotX += dy / 10.0f;
			if (gameManager.GetPlayers().at(0)->getCamera()->rotX > 30) {
				gameManager.GetPlayers().at(0)->getCamera()->rotX = 30;
			}
			else if (gameManager.GetPlayers().at(0)->getCamera()->rotX < -30) {
				gameManager.GetPlayers().at(0)->getCamera()->rotX = -30;
			}
			gameManager.GetPlayers().at(0)->getCamera()->rotY += dx / 10.0f;
			glutWarpPointer(WindowWidth / 2, WindowHeight / 2);
		}
}

void windowReshape(int w, int h){
	WindowWidth = w;
	WindowHeight = h;
	gameManager.width = w;
	gameManager.height = h;
	for ( auto &player : gameManager.GetPlayers()) {
		player->getCamera()->width = w;
		player->getCamera()->height = h;
	}
}


int main(int argc, char* argv[]) {
	initializeThreads();
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(WindowWidth,	WindowHeight);
	glutCreateWindow("Shiro Bougyo");

	glEnable(GL_DEPTH_TEST);
	//Light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	GLfloat LightAmbient[] = {1.5f,1.5f,1.5f, 2.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	//Fog
	glEnable(GL_FOG);
	float FogCol[3] = { 0.8f,0.8f,0.8f };
	glFogfv(GL_FOG_COLOR, FogCol);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 1.f);
	glFogf(GL_FOG_END, 40.f);
	glFogf(GL_FOG_DENSITY, 2.f);
	glHint(GL_FOG_HINT, GL_NICEST);
	
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
#if __APPLE__
	CGSetLocalEventsSuppressionInterval(0.0);
#endif
    glutIdleFunc(onIdle);
    glutDisplayFunc(onDisplay);
	glutReshapeFunc(windowReshape);
    glutKeyboardFunc(onKeyboard);

    glutKeyboardUpFunc(onKeyboardUp);
    glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(WindowWidth / 2, WindowHeight / 2);
	memset(keys, 0, sizeof(keys));
	
	gameManager.Init(&wiiHandler);
	gameManager.addSerialHandler(&serial);

	glutMainLoop();
}
