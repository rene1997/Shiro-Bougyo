//
// Created by Yorick Rommers on 11/05/16.
//

#include "PlayingState.h"
#include "BowModel.h"
#include "WarriorModel.h"
#include "MenuModel.h"

#include "AnimatedModel.h"
#include "StationaryObjModel.h"
#include "AnimatedBowModel.h"
#include "ArrowModel.h"


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include <iostream>

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#endif

void PlayingState::Init(GameStateManager *game, Camera *cam, WiiHandler * hand) {
    this->manager = game;
	this->camera = cam;
    this->wiiHandler = hand;
	

	//bow
	vector<ObjModel*> temp;
	temp.push_back(new BowModel(hand, "models/bow/Bow_recurve.obj"));
	temp.push_back(new BowModel(hand, "models/bow/Bow_01.obj"));
	temp.push_back(new BowModel(hand, "models/bow/Bow_02.obj"));

	bow = new AnimatedBowModel(temp, hand);
	//bow = new AnimatedBowModel(models); #1#

	//Warrior
	for (int i = 1; i < 5; i++ )
	{
		WarriorModel *warrior = new WarriorModel(i *2, -i);
		models.push_back(pair<int, ObjModel*>(i, warrior));
	}


	//arrow
	/*ObjModel *arrow = new ObjModel("models/Arrow/Arrow.obj");
	arrow->xpos = 2;
	arrow->ypos = 2;
	models.push_back(pair<int, ObjModel*>(1, arrow));*/

	ObjModel *arrow = new ArrowModel(1.5f,0, 1.5f);
	arrow->xpos = -10;
	arrow->zpos = 10;
	models.push_back(pair<int, ObjModel*>(1337, arrow));

	WarriorModel *warrior = new WarriorModel(1.5f,1.5f);
	models.push_back(pair<int, ObjModel*>(231231, warrior));
	
	//world 
	ObjModel *world = new StationaryObjModel("models/world/FirstWorld.obj");
	world->xpos = -2;
	world->ypos = -5;
	models.push_back(pair<int, ObjModel*>(1, world));
}

void PlayingState::Cleanup() {

}

void PlayingState::Pause() {

}

void PlayingState::Resume() {

}

void PlayingState::Update(float deltatime) {
	if(wiiHandler->is_A)
		bow->nextModel();
    bool collides = false;
    for( auto &obj1 : models) {
        for (auto &obj2 : models) {
            if (obj1 != obj2 && std::get<0>(obj1.second->CollidesWith(obj2.second))) //get<1> returns a vector with the spheres that are colliding
			{
				printf("%d colliding with %d\n", obj1.first, obj2.first);
				collides = true;
                break;
			}
		}
        if(!collides) {
            obj1.second->update();
        }
        collides = false;
    }
}


void PlayingState::Draw() {
    for( auto &m : models) {
        m.second->draw();
    }

}

void PlayingState::preDraw()
{
	bow->getModel()->draw();
}

void PlayingState::HandleEvents() {
   
}


















