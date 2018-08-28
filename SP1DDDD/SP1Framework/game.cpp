
// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int ShootDirection = GENERAL_DIRECTION;
int bulletcondition = 1;
bool g_abKeyPressed[K_COUNT];
bool bridge = false;
bool health = true;
double g_bossElapsedTime = 0;
int currentHealth;

string line;
string bossmapline;
string aline;
string bossline;
string pauseline;
string createline;
string legendline;
string controlline;
string gunline;
string portalline;
string scoreline;
string stagetwoline;
string stagethreeline;
string loseline;
string spacegunshipline;

WORD charTempColor;
WORD Char = 0x02;
WORD Spaceguncolor = 0x20;
WORD charColor = 0x02;
WORD baseColor = 0x0b;
WORD baseColor2 = 0x0b;
unsigned char charIcon = (char)6;
int  charOption = 0;
int	 charDetail = 0;
bool isDetail = false;
char tempChar;

string topScore[5];
string topName[5] = { "  ", };
string topIcon[5] = { "   ", };
string topColor[5] = { "  ", };
unsigned char topChar[5];
string finalPoints;
char topInitials[3] = { '#', '#', '#' };
int topPoints[5];
bool scoreUpdated = false;


char *BaseMaze[MAP_ROWS];
char *Level1Maze[MAP_ROWS];
char *Level2Maze[MAP2_ROWS];
char *Level3Maze[MAP3_ROWS];
char *SplashMaze[MAP_ROWS];
char *Lose[MAP_ROWS];
char *Score[MAP_ROWS];
char *Pause[MAP_ROWS];
char *Create[MAP_ROWS];
char *Legend[LEGEND_ROWS];
char *Control[CONTROL_ROWS];
char *BossMap[MAP_ROWS];
char *BossChar[27];
char *GunInfo[GUN_ROWS];
char *PortalInfo[PORTAL_ROWS];
char *SpacegunshipInfo[SPACEGUNSHIP_ROWS];

int Rowrender;

bool pausetoggle = false;
bool losetoggle = false;

int KeyonMap = 0;
int DooronMap = 0;
int TurretonMapt = 0;
int TurretonMapT = 0;
int q = 0;
int ItemNumber = 0;
char Character;

bool aSomethingHappened;

PlayerInformation Player;
KDInformation Key, DoorA, Key2, DoorB, Key3, DoorC;

bool g_bStartGame = false;
int g_bStartFrame = 0;

double  g_dElapsedTime;
double  g_eElapsedTime;
double  g_dDeltaTime;
double  g_bBounceTime[6];
double  g_sBounceTime;

// Game specific variables here
TurretInformation Map02, Map03;
//SGameChar turret_t0, turret_t1, turret_t2, turret_t3, turret_t4, turret_t5, turret_t6, turret_t7, turret_t8, turret_t9, turret_t10;
//SGameChar turret_T0, turret_T1, turret_T2, turret_T3, turret_T4, turret_T5, turret_T6, turret_T7;
//SGameChar g_tbullet_t, g_tbullet_t1, g_tbullet_t2, g_tbullet_t3, g_tbullet_t4, g_tbullet_t5, g_tbullet_t6, g_tbullet_t7, g_tbullet_t8, g_tbullet_t9, g_tbullet_t10;
//SGameChar g_tbullet_T, g_tbullet_T1, g_tbullet_T2, g_tbullet_T3, g_tbullet_T4, g_tbullet_T5, g_tbullet_T6, g_tbullet_T7;
//SGameChar turretarrayt[MAX_NUM_OF_TURRETS_DOWN] = { turret_t0, turret_t1, turret_t2, turret_t3, turret_t4, turret_t5, turret_t6, turret_t7, turret_t8, turret_t9, turret_t10 };
//SGameChar turretarrayT[MAX_NUM_OF_TURRETS_RIGHT] = { turret_T0, turret_T1, turret_T2, turret_T3, turret_T4, turret_T5, turret_T6, turret_T7 };
//SGameChar g_turretbulletarrayt[MAX_NUM_OF_TURRETS_DOWN] = { g_tbullet_t, g_tbullet_t1, g_tbullet_t2, g_tbullet_t3, g_tbullet_t4, g_tbullet_t5, g_tbullet_t6, g_tbullet_t7, g_tbullet_t8, g_tbullet_t9, g_tbullet_t10 };
//SGameChar g_turretbulletarrayT[MAX_NUM_OF_TURRETS_RIGHT] = { g_tbullet_T, g_tbullet_T1, g_tbullet_T2, g_tbullet_T3, g_tbullet_T4, g_tbullet_T5, g_tbullet_T6, g_tbullet_T7 };
SGameChar g_enemy, g_enemy1, g_enemy2, g_enemy3, g_enemy4, g_enemy5, g_enemy6,g_enemy7;
SGameChar enemy[] = { g_enemy, g_enemy1, g_enemy2 ,g_enemy3 ,g_enemy4 ,g_enemy5,g_enemy6,g_enemy7 };
SGameChar   g_sChar, g_bullet, g_bulletP, g_portalEntrance, g_portalExit, g_boss, g_bossMainGun, g_bossSubGun1, g_bossSubGun2, g_Wordbullet;
vector <SGameChar> g_bossSubBullet, g_bossSubBullet2;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EGAMEMODES  g_eGamemode = S_CREATION; // starts off with creating character
double  g_dBounceTime;
double  g_eBounceTime;// this is to prevent key bouncing, so we won't trigger keypresses more than once
double g_createBounceTime;

