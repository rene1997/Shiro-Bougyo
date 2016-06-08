//
// Created by Yorick Rommers on 11/05/16.
//
#define MOUSE true //set false to enable nunchuk or true to enable mouse
#include <thread>
#include "PlayingState.h"
#include "BowModel.h"
#include "WarriorModel.h"
#include "SecondWarriorModel.h"
#include "MenuModel.h"

#include "AnimatedModel.h"
#include "StationaryObjModel.h"
#include "AnimatedBowModel.h"
#include "ArrowModel.h"
#include "PointXY.h"
#include "Util.h"
#include "GateModel.h"

#include "sdl_audio.h"
#include "SerialHandler.h"
#include "Overlay.h"


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#else
#include <tuple>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#endif


void PlayingState::Init(GameStateManager *game, WiiHandler * hand) {
    this->manager = game;
//	this->camera = cam;
    this->wiiHandler = hand;
	this->overlay_ = new Overlay();
	SerialHandler *serial = manager->getSerialHandler();
	//Enable the pressure plates:
	serial->sendCommand("EGM");
	

    Camera* cam1 = new Camera();
    Camera* cam2 = new Camera();


	cam1->rotY = 180;
	cam1->posY = 1;
	cam1->posX = 2.5;
	cam1->posZ = 6;

	cam1->posZ = 3.2;
	cam1->posY = 1.8;
	cam1->rotY = 180;

    cam2->rotY = 180;
    cam2->posY = 5;
    cam2->posX = 2.5;
    cam2->posZ = 6;

    cam2->posZ = 3.2;
    cam2->posY = 1.8;
    cam2->rotY = 180;

	//World
	ObjModel *world = new StationaryObjModel("models/world/FirstWorld1.obj");
	world->xpos = -2;
	world->ypos = -5;
	models.push_back(pair<int, ObjModel*>(13, world));


	//adding warriors:
	staticModels.push_back(new ObjModel("models/warrior/warrior.obj")); //warrior 1
	staticModels.push_back(new ObjModel("models/secondwarrior/warrior.obj")); //warrior 2
	staticModels.push_back(new ObjModel("models/blok/blok.obj")); //Gate
	staticModels.push_back(new ObjModel("models/Arrow/Arrow.obj")); //arrow
	staticModels.push_back(new ObjModel("models/warrior/warriorAttack/FirstStand.obj"));
	staticModels.push_back(new ObjModel("models/warrior/warriorAttack/SecondStand.obj"));
	staticModels.push_back(new ObjModel("models/warrior/warriorAttack/ThirdStand.obj"));
	this->gate = new GateModel(staticModels.at(2));

    cam1->width = game->width;
    cam1->height = game->height;
    cam2->width = game->width;
    cam2->height = game->height;
    players.push_back(new Player(cam1, hand, this, 1));
    players.push_back(new Player(cam2, hand, this, 2));
	players[0]->makeBow(staticModels.at(3));
	players[1]->makeBow(staticModels.at(3));

	for (int i = 0; i < 20; i++){
		AddWarrior();
	}
}

struct PointXY PlayingState::SpawnEnemies(){
	int portalNo = rand() % 4;
	float portalx;
	float portaly;

	switch(portalNo){
		case 1:
			portalx = 10.7;
			portaly = -16.0;
			break;
		case 2:
			portalx = 18.7;
			portaly = -9.0;
			break;
		case 3:
			portalx = -10.3;
			portaly = -16.0;
			break;
		default:
			portalx = 18.7;
			portaly = -9.0;
			break;
	}

	struct PointXY point;
	point.X = portalx;
	point.Y = portaly;
	return point;
}

void PlayingState::AddWarrior(){
	int random = rand() % 60;
	if (enemyCount < 20 && random < 5) {
		PointXY point = SpawnEnemies();
		int filename1 = random % 2;
		//string filename2;
		if (random % 2)
		{
			type = WarriorType::first;
			//filename1 = "models/warrior/warrior.obj";
		}
		else
		{
			type = WarriorType::second;
			//filename1 = "models/secondwarrior/warrior.obj";
		}
		//make animated warrior:


		vector<CollisionModel*> models;
		WarriorModel * warriorOne = new WarriorModel(-point.X, -point.Y, type, staticModels.at(filename1), this);
		WarriorModel * warriorOneFirstAnimating = new WarriorModel(-2.5, -2.3, type, staticModels.at(5), this);
		WarriorModel * warriorOneSecondAnimating = new WarriorModel(-2.5, -2.3, type, staticModels.at(6), this);
//		WarriorModel * warriorOneThridAnimating = new WarriorModel(-2.5, -2.3, type, staticModels.at(7), this);

		WarriorModel *warriorTwo = new WarriorModel(warriorOne->xpos, warriorOne->ypos, type, staticModels.at(filename1), this);

		models.push_back(warriorOne);
		models.push_back(warriorOneFirstAnimating);
		models.push_back(warriorOneSecondAnimating);
	//	models.push_back(warriorOneThridAnimating);
		models.push_back(warriorTwo);

		animatedWarior = new AnimatedAttackWarriorOne(models);

		animatedcollisionmodels_.push_back(pair<int, AnimatedCollisionModel*>(0,animatedWarior));
	}
}

