#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Framework\console.h"
#include "shoot.h"
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
	K_P,
	K_E,
	K_Q,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_GAME,
	S_PAUSE,
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
      // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderPausescreen();
void renderenemy();
void renderInfo();
void renderLegend();
void renderCharacter();     // renders the character into the buffer
void renderbulletPRed();
void renderbulletPBlue();
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderbullet();
void information();

void Bossone();
void Stageone();
void bossMove();
void changeMap();
void bossAttackMachineGun();
void bossAttackLazer();
void charshootboss();
void renderShootbossbullet();
void renderBossChar();
void renderBossmap();
void renderBossHealth();

bool upcheck(SGameChar, char** Maze);
bool rightcheck(SGameChar Sprite, char** Maze);
bool downcheck(SGameChar Sprite, char** Maze);
bool leftcheck(SGameChar Sprite, char** Maze);
bool upcheckB(SGameChar Sprite, char** Maze);
bool rightcheckB(SGameChar Sprite, char** Maze);
bool downcheckB(SGameChar Sprite, char** Maze);
bool leftcheckB(SGameChar Sprite, char** Maze);
void actionshoot(SGameChar&, SGameChar&, SGameChar&, SGameChar&, SGameChar&, bool&, char**, double&, double&);
void shoot(bool&, double&, double&, SGameChar&, SGameChar&);
void shootPRed(bool&, double&, double&, SGameChar&, SGameChar&);
void shootPBlue(bool&, double&, double&, SGameChar&, SGameChar&);
void movebullet(SGameChar&, SGameChar&, SGameChar&, char**);
void movebulletPRed(SGameChar&, SGameChar&, SGameChar&, char**);
void movebulletPBlue(SGameChar&, SGameChar&, SGameChar&, char**);

bool bulletcheck(char, char**, SGameChar&);

void moveenemy(char**, SGameChar&, SGameChar&, int&, int&);
int upenemy(char**, SGameChar&, SGameChar&, int&);
int rightenemy(char**, SGameChar&, SGameChar&, int&);
int downenemy(char**, SGameChar&, SGameChar&, int&);
int leftenemy(char**, SGameChar&, SGameChar&, int&);
void track(char**, SGameChar&, SGameChar&);

int bulletAfterPortal();

const int NUM_COLUMNS = 120;
const int NUM_ROWS = 40;
const int MAP_COLUMNS = 64;
const int MAP_ROWS = 32;
const int NUM_OF_KEYS = 10;
const int LEGEND_COLUMNS = 42;
const int LEGEND_ROWS = 5;
const int GUN_COLUMNS = 27;
const int GUN_ROWS = 8;
const int PORTAL_COLUMNS = 12;
const int PORTAL_ROWS = 12;

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
void moveCharacter(double &g_dBounceTime, double &g_dElapsedTime, SGameChar &g_sChar, Console &g_Console, KDInformation &Key, KDInformation &DoorA,
	char **Maze, PlayerInformation &Player, SGameChar &g_portalEntrance, SGameChar &g_portalExit, int &charbossX, int &charbossY, EGAMEMODES &g_eGamemode);
void pause();
#endif // _GAME_H