// Console object
Console g_Console(NUM_COLUMNS, NUM_ROWS, "Game");
// Initialisation

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
{
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_eElapsedTime = 0.0;
	g_dBounceTime = 0.0;
	g_eBounceTime = 0.0;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;
	g_Wordbullet.m_cLocation.Y = 1;

	for (int enemynum = 0; enemynum < NUM_OF_ENEMIES; enemynum++)
	{
		enemy[enemynum].m_cLocation.X = enemylocationX_Level1[enemynum];
		enemy[enemynum].m_cLocation.Y = enemylocationY_Level1[enemynum];
		enemy[enemynum].m_bActive = true;
	}

	g_boss.m_cLocation.X = 10;
	g_boss.m_cLocation.Y = 2;

	g_sChar.m_cLocation.X = 2;
	g_sChar.m_cLocation.Y = 3;
	g_sChar.m_bActive = true;
	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");

	ifstream mapOne("map01.txt");
	if (mapOne.is_open())
	{
		for (int i = 0; i < MAP_ROWS; i++)
		{
			BaseMaze[i] = new char[MAP_COLUMNS];
			Level1Maze[i] = new char[MAP_COLUMNS];
			getline(mapOne, line);
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				if ((line[a] == 43) || (line[a] == 124) || (line[a] == 45))
				{
					line[a] = (char)219;
				}
				Level1Maze[i][a] = line[a];
				BaseMaze[i][a] = Level1Maze[i][a];
			}
		}
		for (int i = 0; i < MAP_ROWS; i++)
		{
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				if (BaseMaze[i][a] == 'k')
				{
					Key.Location[KeyonMap].X = a;
					Key.Location[KeyonMap].Y = i + 1;
					switch (KeyonMap)
					{
					case 0:
					{
						Key.id[KeyonMap] = 0;
						break;
					}
					case 1:
					{
						Key.id[KeyonMap] = 1;
						break;
					}
					case 2:
					{
						Key.id[KeyonMap] = 5;
						break;
					}
					case 3:
					{
						Key.id[KeyonMap] = 4;
						break;
					}
					case 4:
					{
						Key.id[KeyonMap] = 2;
						break;
					}
					case 5:
					{
						Key.id[KeyonMap] = 6;
						break;
					}
					case 6:
					{
						Key.id[KeyonMap] = 3;
						break;
					}
					}
					Key.isKey = true;
					KeyonMap++;
				}
				else if (BaseMaze[i][a] == 'd')
				{
					for (int g = i - 1; g > 0; g--) // Up // Check the fucking maze bitch
					{
						if (BaseMaze[g][a] == 'D')
						{
							DoorA.Sides[DooronMap].AdjacentSides[g].X = a;
							DoorA.Sides[DooronMap].AdjacentSides[g].Y = g;
							DoorA.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					for (int f = a + 1; f < MAP_COLUMNS; f++) //Right
					{
						if (BaseMaze[i][f] == 'D')
						{
							DoorA.Sides[DooronMap].AdjacentSides[f].X = f;
							DoorA.Sides[DooronMap].AdjacentSides[f].Y = i;
							DoorA.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					for (int g = i + 1; g < MAP_ROWS; g++) // Down
					{
						if (BaseMaze[g][a] == 'D')
						{
							DoorA.Sides[DooronMap].AdjacentSides[g].X = a;
							DoorA.Sides[DooronMap].AdjacentSides[g].Y = g;
							DoorA.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					for (int f = a - 1; f > 1; f--) // Left
					{
						if (BaseMaze[i][f] == 'D')
						{
							DoorA.Sides[DooronMap].AdjacentSides[f].X = f;
							DoorA.Sides[DooronMap].AdjacentSides[f].Y = i;
							DoorA.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					DoorA.Location[DooronMap].X = a;
					DoorA.Location[DooronMap].Y = i + 1;
					DoorA.id[DooronMap] = DooronMap;
					DoorA.Checker[DooronMap] = false;
					DooronMap++;
				}

			}
		}
		mapOne.close();
	}
	ifstream bossMap("bossmap.txt");
	if (bossMap.is_open())
	{
		for (int i = 0; i < MAP_ROWS; i++)
		{
			BossMap[i] = new char[MAP_COLUMNS];
			getline(bossMap, bossmapline);
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				if ((bossmapline[a] == 43) || (bossmapline[a] == 124) || (bossmapline[a] == 45))
				{
					bossmapline[a] = (char)219;
				}
				else if (bossmapline[a] == 'a')
				{
					bossmapline[a] = (char)176;
				}
				else if (bossmapline[a] == 'A')
				{
					bossmapline[a] = (char)178;
				}
				BossMap[i][a] = bossmapline[a];
			}

		}
		//		if (bossShip = false)
		//		{
		bossMap.close();
		//   	}
	}
	ifstream bossChar("boss.txt");
	if (bossChar.is_open())
	{
		for (int i = 0; i < 11; i++)
		{
			int Columns = 27;
			BossChar[i] = new char[Columns];
			getline(bossChar, bossline);
			for (int a = 0; a < 27; a++)
			{
				BossChar[i][a] = bossline[a];
			}
		}
		bossChar.close();
	}
	ifstream pauseScreen("pausescreen.txt");
	if (pauseScreen.is_open())
	{
		for (int i = 0; i < MAP_ROWS; i++)
		{
			Pause[i] = new char[MAP_COLUMNS];
			getline(pauseScreen, pauseline);
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				if ((pauseline[a] == 43) || (pauseline[a] == 124) || (pauseline[a] == 45))
				{
					pauseline[a] = (char)219;
				}
				Pause[i][a] = pauseline[a];
			}
		}
		pauseScreen.close();
	}
	ifstream loseScreen("losescreen.txt");
	if (loseScreen.is_open())
	{
		for (int i = 0; i < MAP_ROWS; i++)
		{
			Lose[i] = new char[MAP_COLUMNS];
			getline(loseScreen, loseline);
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				if ((loseline[a] == 43) || (loseline[a] == 124) || (loseline[a] == 45))
				{
					if (!((i >= 6 && i <= 19) && (a > 2 && a < 61)))
					{
						loseline[a] = (char)219;
					}
				}
				Lose[i][a] = loseline[a];
			}
		}
		loseScreen.close();
	}
	ifstream legend("legend.txt");
	if (legend.is_open())
	{
		for (int i = 0; i < LEGEND_ROWS; i++)
		{
			Legend[i] = new char[LEGEND_COLUMNS];
			getline(legend, legendline);
			for (int a = 0; a < LEGEND_COLUMNS; a++)
			{
				Legend[i][a] = legendline[a];
			}
		}
		legend.close();
	}
	ifstream control("control.txt");
	if (control.is_open())
	{
		for (int i = 0; i < CONTROL_ROWS; i++)
		{
			Control[i] = new char[CONTROL_COLUMNS];
			getline(control, controlline);
			for (int a = 0; a < CONTROL_COLUMNS; a++)
			{
				Control[i][a] = controlline[a];
			}
		}
		control.close();
	}
	ifstream gunstream("gun.txt");
	if (gunstream.is_open())
	{
		for (int i = 0; i < GUN_ROWS; i++)
		{
			GunInfo[i] = new char[GUN_COLUMNS];
			getline(gunstream, gunline);
			for (int a = 0; a < GUN_COLUMNS; a++)
			{
				GunInfo[i][a] = gunline[a];
			}
		}
		gunstream.close();
	}
	ifstream portalstream("portal.txt");
	if (portalstream.is_open())
	{
		for (int i = 0; i < PORTAL_ROWS; i++)
		{
			PortalInfo[i] = new char[PORTAL_COLUMNS];
			getline(portalstream, portalline);
			for (int a = 0; a < PORTAL_COLUMNS; a++)
			{
				PortalInfo[i][a] = portalline[a];
			}
		}
		portalstream.close();
	}
	ifstream spacegunstream("spacegunship.txt");
	if (spacegunstream.is_open())
	{
		for (int i = 0; i < SPACEGUNSHIP_ROWS; i++)
		{
			SpacegunshipInfo[i] = new char[SPACEGUNSHIP_COLUMNS];
			getline(spacegunstream, spacegunshipline);
			for (int a = 0; a < SPACEGUNSHIP_COLUMNS; a++)
			{
				SpacegunshipInfo[i][a] = spacegunshipline[a];
			}
		}
		portalstream.close();
	}
	ifstream mapTwo("map02.txt");
	if (mapTwo.is_open())
	{
		KeyonMap = 0;
		DooronMap = 0;
		TurretonMapt = 0;
		TurretonMapT = 0;
		for (int i = 0; i < MAP2_ROWS; i++)
		{
			Level2Maze[i] = new char[MAP2_COLUMNS];
			getline(mapTwo, stagetwoline);
			for (int a = 0; a < MAP2_COLUMNS; a++)
			{
				if ((stagetwoline[a] == 43) || (stagetwoline[a] == 124) || (stagetwoline[a] == 45))
				{
					stagetwoline[a] = (char)219;
				}
				if (stagetwoline[a] == 'h')
				{
					stagetwoline[a] = (char)3;
				}
				Level2Maze[i][a] = stagetwoline[a];
			}
		}
		for (int i = 0; i < MAP2_ROWS; i++)
		{
			for (int a = 0; a < MAP2_COLUMNS; a++)
			{
				if (Level2Maze[i][a] == 't')
				{
					Map02.array_t[TurretonMapt].m_bActive = true;
					Map02.array_t[TurretonMapt].m_cLocation.Y = i;
					Map02.array_t[TurretonMapt].m_cLocation.X = a;
					TurretonMapt++;
				}
				if (Level2Maze[i][a] == 'T')
				{
					Map02.array_T[TurretonMapT].m_bActive = true;
					Map02.array_T[TurretonMapT].m_cLocation.Y = i + 1;
					Map02.array_T[TurretonMapT].m_cLocation.X = a;
					TurretonMapT++;
				}
				if (Level2Maze[i][a] == 'k')
				{
					Key2.Location[KeyonMap].X = a;
					Key2.Location[KeyonMap].Y = i + 1;
					switch (KeyonMap)
					{
					case 0:
					{
						Key2.id[KeyonMap] = 0;
						break;
					}
					case 1:
					{
						Key2.id[KeyonMap] = 3;
						break;
					}
					case 2:
					{
						Key2.id[KeyonMap] = 1;
						break;
					}
					case 3:
					{
						Key2.id[KeyonMap] = 2;
						break;
					}
					case 4:
					{
						Key2.id[KeyonMap] = 5;
						break;
					}
					case 5:
					{
						Key2.id[KeyonMap] = 7;
						break;
					}
					case 6:
					{
						Key2.id[KeyonMap] = 6;
						break;
					}
					case 7:
					{
						Key2.id[KeyonMap] = 4;
						break;
					}
					case 8:
					{
						Key2.id[KeyonMap] = 8;
						break;
					}
					}
					Key2.isKey = true;
					KeyonMap++;
				}
				else if (Level2Maze[i][a] == 'd')
				{
					for (int g = i - 1; g > 0; g--) // Up 
					{
						if (Level2Maze[g][a] == 'D')
						{
							DoorB.Sides[DooronMap].AdjacentSides[g].X = a;
							DoorB.Sides[DooronMap].AdjacentSides[g].Y = g;
							DoorB.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					for (int f = a + 1; f < MAP2_COLUMNS; f++) //Right
					{
						if (Level2Maze[i][f] == 'D')
						{
							DoorB.Sides[DooronMap].AdjacentSides[f].X = f;
							DoorB.Sides[DooronMap].AdjacentSides[f].Y = i;
							DoorB.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					for (int g = i + 1; g < MAP2_ROWS; g++) // Down
					{
						if (Level2Maze[g][a] == 'D')
						{
							DoorB.Sides[DooronMap].AdjacentSides[g].X = a;
							DoorB.Sides[DooronMap].AdjacentSides[g].Y = g;
							DoorB.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					for (int f = a - 1; f > 1; f--) // Left
					{
						if (Level2Maze[i][f] == 'D')
						{
							DoorB.Sides[DooronMap].AdjacentSides[f].X = f;
							DoorB.Sides[DooronMap].AdjacentSides[f].Y = i;
							DoorB.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					DoorB.Location[DooronMap].X = a;
					DoorB.Location[DooronMap].Y = i + 1;
					DoorB.id[DooronMap] = DooronMap;
					DoorB.Checker[DooronMap] = false;
					DooronMap++;
				}
			}
		}
	}
	ifstream creationScreen("characterselection.txt");
	if (creationScreen.is_open())
	{
		for (int i = 0; i < MAP_ROWS; i++)
		{
			Create[i] = new char[72];
			getline(creationScreen, createline);
			for (int a = 0; a < 72; a++)
			{
				if (((createline[a] == '-') || (createline[a] == '+') || (createline[a] == '|') || (createline[a] == '_')) && 
					(!((a >=2 && a <= 69) && (i >= 21 && i <= 28))))
				{
					createline[a] = (char)219;
				}
				Create[i][a] = createline[a];
			}
		}
		creationScreen.close();
	}
	ifstream mapThree("map03.txt");
	if (mapThree.is_open())
	{
		KeyonMap = 0;
		DooronMap = 0;
		TurretonMapt = 0;
		TurretonMapT = 0;
		for (int i = 0; i < MAP3_ROWS; i++)
		{
			Level3Maze[i] = new char[MAP3_COLUMNS];
			getline(mapThree, stagethreeline);
			for (int a = 0; a < MAP3_COLUMNS; a++)
			{
				if ((stagethreeline[a] == 43) || (stagethreeline[a] == 124) || (stagethreeline[a] == 45))
				{
					stagethreeline[a] = (char)219;
				}
				if (stagethreeline[a] == 'h')
				{
					stagethreeline[a] = (char)3;
				}
				Level3Maze[i][a] = stagethreeline[a];
			}
		}
		for (int i = 0; i < MAP3_ROWS; i++)
		{
			for (int a = 0; a < MAP3_COLUMNS; a++)
			{
				if (Level3Maze[i][a] == 't')
				{
					Map03.array_t[TurretonMapt].m_bActive = true;
					Map03.array_t[TurretonMapt].m_cLocation.Y = i;
					Map03.array_t[TurretonMapt].m_cLocation.X = a;
					TurretonMapt++;
				}
				if (Level3Maze[i][a] == 'T')
				{
					Map03.array_T[TurretonMapT].m_bActive = true;
					Map03.array_T[TurretonMapT].m_cLocation.Y = i + 1;
					Map03.array_T[TurretonMapT].m_cLocation.X = a;
					TurretonMapT++;
				}
				if (Level3Maze[i][a] == 'k')
				{
					Key3.Location[KeyonMap].X = a;
					Key3.Location[KeyonMap].Y = i + 1;
					switch (KeyonMap)
					{
					case 0:
					{
						Key3.id[KeyonMap] = 10;
						break;
					}
					case 1:
					{
						Key3.id[KeyonMap] = 4;
						break;
					}
					case 2:
					{
						Key3.id[KeyonMap] = 7;
						break;
					}
					case 3:
					{
						Key3.id[KeyonMap] = 6;
						break;
					}
					case 4:
					{
						Key3.id[KeyonMap] = 9;
						break;
					}
					case 5:
					{
						Key3.id[KeyonMap] = 0;
						break;
					}
					case 6:
					{
						Key3.id[KeyonMap] = 2;
						break;
					}
					case 7:
					{
						Key3.id[KeyonMap] = 5;
						break;
					}
					case 8:
					{
						Key3.id[KeyonMap] = 3;
						break;
					}
					case 9:
					{
						Key3.id[KeyonMap] = 8;
						break;
					}
					case 10:
					{
						Key3.id[KeyonMap] = 1;
						break;
					}
					case 11:
					{
						Key3.id[KeyonMap] = 5;
						break;
					}
					case 12:
					{
						Key3.id[KeyonMap] = 8;
						break;
					}
					case 13:
					{
						Key3.id[KeyonMap] = 6;
						break;
					}
					case 14:
					{
						Key3.id[KeyonMap] = 11;
						break;
					}
					case 15:
					{
						Key3.id[KeyonMap] = 4;
						break;
					}
					case 16:
					{
						Key3.id[KeyonMap] = 15;
						break;
					}
					}
					Key3.isKey = true;
					KeyonMap++;
				}
				else if (Level3Maze[i][a] == 'd')
				{
					for (int g = i - 1; g > 0; g--) // Up 
					{
						if (Level3Maze[g][a] == 'D')
						{
							DoorC.Sides[DooronMap].AdjacentSides[g].X = a;
							DoorC.Sides[DooronMap].AdjacentSides[g].Y = g;
							DoorC.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					for (int f = a + 1; f < MAP2_COLUMNS; f++) //Right
					{
						if (Level3Maze[i][f] == 'D')
						{
							DoorC.Sides[DooronMap].AdjacentSides[f].X = f;
							DoorC.Sides[DooronMap].AdjacentSides[f].Y = i;
							DoorC.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					for (int g = i + 1; g < MAP2_ROWS; g++) // Down
					{
						if (Level3Maze[g][a] == 'D')
						{
							DoorC.Sides[DooronMap].AdjacentSides[g].X = a;
							DoorC.Sides[DooronMap].AdjacentSides[g].Y = g;
							DoorC.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					for (int f = a - 1; f > 1; f--) // Left
					{
						if (Level3Maze[i][f] == 'D')
						{
							DoorC.Sides[DooronMap].AdjacentSides[f].X = f;
							DoorC.Sides[DooronMap].AdjacentSides[f].Y = i;
							DoorC.Checker[DooronMap] = false;
						}
						else
						{
							break;
						}
					}
					DoorC.Location[DooronMap].X = a;
					DoorC.Location[DooronMap].Y = i + 1;
					DoorC.id[DooronMap] = DooronMap;
					DoorC.Checker[DooronMap] = false;
					DooronMap++;
				}
			}
		}
	}
	ifstream scoreScreen("scorescreen.txt");
	if (scoreScreen.is_open())
	{
		for (int i = 0; i < 19; i++)
		{
			Score[i] = new char[54];
			getline(scoreScreen, scoreline);
			for (int a = 0; a < 54; a++)
			{
				if (scoreline[a] == '|')
				{
					scoreline[a] = (char)219;
				}
				Score[i][a] = scoreline[a];
			}
		}
		scoreScreen.close();
	}
	Player.Health = 1;
	Player.Points = 0;
	Player.CurrentWeapon = 1;
	Player.Key[MAX_NUM_OF_KEYS] = { 0, };
	Player.Direction = "Right";
	currentHealth = Player.Health;
}

void initafterlose()
{
	/*g_dElapsedTime = 0.0;
	g_eElapsedTime = 0.0;
	g_dBounceTime = 0.0;
	g_eBounceTime = 0.0;*/

	g_Wordbullet.m_cLocation.Y = 1;
	g_enemy.m_bActive = true;

	g_boss.m_cLocation.X = 10;
	g_boss.m_cLocation.Y = 2;

	g_sChar.m_cLocation.X = 2;
	g_sChar.m_cLocation.Y = 3;
	g_sChar.m_bActive = true;
	Player.Health = 1;
	Player.Points = 0;
	Player.CurrentWeapon = 1;
	Player.Key[MAX_NUM_OF_KEYS] = { 0, };
	/*g_bossSubBullet.erase(g_bossSubBullet.begin(), g_bossSubBullet.begin() + g_bossSubBullet.size());
	g_bossSubBullet2.erase(g_bossSubBullet2.begin(), g_bossSubBullet2.begin() + g_bossSubBullet2.size());*/
	for (int bAOPosition = 0; bAOPosition < 3; bAOPosition++)
	{
		bossAttackOn[bAOPosition] = false;
	}
	delete[] * BaseMaze;
	for (int i = 0; i < MAP_ROWS; i++)
	{
		BaseMaze[i] = new char[MAP_COLUMNS];
		for (int a = 0; a < MAP_COLUMNS; a++)
		{
			BaseMaze[i][a] = Level1Maze[i][a];
			if ((BossMap[i][a] == '1') || (BossMap[i][a] == '0'))
			{
				BossMap[i][a] = ' ';
			}
		}
	}
}

void initstagetwo()
{
	bossHealth = BOSS_HEALTH;
	Player.Points += 10000 / ((int)(g_dElapsedTime - g_bossElapsedTime));
	g_sChar.m_cLocation.X = 2;
	g_sChar.m_cLocation.Y = 3;
	g_portalEntrance.m_cLocation.X = 0;
	g_portalEntrance.m_cLocation.Y = 0;
	g_portalExit.m_cLocation.X = 0;
	g_portalExit.m_cLocation.Y = 0;
	for (int enemynum = 0; enemynum < NUM_OF_ENEMIES; enemynum++)
	{
		enemy[enemynum].m_cLocation.X = enemylocationX_Level2[enemynum];
		enemy[enemynum].m_cLocation.Y = enemylocationY_Level2[enemynum];
		enemy[enemynum].m_bActive = true;
	}
	charbossX = 4; // 100 
	charbossY = 3; // 28
}

void initstagethree()
{
	for (int enemynum = 0; enemynum < NUM_OF_ENEMIES; enemynum++)
	{
		enemy[enemynum].m_cLocation.X = enemylocationX_Level3[enemynum];
		enemy[enemynum].m_cLocation.Y = enemylocationY_Level3[enemynum];
		enemy[enemynum].m_bActive = true;
	}
	bossHealth = BOSS_HEALTH;
	Player.Points += 10000 / ((int)(g_dElapsedTime - g_bossElapsedTime));
	g_sChar.m_cLocation.X = 2;
	g_sChar.m_cLocation.Y = 3;
	g_portalEntrance.m_cLocation.X = 0;
	g_portalEntrance.m_cLocation.Y = 0;
	g_portalExit.m_cLocation.X = 0;
	g_portalExit.m_cLocation.Y = 0;
	charbossX = 24;
	charbossY = 28;
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	delete[] * BaseMaze;
	delete[] * Level1Maze;
	delete[] * Level2Maze;
	delete[] * SplashMaze;
	delete[] * Lose;
	delete[] * Pause;
	delete[] * Create;
	delete[] * Legend;
	delete[] * BossMap;
	delete[] * BossChar;
	delete[] * GunInfo;
	delete[] * PortalInfo;
	delete[] * SpacegunshipInfo;
	g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	g_abKeyPressed[K_P] = isKeyPressed(0x50);
	g_abKeyPressed[K_R] = isKeyPressed(0x52);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_eElapsedTime += dt;
	g_dDeltaTime = dt;

	if ((g_sBounceTime < g_dElapsedTime) && (g_eGameState != S_PAUSE))
	{
		Player.Points -= 5;
		g_sBounceTime = g_dElapsedTime + 2.5;
		if (Player.Points < 0)
			Player.Points = 0;
	}

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	case S_PAUSE: pause();
		break;
	case S_SCORE: score();
		break;
	case S_LOSE: playerlose();
		break;
	}
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_abKeyPressed[K_SPACE])
	{
		g_bStartGame = true;
		g_eBounceTime += 0.125;
	}
	if (g_bStartGame == true) // wait for 3 seconds to switch to game mode, else do nothing
		g_eGameState = S_GAME;
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(baseColor);
}

void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
	else if (g_abKeyPressed[K_P])
	{
		if (g_dElapsedTime > g_eBounceTime)
		{
			if (pausetoggle == false)
			{
				pausetoggle = true;
				g_eGameState = S_PAUSE;
			}
			else
			{
				pausetoggle = false;
				g_eGameState = S_GAME;
			}
			g_eBounceTime = g_dElapsedTime + 0.125;
		}
	}
}

void processLoseUserInput()
{
	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
	else if (g_abKeyPressed[K_R])
	{
		g_bQuitGame = true;
		g_eGameState = S_SPLASHSCREEN;
		g_eGamemode = S_STAGEONE;
		initafterlose();
		changeMap();
	}
}

//Rendering

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_GAME: renderGame();
		break;
	case S_PAUSE: renderGame();
		break;
	case S_SCORE: renderGame();
		break;
	case S_LOSE: renderGame();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void renderSplashScreen()  // renders the splash screen
{
	if (g_bStartFrame < 40)
	{
		ifstream splashScreen("Gametitle.txt");
		if (splashScreen.is_open())
		{
			for (int i = 0; i < 29; i++)
			{
				int Columns = 72;
				SplashMaze[i] = new char[Columns];
				getline(splashScreen, line);
				line.resize(72);
				COORD c;
				c.X = 0;
				c.Y = i + 1;

				if (i > 19)
				{
					g_Console.writeToBuffer(c, line, 0x20);
				}
				else if (i == 10)
				{
					for (int a = 0; a < 70; a++)
					{
						if ((a > 22) && (a < 43))
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x0E);
						}
					}
				}
				else if (i > 9)
				{
					for (int a = 0; a < 70; a++)
					{
						if (a < 16)
						{
							switch (line[a])
							{
							case 'x':
							{
								g_Console.writeToBuffer(a, c.Y, line[a], 0x20);
								break;
							}
							case '@':
							{
								g_Console.writeToBuffer(a, c.Y, line[a], 0xc0);
								break;
							}
							case '|':
							{
								g_Console.writeToBuffer(a, c.Y, line[a], 0x60);
								break;
							}
							case '/':
							{
								g_Console.writeToBuffer(a, c.Y, line[a], 0x60);
								break;
							}
							default:
							{
								g_Console.writeToBuffer(a, c.Y, line[a], baseColor);
								break;
							}
							}
						}
						if (a > 15)
						{
							switch (line[a])
							{
							case 1:
							{
								break;
							}
							default:
							{
								g_Console.writeToBuffer(a, c.Y, line[a], baseColor);
								break;
							}
							}
						}
					}
				}

				else if (i > 2)
				{
					for (int a = 0; a < 70; a++)
					{
						switch (line[a])
						{
						case '(':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xBF);
							break;
						}
						case ')':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xBF);
							break;
						}
						case '/':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xBF);
							break;
						}
						case '|':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xBF);
							break;
						}
						case ',':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xBF);
							break;
						}
						case '\'':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xBF);
							break;
						}
						case '\\':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xBF);
							break;
						}
						case '.':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xBB);
							break;
						}
						case '`':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xBF);
							break;
						}
						case '_':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xBF);
							break;
						}
						default:
						{
							g_Console.writeToBuffer(a, c.Y, line[a], baseColor);
							break;
						}
						}
					}
				}
				else if (i < 2)
				{
					for (int a = 0; a < 70; a++)
					{
						switch (line[a])
						{
						case '(':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFB);
							break;
						}
						case ')':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFB);
							break;
						}
						case '_':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFB);
							break;
						}
						case '`':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFB);
							break;
						}
						case '.':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFF);
							break;
						}
						case '\'':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFB);
							break;
						}
						}
					}
				}

				//if (i < 8 && i > 2)
				//{
				//	g_Console.writeToBuffer(c, line, 0x99f);
				//}
			}
			splashScreen.close();
		}
	}
	else
	{
		ifstream splashScreen("Gametitle2.txt");
		if (splashScreen.is_open())
		{
			for (int i = 0; i < 29; i++)
			{
				int Columns = 72;
				SplashMaze[i] = new char[Columns];
				getline(splashScreen, line);

				COORD c;
				c.X = 0;
				c.Y = i + 1;
				if (i > 19)
				{
					g_Console.writeToBuffer(c, line, 0x20);
				}
				else if (i == 10)
				{
					for (int a = 0; a < 70; a++)
					{
						if ((a > 22) && (a < 43))
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x0E);
						}
					}
				}
				else if (i > 9)
				{
					for (int a = 0; a < 70; a++)
					{
						if (a < 16)
						{
							switch (line[a])
							{
							case 'x':
							{
								g_Console.writeToBuffer(a, c.Y, line[a], 0x20);
								break;
							}
							case '@':
							{
								g_Console.writeToBuffer(a, c.Y, line[a], 0xc0);
								break;
							}
							case '|':
							{
								g_Console.writeToBuffer(a, c.Y, line[a], 0x60);
								break;
							}
							case '/':
							{
								g_Console.writeToBuffer(a, c.Y, line[a], 0x60);
								break;
							}
							default:
							{
								g_Console.writeToBuffer(a, c.Y, line[a], baseColor);
								break;
							}
							}
						}
						if (a > 15)
						{
							switch (line[a])
							{
							case 1:
							{
								break;
							}
							default:
							{
								g_Console.writeToBuffer(a, c.Y, line[a], baseColor);
								break;
							}
							}
						}
					}
				}

				else if (i > 3)
				{
					for (int a = 0; a < 70; a++)
					{
						switch (line[a])
						{
						case '(':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x3F);
							break;
						}
						case ')':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x3F);
							break;
						}
						case '/':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x3F);
							break;
						}
						case '|':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x3F);
							break;
						}
						case ',':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x3F);
							break;
						}
						case '\'':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x3F);
							break;
						}
						case '\\':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x3F);
							break;
						}
						case '.':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x33);
							break;
						}
						case '`':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x3F);
							break;
						}
						case '_':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0x3F);
							break;
						}
						default:
						{
							g_Console.writeToBuffer(a, c.Y, line[a], baseColor);
							break;
						}
						}
					}
				}
				else if (i < 2)
				{
					for (int a = 0; a < 70; a++)
					{
						switch (line[a])
						{
						case '(':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFB);
							break;
						}
						case ')':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFB);
							break;
						}
						case '_':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFB);
							break;
						}
						case '`':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFB);
							break;
						}
						case '.':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFF);
							break;
						}
						case '\'':
						{
							g_Console.writeToBuffer(a, c.Y, line[a], 0xFB);
							break;
						}
						}
					}
				}
			}
			splashScreen.close();
		}
	}
	if (g_bStartFrame < 81)
	{
		g_bStartFrame++;
	}
	else
	{
		g_bStartFrame = 0;
	}
}

