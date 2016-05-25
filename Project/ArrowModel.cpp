//
// Created by Yorick Rommers on 20/05/16.
//

#include <cmath>
#include <iostream>
#include "ArrowModel.h"
#include "BowModel.h"

ArrowModel::ArrowModel( float startx, float starty, float startz) : CollisionModel("models/Arrow/Arrow.obj") {

    //startpoint arrow:
	xpos = startx;
	ypos = starty;
	zpos = startz;


    boundingSpheres.clear(); //Clear base boundingspheres
    ArrowModel::InitBoundingSpheres();

}

ArrowModel::~ArrowModel()
{
}

void ArrowModel::InitBoundingSpheres() {
    //Calculate width
    float width = vertices_max->x - vertices_min->x;
    float height = vertices_max->y - vertices_min->y;
    float depth = vertices_max->z - vertices_min->z;

    //X, Y and Z of sphere is the middle of the model

    float x, y, z ;
    x = y = z = 0;

    x = width / 2 + vertices_min->x;
    y = height / 2+vertices_min->y;
    z = depth / 2+vertices_min->z;

    printf("DO NOT FEAR ARROW IS HERE\n");

    //depth

    for(int i = 0; i < 8; i++){
        boundingSpheres.push_back(new Sphere(vertices_min->x, y, i*z, 0.12f));
    }

}

void ArrowModel::CalcBoundingSpheres() {
    for (auto &sphere : boundingSpheres) {
        sphere->xpos = sphere->x + this->xpos;
        sphere->ypos = sphere->y + this->ypos;
        sphere->zpos = sphere->z + this->zpos;
    }
}

void ArrowModel::update(float deltatime) {
	


	xrot += 01;


}

void ArrowModel::draw() {
    CollisionModel::draw();
}






