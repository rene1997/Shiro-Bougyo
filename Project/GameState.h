#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameStateManager.h"

class GameState {
	public:
		virtual void Init(GameStateManager* game) = 0;
		virtual void Cleanup() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

		//void ChangeState(GameStateManager* game, GameState* state) { game->ChangeState(state); }

	protected: 
		GameState() { }
};
#endif