void renderGame()
{
	if (g_eGameState == S_GAME)
	{
		if (g_eGamemode == S_CREATION)
		{
			renderCreation();
			renderCreationOptions();
			renderCreationPreview();
			renderCreationDetails();
		}
		else if ((g_eGamemode == S_STAGEONE) || (g_eGamemode == S_STAGETWO) || (g_eGamemode == S_STAGETHREE))
		{
			renderMap();        // renders the map to the buffer first 
			renderInfo();
			renderLegend();
			renderControl();
			renderenemy();
			renderCharacter();  // renders the character into the buffer
			renderBossChar();
			renderbullet();
			renderbulletPRed();
			renderbulletPBlue();
			switch (g_eGamemode)
			{
			case S_STAGETWO:
			{
				renderTbullet(Map02);
				break;
			}
			case S_STAGETHREE:
			{
				renderTbullet(Map03);
				break;
			}
			}
		}
		else if ((g_eGamemode == S_BOSSONE) || (g_eGamemode == S_BOSSTWO))
		{
			renderBossmap();
			renderInfo();
			renderLegend();
			renderControl();
			renderCharacter();
			//renderbossattack();
			renderShootbossbullet();
			renderBossHealth();
		}
	}
	else if (g_eGameState == S_PAUSE)
	{
		renderPausescreen();
		renderInfo();
		renderLegend();
		renderControl();
	}
	else if (g_eGameState == S_SCORE)
	{
		renderScoreScreen();
		renderTopFive();
		renderAlphabets();
		renderCurrentInfo();
	}
	else if (g_eGameState == S_LOSE)
	{
		renderLosescreen();
		renderInfo();
		renderLegend();
		renderControl();
	}
}