void PlayingState::ScalePowerUp() {
	for (auto &m : animatedcollisionmodels_) {
		WarriorModel *warrior = dynamic_cast<WarriorModel*>(m.second->getModel());
		if (warrior != 0) {
			warrior->setSize(3);
			warrior->PowerUpBoundingSpheres();
		}
	}
	std::thread scaleThread(&PlayingState::PowerUpThread,this); //Serialthread
	scaleThread.detach();
}

void PlayingState::DestoryPowerUp()
{
	std::thread destroyThread(&PlayingState::DestroyPowerUpThread, this); //Serialthread
	destroyThread.detach();
}

void PlayingState::SetEnemyCount(int offset)
{
	enemyCount += offset;
}

void PlayingState::PowerUpThread()
{
	Util::USleep(30000);
	//Restore warrior scale:
	for (auto &m : animatedcollisionmodels_) {
		WarriorModel *warrior = dynamic_cast<WarriorModel*>(m.second->getModel());
		if (warrior != 0) {
			warrior->setSize(1);
			warrior->InitBoundingSpheres();
		}
	}
}

void PlayingState::DestroyPowerUpThread()
{
	float height = 0;
	int war;
	int rot = 0;
	std::vector<pair<int, AnimatedCollisionModel*>>::const_iterator iter;
	while (height < 40) {
		for (iter = animatedcollisionmodels_.begin(), war = 0; iter != animatedcollisionmodels_.end() && war < 10; ++iter, war++) {
				WarriorModel *warrior = dynamic_cast<WarriorModel*>(iter->second->getModel());
				if (warrior != 0) {
					warrior->setPosition(0,height,0);
					warrior->setRotation(warrior->xrot, rot, warrior->zrot);
				}
			}
		rot+=60;
		height+=0.1;
		Util::USleep(30);
	}
	//removing them:
	for (int count = 0; count < 10; count++) {
		for (iter = animatedcollisionmodels_.begin(); iter != animatedcollisionmodels_.end(); ++iter) {
			WarriorModel *warrior = dynamic_cast<WarriorModel*>(iter->second->getModel());
			if (warrior != 0) {
				animatedcollisionmodels_.erase(iter);
				break;
			}
		}
	}
}

void PlayingState::Cleanup() {}

void PlayingState::Pause() {}

void PlayingState::Resume() {}

void PlayingState::Update(float deltatime) {
	Update(deltatime, false);
}

