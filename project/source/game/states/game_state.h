/// \file game/states/game_state.h
/// \author Juan Carlos De Abreu (jcabreur@gmail.com)
/// \date 2010/02/06
/// \version 1.0
// 
/// \brief This file declares the DissertationProject::States::GameState 
/// class, which implement the basic functionalities of a game state.
#ifndef GAME_STATES_GAME_STATE_H__
#define GAME_STATES_GAME_STATE_H__

#include "global.h"

BEGIN_PROJECT_NAMESPACE();

// Define class prototype.
class Game;

BEGIN_NAMESPACE(States);

class GameState {
 public:
  // Allow to the game state manager has access to the private data.
  friend class GameStateManager;

  /// \brief Standard constructor.
  GameState();

  /// \brief Initializer constructor.
  ~GameState();

  /// \brief Enum which define all the posible states on the game.
  enum StateId {
    kLoadState,
    kIntroState,
    kMenuState,
    kPlayState,
    kCreditsState
  };

 protected:
  /// \brief Initialize all the resources needed by the game state. 
  virtual void Initialize();

  /// \brief Release all the resources used by the game state.
  virtual void Release();

  /// \brief Enter to the current state.
  virtual void Enter() = 0;

  /// \brief Exit the current state.
  virtual void Exit() = 0;

  /// \brief Pause the execution of the current state.
  virtual void Pause() = 0;

  /// \brief Restore the exection of the previous state.
  virtual void Resume() = 0;

  /// \brief Method to update the state's logic. This method is called on each 
  /// frame.
  /// \param[in] game Shared game data.
  virtual void Update(Game& game) = 0;

  /// \brief Method to display the data of the state. This method is called on 
  /// each frame.
  /// \param[in] game Shared game data.
  virtual void Render(Game& game) = 0;

  /// \brief Method to handle the events. This method is called every time 
  /// that a event is triggered.
  /// \param[in] game Shared game data.
  virtual void HandleEvents(Game& game) = 0;

  /// \brief Change the current game state and set the one passed as parameter.
  /// \param[in] game Shared game data.
  /// \param[in] Id of the game state.
  void ChangeState(Game& game, StateId state);

  /// \brief Pause the current state and add the new state to the top of the 
  /// stack.
  /// \param[in] game Shared game data.
  /// \param[in] Id of the game state.
  void PushState(Game& game, StateId state);

  /// \brief Remove the current state and resume state at the top of the stack.
  /// \param[in] game Shared game data.
  void PopState(Game& game);

 private:
  DISALLOW_COPY_AND_ASSIGN(GameState);
};

END_NAMESPACE(States);
END_PROJECT_NAMESPACE();

#endif  // GAME_STATES_GAME_STATE_H__