void renderCreation() // renders tha creation text map
{
	COORD c;
	string acreateline;
	acreateline.resize(72, ' ');
	for (int i = 0; i < MAP_ROWS; i++)
	{
		c.X = 0;
		c.Y = i + 1;
		for (int a = 0; a < 72; a++)
		{
			acreateline[a] = Create[i][a];
		}
		g_Console.writeToBuffer(c, acreateline, baseColor);
	}
}

void renderCreationPreview() // renders the character
{
	g_Console.writeToBuffer(35, 10, charIcon, charColor);
}

void renderCreationOptions() // renders options at left
{
	string colour = "Colour";
	string icon = "Icon";
	string confirm = "Confirm";
	switch (charOption)
	{
	case 0:
	{
		g_Console.writeToBuffer(4, 8, colour, 0x04);
		g_Console.writeToBuffer(4, 10, icon, 0x0e);
		g_Console.writeToBuffer(4, 12, confirm, 0x0e);
		break;
	}
	case 1:
	{
		g_Console.writeToBuffer(4, 8, colour, 0x0e);
		g_Console.writeToBuffer(4, 10, icon, 0x04);
		g_Console.writeToBuffer(4, 12, confirm, 0x0e);
		break;
	}
	case 2:
	{
		g_Console.writeToBuffer(4, 8, colour, 0x0e);
		g_Console.writeToBuffer(4, 10, icon, 0x0e);
		g_Console.writeToBuffer(4, 12, confirm, 0x04);
		break;
	}
	}
}

void renderCreationDetails()
{
	string red = "Red", blue = "Blue", green = "Green", yellow = "Yellow";
	string spade = "Spade", omega = "Omega", coolSymbol = "Cool Symbol", smallDot = "Inaccurate Hit Box";
	switch (charOption)
	{
	case 0:
	{
		if (isDetail == true)
		{
			switch (charDetail)
			{
			case 0:
			{
				g_Console.writeToBuffer(48, 6, red, 0x04);
				g_Console.writeToBuffer(48, 9, blue, 0x0e);
				g_Console.writeToBuffer(48, 12, green, 0x0e);
				g_Console.writeToBuffer(48, 15, yellow, 0x0e);
				break;
			}
			case 1:
			{
				g_Console.writeToBuffer(48, 6, red, 0x0e);
				g_Console.writeToBuffer(48, 9, blue, 0x04);
				g_Console.writeToBuffer(48, 12, green, 0x0e);
				g_Console.writeToBuffer(48, 15, yellow, 0x0e);
				break;
			}
			case 2:
			{
				g_Console.writeToBuffer(48, 6, red, 0x0e);
				g_Console.writeToBuffer(48, 9, blue, 0x0e);
				g_Console.writeToBuffer(48, 12, green, 0x04);
				g_Console.writeToBuffer(48, 15, yellow, 0x0e);
				break;
			}
			case 3:
			{
				g_Console.writeToBuffer(48, 6, red, 0x0e);
				g_Console.writeToBuffer(48, 9, blue, 0x0e);
				g_Console.writeToBuffer(48, 12, green, 0x0e);
				g_Console.writeToBuffer(48, 15, yellow, 0x04);
				break;
			}
			}
		}
		break;
	}
	case 1:
	{
		if (isDetail == true)
		{
			switch (charDetail)
			{
			case 0:
			{
				g_Console.writeToBuffer(48, 6, spade, 0x04);
				g_Console.writeToBuffer(48, 9, omega, 0x0e);
				g_Console.writeToBuffer(48, 12, coolSymbol, 0x0e);
				g_Console.writeToBuffer(48, 15, smallDot, 0x0e);
				break;
			}
			case 1:
			{
				g_Console.writeToBuffer(48, 6, spade, 0x0e);
				g_Console.writeToBuffer(48, 9, omega, 0x04);
				g_Console.writeToBuffer(48, 12, coolSymbol, 0x0e);
				g_Console.writeToBuffer(48, 15, smallDot, 0x0e);
				break;
			}
			case 2:
			{
				g_Console.writeToBuffer(48, 6, spade, 0x0e);
				g_Console.writeToBuffer(48, 9, omega, 0x0e);
				g_Console.writeToBuffer(48, 12, coolSymbol, 0x04);
				g_Console.writeToBuffer(48, 15, smallDot, 0x0e);
				break;
			}
			case 3:
			{
				g_Console.writeToBuffer(48, 6, spade, 0x0e);
				g_Console.writeToBuffer(48, 9, omega, 0x0e);
				g_Console.writeToBuffer(48, 12, coolSymbol, 0x0e);
				g_Console.writeToBuffer(48, 15, smallDot, 0x04);
				break;
			}
			}
		}
		break;
	}
	case 2:
	{
		if (isDetail == true)
		{
			switch (charDetail)
			{
			case 0:
			{
				g_Console.writeToBuffer(48, 8, "Confirm", 0x04);
				g_Console.writeToBuffer(48, 12, "Cancel", 0x0e);
				break;
			}
			case 1:
			{
				g_Console.writeToBuffer(48, 8, "Confirm", 0x0e);
				g_Console.writeToBuffer(48, 12, "Cancel", 0x04);
				break;
			}
			}
		}
		break;
	}
	}
}

