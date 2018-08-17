#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
using namespace std;

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
	K_1,
	K_2,
	K_3,
	K_NUMPAD0,
	K_NUMPAD1,
	K_NUMPAD2,
	K_E,
	K_Q,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_GAME,
    S_COUNT
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
void renderInfo();
void renderCharacter();     // renders the character into the buffer
void renderbulletPRed();
void renderbulletPBlue();
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderbullet();
void shoot(bool &aSomethingHappened, double &g_eBounceTime, double &g_eElapsedTime, int &ShootDirection, SGameChar &g_bullet, SGameChar &g_sChar, int &ShootDirectionFinal, bool &Bulletpos, bool g_abKeyPressed[K_COUNT]);
void shootPRed(bool &aSomethingHappened, double &g_eBounceTime, double &g_eElapsedTime, int &ShootDirection, SGameChar &g_bulletP, SGameChar &g_sChar, int &ShootDirectionFinalRed, bool &BulletposPRed, bool g_abKeyPressed[K_COUNT]);
void shootPBlue(bool &aSomethingHappened, double &g_eBounceTime, double &g_eElapsedTime, int &ShootDirection, SGameChar &g_bulletP, SGameChar &g_sChar, int &ShootDirectionFinalBlue, bool &BulletposPBlue, bool g_abKeyPressed[K_COUNT]);
void movebullet(bool &Bulletpos, int &ShootDirectionFinal, SGameChar &g_bullet, SGameChar &g_portalEntrance, SGameChar &g_portalExit);
void movebulletPRed(bool&, int &ShootDirectionFinalRed, SGameChar &g_bulletP, SGameChar &g_portalEntrance, SGameChar &g_sChar, char **Maze);
void movebulletPBlue(bool &BulletposPBlue, int &ShootDirectionFinalBlue, SGameChar &g_bulletP, SGameChar &g_portalExit, SGameChar &g_sChar, char **Maze);
void information();
void asdf();

bool upcheck(SGameChar);
bool rightcheck(SGameChar Sprite);
bool downcheck(SGameChar Sprite);
bool leftcheck(SGameChar Sprite);
bool upcheckB(SGameChar Sprite);
bool rightcheckB(SGameChar Sprite);
bool downcheckB(SGameChar Sprite);
bool leftcheckB(SGameChar Sprite);
bool bulletcheck(char Character, int &ShootDirection, char **Maze, SGameChar &g_sChar);
void actionshoot(SGameChar &g_sChar, SGameChar &g_bullet, SGameChar &g_bulletP, SGameChar &g_portalEntrance, SGameChar &g_portalExit, bool &aSomethingHappened,
	int &bulletcondition, int &ShootDirection, int &ShootDirectionFinal, bool &Bulletpos, int &ShootDirectionFinalRed, bool &BulletposPRed, int &ShootDirectionFinalBlue,
	bool &BulletposPBlue, char **Maze, double &g_eBounceTime, double &g_eElapsedTime, bool g_abKeyPressed[K_COUNT]);

int bulletAfterPortal();

const int NUM_COLUMNS = 200;
const int NUM_ROWS = 50;
const int MAP_COLUMNS = 135;
const int MAP_ROWS = 33;
const int NUM_OF_KEYS = 10;

struct PlayerInformation 
{
	int Health;
	int Points;
	int CurrentWeapon;
	bool Key[NUM_OF_KEYS];
};

struct Adjacent
{
	COORD AdjacentSides[MAP_COLUMNS];
};

struct KDInformation
{
	bool Checker[NUM_OF_KEYS];
	bool isKey = false;
	int id[NUM_OF_KEYS];
	COORD Location[NUM_OF_KEYS];
	Adjacent Sides[NUM_OF_KEYS];
};

bool doorcheck(KDInformation Item, int ItemNumber);

#endif // _GAME_H