#pragma once
#include "AnimatedModel.h"
#include "WiiHAndler.h"
#include "BowModel.h"

class AnimatedBowModel :
	public AnimatedModel
{
public:
	AnimatedBowModel(vector<ObjModel*> models, WiiHandler * wiihandler);
	~AnimatedBowModel();

};

