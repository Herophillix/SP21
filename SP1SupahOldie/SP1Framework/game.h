#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Framework\console.h"
#include "shoot.h"
#include "boss.h"
#include "enemy.h"
#include <vector>
using namespace std;

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;
extern bool bridge;
extern bool health;
extern bool characterIsHit;
extern double g_bossElapsedTime;
const int NUM_COLUMNS = 160;
const int NUM_ROWS = 50;
const int MAP_COLUMNS = 64;
const int MAP_ROWS = 32;
const int MAP2_COLUMNS = 103;
const int MAP2_ROWS = 31;
const int NUM_OF_KEYS = 10;
const int LEGEND_COLUMNS = 42;
const int LEGEND_ROWS = 5;
const int GUN_COLUMNS = 27;
const int GUN_ROWS = 8;
const int PORTAL_COLUMNS = 12;
const int PORTAL_ROWS = 12;
const int SPACEGUNSHIP_COLUMNS = 19;
const int SPACEGUNSHIP_ROWS = 10;
const int BOSS_HEALTH = 10;
const int GENERAL_DIRECTION = 2; // RIGHT

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
	K_ENTER,
	K_1,
	K_2,
	K_3,
	K_E,
	K_P,
	K_Q,
	K_R,
	K_W,
	K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_GAME,
	S_PAUSE,
	S_LOSE,
	S_SCORE,
	S_COUNT
};
enum EGAMEMODES
{
	S_STAGEONE,
	S_BOSSONE,
	S_CREATION,
	S_STAGETWO
};
// struct for the game character
struct SGameChar
{
	COORD m_cLocation;
	bool  m_bActive;
};

struct PlayerInformation
{
	int Health;
	int Points;
	int CurrentWeapon;
	bool Key[NUM_OF_KEYS];
	string Direction;
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

void init(void);      // initialize your variables, allocate memory, etc
void getInput(void);      // get input from player
void update(double dt); // update the game and the state of the game
void render(void);      // renders the current state of the game to the console
void shutdown(void);      // do clean up, free memory

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
void playerlose();
void renderLosescreen();

void checkhealth();
void initafterlose();
void initstagetwo();

void Bossone();
void BossoneVar(double&, double&, double&, SGameChar&, Console&, char**, PlayerInformation&, SGameChar&, SGameChar&, SGameChar&, SGameChar&, SGameChar&, bool&, double(&g_bBounceTime)[6], vector<SGameChar>&, vector<SGameChar>&);
void Stageone();
void bossMove(SGameChar&);
void changeMap();
void bossAttackMachineGun(SGameChar&, SGameChar&, SGameChar&);
void bossAttackMachineGunLeft(SGameChar&, SGameChar&, char**, vector<SGameChar>&);
void bossAttackMachineGunRight(SGameChar&, SGameChar&, char**, vector<SGameChar>&);
void bossAttackLazer(SGameChar&, SGameChar&, char**);
void charshootboss(SGameChar&, SGameChar&, bool&, double(&g_bBounceTime)[6], double&, char**);
void renderShootbossbullet();
void renderBossChar();
void renderBossmap();
void renderBossHealth();
SGameChar createBossSubBullet(SGameChar&);

bool upcheck(SGameChar&, char**, char);
bool rightcheck(SGameChar&, char**, char);
bool downcheck(SGameChar&, char**, char);
bool leftcheck(SGameChar&, char**, char);
//bool upcheckB(SGameChar&, char**);
//bool rightcheckB(SGameChar&, char**);
//bool downcheckB(SGameChar&, char**);
//bool leftcheckB(SGameChar&, char**);
void actionshoot(SGameChar&, SGameChar&, SGameChar&, SGameChar&, SGameChar&, bool&, char**, double&, double&);
void shoot(bool&, double&, double&, SGameChar&, SGameChar&);
void shootPRed(bool&, double&, double&, SGameChar&, SGameChar&);
void shootPBlue(bool&, double&, double&, SGameChar&, SGameChar&);
void movebullet(SGameChar&, SGameChar&, SGameChar&, char**);
void movebulletPRed(SGameChar&, SGameChar&, SGameChar&, char**);
void movebulletPBlue(SGameChar&, SGameChar&, SGameChar&, char**);

bool bulletcheck(char, char**, SGameChar&);

void moveenemy(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation &, SGameChar &);
int upenemy(double&, double&, char**, SGameChar&, SGameChar&, int&, PlayerInformation&, SGameChar &);
int rightenemy(double&, double&, char**, SGameChar&, SGameChar&, int&, PlayerInformation&, SGameChar &);
int downenemy(double&, double&, char**, SGameChar&, SGameChar&, int&, PlayerInformation&, SGameChar &);
int leftenemy(double&, double&, char**, SGameChar&, SGameChar&, int&, PlayerInformation&, SGameChar &);
void track(double&, double&, char**, SGameChar&, SGameChar&, int &, PlayerInformation &, SGameChar &);

void moveenemy1(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &);
void moveenemy2(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &);
void moveenemy3(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &);
void moveenemy4(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &);
void moveenemy5(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &);
void moveenemy6(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &);
void ShootEnemy(SGameChar &g_bullet, SGameChar &g_Enemy, PlayerInformation&);

int bulletAfterPortal();

bool doorcheck(KDInformation, int, KDInformation);
void moveCharacter(double&, double&, SGameChar&, Console&, KDInformation&, KDInformation&,
	char**, PlayerInformation&, SGameChar&, SGameChar&, int&, int&, EGAMEMODES&, bool&, double&, int&);
void moveCharacterInBoss(double&, double&, double&, SGameChar&, Console&, char**, PlayerInformation&, bool&);
void pause();

void createCharacter();
void renderCreation();
void changeCharacter(WORD&, unsigned char&, int&, int&, double&, double&, bool&, EGAMEMODES&);
void changeDetail(WORD&, unsigned char&, int&, int&, double&, double&, bool&, EGAMEMODES&);
void renderCreationPreview();
void renderCreationOptions();
void renderCreationDetails();

void score();
void renderScoreScreen();
void renderTopFive();
void currentNameInput(double&, char (&topInitials)[3]);
void renderAlphabets();
void renderCurrentInfo();

void charIsHit();
#endif // _GAME_H