void renderenemy()
{
	WORD enemyColor[8] = { 0x0C, };

	for (int i = 0; i < 8; i++)
	{
		if (enemy[i].m_bActive == true)
		{
			enemyColor[i] = 0x0A;
			g_Console.writeToBuffer(enemy[i].m_cLocation, (char)1, enemyColor[i]);
		}
		else
		{
			g_Console.writeToBuffer(enemy[i].m_cLocation, ' ', baseColor);
		}

	}
}

void renderMap()
{
	COORD c;
	string aline;
	switch (g_eGamemode)
	{
	case S_STAGEONE:
	{
		aline.resize(MAP_COLUMNS, ' ');
		Rowrender = MAP_ROWS;
		break;
	}
	case S_BOSSONE:
	{
		aline.resize(MAP_COLUMNS, ' ');
		Rowrender = MAP_ROWS;
		break;
	}
	case S_STAGETWO:
	{
		aline.resize(MAP2_COLUMNS, ' ');
		Rowrender = MAP2_ROWS;
		break;
	}
	case S_BOSSTWO:
	{
		aline.resize(MAP_COLUMNS, ' ');
		Rowrender = MAP_ROWS;
		break;
	}
	case S_STAGETHREE:
	{
		aline.resize(MAP3_COLUMNS, ' ');
		Rowrender = MAP3_ROWS;
		break;
	}
	}
	for (int i = 0; i < Rowrender; i++)
	{
		c.X = 0;
		c.Y = i + 1;
		for (int a = 0; a < (int)aline.size(); a++)
		{
			aline[a] = BaseMaze[i][a];
			if ((aline[a] == 'D') || (aline[a] == 'I'))
			{
				aline[a] = (char)219;
			}
			if (aline[a] == 's')
			{
				aline[a] = char(128);
			}
		}
		g_Console.writeToBuffer(c, aline, baseColor);
		for (int a = 0; a < (int)aline.size(); a++)
		{
			aline[a] = BaseMaze[i][a];
			if (a == g_portalEntrance.m_cLocation.X && i == g_portalEntrance.m_cLocation.Y)
			{
				aline[a] = (char)176;
				g_Console.writeToBuffer(a, i + 1, aline[a], 0x60);
			}
			if (a == g_portalExit.m_cLocation.X && i == g_portalExit.m_cLocation.Y)
			{
				aline[a] = (char)177;
				g_Console.writeToBuffer(a, i + 1, aline[a], 0x1f);
			}
			if (aline[a] == 'k')
			{
				aline[a] = (char)168;
				g_Console.writeToBuffer(a, i + 1, aline[a], 0x0e);
			}
			if (aline[a] == 'd')
			{
				aline[a] = (char)219;
				g_Console.writeToBuffer(a, i + 1, aline[a], 0xe6);
			}
			if (aline[a] == 'w')
			{
				aline[a] = (char)178;
				g_Console.writeToBuffer(a, i + 1, aline[a], 0x91);
			}
			if (aline[a] == (char)240)
			{
				g_Console.writeToBuffer(a, i + 1, aline[a], 0x16);
			}
			if (aline[a] == (char)3)
			{
				if (health == false)
				{
					BaseMaze[i][a] = ' ';
				}
				else
				{
					g_Console.writeToBuffer(a, i + 1, aline[a], 0x0c);
				}
			}
			if (aline[a] == 'b')
			{
				if (bridge == true)
				{
					aline[a] = ' ';
					g_Console.writeToBuffer(a, i + 1, aline[a], baseColor);
				}
				else
				{
					aline[a] = (char)178;
					g_Console.writeToBuffer(a, i + 1, aline[a], baseColor);
				}
			}
			if (aline[a] == 'g')
			{
				if (bridge == true)
				{
					aline[a] = (char)219;
					g_Console.writeToBuffer(a, i + 1, aline[a], baseColor);
				}
				else
				{
					aline[a] = ' ';
					g_Console.writeToBuffer(a, i + 1, aline[a], baseColor);
				}
			}
			if (aline[a] == 'm')
			{
				if (bridge == true)
				{
					aline[a] = ' ';
					g_Console.writeToBuffer(a, i + 1, aline[a], baseColor);
				}
				else
				{
					aline[a] = (char)219;
					g_Console.writeToBuffer(a, i + 1, aline[a], baseColor);
				}
			}
		}
	}
}

void renderPausescreen()
{
	COORD c;
	string pauseline;
	pauseline.resize(MAP_COLUMNS, ' ');
	for (int i = 0; i < MAP_ROWS; i++)
	{
		c.X = 0;
		c.Y = i + 1;
		for (int a = 0; a < MAP_COLUMNS; a++)
		{
			pauseline[a] = Pause[i][a];
			g_Console.writeToBuffer(c, pauseline, baseColor);
		}
	}
}

void renderLosescreen()
{
	COORD c;
	string loseline;
	loseline.resize(MAP_COLUMNS, ' ');
	for (int i = 0; i < MAP_ROWS; i++)
	{
		c.X = 0;
		c.Y = i + 1;
		for (int a = 0; a < MAP_COLUMNS; a++)
		{
			loseline[a] = Lose[i][a];
			g_Console.writeToBuffer(c, loseline, baseColor);
		}
	}
}

void renderBossmap()
{
	COORD c;
	string abossline;
	abossline.resize(MAP_COLUMNS, ' ');

	for (int i = 0; i < MAP_ROWS; i++)
	{
		for (int a = 0; a < MAP_COLUMNS; a++)
		{
			abossline[a] = BossMap[i][a];
			switch (abossline[a])
			{
			case 'x':
			{
				BossMap[i][a] = ' ';
				break;
			}
			case 'v':
			{
				BossMap[i][a] = ' ';
				break;
			}
			case '/':
			{
				BossMap[i][a] = ' ';
				break;
			}
			case '\\':
			{
				BossMap[i][a] = ' ';
				break;
			}
			case '<':
			{
				BossMap[i][a] = ' ';
				break;
			}
			case '>':
			{
				BossMap[i][a] = ' ';
				break;
			}
			}
		}
	}

	for (int i = 0; i < 11; i++)
	{
		for (int a = 0; a < 27; a++)
		{
			if (BossChar[i][a] != ' ')
			{
				BossMap[i + g_boss.m_cLocation.Y][a + g_boss.m_cLocation.X] = BossChar[i][a];
			}
		}
		/*g_Console.writeToBuffer(g_boss.m_cLocation.X, c.Y, bossline, 0x04);*/
	}

	for (int i = 0; i < MAP_ROWS; i++)
	{
		c.X = 0;
		c.Y = i + 1;
		for (int a = 0; a < MAP_COLUMNS; a++)
		{
			abossline[a] = BossMap[i][a];
			switch (abossline[a])
			{
			case '0':
			{
				g_Console.writeToBuffer(a, c.Y, abossline[a], 0xe0);
				break;
			}
			case '1':
			{
				g_Console.writeToBuffer(a, c.Y, abossline[a], 0x40);
				break;
			}
			default:
			{
				g_Console.writeToBuffer(a, c.Y, abossline[a], baseColor);
				break;
			}
			}
		}
	}

	for (int i = 0; i < MAP_ROWS; i++)
	{
		for (int a = 0; a < MAP_COLUMNS; a++)
		{
			abossline[a] = BossMap[i][a];
			switch (abossline[a])
			{
			case '0':
			{
				BossMap[i][a] = ' ';
				break;
			}
			case '1':
			{
				BossMap[i][a] = ' ';
				break;
			}
			}
		}
	}

}

