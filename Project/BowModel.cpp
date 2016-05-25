#include "BowModel.h"
#include <iostream>
#include "Camera.h"
#include "WiiHandler.h"
#include "AnimatedModel.h"
#include <math.h>
#include "GameState.h"

# define M_PI           3.14159265358979323846  /* pi */


BowModel::BowModel(WiiHandler * hand, string filename, GameState * state, Camera * cam): ObjModel(filename) {
	this->wiiHandler = hand;
	this->camera_ = cam;
	this->state = state;
	crosshair = new ObjModel("models/crosshair/crosshair.obj");
	SetPositions(0, 0, 0, 0);
	arrow  = new ArrowModel(xpos, ypos, zpos);
	setCrosshairPositions(0, 0,0,0);
	setArrowPosition();

}

BowModel::~BowModel()
{

}

void BowModel::SetPositions(float x, float y, float rotx, float roty) {
	//set bow on camera position

	xpos = bowPostion;
	ypos = y ;
	zpos = -1;
	yrot = 180;

	////set rotation bow equals to rotation camera
	//if (roty > -90 && roty < 90)
	//	xrot = -rotx;
	//else
	//	xrot = rotx;
	//yrot = -roty + 180;
	//zrot = 0;

	//////translate bow to correct position
	//cout << "rotx: " << rotx << endl;

	////if rotate on x as:
	//ypos -= (sin(toRadian(rotx)));
	//zpos -= (cos(toRadian(rotx)) * cos(toRadian(roty)));
	//
	////if rotate on y as: 
	//xpos += (sin(toRadian(roty)));
	//
	////set bow correct position

	//xpos += bowPostion	 * (cos(toRadian(roty)));
	//zpos += bowPostion * (sin(toRadian(roty)));

	//set crosshair positions
	//setCrosshairPositions(x, y, rotx, roty);



}

void BowModel::setCrosshairPositions(float x, float y, float rotx, float roty)
{
	//set crosshair on camera position
	crosshair->xpos = 0;
	crosshair->ypos = 0;
	crosshair->xrot = crosshair->yrot = crosshair->zrot =   0;
	crosshair->zpos = -1;
	////set rotation croshair equals to rotation camera
	////	xrot = -rotx;
	//if (roty > -90 && roty < 90)
	//	crosshair->xrot = -rotx;
	//else
	//	crosshair->xrot = rotx;
	//crosshair->yrot = -roty + 180;
	//crosshair->zrot = 0;

	////translate bow to correct position

	////if rotate on x as:
	//crosshair->ypos -= (sin(toRadian(rotx)));
	//crosshair->zpos -= (cos(toRadian(rotx)) * cos(toRadian(roty)));


	//if rotate on y as: 
	//crosshair->xpos += (sin(toRadian(roty)));

}

void BowModel::setArrowPosition()
{
	arrow->xpos = xpos + 0.21;
	arrow->ypos = ypos;
	arrow->zpos = zpos - 0.7;
	arrow->xrot = xrot;
	arrow->yrot = yrot;
	arrow->zrot = zrot;
}

void BowModel::draw()
{
	ObjModel::draw();
	arrow->draw();
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.8, 0.8, 0.8);
	crosshair->draw();
	glEnable(GL_TEXTURE_2D);


}

float BowModel::toRadian(float degree) {
	return (degree / 180) * M_PI;
}

void BowModel::update(float deltatime)
{
	//counter++;
	//if(wiiHandler->is_A && counter >= 60)
	//{
		counter = 0;
		//TODO make delay and animate

		//set rotation bow equals to rotation camera
		float pointx = 0, pointy = 0, pointz = 0;
		float xrotcam = 0, yrotcam = 0, zrotcam = 0;

		if (camera_->rotY > -90 && camera_->rotY < 90)
			xrotcam = - camera_->rotX;
		else
			xrotcam = camera_->rotX;
		yrotcam = -camera_->rotY;
		zrotcam = 0;

		////translate bow to correct position
		//cout << "rotx: " << rotx << endl;

		//if rotate on x as:
		pointy -= (sin(toRadian(camera_->rotX)));
		pointz -= (cos(toRadian(camera_->rotX)) * cos(toRadian(camera_->rotY)));
		
		//if rotate on y as: 
		pointx += (sin(toRadian(camera_->rotY)));


		arrow->fire(pointx, pointy, pointz, xrotcam, yrotcam, zrotcam);
		state->AddModel(arrow);
		setArrowPosition();
	//}
	//if(!wiiHandler->is_A)
	//{
	//	counter = 0;
	}



