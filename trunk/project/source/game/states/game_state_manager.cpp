/// \file game/states/game_state_manager.cpp
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/02/06
/// \version 1.0
///
/// \brief This file implements the DissertationProject::States::GameStateManager 
/// class, declared at game/states/game_manager.h.
#include "game/states/game_state_manager.h"

BEGIN_PROJECT_NAMESPACE();
BEGIN_NAMESPACE(States);

GameStateManager::GameStateManager() {
  // Load all the default game states.
  Initialize();
}

GameStateManager::~GameStateManager() {
  // Release all the game states resources.
  Release();
}

void GameStateManager::Initialize() {
  // Register all the default game states.
}

void GameStateManager::Release() {
  // Release all the states stacked.
  while (!states_.empty()) states_.pop();

  // Iterate over all the registered states and release it's resources.
  std::map<GameState::StateId, GameState*>::iterator it = game_states_.begin();
  std::map<GameState::StateId, GameState*>::iterator end = game_states_.end();
  for (; it != end; ++it) UnregisterState(it->first);
  game_states_.clear();
}

void GameStateManager::RegisterState(GameState* game_state, GameState::StateId state) {
  // Add the state to game state manager map.
  game_states_[state] = game_state;
  game_state->Initialize();
}

void GameStateManager::UnregisterState(GameState::StateId state) {
  // Remove the state from the game state manager map.
  if (game_states_[state]) delete game_states_[state];
  game_states_[state] = NULL;
}

void GameStateManager::ChangeState(GameState::StateId state) {
  // Check if a current game state exist and if so removed.
  if (!states_.empty()) {
    game_states_[states_.top()]->Exit();
    states_.pop();
  }

  // Add the new game state.
  states_.push(state);
  game_states_[state]->Enter();
}

void GameStateManager::PushState(GameState::StateId state) {
  // Check if a current game state exist and if so pause it's execution.
  if (!states_.empty())
    game_states_[states_.top()]->Pause();

  // Add the new game state.
  states_.push(state);
  game_states_[state]->Enter();
}

void GameStateManager::PopState() {
  // Check if a current game state exist and if so finish it's execution.
  if (!states_.empty()) {
    game_states_[states_.top()]->Exit();
    states_.pop();
  }

  // Restore the previous game state execution.
  if (!states_.empty())
    game_states_[states_.top()]->Resume();
}

void GameStateManager::Update(Game& game) {
  // Check if a current game state exist and if so update it.
  if (!states_.empty())
    game_states_[states_.top()]->Update(game);
}

void GameStateManager::Render(Game& game) {
  // Check fi a current game state exist and if so render it.
  if (!states_.empty())
    game_states_[states_.top()]->Render(game);
}

void GameStateManager::HandleEvents(Game& game) {
  // Check if a current game state exist and if so handle the event.
  if (!states_.empty())
    game_states_[states_.top()]->HandleEvents(game);
}

END_NAMESPACE(States);
END_PROJECT_NAMESPACE();