void renderInfo()
{
	int infoIncrement = 3;
	const int infoSize = 5;
	COORD c, a;
	string Info[infoSize] = { "Player Health: ", "Points: ", "Current Weapon: ", "Keys: ", "Direction: " };
	string Number[infoSize] = { to_string(Player.Health), to_string(Player.Points), to_string(Player.CurrentWeapon)," ",Player.Direction };
	int SpriteRow[infoSize] = { 0, 3, 3 + 3, 3 + 3 + 3 + PORTAL_ROWS, 3 + 3 + 3 + 3 + PORTAL_ROWS };
	for (int i = 0; i < MAP_ROWS; i++)
	{
		switch (g_eGamemode)
		{
		case S_STAGEONE: c.X = MAP_COLUMNS + 2;
			break;
		case S_BOSSONE: c.X = MAP_COLUMNS + 2;
			break;
		case S_STAGETWO: c.X = MAP2_COLUMNS + 2;
			break;
		case S_BOSSTWO: c.X = MAP_COLUMNS + 2;
			break;
		case S_STAGETHREE: c.X = MAP3_COLUMNS + 2;
			break;
		}
		c.Y = i + 1;
		int keySpacing = c.X + Info[3].length();
		for (int a = 0; a < infoSize; a++)
		{
			if (i == SpriteRow[a])
			{
				g_Console.writeToBuffer(c, Info[a], baseColor);
				c.X += (short)Info[a].length();
				g_Console.writeToBuffer(c, Number[a], baseColor);
			}
		}
		for (int keyCounter = 0; keyCounter < MAX_NUM_OF_KEYS; keyCounter++)
		{
			if (Player.Key[keyCounter] == true)
			{
				g_Console.writeToBuffer(keySpacing + keyCounter, SpriteRow[3] + 1, (char)168, baseColor);
				keySpacing += 1;
			}
		}
		if (i == 0)
		{
			for (int heartCounter = 0; heartCounter < Player.Health; heartCounter++)
			{
				g_Console.writeToBuffer(c.X + (heartCounter * 2), c.Y + 1, (char)3, 0x04);
			}
		}
		//if (i < infoSize * infoIncrement)
		//{
		//	g_Console.writeToBuffer(c, Info[i / infoIncrement], 0xe2);
		//	c.X += Info[i / infoIncrement].length();
		//	keySpacing += Info[3].length();
		//	g_Console.writeToBuffer(c, Number[i / infoIncrement], 0xe2);
		//	for (int keyCounter = 0; keyCounter < NUM_OF_KEYS; keyCounter++)
		//	{
		//		if (Player.Key[keyCounter] == true)
		//		{
		//			g_Console.writeToBuffer(keySpacing + keyCounter, (3 + 1) * infoIncrement - 2 + GUN_ROWS, (char)168, 0xe2);
		//			keySpacing += 1;
		//		}
		//	}
		//}
	}
	if ((g_eGamemode == S_BOSSONE) || (g_eGamemode == S_BOSSTWO))
	{
		int ColorNumber;
		for (int b = 0; b < SPACEGUNSHIP_ROWS; b++)
		{
			a.X = MAP_COLUMNS + 2;
			a.Y = SpriteRow[2] + 1;
			for (int yt = 0; yt < SPACEGUNSHIP_COLUMNS; yt++)
			{
				spacegunshipline[yt] = SpacegunshipInfo[b][yt];
				if (yt == 9 && (b >= 2 && b <= 8))
				{
					switch (Char)
					{
					case 0x02:
					{
						ColorNumber = 0;
						break;
					}
					case 0x03:
					{
						ColorNumber = 1;
						break;
					}
					case 0x01:
					{
						ColorNumber = 2;
						break;
					}
					case 0x05:
					{
						ColorNumber = 3;
						break;
					}
					case 0x04:
					{
						ColorNumber = 4;
						break;
					}
					case 0x06:
					{
						ColorNumber = 5;
						break;
					}
					}
					WORD Spaceguncolore[] = { 0x20,0x30,0x10,0x50,0x40,0x60 };
					for (ColorNumber; ColorNumber >= 0; ColorNumber--)
					{
						g_Console.writeToBuffer(a.X + yt, a.Y + 9 - ColorNumber, spacegunshipline[yt], Spaceguncolor);
					}
				}
				else
				{
					g_Console.writeToBuffer(a.X + yt, a.Y + b + 1, spacegunshipline[yt], baseColor);
				}
			}
		}
	}
	else if (bulletcondition == 1)
	{
		for (int b = 0; b < GUN_ROWS; b++)
		{
			switch (g_eGamemode)
			{
			case S_STAGEONE: a.X = MAP_COLUMNS + 2;
				break;
			case S_BOSSONE: a.X = MAP_COLUMNS + 2;
				break;
			case S_STAGETWO: a.X = MAP2_COLUMNS + 2;
				break;
			case S_BOSSTWO: a.X = MAP2_COLUMNS + 2;
				break;
			case S_STAGETHREE: a.X = MAP3_COLUMNS + 2;
				break;
			}
			a.Y = SpriteRow[2] + 1;
			for (int yt = 0; yt < GUN_COLUMNS; yt++)
			{
				gunline[yt] = GunInfo[b][yt];
				g_Console.writeToBuffer(a.X + yt, a.Y + b + 1, gunline[yt], baseColor);
			}
		}
	}
	else if ((bulletcondition == 2) || (bulletcondition == 3))
	{
		for (int b = 0; b < PORTAL_ROWS; b++)
		{
			if ((g_eGamemode == S_STAGEONE) || (g_eGamemode == S_BOSSONE) || (g_eGamemode == S_BOSSTWO))
			{
				a.X = MAP_COLUMNS + 2;
			}
			else if (g_eGamemode == S_STAGETWO)
			{
				a.X = MAP2_COLUMNS + 2;
			}
			else if (g_eGamemode == S_STAGETHREE)
			{
				a.X = MAP3_COLUMNS + 2;
			}
			a.Y = SpriteRow[2] + 1;

			for (int yt = 0; yt < PORTAL_COLUMNS; yt++)
			{
				portalline[yt] = PortalInfo[b][yt];
				g_Console.writeToBuffer(a.X + yt, a.Y + b + 1, portalline[yt], baseColor);
				if (bulletcondition == 2)
				{
					if ((yt >= 3 && yt <= 8) && ((b >= 4 && b <= 8)))
					{
						g_Console.writeToBuffer(a.X + yt, a.Y + b + 1, portalline[yt], 0x6f);
					}
				}
				else if (bulletcondition == 3)
				{
					if ((yt >= 3 && yt <= 8) && ((b >= 4 && b <= 8)))
					{
						g_Console.writeToBuffer(a.X + yt, a.Y + b + 1, portalline[yt], 0x1f);
					}
				}
			}
		}
	}
}

void renderLegend()
{
	for (int i = 0; i < LEGEND_ROWS; i++)
	{
		COORD c;
		c.X = 1;
		if ((g_eGamemode == S_STAGEONE) || (g_eGamemode == S_BOSSONE) || (g_eGamemode == S_BOSSTWO))
		{
			c.Y = MAP_ROWS + i + 2;
		}
		else if (g_eGamemode == S_STAGETWO)
		{
			c.Y = MAP2_ROWS + i + 2;
		}
		else if (g_eGamemode == S_STAGETHREE)
		{
			c.Y = MAP3_ROWS + i + 2;
		}
		legendline.resize(LEGEND_COLUMNS, ' ');
		for (int a = 0; a < LEGEND_COLUMNS; a++)
		{
			legendline[a] = Legend[i][a];
			g_Console.writeToBuffer(c, legendline, baseColor);
		}
		for (int a = 0; a < LEGEND_COLUMNS; a++)
		{
			legendline[a] = Legend[i][a];
			if (legendline[a] == '1')
			{
				legendline[a] = charIcon;
				g_Console.writeToBuffer(c.X, c.Y, legendline[a], charColor);
			}
			else if (legendline[a] == '2')
			{
				legendline[a] = (char)168;
				g_Console.writeToBuffer(c.X, c.Y, legendline[a], 0x0e);
			}
			else if (legendline[a] == '3')
			{
				legendline[a] = (char)1;
				g_Console.writeToBuffer(c.X, c.Y, legendline[a], 0x0A);
			}
			else if (legendline[a] == '4')
			{
				legendline[a] = (char)64;
				g_Console.writeToBuffer(c.X, c.Y, legendline[a]);
			}
			else if (legendline[a] == '5')
			{
				legendline[a] = (char)219;
				g_Console.writeToBuffer(c.X + a, c.Y, legendline[a], baseColor);
			}
			else if (legendline[a] == '6')
			{
				legendline[a] = (char)219;
				g_Console.writeToBuffer(c.X + a, c.Y, legendline[a], 0xe6);
			}
			else if (legendline[a] == '7')
			{
				legendline[a] = (char)176;
				g_Console.writeToBuffer(c.X + a, c.Y, legendline[a], 0x40);
			}
			else if (legendline[a] == '8')
			{
				legendline[a] = (char)177;
				g_Console.writeToBuffer(c.X + a, c.Y, legendline[a], 0x1f);
			}
		}
	}

}

void renderScoreScreen()
{
	COORD c;
	scoreline.resize(MAP_COLUMNS, ' ');
	for (int i = 0; i < 19; i++)
	{
		c.X = 0;
		c.Y = i + 1;
		for (int a = 0; a < 54; a++)
		{
			scoreline[a] = Score[i][a];
			g_Console.writeToBuffer(c, scoreline, baseColor);
		}
	}
}

void renderTopFive()
{
	COORD Initials;
	COORD Points;
	COORD Icon;
	Initials.X = 9;
	Initials.Y = 12;
	Points.X = 34;
	Points.Y = 12;
	Icon.X = 23;
	Icon.Y = 12;
	for (int i = 0; i < 5; i++, Points.Y++, Initials.Y++, Icon.Y++)
	{
		Initials.X = 9;
		Points.X = 34;
		Icon.X = 23;
		if (topName[i] != "")//initals - 3 letters
		{
			for (int j = 0; j < 3; j++, Initials.X += 2)
			{
				g_Console.writeToBuffer(Initials, topName[i][j], baseColor);
			}
		}
		for (int j = 0; j < 6; j++) // set top 5 scores to printable form
		{
			if (topScore[i][j] == ' ')
			{
				topScore[i] = topScore[i].substr(0, j);
				j = 6;
			}
		}
		for (int j = 0; j < 6; j++, Points.X += 2) // print top 5 scores
		{
			while (topScore[i].length() < 6)
			{
				topScore[i] = "0" + topScore[i];
			}
			g_Console.writeToBuffer(Points, topScore[i][j], baseColor);
		}

		g_Console.writeToBuffer(Icon, topChar[i], stoi(topColor[i], nullptr, 16)); //print icons
	}
}

void renderAlphabets()
{
	COORD c;
	c.X = 23;
	c.Y = 5;

	for (int i = 0; i < 3; i++, c.X += 3)
	{
		if (topInitials[i] == '#')
			g_Console.writeToBuffer(c, '_', baseColor);
		else
			g_Console.writeToBuffer(c, topInitials[i], baseColor);
	}
}

void renderCurrentInfo()
{
	COORD c;
	c.X = 26;
	c.Y = 6;
	COORD d;
	d.X = 26;
	d.Y = 7;

	//for (int i = 0; i < 6; i++)
	//{
	//	if (finalPoints[i] == ' ')
	//	{
	//		finalPoints = finalPoints.substr(0, i);
	//		i = 6;
	//	}
	//}

	for (int i = 0; i < 6; i++, c.X += 2)
	{
		while (finalPoints.length() < 6)
		{
			finalPoints = "0" + finalPoints;
		}
		g_Console.writeToBuffer(c, finalPoints[i], baseColor);
	}

	g_Console.writeToBuffer(d, charIcon, charColor);

}

