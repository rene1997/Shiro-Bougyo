#pragma once
#include "ObjModel.h"
#include "Camera.h"
#include "WiiHandler.h"
#include "AnimatedModel.h"
#include "ArrowModel.h"


class GameState;
class Player;

class BowModel :
	public ObjModel
{
public:
	BowModel(WiiHandler * hand, string filename, GameState * state, Camera * cam, Player * player);
	~BowModel();
	void draw() override;
	static float toRadian(float degree);
	void fireArrow() const;
	void update(float deltatime) override;
private:
	ObjModel * crosshair;
	GameState * state;
	Camera* camera_;
	WiiHandler * wiiHandler;
	Player * player_;

	void SetPositions(float x, float y, float rotx, float roty);
	void setCrosshairPositions(float x, float y, float rotx, float roty) const;
	
	float bowPostion = 0.8f;
	int wiiXPos = 0;
	int wiiYPos = 0;
};

