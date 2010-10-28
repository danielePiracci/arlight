/// \file game/states/game_state.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/02/06
/// \version 1.0
///
/// \brief This file implements the DissertationProject::GameState class, 
/// declared at game/states/game_state.h.
#include "game/states/game_state.h"

//#include "game/game.h"

BEGIN_PROJECT_NAMESPACE();
BEGIN_NAMESPACE(States);

GameState::GameState() { }

GameState::~GameState() { }

void GameState::Initialize() {

}

void GameState::Release() {

}

void GameState::ChangeState(Game& game, GameState::StateId state) {
//  game.GetStateManager().ChangeState(state);
}

void GameState::PushState(Game& game, StateId state) {
//  game.GetStateManager().PushState(state);
}

void GameState::PopState(Game& game) {
//  game.GetStateManager().PopState();
}

END_NAMESPACE(States);
END_PROJECT_NAMESPACE();
