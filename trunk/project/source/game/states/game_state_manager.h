/// \file game/states/game_state_manager.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/02/06
/// \version 1.0
// 
/// \brief This file declares the DissertationProject::States::GameStateManager 
/// class, which implement the basic functionalities of a game state manager.
#ifndef GAME_STATES_GAME_MANAGER_H__
#define GAME_STATES_GAME_MANAGER_H__

#include "global.h"
#include "game/states/game_state.h"

#include "map"
#include "stack"

BEGIN_PROJECT_NAMESPACE();
BEGIN_NAMESPACE(States);

class GameStateManager {
 public:
  /// \brief Standard constructor.
  GameStateManager();

  /// \brief Initializer constructor.
  ~GameStateManager();

  /// \brief Initialize all the resources needed by the game state manager. 
  /// This method should be modified in order to register default states if 
  /// new default states are created for the game.
  void Initialize();

  /// \brief Release all the resources used by the game state manager.
  void Release();

  /// \brief Change the current game state and set the one passed as parameter.
  /// \param[in] Id of the game state.
  void ChangeState(GameState::StateId state);

  /// \brief Pause the current state and add the new state to the top of the 
  /// stack.
  /// \param[in] Id of the game state.
  void PushState(GameState::StateId state);

  /// \brief Remove the current state and resume state at the top of the stack.
  void PopState();

  /// \brief Method to update the state's logic. This method is called on each 
  /// frame.
  /// \param[in] game Shared game data.
  void Update(Game& game);

  /// \brief Method to display the data of the state. This method is called on 
  /// each frame.
  /// \param[in] game Shared game data.
  void Render(Game& game);

  /// \brief Method to handle the events. This method is called every time 
  /// that a event is triggered.
  /// \param[in] game Shared game data.
  void HandleEvents(Game& game);

  /// \brief Register a game state.
  /// \param[in] game_state Pointer to the game state object.
  /// \param[in] state Id of the game state.
  void RegisterState(GameState* game_state, GameState::StateId state);

  /// \brief Unregister a game state.
  /// \param[in] Id of the game state.
  void UnregisterState(GameState::StateId state);

 private:
  /// \brief Map with all the game loaded game states.
  std::map<GameState::StateId, GameState*> game_states_;

  /// \brief Stack of game states. This allow pause and resume game states.
  std::stack<GameState::StateId> states_;

  DISALLOW_COPY_AND_ASSIGN(GameStateManager);
};

END_NAMESPACE(States);
END_PROJECT_NAMESPACE();

#endif  // GAME_STATES_GAME_MANAGER_H__
