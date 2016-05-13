//
// Created by Yorick Rommers on 11/05/16.
//

#include "PlayingState.h"
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

void PlayingState::Init(GameStateManager *game) {
    this->manager = game;
    models.push_back(pair<int, ObjModel*>(1, new ObjModel("Project/models/bloemetje/PrimroseP.obj")));
    ObjModel *baksteen = new ObjModel("Project/models/cube/cube-textures.obj");
    baksteen->xpos = 2;

    models.push_back(pair<int, ObjModel *>(1, baksteen));
}

void PlayingState::Cleanup() {

}

void PlayingState::Pause() {

}

void PlayingState::Resume() {

}

void PlayingState::HandleEvents() {

}

void PlayingState::Update() {
    for( auto &m : models){
        m.second->xrot += 10;
//        m.second->zrot +=1;
        m.second->xpos += 0.01;
        if(m.second->xpos > 5){
            m.second->xpos = -5;
        }

    }
}
void PlayingState::Draw() {
    for( auto &m : models){
        m.second->draw();
    }

}












