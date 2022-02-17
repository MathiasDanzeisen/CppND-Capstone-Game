#ifndef CONFIG_H
#define CONFIG_H

namespace config {
    //virtual resolution
    static constexpr int VRES_POINTS_MIN{0};
    static constexpr int VRES_POINTS_MAX{2000};  

    ///////////
    // game config
    static constexpr int  PLAYER_SPEED_INC{1};  // speed increment of player: points per frame
    static constexpr int  BULLET_SPEED_CONST{-10};  // const speed of bullet: points per frame
    // _SPEED_ENEMY: constant speed of the enemy
    static constexpr int  ENEMY_SPEED_INIT{5};  // init value
    static constexpr int  ENEMY_SPEED_LEV_INC{1};  // increment for each difficulty level

    // ENEMY_SPORN_INTERVALL: Enemy is created every x frames
    static constexpr int ENEMY_SPORN_INTERVALL_INIT{50}; // init value
    static constexpr int ENEMY_SPORN_INTERVALL_LEV_INC{-5}; // increment for each difficulty level

    // DIFFICULTY_LEVEL_SCORE: score points which set the difficulty level  
    static constexpr int DIFFICULTY_LEVEL_SCORE_BASE{10};  // base where the difficulty levels start
    static constexpr int DIFFICULTY_LEVEL_SCORE_INTERVALL{10}; // score points needed to set the next level

    ///////////
    // fx config (sizes in Points)
    static constexpr char PLAYER1_GRAPIC_PATH[]{"data/player_skunk1.png"};  //
    static constexpr int PLAYER1_GRAPIC_SIZE{110}; 
    static constexpr char BULLET_GRAPIC_PATH[]{"data/bullet_green_dn_1.png"};
    static constexpr int BULLET_GRAPIC_SIZE{70}; 
    static constexpr char ENEMY_GRAPIC_PATH[]{"data/player_cat_red.png"};
    static constexpr int ENEMY_GRAPIC_SIZE{70}; 
    static constexpr char BACKGROUND_GRAPIC_PATH[]{"data/background_alley-gceda_1920.jpg"};  
    
}
  
#endif