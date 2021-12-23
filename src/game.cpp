#include "game.h"
#include "SDL.h"
#include "logic.h"
#include <iostream>

// Constrctor
//  Set sporn threadsholds for enemies in random generator
Game::Game()
    : engine(dev()), random_w(Logic::POINTS_MIN, Logic::POINTS_MAX),
      random_h(Logic::POINTS_MIN, std::ceil(Logic::POINTS_MAX * 0.3))
{
  _logic = std::make_shared<Logic>();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // Init
  // Move player to intial position
  _logic->_player1->moveToPos(std::ceil(Logic::POINTS_MAX * 0.5),
                              std::ceil(Logic::POINTS_MAX * 0.9));
  renderer.Init(_logic.get());

  // TODO: remove

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Clean screen
    renderer.Clear();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, *_logic);
    Update();
    renderer.Render(_logic.get());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

// void Game::PlaceFood() {
// int x, y;
// while (true) {
//   x = random_w(engine);
//   y = random_h(engine);
//   // Check that the location is not occupied by a snake item before placing
//   // food.
//   if (!snake.SnakeCell(x, y)) {
//     food.x = x;
//     food.y = y;
//     return;
//   }
// }
// }

void Game::Update()
{

  /////////////////////
  // player
  // Set speed of player

  if (_logic->keyInDown)
  {
    _logic->_player1->setVelo(_logic->_player1->getVeloX(),
                              _logic->_player1->getVeloY() + _SPEED_INC_PLAYER);
  }
  if (_logic->keyInUp)
  {
    _logic->_player1->setVelo(_logic->_player1->getVeloX(),
                              _logic->_player1->getVeloY() - _SPEED_INC_PLAYER);
  }
  if (_logic->keyInLeft)
  {
    _logic->_player1->setVelo(_logic->_player1->getVeloX() - _SPEED_INC_PLAYER,
                              _logic->_player1->getVeloY());
  }
  if (_logic->keyInRight)
  {
    _logic->_player1->setVelo(_logic->_player1->getVeloX() + _SPEED_INC_PLAYER,
                              _logic->_player1->getVeloY());
  }

  // update player
  int xPosNew = _logic->_player1->getPosX() + _logic->_player1->getVeloX();
  int yPosNew = _logic->_player1->getPosY() + _logic->_player1->getVeloY();

  // make sure player is in the field
  if (xPosNew >= Logic::POINTS_MIN &&
      (xPosNew + _logic->_player1->getObjWPoints()) <= Logic::POINTS_MAX &&
      yPosNew >= Logic::POINTS_MIN &&
      (yPosNew + _logic->_player1->getObjHPoints()) <= Logic::POINTS_MAX)
  {
    // move player
    _logic->_player1->moveToPos(xPosNew, yPosNew);
  }
  else
  {
    // limit player movement
    _logic->_player1->setVelo(0, 0);
  }
  // TODO:

  // Create bullet
  if (_logic->keyInAction1)
  {
    // add new bullet which travlles straight
    // *shoot upwards: neagtive y
    auto bul = std::make_unique<Object2d>();
    bul->setVelo(0, _SPEED_CONST_BULLET);
    bul->moveToPos(_logic->_player1->getPosX(), _logic->_player1->getPosY());
    _logic->_bullets.push_back(std::move(bul));
  }

  // Iterate over all bullets: Update or delete
  if (!_logic->_bullets.empty())
  {
    for (long unsigned int i = 0; i < _logic->_bullets.size(); i++)
    {
      int xPosNew = _logic->_bullets.at(i)->getPosX() +
                    _logic->_bullets.at(i)->getVeloX();
      int yPosNew = _logic->_bullets.at(i)->getPosY() +
                    _logic->_bullets.at(i)->getVeloY();

      // check: bullet is in the field
      if (xPosNew >= Logic::POINTS_MIN &&
          (xPosNew + _logic->_bullets.at(i)->getObjWPoints()) <=
              Logic::POINTS_MAX &&
          yPosNew >= Logic::POINTS_MIN &&
          (yPosNew + _logic->_bullets.at(i)->getObjHPoints()) <=
              Logic::POINTS_MAX)
      {
        // yes: Move bullet
        _logic->_bullets.at(i)->moveToPos(xPosNew, yPosNew);
      }
      else
      {
        // no: delete
        _logic->_bullets.erase(_logic->_bullets.begin() + i);
      }
    }
  }

  enemySpornIntervall = 50;

  static int enemySpornCounter{0};
  if (enemySpornCounter >= enemySpornIntervall)
  {
    AddEnemy();
    enemySpornCounter = 0;
  }
  enemySpornCounter++;

  // Iterate over all enemies: Update or delete
  if (!_logic->_enemies.empty())
  {
    for (long unsigned int i = 0; i < _logic->_enemies.size(); i++)
    {
      int xPosNew = _logic->_enemies.at(i)->getPosX() +
                    _logic->_enemies.at(i)->getVeloX();
      int yPosNew = _logic->_enemies.at(i)->getPosY() +
                    _logic->_enemies.at(i)->getVeloY();

      // check: enemy is in the field
      if (xPosNew >= Logic::POINTS_MIN &&
          (xPosNew + _logic->_enemies.at(i)->getObjWPoints()) <=
              Logic::POINTS_MAX &&
          yPosNew >= Logic::POINTS_MIN &&
          (yPosNew + _logic->_enemies.at(i)->getObjHPoints()) <=
              Logic::POINTS_MAX)
      {
        // yes: Move bullet
        _logic->_enemies.at(i)->moveToPos(xPosNew, yPosNew);
      }
      else
      {
        // no: delete
        _logic->_enemies.erase(_logic->_enemies.begin() + i);
      }
      // #TODO: check for collosion with player
      

      // #TODO: check for collision wizth bullet
    }
  }
}

void Game::AddEnemy()
{
  // enemies
  // Create random
  int x_enem = random_w(engine);
  int y_enem = random_h(engine);
  auto enem = std::make_unique<Object2d>();
  enem->setVelo(0, _SPEED_CONST_ENEMY);
  enem->moveToPos(x_enem, y_enem);
  _logic->_enemies.push_back(std::move(enem));
}

int Game::GetScore() const { return score; }