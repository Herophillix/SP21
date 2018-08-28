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
extern double g_bossElapsedTime;
const int NUM_COLUMNS = 160;
const int NUM_ROWS = 40;
const int MAP_COLUMNS = 64;
const int MAP_ROWS = 32;
const int MAP2_COLUMNS = 103;
const int MAP2_ROWS = 31;
const int MAP3_COLUMNS = 103;
const int MAP3_ROWS = 31;
const int MAX_NUM_OF_KEYS = 17;
const int LEGEND_COLUMNS = 42;
const int LEGEND_ROWS = 5;
const int CONTROL_COLUMNS = 50;
const int CONTROL_ROWS = 7;
const int GUN_COLUMNS = 27;
const int GUN_ROWS = 8;
const int PORTAL_COLUMNS = 12;
const int PORTAL_ROWS = 12;
const int SPACEGUNSHIP_COLUMNS = 19;
const int SPACEGUNSHIP_ROWS = 10;
const int BOSS_HEALTH = 10;
const int GENERAL_DIRECTION = 2; // RIGHT
const int MAX_NUM_OF_TURRETS_RIGHT = 8;
const int MAX_NUM_OF_TURRETS_DOWN = 11;
const int NUM_OF_ENEMIES = 8;
const int enemylocationX_Level1[NUM_OF_ENEMIES] = { 50,50,50,54,32,31,25 };
const int enemylocationY_Level1[NUM_OF_ENEMIES] = { 29,12,13,3,3,20,17};

const int enemylocationX_Level2[NUM_OF_ENEMIES] = { 34,21,24,54,60,89,54 };
const int enemylocationY_Level2[NUM_OF_ENEMIES] = { 23,26,17,4,25,16,16};

const int enemylocationX_Level3[NUM_OF_ENEMIES] = { 36,82,13,56,19,10,77,100 };
const int enemylocationY_Level3[NUM_OF_ENEMIES] = { 12,25,13,11,23,18,5,25};

								 // Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_ENTER,
	K_SPACE,
	K_NUMPAD0,
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
	S_STAGETWO,
	S_BOSSTWO,
	S_STAGETHREE,
	S_BOSSTHREE,
	S_CREATION
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
	bool Key[MAX_NUM_OF_KEYS];
	string Direction;
};

struct Adjacent
{
	COORD AdjacentSides[MAP_COLUMNS];
};

struct KDInformation
{
	bool Checker[MAX_NUM_OF_KEYS];
	bool isKey = false;
	int id[MAX_NUM_OF_KEYS];
	COORD Location[MAX_NUM_OF_KEYS];
	Adjacent Sides[MAX_NUM_OF_KEYS];
};

struct TurretInformation
{
	SGameChar array_t[MAX_NUM_OF_TURRETS_DOWN];
	SGameChar array_T[MAX_NUM_OF_TURRETS_RIGHT];
	SGameChar array_tbullet[MAX_NUM_OF_TURRETS_DOWN];
	SGameChar array_Tbullet[MAX_NUM_OF_TURRETS_RIGHT];
	bool array_tcheck[MAX_NUM_OF_TURRETS_DOWN];
	bool array_Tcheck[MAX_NUM_OF_TURRETS_RIGHT];
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
void processLoseUserInput();
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderPausescreen();
void renderenemy();
void renderInfo();
void renderLegend();
void renderControl();
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
void initstagethree();

void Boss();
void BossoneVar(double&, double&, double&, SGameChar&, Console&, char**, PlayerInformation&, SGameChar&, SGameChar&, SGameChar&, SGameChar&, SGameChar&, bool&, double(&g_bBounceTime)[6], vector<SGameChar>&, vector<SGameChar>&);
void Stage();
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
void actionshoot(SGameChar&, SGameChar&, SGameChar&, SGameChar&, SGameChar&, bool&, char**, double&, double&);
void shoot(bool&, double&, double&, SGameChar&, SGameChar&, char**);
void shootPRed(bool&, double&, double&, SGameChar&, SGameChar&, char**);
void shootPBlue(bool&, double&, double&, SGameChar&, SGameChar&, char**);
void movebullet(SGameChar&, SGameChar&, SGameChar&, char**);
void movebulletPRed(SGameChar&, SGameChar&, SGameChar&, char**);
void movebulletPBlue(SGameChar&, SGameChar&, SGameChar&, char**);

bool bulletcheck(char, char**, SGameChar&);

void moveenemy(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation &, SGameChar &, EGAMEMODES &);///
int upenemy(double&, double&, char**, SGameChar&, SGameChar&, int&, PlayerInformation&, SGameChar &);///
int rightenemy(double&, double&, char**, SGameChar&, SGameChar&, int&, PlayerInformation&, SGameChar &);///
int downenemy(double&, double&, char**, SGameChar&, SGameChar&, int&, PlayerInformation&, SGameChar &);///
int leftenemy(double&, double&, char**, SGameChar&, SGameChar&, int&, PlayerInformation&, SGameChar &);///
void track(double&, double&, char**, SGameChar&, SGameChar&, int &, PlayerInformation &, SGameChar &);///

void moveenemy1(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &);///
void moveenemy2(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &);///
void moveenemy3(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &, EGAMEMODES &);///
void moveenemy4(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &, EGAMEMODES &);///
void moveenemy5(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &, EGAMEMODES &);///
void moveenemy6(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &, EGAMEMODES &);///
void moveenemy7(double&, double&, char**, SGameChar&, SGameChar&, int&, int&, PlayerInformation&, SGameChar &, EGAMEMODES &);///
void ShootEnemy(SGameChar&, SGameChar&, PlayerInformation&);////
void charIsHit();

int bulletAfterPortal();

bool doorcheck(KDInformation&, int&, KDInformation&, SGameChar&);
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

void renderTbullet(TurretInformation&);
void turretshoott(TurretInformation&, bool&, char**, double&, double&, SGameChar&, SGameChar&, PlayerInformation&, bool&, int&);
void turretshootT(TurretInformation&, bool&, char**, double&, double&, SGameChar&, SGameChar&, PlayerInformation&, bool&, int&);
void Shootturret(SGameChar &, SGameChar(&turretT)[MAX_NUM_OF_TURRETS_RIGHT], SGameChar(&turrett)[MAX_NUM_OF_TURRETS_DOWN], PlayerInformation&);

void score();
void renderScoreScreen();
void renderTopFive();
void currentNameInput(double&, char(&topInitials)[3]);
void renderAlphabets();
void renderCurrentInfo();

#endif // _GAME_H