#include "game.h"
#include "SDL.h"
#include "logic.h"
#include <iostream>

// Constrctor
//  Set sporn thresholds for enemies in random generator
Game::Game()
    : engine(dev()),
      _random_w(config::VRES_POINTS_MIN, config::VRES_POINTS_MAX),
      _random_h(config::VRES_POINTS_MIN,
                std::ceil(config::VRES_POINTS_MAX * 0.3)) {
  _logic = std::make_shared<Logic>();
}

void Game::run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // Init
  // Move player to initial position
  _logic->_player1->setCurrPos(config::PLAYER_INIT_POS);

  while (running) {
    frame_start = SDL_GetTicks();

    // Clean screen
    renderer.Clear();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, *_logic);
    update(running);
    renderer.Render(_logic.get());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(_score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::update(bool &running) {

  /////////////////////
  // player

  // steer according to user input
  if (_logic->keyInDown) {
    _logic->_player1->accelerate(0, config::PLAYER_SPEED_INC);
  }
  if (_logic->keyInUp) {
    _logic->_player1->accelerate(0, -config::PLAYER_SPEED_INC);
  }
  if (_logic->keyInLeft) {
    _logic->_player1->accelerate(-config::PLAYER_SPEED_INC, 0);
  }
  if (_logic->keyInRight) {
    _logic->_player1->accelerate(config::PLAYER_SPEED_INC, 0);
  }

  // make sure player is in the field after moving
  if (!_logic->_player1->isObjOnScreen(_logic->_player1->getNextPos())) {
    // limit player movement
    _logic->_player1->setVelo(0, 0);
  }
  // move and update reload
  _logic->_player1->update();

  /////////////////////
  // bullets

  // Fire button was hit
  if (_logic->keyInAction1) {
    if (_logic->_player1->isReadyToFire()) {

      // add new bullet which travels straight
      // *shoot upwards: negative y
      auto bul = std::make_unique<Bullet>();
      bul->setVelo(0, config::BULLET_SPEED_CONST);
      bul->setCurrPos(_logic->_player1->getCurrPos());
      _logic->_bullets.push_back(std::move(bul));

      _logic->_player1->fire();
    }
  }

  // Iterate over all bullets: Update or delete
  if (!_logic->_bullets.empty()) {
    auto iterBullet = _logic->_bullets.begin();

    while (iterBullet != _logic->_bullets.end()) {
      auto PosNew = (*iterBullet)->getNextPos();

      // check: bullet is in the field
      if ((*iterBullet)->isObjOnScreen((*iterBullet)->getNextPos())) {
        // bullet is in the field: Move bullet
        (*iterBullet)->setCurrPos(PosNew);
        iterBullet++;
      } else {
        // bullet out of the field: delete
        iterBullet = _logic->_bullets.erase(iterBullet);
      }
    }
  }

  /////////////////////
  // enemies

  // add new enemies according to current difficulty level
  addEnemy(getLevel());

  // Iterate over all enemies: Update or delete
  if (!_logic->_enemies.empty()) {
    auto iterEnem = _logic->_enemies.begin();
    while (iterEnem != _logic->_enemies.end()) {
      auto PosNew = (*iterEnem)->getNextPos();

      bool deleteEnemy = false;
      // check: enemy is in the field
      if ((*iterEnem)->isObjOnScreen(PosNew)) {
        // Enemy is in the field: Move enemy
        (*iterEnem)->setCurrPos(PosNew);

        // check for collosion with player
        if (_logic->_player1->checkCollision(*(*iterEnem))) {
          std::cout << "Game over!" << std::endl;
          running = false;
        }

        // check enemies for collosion with bullets
        auto iterBullet = _logic->_bullets.begin();
        while (iterBullet != _logic->_bullets.end()) {
          // Was enemy hit bullet
          //  delete enemy and increase score
          if ((*iterEnem)->checkCollision(*(*iterBullet))) {
            deleteEnemy = true;
            this->updateScoreEnemyHit();
            break;
          }
          iterBullet++;
        }
      } else {
        // Enemy not in the field anymore:
        //  delete enemy + update score
        deleteEnemy = true;
        this->updateScoreEnemyPassed();
      }

      if (!deleteEnemy) {
        iterEnem++;
      } else {
        iterEnem = _logic->_enemies.erase(iterEnem);
      }
    }
  }
  // Set Difficulty according to score
  updateLevel();
}

void Game::updateLevel() {
  if (getScore() >= config::DIFFICULTY_LEVEL_SCORE_BASE) {
    // calc dificulty level
    _level = (getScore() - config::DIFFICULTY_LEVEL_SCORE_BASE) /
             config::DIFFICULTY_LEVEL_SCORE_INTERVALL;
  }
}

void Game::addEnemy(int level) {

  static int enemySpornCounter{0};

  // Adjust enemy sporn rate according to difficulty
  _enemySpornIntervall = config::ENEMY_SPORN_INTERVALL_INIT +
                         level * config::ENEMY_SPORN_INTERVALL_LEV_INC;
  // Adjust enemy speed according to difficulty
  _enemySpeed = config::ENEMY_SPEED_INIT + level * config::ENEMY_SPEED_LEV_INC;

  if (enemySpornCounter >= _enemySpornIntervall) {

    // Sporn enemy at random position
    int x_enem = _random_w(engine);
    int y_enem = _random_h(engine);
    auto enem = std::make_unique<Enemy>();
    enem->setVelo(0, _enemySpeed);
    enem->setCurrPos(objPosition_t{x_enem, y_enem});
    _logic->_enemies.push_back(std::move(enem));
    enemySpornCounter = 0;
  }
  enemySpornCounter++;
}

long int Game::getScore() const { return _score; }

void Game::updateScoreEnemyHit() { _score = _score + 1; }

void Game::updateScoreEnemyPassed() {
  if (_score > 0)
    _score = _score - 1;
}