//
// Created by Yorick Rommers on 2016/06/03.
//

#include "Player.h"

Camera *Player::getCamera() {
    if(c) return c;
    return nullptr;
}

Player::Player(Camera* camera, ::WiiHandler* hand, GameState * state, unsigned char playerID)
{
	this->gamestate_ = state;
	this->c = camera;
	this->wiiHandler_ = hand;
	this->playerID = playerID;
}

Player::~Player() {

}

void Player::makeBow(ObjModel *arrowModel)
{
	vector<ObjModel*> temp;
	temp.push_back(new BowModel(wiiHandler_, "models/bow/Bow_recurve.obj", gamestate_, c, this, arrowModel));
	temp.push_back(new BowModel(wiiHandler_, "models/bow/Bow_01.obj", gamestate_, c, this, arrowModel));
	temp.push_back(new BowModel(wiiHandler_, "models/bow/Bow_02.obj", gamestate_, c, this, arrowModel));
	
	this->bow = new AnimatedBowModel(temp, wiiHandler_);
}

void Player::addKill()
{
	kills++;
}


unsigned char Player::getPlayerID() {
    return playerID;
}

int Player::getKills() {
	return this->kills;	
}