void renderControl()
{
	for (int i = 0; i < CONTROL_ROWS; i++)
	{
		COORD c;	
		if ((g_eGamemode == S_STAGEONE) || (g_eGamemode == S_BOSSONE) || (g_eGamemode == S_BOSSTWO))
		{
			c.X = MAP_COLUMNS + 2;
		}
		else if (g_eGamemode == S_STAGETWO)
		{
			c.X = MAP2_COLUMNS + 2;
		}
		else if (g_eGamemode == S_STAGETHREE)
		{
			c.X = MAP3_COLUMNS + 2;
		}
		c.Y = 3 + 3 + 3 + 3 + 3 + PORTAL_ROWS + i;
		controlline.resize(CONTROL_COLUMNS, ' ');
		for (int a = 0; a < CONTROL_COLUMNS; a++)
		{
			controlline[a] = Control[i][a];
			g_Console.writeToBuffer(c, controlline, baseColor);
		}
	}
}

void renderCharacter()
{
	// Draw the location of the character
	if ((g_eGamemode == S_STAGEONE) || (g_eGamemode == S_STAGETWO) || (g_eGamemode == S_STAGETHREE))
	{
		if (characterIsHit == true)
		{
			playerIsHitFrame++;
			if (playerIsHitFrame % 10 == 0)
			{
				if (charColor == charTempColor)
				{
					charColor = 0x00;
				}
				else
				{
					charColor = charTempColor;
				}
			}
			if (playerIsHitFrame > 100)
			{
				characterIsHit = false;
				playerIsHitFrame = 0;
			}
			g_Console.writeToBuffer(g_sChar.m_cLocation, charIcon, charColor);
		}
		else
		{
			charColor = charTempColor;
			g_Console.writeToBuffer(g_sChar.m_cLocation, charIcon, charColor);
		}
	}
	else if ((g_eGamemode == S_BOSSONE) || (g_eGamemode == S_BOSSTWO))
	{
		if (characterIsHit == true)
		{
			playerIsHitFrame++;
			if (playerIsHitFrame % 10 == 9)
			{
				if (charColor == 0x02)
				{
					g_Console.writeToBuffer(g_sChar.m_cLocation, charIcon, 0x0);
				}
				else
				{
					g_Console.writeToBuffer(g_sChar.m_cLocation, charIcon, charColor);
				}
			}
			if (playerIsHitFrame > 100)
			{
				characterIsHit = false;
				playerIsHitFrame = 0;
			}
		}
		else
		{
			g_Console.writeToBuffer(g_sChar.m_cLocation, charIcon, charColor);
		}
	}
}

void renderShootbossbullet()
{
	if (charWordBulletHold == true)
	{
		for (int i = 5; i >= -1; i--)
		{
			if (g_dElapsedTime > g_bBounceTime[i])
			{
				switch (i)
				{
				case 0:
				{
					Char = 0x03;
					Spaceguncolor = 0x30;
					charWordBulletCharge = i + 1;
					i = -2;
					break;
				}
				case 1:
				{
					Char = 0x01;
					Spaceguncolor = 0x10;
					charWordBulletCharge = i + 1;
					i = -2;
					break;
				}
				case 2:
				{
					Char = 0x05;
					Spaceguncolor = 0x50;
					charWordBulletCharge = i + 1;
					i = -2;
					break;
				}
				case 3:
				{
					Char = 0x04;
					Spaceguncolor = 0x40;
					charWordBulletCharge = i + 1;
					i = -2;
					break;
				}
				case 4:
				{
					Char = 0x06;
					Spaceguncolor = 0x60;
					charWordBulletCharge = i + 1;
					i = -2;
					break;
				}
				case 5:
				{
					Char = 0x06;
					Spaceguncolor = 0x60;
					charWordBulletCharge = i;
					charWordBulletHold = false;
					charWordBulletTimeout = true;
					i = -2;
					break;
				}
				}

				if (i == -1)
				{
					Char = 0x02;
					Spaceguncolor = 0x20;
					charWordBulletCharge = 0;
				}
			}
		}
	}
	if (charWordBullet == true)
	{
		g_Console.writeToBuffer(g_Wordbullet.m_cLocation, (char)254, Char);
	}
}

void renderbullet()
{
	if (Bulletpos == true)
	{
		WORD Char = baseColor;
		g_Console.writeToBuffer(g_bullet.m_cLocation, (char)254, Char);
	}
}

void renderbulletPRed()
{
	if (BulletposPRed == true)
	{
		WORD Char = 0x40;
		g_Console.writeToBuffer(g_bulletP.m_cLocation, (char)254, Char);
	}
}

void renderbulletPBlue()
{
	if (BulletposPBlue == true)
	{
		WORD Char = 0x1F;
		g_Console.writeToBuffer(g_bulletP.m_cLocation, (char)254, Char);
	}
}

void renderTbullet(TurretInformation& Map)
{
	WORD Char = 0x08;
	for (int TurretBullett = 0; TurretBullett < MAX_NUM_OF_TURRETS_DOWN; TurretBullett++)
	{
		g_Console.writeToBuffer(Map.array_tbullet[TurretBullett].m_cLocation, (char)254, Char);
		if (Map.array_tbullet[TurretBullett].m_bActive == false)
		{
			g_Console.writeToBuffer(Map.array_tbullet[TurretBullett].m_cLocation, ' ', baseColor);
		}
	}
	for (int TurretBulletT = 0; TurretBulletT < MAX_NUM_OF_TURRETS_RIGHT; TurretBulletT++)
	{
		g_Console.writeToBuffer(Map.array_Tbullet[TurretBulletT].m_cLocation, (char)254, Char);
		if (Map.array_Tbullet[TurretBulletT].m_bActive == false)
		{
			g_Console.writeToBuffer(Map.array_Tbullet[TurretBulletT].m_cLocation, ' ', baseColor);
		}
	}
}

void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x59);
}

void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}

void renderBossChar()
{
	//render boss @ location onto first map 
	g_Console.writeToBuffer(charbossX, charbossY, (char)64);
}

void renderBossHealth()
{
	COORD c;
	string bossline;
	for (int i = 1; i < 5; i++)
	{
		bossline.resize(22, ' ');
		c.Y = i + 1;
		switch (i)
		{
		case 1:
		{
			bossline = "   Boss HP (" + to_string(bossHealth) + "/" + to_string(bossMaxHealth) + ")  ";
			while (bossline.length() <= 21)
			{
				bossline += ' ';
			}
			if (bossline.length() >= 23)
			{
				bossline = bossline.substr(0, 22);
			}
			g_Console.writeToBuffer(20, c.Y, bossline, 0xF0);
			break;
		}
		case 2:
		{
			for (int a = 20; a < 42; a++)
			{

				switch (a)
				{
				case 20:
				{
					g_Console.writeToBuffer(20, c.Y, bossline[a - 20], 0xFF);
					break;
				}
				case 41:
				{
					g_Console.writeToBuffer(a, c.Y, bossline[a - 20], 0xFF);
					break;
				}
				default:
				{
					if (((bossHealth * 20) / bossMaxHealth) >= (a - 20))
					{
						g_Console.writeToBuffer(a, c.Y, bossline[a - 20], 0x44);
					}
					else
					{
						g_Console.writeToBuffer(a, c.Y, bossline[a - 20], 0x00);
					}
					break;
				}
				}
			}
			break;
		}
		case 3:
		{
			g_Console.writeToBuffer(20, c.Y, bossline, 0xFF);
			break;
		}
		case 4:
		{
			if (bossHealth <= 0)
			{
				switch (g_eGamemode)
				{
				case S_BOSSONE:
				{
					g_eGamemode = S_STAGETWO;
					initstagetwo();
					break;
				}
				case S_BOSSTWO:
				{
					g_eGamemode = S_STAGETHREE;
					initstagethree();
					break;
				}
				}
				changeMap();
			}
			break;

		}
		}

	}
}

//Gameplay

void gameplay()            // gameplay logic
{
	switch (g_eGamemode)
	{
	case S_CREATION: createCharacter();
		break;
	case S_STAGEONE: Stage();
		break;
	case S_BOSSONE: Boss();
		break;
	case S_STAGETWO: Stage();
		break;
	case S_BOSSTWO: Boss();
		break;
	case S_STAGETHREE: Stage();
		break;
	}
}

void createCharacter()
{
	changeCharacter(charColor, charIcon, charOption, charDetail, g_createBounceTime, g_dElapsedTime, isDetail, g_eGamemode);
	charTempColor = charColor;
	Player.Points = 2500;
}

void Stage()
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exitmoveenemy(Maze, g_enemy, g_sChar, timer, Direction,Player,g_bullet);
	moveenemy(g_eBounceTime, g_dElapsedTime, BaseMaze, enemy[0], g_sChar, timer, Direction, Player, g_bullet, g_eGamemode);
	moveenemy1(g_eBounceTime, g_dElapsedTime, BaseMaze, enemy[1], g_sChar, timer1, one, Player, g_bullet);
	moveenemy2(g_eBounceTime, g_dElapsedTime, BaseMaze, enemy[2], g_sChar, timer2, two, Player, g_bullet);
	moveenemy3(g_eBounceTime, g_dElapsedTime, BaseMaze, enemy[3], g_sChar, timer, Direction3, Player, g_bullet, g_eGamemode);
	moveenemy4(g_eBounceTime, g_dElapsedTime, BaseMaze, enemy[4], g_sChar, timer, Direction4, Player, g_bullet, g_eGamemode);
	moveenemy5(g_eBounceTime, g_dElapsedTime, BaseMaze, enemy[5], g_sChar, timer, Direction5, Player, g_bullet, g_eGamemode);
	moveenemy6(g_eBounceTime, g_dElapsedTime, BaseMaze, enemy[6], g_sChar, timer, Direction6, Player, g_bullet, g_eGamemode);
	moveenemy7(g_eBounceTime, g_dElapsedTime, BaseMaze, enemy[7], g_sChar, timer, Direction7, Player, g_bullet, g_eGamemode);
	actionshoot(g_sChar, g_bullet, g_bulletP, g_portalEntrance, g_portalExit, aSomethingHappened, BaseMaze, g_eBounceTime, g_eElapsedTime);
	if (g_eGamemode == S_STAGEONE)
	{
		moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key, DoorA, BaseMaze, Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode, characterIsHit, g_eBounceTime, currentHealth);
	}
	if (g_eGamemode == S_STAGETWO)
	{
		moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key2, DoorB, BaseMaze, Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode, characterIsHit, g_eBounceTime, currentHealth);
		turretshoott(Map02, aSomethingHappened, BaseMaze, g_eBounceTime, g_eElapsedTime, g_sChar, g_bullet, Player, characterIsHit, currentHealth);
		turretshootT(Map02, aSomethingHappened, BaseMaze, g_eBounceTime, g_eElapsedTime, g_sChar, g_bullet, Player, characterIsHit, currentHealth);
	}
	else if (g_eGamemode == S_STAGETHREE)
	{
		moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key3, DoorC, BaseMaze, Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode, characterIsHit, g_eBounceTime, currentHealth);
		turretshoott(Map03, aSomethingHappened, BaseMaze, g_eBounceTime, g_eElapsedTime, g_sChar, g_bullet, Player, characterIsHit, currentHealth);
		turretshootT(Map03, aSomethingHappened, BaseMaze, g_eBounceTime, g_eElapsedTime, g_sChar, g_bullet, Player, characterIsHit, currentHealth);
	}
	information();
	charIsHit();
	checkhealth();
}