void PlayingState::Update(float deltatime, bool keys) {


	/* nunchuk */
	/*players[0]->getCamera()->rotX = wiiHandler->rot1X;
	players[0]->getCamera()->rotY = wiiHandler->rot1Y;
	glutWarpPointer(players[0]->getCamera()->width / 2, players[0]->getCamera()->height / 2);*/

    for (int i = 0; i < players.size(); i++) {
        if (i == 0 && !MOUSE) {
            players[i]->getCamera()->rotX = wiiHandler->rot1X;
            players[i]->getCamera()->rotY = wiiHandler->rot1Y;
            glutWarpPointer(players.at(i)->getCamera()->width / 2, players.at(i)->getCamera()->height / 2);
        }
        if (i == 1) {
            players[i]->getCamera()->rotX = wiiHandler->rot2X;
            players[i]->getCamera()->rotY = wiiHandler->rot2Y;
            glutWarpPointer(players.at(i)->getCamera()->width / 2, players.at(i)->getCamera()->height / 2);
        }
    }


	/* nunchuk */
	/*players[1]->getCamera()->rotX = wiiHandler->rot2X;
	players[1]->getCamera()->rotY = wiiHandler->rot2Y;
	glutWarpPointer(players.at(1)->getCamera()->width / 2, players.at(1)->getCamera()->height / 2);*/

	//speler 1 booog
	if (wiiHandler->is_B1 || keys)
	{
		counter1 += deltatime;
		if (counter1 < 33) players[0]->bow->setIndex(0);
		else if (counter1 < 66) players[0]->bow->setIndex(1);
		else players[0]->bow->setIndex(2);
		if (counter1 >= 100)
		{
			players[0]->bow->nextModel();
			if (counter1 >= 59)
			{
				players[0]->bow->getModel()->update(-1);
				players[0]->bow->setIndex(0);
				counter1 = 0;
			}
		}
	}
	else
	{
		counter1 = 0;
		players[0]->bow->setIndex(0);
	}

	players.at(1)->getCamera()->rotX++;

	//Collision Gate with Warrior
	for (auto &Warrior : animatedcollisionmodels_)
	{
			if ((Warrior.second->getModel() != this->gate) && std::get<0>(Warrior.second->getModel()->CollidesWith(this->gate)))
			{
				collidesGate = true;
				counterWarrior +=1;
				if(counterWarrior > 33 || counterWarrior < 66)
				{
					animatedWarior->setIndex(1);
				}
				if(counterWarrior > 66 || counterWarrior < 99)
				{
					animatedWarior->setIndex(0);
					counterWarrior =  99;
				}else if(counterWarrior > 101)
				{
					animatedWarior->setIndex(2);
					counterWarrior = 0;
				}
					
			}
		if (!collidesGate) {
			Warrior.second->getModel()->update(deltatime);
		}
		collidesGate = false;
	}
	if (wiiHandler->is_B2)
	{
		counter2 += deltatime;
		if (counter2 < 33) players[1]->bow->setIndex(0);
		else if (counter2 < 66) players[1]->bow->setIndex(1);
		else players[1]->bow->setIndex(2);
		if (counter2 >= 100)
		{
			players[1]->bow->nextModel();
			if (counter2 >= 59)
			{
				players[1]->bow->getModel()->update(-1);
				players[1]->bow->setIndex(0);
				counter2 = 0;
			}
		}
	}
	else
	{
		counter2 = 0;
		players[1]->bow->setIndex(0);

	}

		bool collides = false;
		for (auto &obj1 : collisionModels) {
			for (auto &obj2 : collisionModels) {
				collides = CheckCollision(obj1.second, obj2.second);
				
			}
			
			for (auto &obj3 : animatedcollisionmodels_)
			{
				collides = CheckCollision(obj1.second, obj3.second->getModel());
			}

			if (!collides) {
				obj1.second->update(deltatime);
			}
			collides = false;
		}

		for (auto &obj1 : animatedcollisionmodels_) {
			for (auto &obj2 : animatedcollisionmodels_) {
				collides = CheckCollision(obj1.second->getModel(), obj2.second->getModel());

			}

			for (auto &obj3 : collisionModels) {
				collides = CheckCollision(obj1.second->getModel(), obj3.second);

			}

			if (!collides) {
				obj1.second->getModel()->update(deltatime);
			}
		}

		for (auto &m : models) {
			m.second->update(deltatime);
		}
		for (auto &m : collisionModels) {
			m.second->update(deltatime);
		}

		
		//bow->getModel()->update(deltatime);
	}


bool PlayingState::CheckCollision(CollisionModel * obj1, CollisionModel * obj2)
{
	bool collides = false;
	if (obj1 != obj2 && std::get<0>(obj1->CollidesWith(
		obj2))) //get<1> returns a vector with the spheres that are colliding
	{
		//                printf("%d colliding with %d\n", obj1.first, obj2.first);
		collides = true;
		WarriorModel *warrior1 = dynamic_cast<WarriorModel *>(obj1);
		WarriorModel *warrior2 = dynamic_cast<WarriorModel *>(obj2);
		ArrowModel *arrow1 = dynamic_cast<ArrowModel *>(obj1);
		ArrowModel *arrow2 = dynamic_cast<ArrowModel *>(obj2);

		if ((warrior1 != 0 || warrior2 != 0) && (arrow1 != 0 || arrow2 != 0)) {
			std::thread arrowHitThread(&SDL_Audio::playArrowHit, SDL_Audio()); //play arrowhit sound
			arrowHitThread.detach();

			//set player who shot the arrow
			Player * from_player;
			if (arrow1 != nullptr) {
				from_player = arrow1->getPlayer();
				DeleteModel(arrow1);
			}
			else {
				from_player = arrow2->getPlayer();
				DeleteModel(arrow2);
			}


			if (warrior1 != nullptr) {
				//returns false if warrior health <= 0
				warrior1->removeHealth(from_player);

			}
			else {
				//returns false if warrior health <= 0
				warrior2->removeHealth(from_player);

			}
		}
		
	}
	return collides;
}

void PlayingState::DrawModels(){

    for( auto &m : models) {
        m.second->draw();
    }
    for( auto &n : collisionModels) {
        n.second->draw();
    }
	for(auto &o : animatedcollisionmodels_){
		o.second->getModel()->draw();
	}
	//FirstStand->getModel()->draw();
}


