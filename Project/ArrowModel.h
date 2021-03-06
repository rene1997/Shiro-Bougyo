//
// Created by Yorick Rommers on 20/05/16.
//

#ifndef SHIRO_BOUGYO_ARROWMODEL_H
#define SHIRO_BOUGYO_ARROWMODEL_H

#include "GameState.h"
#include "CollisionModel.h"

class Player;
class GameState;

class ArrowModel : public CollisionModel {
public:
    //ArrowModel( float x, float y, float z);

	ArrowModel(float startx, float starty, float startz, float xdirection, float ydirection, GameState * state, Player * player, ObjModel *model);
	~ArrowModel(void);

	void InitBoundingSpheres() override;
    void CalcBoundingSpheres() override;
	float toRadian(float degree);
	void draw() override;
    void update(float deltatime) override;
	Player* getPlayer() const;
private:
	GameState * state;
	Player * player_;
};


#endif //SHIRO_BOUGYO_ARROWMODEL_H