void Boss()
{
	BossoneVar(g_dBounceTime, g_eBounceTime, g_dElapsedTime, g_sChar, g_Console, BossMap, Player, g_bossMainGun, g_boss,
		g_bossSubGun1, g_bossSubGun2, g_Wordbullet, charWordBullet, g_bBounceTime, g_bossSubBullet, g_bossSubBullet2);
} 

void information()
{
	Player.CurrentWeapon = bulletcondition;
}

void changeMap()
{
	switch (g_eGameState)
	{
	case S_GAME:
	{
		switch (g_eGamemode)
		{
		case S_STAGEONE:
		{
			delete[] * BaseMaze;
			*BaseMaze = new char[MAP_COLUMNS];
			for (int i = 0; i < MAP_ROWS; i++)
			{
				for (int a = 0; a < MAP_COLUMNS; a++)
				{
					BaseMaze[i][a] = Level1Maze[i][a];
				}
			}
			break;
		}
		case S_BOSSONE:
		{
			delete[] * BaseMaze;
			*BaseMaze = new char[MAP_COLUMNS];
			g_sChar.m_cLocation.X = 32;
			g_sChar.m_cLocation.Y = 30;
			for (int i = 0; i < MAP_ROWS; i++)
			{
				for (int a = 0; a < MAP_COLUMNS; a++)
				{
					BaseMaze[i][a] = BossMap[i][a];
				}
			}
			break;
		}
		case S_STAGETWO:
		{
			delete[] * BaseMaze;
			*BaseMaze = new char[MAP2_COLUMNS];
			for (int i = 0; i < MAP2_ROWS; i++)
			{
				for (int a = 0; a < MAP2_COLUMNS; a++)
				{
					BaseMaze[i][a] = Level2Maze[i][a];
				}
			}
			break;
		}
		case S_BOSSTWO:
		{
			delete[] * BaseMaze;
			*BaseMaze = new char[MAP_COLUMNS];
			for (int i = 0; i < MAP_ROWS; i++)
			{
				for (int a = 0; a < MAP_COLUMNS; a++)
				{
					BaseMaze[i][a] = BossMap[i][a];
				}
			}
			break;
		case S_STAGETHREE:
		{
			delete[] * BaseMaze;
			*BaseMaze = new char[MAP3_COLUMNS];
			for (int i = 0; i < MAP3_ROWS; i++)
			{
				for (int a = 0; a < MAP3_COLUMNS; a++)
				{
					BaseMaze[i][a] = Level3Maze[i][a];
				}
			}
			break;
		}
		break;
		}
		}
	}
	}
}

void pause()
{
	processUserInput();
}

void playerlose()
{
	processLoseUserInput();
}

void checkhealth()
{
	if (Player.Health == 0)
	{
		finalPoints = to_string(Player.Points);

		ifstream highScore("highscore.txt");
		string scoreLine;
		if (highScore.is_open())
		{
			for (int i = 0; i < 5; i++)
			{
				getline(highScore, scoreLine);
				topScore[i].resize(6, ' ');
				topName[i].resize(3, '~');
				topIcon[i].resize(3, '0');
				topColor[i].resize(2, '0');
				for (int j = 0; j < 3; j++)
				{
					topName[i][j] = scoreLine[j];
				}
				for (int j = 3; j < 9; j++)
				{
					topScore[i][j - 3] = scoreLine[j];
				}
				topPoints[i] = stoi(topScore[i], nullptr, 10);
				for (int j = 9; j < 12; j++)
				{
					topIcon[i][j - 9] = scoreLine[j];
				}
				topChar[i] = (unsigned char)stoi(topIcon[i], nullptr, 10);
				for (int j = 12; j < 14; j++)
				{
					topColor[i][j - 12] = scoreLine[j];
				}
			}
		}
		g_eGameState = S_SCORE;
	}
}

void charIsHit()/////////////////////
{
	if (currentHealth > Player.Health)
	{
		Player.Points -= 500;
		currentHealth = Player.Health;
		characterIsHit = true;
		g_eBounceTime = g_dElapsedTime + 2;// immunity time after getting hit by boss
	}
}

void score()
{
	if (scoreUpdated == false)
	{
		currentNameInput(g_dElapsedTime, topInitials);
		if ((topInitials[2] != '#') && (g_abKeyPressed[K_ENTER]))
		{
			int playerPosition = 6;
			int newTopStorage[5];
			string tempTopString[5];
			string tempOldString[5];
			string tempIconString[5];
			string tempIconChar = to_string((int)charIcon);
			string tempColorString[5];
			bool playerTop = false;

			while (tempIconChar.length() < 3)
			{
				tempIconChar = "0" + tempIconChar;
			}

			stringstream charStream;
			charStream << hex << charColor;
			string tempCharColor(charStream.str());

			while (tempCharColor.length() < 2)
			{
				tempCharColor = "0" + tempCharColor;
			}

			for (int i = 0; i < 5; i++)
			{
				if ((playerTop == true))
				{
					if (i != 4)
					{
						newTopStorage[i + 1] = topPoints[i];
					}
				}
				else if ((stoi(finalPoints, nullptr, 10) >= topPoints[i]) && (playerTop == false))
				{
					newTopStorage[i + 1] = topPoints[i];
					newTopStorage[i] = stoi(finalPoints, nullptr, 10);
					playerPosition = i;
					playerTop = true;
				}
				else
				{
					newTopStorage[i] = topPoints[i];
				}
			}
			for (int i = 0; i < 5; i++)
			{
				tempTopString[i] = to_string(newTopStorage[i]);
				tempOldString[i] = to_string(topPoints[i]);
				tempIconString[i] = to_string((int)topChar[i]);

				stringstream charStream;
				charStream << hex << stoi(topColor[i], nullptr, 16);
				string streamResult(charStream.str());

				tempColorString[i] = streamResult;

				while (tempTopString[i].length() < 6)
				{
					tempTopString[i] = "0" + tempTopString[i];
				}
				while (tempOldString[i].length() < 6)
				{
					tempOldString[i] = "0" + tempOldString[i];
				}
				while (tempIconString[i].length() < 3)
				{
					tempIconString[i] = "0" + tempIconString[i];
				}
				while (tempColorString[i].length() < 2)
				{
					tempColorString[i] = "0" + tempColorString[i];
				}

				if (playerPosition == i)
				{
					tempTopString[i] = tempTopString[i] + tempIconChar + tempCharColor;
					for (int j = 2; j > -1; j--)
					{
						tempTopString[i] = topInitials[j] + tempTopString[i];
					}
				}
				else
				{
					if (i < playerPosition)
						tempTopString[i] = topName[i] + tempTopString[i] + tempIconString[i] + tempColorString[i];
					else
						tempTopString[i] = topName[i - 1] + tempTopString[i] + tempIconString[i - 1] + tempColorString[i - 1];
				}

				tempOldString[i] = topName[i] + tempOldString[i] + tempIconString[i] + tempColorString[i];
			}
			string scoreChangeLine;
			//fstream writeHighScore;
			//writeHighScore.open("highscore.txt");
			////int i = 0;
			//if (writeHighScore.is_open())
			//{
			//	//while (getline(writeHighScore, scoreChangeLine))
			//	//{
			//	//	if (scoreChangeLine.find(tempOldString[i]) != string::npos)
			//	//	{
			//	//		length = writeHighScore.tellg();
			//	//		writeHighScore.seekg((length - scoreChangeLine.length()) + 3 /* length of initals*/ - 1); //coz start with 0 I think
			//	//		writeHighScore.write("", tempTopString[i].length());
			//	//		cout << scoreChangeLine << 
			//	//	}
			//	//}
			//	for (int i = 0; i < 5; i++)
			//	{
			//		getline(writeHighScore, scoreChangeLine);

			//		int spot = scoreChangeLine.find(tempOldString[i]);
			//		if (spot >= 0)
			//		{
			//			string findString = scoreChangeLine.substr(0, spot);
			//			findString += tempTopString[i];
			//			findString += scoreChangeLine.substr(spot + tempOldString[i].length(), scoreChangeLine.length());
			//			scoreChangeLine = findString;
			//		}

			//		writeHighScore << scoreChangeLine << endl;
			//	}
			//}
			//else
			//{
			//	cerr << "highscore.txt could not be open";
			//}

			ofstream writeHighScore("temptext.txt");

			for (int i = 0; i < 5; i++)
			{
				writeHighScore << tempTopString[i] << endl;
			}

			writeHighScore.close();

			remove("highscore.txt");
			rename("temptext.txt", "highscore.txt");

			ifstream highScore("highscore.txt");
			string scoreLine;
			if (highScore.is_open())
			{
				for (int i = 0; i < 5; i++)
				{
					getline(highScore, scoreLine);
					topScore[i].resize(6, ' ');
					topName[i].resize(3, '~');
					for (int j = 0; j < 3; j++)
					{
						topName[i][j] = scoreLine[j];
					}
					for (int j = 3; j < 9; j++)
					{
						topScore[i][j - 3] = scoreLine[j];
					}
					topPoints[i] = stoi(topScore[i], nullptr, 10);
					for (int j = 9; j < 12; j++)
					{
						topIcon[i][j - 9] = scoreLine[j];
					}
					topChar[i] = (char)stoi(topIcon[i], nullptr, 10);
					for (int j = 12; j < 14; j++)
					{
						topColor[i][j - 12] = scoreLine[j];
					}
				}
			}

			scoreUpdated = true;
		}
	}
}

