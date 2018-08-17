#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
	K_NUMPAD0,
	K_NUMPAD1,
	K_NUMPAD2,
	K_E,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_GAME,
	S_BOSS,
    S_COUNT
};
enum EGAMEMODES
{	
	S_STAGEONE,
	S_BOSSONE
};
// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderBossChar();      // renders the boss character into the map
void renderbulletPRed();
void renderbulletPBlue();
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderbullet();
void renderBossmap();
void renderBossHealth();
void shoot();
void shootPRed();
void shootPBlue();
void movebullet();
void movebulletPRed();
void movebulletPBlue();
void Bossone();
void Stageone();
bool upcheck(SGameChar Sprite);
bool rightcheck(SGameChar Sprite);
bool downcheck(SGameChar Sprite);
bool leftcheck(SGameChar Sprite);
void renderBossonto();
void bossMove();
void changeMap();
void renderbossattack();
void bossAttackMachineGun();
void bossAttackLazer();
void charshootboss();
void renderShootbossbullet();
void movecharbullet();
#endif // _GAME_H