void PlayingState::Draw() {

//    printf("Draw\n");

    if (players.size() == 2) { //TODO: replace with players.size
        Camera *cam1 = players.at(0)->getCamera();
        Camera *cam2 = players.at(1)->getCamera();


        for (int loop = 0; loop < 2; loop++)                /* Loop To Draw Our 4 Views */
        {
            glClearColor(0.6f, 0.6f, 1, 1);

            if (loop == 0)    /* If We Are Drawing The First Scene */
            {
                /* Set The Viewport To The Top Left.  It Will Take Up Half The Screen Width And Height */
                glViewport(0, 0, cam1->width / 2, cam1->height);
                glMatrixMode(GL_PROJECTION);        /* Select The Projection Matrix */
                glLoadIdentity();                            /* Reset The Projection Matrix */
                gluPerspective(60.0f, (float) cam1->width / cam1->height, 0.1, 100);

            }

            if (loop == 1)    /* If We Are Drawing The Second Scene */
            {
//			/* Set The Viewport To The Top Left.  It Will Take Up Half The Screen Width And Height */
                glViewport(cam2->width / 2, 0, cam2->width / 2, cam2->height);
                glMatrixMode(GL_PROJECTION);        /* Select The Projection Matrix */
                glLoadIdentity();                            /* Reset The Projection Matrix */
                gluPerspective(60.0f, (float) cam2->width / cam2->height, 0.1, 100);
            }

            glMatrixMode(GL_MODELVIEW);            /* Select The Modelview Matrix */
            glLoadIdentity();                                /* Reset The Modelview Matrix */

            glClear(GL_DEPTH_BUFFER_BIT);        /* Clear Depth Buffer */

            if (loop == 0)    /* Are We Drawing The First Image?  (Original Texture... Ortho) */
            {
                preTranslateDraw(players.at(0));
                glRotatef(cam1->rotX, 1, 0, 0);
                glRotatef(cam1->rotY, 0, 1, 0);
                glTranslatef(cam1->posX, cam1->posY, cam1->posZ);
                DrawModels();
            }

            if (loop == 1)    /* Are We Drawing The Second Image?  (3D Texture Mapped Sphere... Perspective) */
            {
                preTranslateDraw(players.at(1));
                glRotatef(cam2->rotX, 1, 0, 0);
                glRotatef(cam2->rotY, 0, 1, 0);
                glTranslatef(cam2->posX, cam2->posY, cam2->posZ);
                DrawModels();
            }

			//draw port xpbar


			//TODO: call this method if gameover :) 
			//overlay_->drawGameOver(this->players, loop, true);
			overlay_->drawHealthBar(players.at(0), this->gate);
        }
    }

    else {
        //draw 1 player full screen

//        printf("Player %u draw\n", players.at(0)->getPlayerID());

        Camera *cam1 = players.at(0)->getCamera();
//        printf("Camera : \n %f %f %f\n", cam1->posX, cam1->posY, cam1->posZ);
//        printf("%d %d\n", cam1->width, cam1->height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0f, (float) cam1->width / cam1->height, 0.1, 100);


        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();
//        load bow
        preTranslateDraw(players.at(0));
        glRotatef(cam1->rotX, 1, 0, 0);
        glRotatef(cam1->rotY, 0, 1, 0);
        glTranslatef(cam1->posX, cam1->posY, cam1->posZ);
        DrawModels();
		overlay_->drawGameOver(this->players, 0, true);

    }

	

}

void PlayingState::preTranslateDraw(Player * p) {
	if(p->bow)
		p->bow->getModel()->draw();
}

void PlayingState::HandleEvents() {
   
}

void PlayingState::AddModel(CollisionModel *model) {
    collisionModels.push_back(pair<int, CollisionModel*>(collisionModels.size(), model));
}

void PlayingState::DeleteModel(CollisionModel *model) {
	std::vector<pair<int, CollisionModel*>>::const_iterator iter;
	for (iter = collisionModels.begin(); iter != collisionModels.end(); ++iter){
		if(iter->second == model){
			WarriorModel *warrior = dynamic_cast<WarriorModel*>(iter->second);
			if (warrior != 0) {
				SetEnemyCount(-1);
			}
			collisionModels.erase(iter);
			break;
		}
	}

	std::vector<pair<int, AnimatedCollisionModel*>>::const_iterator iter2;
	for (iter2 = animatedcollisionmodels_.begin(); iter2 != animatedcollisionmodels_.end(); ++iter2) {
		if (iter2->second->getModel() == model) {
			WarriorModel *warrior = dynamic_cast<WarriorModel*>(iter2->second->getModel());
			if (warrior != 0) {
				SetEnemyCount(-1);
			}
			animatedcollisionmodels_.erase(iter2);
			break;
		}
	}
}

vector<Player *> PlayingState::GetPlayers() {
    return players;
}




















