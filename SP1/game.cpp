
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
int ShootDirection = 2;
int bulletcondition = 1;
bool g_abKeyPressed[K_COUNT];

string line;
string bossmapline;
string aline;
string bossline;
string pauseline;
string createline;
string legendline;
string gunline;
string portalline;
string stagetwoline;
string loseline;

WORD Char = 0x02;
WORD charColor = 0x02;
WORD baseColor = 0x0b;
WORD baseColor2 = 0x0b;
char charIcon = (char)3;
int  charOption = 0;
int	 charDetail = 0;
bool isDetail = false;
char tempChar;

char *BaseMaze[MAP_ROWS];
char *Level1Maze[MAP_ROWS];
char *Level2Maze[MAP2_ROWS];
char *SplashMaze[MAP_ROWS];
char *Lose[MAP_ROWS];
char *Pause[MAP_ROWS];
char *Create[MAP_ROWS];
char *Legend[LEGEND_ROWS];
char *BossMap[MAP_ROWS];
char *BossChar[27];
char *GunInfo[GUN_ROWS];
char *PortalInfo[PORTAL_ROWS];

//bool characterIsHit = false;
//int playerIsHitFrame = 0;
//int bossInterval = 0;
//bool bossDirection = false;
//int rollForBossAttack = 0;
//int bossAttackMax = 0;
//int bossAttackFrame[3] = { 0, 0, 0 };
//int k = 0;
//bool bossAttackOn[3] = { false, };
//int subBulletmax = 5;
//int subBulletsCreated = 0;
//int subBulletsCreated2 = 0;
//bool subBulletsAllCreated = false;
//bool subBulletsAllCreated2 = false;
//bool bossLazerMaxReached = false;
//bool charWordBullet = false;
//bool charWordBulletHold = false;
//bool charWordBulletTimeout = false;
//int charWordBulletCharge = 0;
//int bossHealth = 10;
//int bossMaxHealth = 10;
//int charbossX = 4;
//int charbossY = 3;
int Rowrender;

bool pausetoggle = false;
bool losetoggle = false;

int KeyonMap = 0;
int DooronMap = 0;
int q = 0;
int ItemNumber = 0;
char Character;

bool aSomethingHappened;

int timer;
int Direction = 2;

const int enemylocationX = 50;
const int enemylocationY = 29;

PlayerInformation Player;
KDInformation Key, DoorA, Key2, DoorB;

bool g_bStartGame = false;
int g_bStartFrame = 0;

double  g_dElapsedTime;
double  g_eElapsedTime;
double  g_dDeltaTime;
double  g_bBounceTime[6];

// Game specific variables here

SGameChar   g_sChar, g_enemy, g_bullet, g_bulletP, g_portalEntrance, g_portalExit, g_boss, g_bossMainGun, g_bossSubGun1, g_bossSubGun2, g_Wordbullet;
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
	g_enemy.m_cLocation.X = enemylocationX;
	g_enemy.m_cLocation.Y = enemylocationY;
	g_enemy.m_bActive = true;

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
	ifstream mapTwo("map02.txt");
	if (mapTwo.is_open())
	{
		KeyonMap = 0;
		DooronMap = 0;
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
				Level2Maze[i][a] = stagetwoline[a];
			}
		}
		for (int i = 0; i < MAP2_ROWS; i++)
		{
			for (int a = 0; a < MAP2_COLUMNS; a++)
			{
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
						Key2.id[KeyonMap] = 1;
						break;
					}
					case 2:
					{
						Key2.id[KeyonMap] = 5;
						break;
					}
					case 3:
					{
						Key2.id[KeyonMap] = 4;
						break;
					}
					case 4:
					{
						Key2.id[KeyonMap] = 2;
						break;
					}
					case 5:
					{
						Key2.id[KeyonMap] = 6;
						break;
					}
					case 6:
					{
						Key2.id[KeyonMap] = 3;
						break;
					}
					}
					Key2.isKey = true;
					KeyonMap++;
				}
				else if (Level2Maze[i][a] == 'd')
				{
					for (int g = i - 1; g > 0; g--) // Up // Check the fucking maze bitch
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
				if ((createline[a] == '-') || (createline[a] == '+') || (createline[a] == '|') || (createline[a] == '_'))
				{
					createline[a] = (char)219;
				}
				Create[i][a] = createline[a];
			}
		}
		creationScreen.close();
	}
	Player.Health = 1;
	Player.Points = 0;
	Player.CurrentWeapon = 1;
	Player.Key[NUM_OF_KEYS] = { 0, };
}

void initafterlose()
{
	/*g_dElapsedTime = 0.0;
	g_eElapsedTime = 0.0;
	g_dBounceTime = 0.0;
	g_eBounceTime = 0.0;*/

	g_Wordbullet.m_cLocation.Y = 1;
	g_enemy.m_cLocation.X = enemylocationX;
	g_enemy.m_cLocation.Y = enemylocationY;
	g_enemy.m_bActive = true;

	g_boss.m_cLocation.X = 10;
	g_boss.m_cLocation.Y = 2;

	g_sChar.m_cLocation.X = 2; 
	g_sChar.m_cLocation.Y = 3;
	g_sChar.m_bActive = true;
	Player.Health = 1;
	Player.Points = 0;
	Player.CurrentWeapon = 1;
	Player.Key[NUM_OF_KEYS] = { 0, };
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

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	case S_PAUSE: pause();
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
		else if ((g_eGamemode == S_STAGEONE) || (g_eGamemode == S_STAGETWO))
		{
			renderMap();        // renders the map to the buffer first 
			renderInfo();
			renderLegend();
			renderCharacter();  // renders the character into the buffer
			renderenemy();
			renderBossChar();
			renderbullet();
			renderbulletPRed();
			renderbulletPBlue();
		}
		else if (g_eGamemode == S_BOSSONE)
		{
			renderBossmap();
			renderInfo();
			renderLegend();
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
	}
	else if (g_eGameState == S_LOSE)
	{
		renderLosescreen();
		renderInfo();
		renderLegend();
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
			if (acreateline[a] == 'D')
			{
				acreateline[a] = (char)219;
			}
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
	string heart = "Heart", omega = "Omega", coolSymbol = "Cool Symbol", smallDot = "Inaccurate Hit Box";
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
				g_Console.writeToBuffer(48, 6, heart, 0x04);
				g_Console.writeToBuffer(48, 9, omega, 0x0e);
				g_Console.writeToBuffer(48, 12, coolSymbol, 0x0e);
				g_Console.writeToBuffer(48, 15, smallDot, 0x0e);
				break;
			}
			case 1:
			{
				g_Console.writeToBuffer(48, 6, heart, 0x0e);
				g_Console.writeToBuffer(48, 9, omega, 0x04);
				g_Console.writeToBuffer(48, 12, coolSymbol, 0x0e);
				g_Console.writeToBuffer(48, 15, smallDot, 0x0e);
				break;
			}
			case 2:
			{
				g_Console.writeToBuffer(48, 6, heart, 0x0e);
				g_Console.writeToBuffer(48, 9, omega, 0x0e);
				g_Console.writeToBuffer(48, 12, coolSymbol, 0x04);
				g_Console.writeToBuffer(48, 15, smallDot, 0x0e);
				break;
			}
			case 3:
			{
				g_Console.writeToBuffer(48, 6, heart, 0x0e);
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
	WORD enemyColor = 0x0C;
	if (g_enemy.m_bActive)
	{
		enemyColor = 0x0A;
	}
	g_Console.writeToBuffer(g_enemy.m_cLocation, (char)1, enemyColor);
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
	}
	for (int i = 0; i < Rowrender; i++)
	{
		c.X = 0;
		c.Y = i + 1;
		for (int a = 0; a < (int)aline.size(); a++)
		{
			aline[a] = BaseMaze[i][a];
			if (aline[a] == 'D')
			{
				aline[a] = (char)219;
			}
		}
		g_Console.writeToBuffer(c, aline, baseColor);
		for (int a = 0; a < (int)aline.size(); a++)
		{
			aline[a] = BaseMaze[i][a];
			if (a == g_portalEntrance.m_cLocation.X && i == g_portalEntrance.m_cLocation.Y)
			{
				aline[a] = (char)176;
				g_Console.writeToBuffer(a,i + 1, aline[a], 0x60);
			}
			if (a == g_portalExit.m_cLocation.X && i == g_portalExit.m_cLocation.Y)
			{
				aline[a] = (char)177;
				g_Console.writeToBuffer(a,i + 1, aline[a], 0x1f);
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
	const int infoSize = 4;
	COORD c, a;
	string Info[infoSize] = { "Player Health: ", "Points: ", "Current Weapon: ", "Keys: " };
	string Number[infoSize] = { to_string(Player.Health), to_string(Player.Points), to_string(Player.CurrentWeapon), };
	int SpriteRow[infoSize] = { 0, 3, 3 + 3, 3 + 3 + 3 + PORTAL_ROWS };
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
		}
		c.Y = i + 1;
		int keySpacing = c.X + Info[3].length();
		for (int a = 0; a < infoSize; a++)
		{
			if (i == SpriteRow[a])
			{
				g_Console.writeToBuffer(c, Info[a], baseColor);
				c.X += Info[a].length();
				g_Console.writeToBuffer(c, Number[a], baseColor);
			}
		}
		for (int keyCounter = 0; keyCounter < NUM_OF_KEYS; keyCounter++)
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
	if (g_eGamemode == S_BOSSONE)
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
			}
			a.Y = SpriteRow[2] + 1;
			for (int yt = 0; yt < GUN_COLUMNS; yt++)
			{
				gunline[yt] = GunInfo[b][yt];
				g_Console.writeToBuffer(a.X + yt, a.Y + b + 1, gunline[yt], baseColor);
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
			if ((g_eGamemode == S_STAGEONE) || (g_eGamemode == S_BOSSONE))
			{
				a.X = MAP_COLUMNS + 2;
			}
			else if (g_eGamemode == S_STAGETWO)
			{
				a.X = MAP2_COLUMNS + 2;
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
		c.Y = MAP_ROWS + i + 2;
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

void renderCharacter()
{
	// Draw the location of the character
	switch (g_eGamemode)
	{
	case S_STAGEONE:
	{
		g_Console.writeToBuffer(g_sChar.m_cLocation, charIcon, charColor);
		break;
	}
	case S_STAGETWO:
	{
		g_Console.writeToBuffer(g_sChar.m_cLocation, charIcon, charColor);
		break;
	}
	case S_BOSSONE:
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
				charColor = 0x02;
				playerIsHitFrame = 0;
			}
		}
		else
		{
			g_Console.writeToBuffer(g_sChar.m_cLocation, charIcon, charColor);
		}
		break;
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
					charWordBulletCharge = i + 1;
					i = -2;
					break;
				}
				case 1:
				{
					Char = 0x01;
					charWordBulletCharge = i + 1;
					i = -2;
					break;
				}
				case 2:
				{
					Char = 0x05;
					charWordBulletCharge = i + 1;
					i = -2;
					break;
				}
				case 3:
				{
					Char = 0x04;
					charWordBulletCharge = i + 1;
					i = -2;
					break;
				}
				case 4:
				{
					Char = 0x06;
					charWordBulletCharge = i + 1;
					i = -2;
					break;
				}
				case 5:
				{
					Char = 0x06;
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

//Gameplay

void gameplay()            // gameplay logic
{
	switch (g_eGamemode)
	{
	case S_CREATION: createCharacter();
		break;
	case S_STAGEONE: Stageone();
		break;
	case S_BOSSONE: Bossone();
		break;
	case S_STAGETWO: Stageone();
		break;
	}
}
void createCharacter()
{
	changeCharacter(charColor, charIcon, charOption, charDetail, g_createBounceTime, g_dElapsedTime, isDetail, g_eGamemode);
}
void Stageone()
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveenemy(BaseMaze, g_enemy, g_sChar, timer, Direction);
	actionshoot(g_sChar, g_bullet, g_bulletP, g_portalEntrance, g_portalExit, aSomethingHappened, BaseMaze, g_eBounceTime, g_eElapsedTime);
	if (g_eGamemode == S_STAGEONE)
	{
		moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key, DoorA, BaseMaze, Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode);	 // moves the character, collision detection, physics, etc, sound can be played here too.
	}
	else if (g_eGamemode == S_STAGETWO)
	{
		moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key2, DoorB, BaseMaze, Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode);
	}
	information();
	checkhealth();
}
void Bossone()
{
	BossoneVar(g_dBounceTime, g_eBounceTime, g_dElapsedTime, g_sChar, g_Console, BossMap, Player, g_bossMainGun, g_boss, g_bossSubGun1, g_bossSubGun2, g_Wordbullet, charWordBullet, g_bBounceTime, g_bossSubBullet, g_bossSubBullet2);
	//bossMove();
	//if (bossAttackOn[0] == true)
	//{
	//	bossAttackLazer();
	//}
	//if (bossAttackOn[1] == true)
	//{
	//	bossAttackMachineGunLeft();
	//}
	//if (bossAttackOn[2] == true)
	//{
	//	bossAttackMachineGunRight();
	//}
	//moveCharacterInBoss(g_dBounceTime, g_eBounceTime, g_dElapsedTime, g_sChar, g_Console, BossMap, Player, characterIsHit);
	//charshootboss();
	//processUserInput();
	//checkhealth();
	//bossMove();
	//moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key, DoorA, BaseMaze, Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode);
	//charshootboss();
	//processUserInput();
	//bossAttackLazer();
	///*movecharbullet();*/

}
void renderBossChar()
{
	//render boss @ location onto first map 
	g_Console.writeToBuffer(charbossX,charbossY,(char)64);
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
				g_eGamemode = S_STAGETWO;
				g_sChar.m_cLocation.X = 2;
				g_sChar.m_cLocation.Y = 3;
				charbossX = 98;
				charbossY = 28;
				changeMap();
			}
			break;

		}
		}

	}
}

void information()
{
	Player.CurrentWeapon = bulletcondition;
}

bool doorcheck(KDInformation Item, int ItemNumber, KDInformation Key)
{
	if ((Item.Location[ItemNumber].Y == g_sChar.m_cLocation.Y - 1) && (Item.Location[ItemNumber].X == g_sChar.m_cLocation.X) ||
		(Item.Location[ItemNumber].Y == g_sChar.m_cLocation.Y) && (Item.Location[ItemNumber].X == g_sChar.m_cLocation.X + 1) ||
		(Item.Location[ItemNumber].Y == g_sChar.m_cLocation.Y + 1) && (Item.Location[ItemNumber].X == g_sChar.m_cLocation.X) ||
		(Item.Location[ItemNumber].Y == g_sChar.m_cLocation.Y) && (Item.Location[ItemNumber].X == g_sChar.m_cLocation.X - 1))
	{
		if (Item.isKey == true)
		{
			return true;
		}
		else if (Key.Checker[Item.id[ItemNumber]] == true)
		{
			return true;
		}
	}
	else
	{
		return false;
	}
	return false;
}
void changeMap()
{
	switch (g_eGameState)
	{
		//case S_PAUSE:
		//{
		//	delete[] * BaseMaze;
		//	*BaseMaze = new char[MAP_COLUMNS];
		//	for (int i = 0; i < MAP_ROWS; i++)
		//	{
		//		for (int a = 0; a < MAP_COLUMNS; a++)
		//		{
		//			BaseMaze[i][a] = Pause[i][a];
		//		}
		//	}
		//	break;
		//}
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
		break;
		}
	}
	}
}

//void bossMove()
//{
//	bossInterval++;
//	if (bossInterval > 20)
//	{
//		if (bossDirection)
//		{
//			g_boss.m_cLocation.X--;
//		}
//		else
//		{
//			if (g_boss.m_cLocation.X > 30)
//			{
//				bossDirection = true;
//			}
//			g_boss.m_cLocation.X++;
//		}
//		rollForBossAttack = rand() % 3;
//		switch (rollForBossAttack)
//		{
//		case 0:
//		{
//			if (bossAttackOn[0] == false)
//			{
//				bossAttackOn[0] = true;
//			}
//			break;
//		}
//		case 1:
//		{
//			if (bossAttackOn[1] == false)
//			{
//				bossAttackOn[1] = true;
//				break;
//			}
//		}
//		case 2:
//		{
//			if (bossAttackOn[2] == false)
//			{
//				bossAttackOn[2] = true;
//				break;
//			}
//		}
//		}
//		if (g_boss.m_cLocation.X < 5)
//		{
//			bossDirection = false;
//		}
//		bossInterval = 0;
//	}
//}
//void bossAttackLazer()
//{
//	g_bossMainGun.m_cLocation.X = g_boss.m_cLocation.X + 10;
//	g_bossMainGun.m_cLocation.Y = g_boss.m_cLocation.Y + 13;
//
//	bossAttackFrame[0]++;
//	if (bossAttackFrame[0] > 15)
//	{
//		if (bossLazerMaxReached == true)
//		{
//			bossAttackMax--;
//			if (bossAttackMax == 0)
//			{
//				bossLazerMaxReached = false;
//				bossAttackOn[0] = false;
//			}
//		}
//		else
//		{
//			if (bossAttackMax == 17)
//			{
//				bossLazerMaxReached = true;
//			}
//			if (bossAttackMax < 17)
//			{
//				bossAttackMax++;
//			}
//		}
//
//		bossAttackFrame[0] = 0;
//		k--;
//		if (k == -1)
//		{
//			k = 7;
//		}
//	}
//
//	COORD c;
//
//	if (bossLazerMaxReached == true)
//	{
//		for (int i = 17 - bossAttackMax; i < 17; i++)
//		{
//
//			string bossAttackline = "0001111";
//			string bossAttackBufferLine = "       ";
//			c.Y = g_bossMainGun.m_cLocation.Y + i;
//			for (int j = i; j < 7 + i; j++)
//			{
//				bossAttackBufferLine[(j - i) % 7] = bossAttackline[(j + k) % 7];
//			}
//			switch (i)
//			{
//			case 0:
//			{
//				bossAttackBufferLine = bossAttackBufferLine.substr(4, 1);
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 2] = ' ';
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 4] = ' ';
//				for (int a = 0; a < 1; a++)
//				{
//					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 3] = bossAttackBufferLine[a];
//				}
//				break;
//			}
//			case 1:
//			{
//				bossAttackBufferLine = bossAttackBufferLine.substr(3, 3);
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 1] = ' ';
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 5] = ' ';
//				for (int a = 0; a < 3; a++)
//				{
//					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 2 + a] = bossAttackBufferLine[a];
//				}
//				break;
//			}
//			case 2:
//			{
//				bossAttackBufferLine = bossAttackBufferLine.substr(1, 5);
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X] = ' ';
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 6] = ' ';
//				for (int a = 0; a < 5; a++)
//				{
//					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 1 + a] = bossAttackBufferLine[a];
//				}
//				break;
//			}
//			default:
//			{
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X - 1] = ' ';
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 7] = ' ';
//				for (int a = 0; a < 7; a++)
//				{
//					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + a] = bossAttackBufferLine[a];
//				}
//			}
//			}
//		}
//	}
//	else
//	{
//		for (int i = 0; i < bossAttackMax; i++)
//		{
//
//			string bossAttackline = "0001111";
//			string bossAttackBufferLine = "       ";
//			c.Y = g_bossMainGun.m_cLocation.Y + i;
//			for (int j = i; j < bossAttackMax + i; j++)
//			{
//				bossAttackBufferLine[(j - i) % 7] = bossAttackline[(j + k) % 7];
//			}
//			switch (i)
//			{
//			case 0:
//			{
//				bossAttackBufferLine = bossAttackBufferLine.substr(4, 1);
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 2] = ' ';
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 4] = ' ';
//				for (int a = 0; a < 1; a++)
//				{
//					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 3] = bossAttackBufferLine[a];
//				}
//				break;
//			}
//			case 1:
//			{
//				bossAttackBufferLine = bossAttackBufferLine.substr(3, 3);
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 1] = ' ';
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 5] = ' ';
//				for (int a = 0; a < 3; a++)
//				{
//					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 2 + a] = bossAttackBufferLine[a];
//				}
//				break;
//			}
//			case 2:
//			{
//				bossAttackBufferLine = bossAttackBufferLine.substr(1, 5);
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X] = ' ';
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 6] = ' ';
//				for (int a = 0; a < 5; a++)
//				{
//					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 1 + a] = bossAttackBufferLine[a];
//				}
//				break;
//			}
//			default:
//			{
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X - 1] = ' ';
//				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 7] = ' ';
//				for (int a = 0; a < 7; a++)
//				{
//					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + a] = bossAttackBufferLine[a];
//				}
//			}
//			}
//		}
//	}
//
//}
//void bossAttackMachineGunLeft()
//{
//	g_bossSubGun1.m_cLocation.X = g_boss.m_cLocation.X + 4;
//	g_bossSubGun1.m_cLocation.Y = g_boss.m_cLocation.Y + 8;
//
//	bossAttackFrame[1]++;
//	if (bossAttackFrame[1] % 10 == 0)
//	{
//		if (bossAttackFrame[1] > 50)
//		{
//			if (subBulletsAllCreated == false)
//			{
//				/*subBulletsToCreate++;
//				for (; subBulletsCreated < subBulletsToCreate; subBulletsCreated++)
//				{
//				g_bossSubBullet.push_back(createBossSubBullet(g_bossSubGun1));
//				}*/
//				g_bossSubBullet.push_back(createBossSubBullet(g_bossSubGun1));
//				subBulletsCreated++;
//				if (subBulletsCreated == subBulletmax)
//				{
//					subBulletsAllCreated = true;
//				}
//			}
//			bossAttackFrame[1] = 0;
//		}
//		for (int bulletCount = 0; bulletCount < subBulletsCreated; bulletCount++)
//		{
//			if (BossMap[g_bossSubBullet[bulletCount].m_cLocation.Y][g_bossSubBullet[bulletCount].m_cLocation.X] == (char)219)
//			{
//				g_bossSubBullet.erase(g_bossSubBullet.begin());
//				subBulletsCreated--;
//
//				if (subBulletsCreated == 0)
//				{
//					bossAttackOn[1] = false;
//					subBulletsAllCreated = false;
//					return;
//				}
//			}
//			else
//			{
//				g_bossSubBullet[bulletCount].m_cLocation.Y++;
//			}
//		}
//	}
//	for (int bulletCount = 0; bulletCount < subBulletsCreated; bulletCount++)
//	{
//		BossMap[g_bossSubBullet[bulletCount].m_cLocation.Y - 1][g_bossSubBullet[bulletCount].m_cLocation.X] = '0';
//	}
//}
//void bossAttackMachineGunRight()
//{
//	g_bossSubGun2.m_cLocation.X = g_boss.m_cLocation.X + 21;
//	g_bossSubGun2.m_cLocation.Y = g_boss.m_cLocation.Y + 8;
//
//	bossAttackFrame[2]++;
//	if (bossAttackFrame[2] % 10 == 0)
//	{
//		if (bossAttackFrame[2] > 50)
//		{
//			if (subBulletsAllCreated2 == false)
//			{
//				/*subBulletsToCreate++;
//				for (; subBulletsCreated < subBulletsToCreate; subBulletsCreated++)
//				{
//				g_bossSubBullet.push_back(createBossSubBullet(g_bossSubGun1));
//				}*/
//				g_bossSubBullet2.push_back(createBossSubBullet(g_bossSubGun2));
//				subBulletsCreated2++;
//				if (subBulletsCreated2 == subBulletmax)
//				{
//					subBulletsAllCreated2 = true;
//				}
//			}
//			bossAttackFrame[2] = 0;
//		}
//		for (int bulletCount = 0; bulletCount < subBulletsCreated2; bulletCount++)
//		{
//			if (BossMap[g_bossSubBullet2[bulletCount].m_cLocation.Y][g_bossSubBullet2[bulletCount].m_cLocation.X] == (char)219)
//			{
//				g_bossSubBullet2.erase(g_bossSubBullet2.begin());
//				subBulletsCreated2--;
//
//				if (subBulletsCreated2 == 0)
//				{
//					bossAttackOn[2] = false;
//					subBulletsAllCreated2 = false;
//					return;
//				}
//			}
//			else
//			{
//				g_bossSubBullet2[bulletCount].m_cLocation.Y++;
//			}
//		}
//	}
//	for (int bulletCount = 0; bulletCount < subBulletsCreated2; bulletCount++)
//	{
//		BossMap[g_bossSubBullet2[bulletCount].m_cLocation.Y - 1][g_bossSubBullet2[bulletCount].m_cLocation.X] = '0';
//	}
//}
//void bossAttackMachineGun()
//{
//	g_bossSubGun1.m_cLocation.X = g_boss.m_cLocation.X + 4;
//	g_bossSubGun1.m_cLocation.Y = g_boss.m_cLocation.Y + 8;
//	g_bossSubGun2.m_cLocation.X = g_boss.m_cLocation.X + 17;
//	g_bossSubGun2.m_cLocation.Y = g_boss.m_cLocation.Y + 8;
//}
//void charshootboss()
//{
//	int i = 0;
//	double j = 0.2;
//	if (g_abKeyPressed[K_SPACE])
//	{
//		if (charWordBulletTimeout == false)
//		{
//			g_Wordbullet.m_cLocation.X = g_sChar.m_cLocation.X;
//			g_Wordbullet.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
//			charWordBullet = true;
//			charWordBulletCharge = 0;
//			if (charWordBulletHold == false)
//			{
//				for (; i < 6; i++, j += 0.5)
//				{
//					if (i == 5)
//					{
//						g_bBounceTime[i] = g_dElapsedTime + 3;
//					}
//					else
//					{
//						g_bBounceTime[i] = g_dElapsedTime + j;
//					}
//				}
//			}
//			charWordBulletHold = true;
//		}
//	}
//	else
//	{
//		charWordBulletTimeout = false;
//		charWordBulletHold = false;
//	}
//	if (BossMap[g_Wordbullet.m_cLocation.Y - 1][g_Wordbullet.m_cLocation.X] == (char)219)
//	{
//		charWordBullet = false;
//	}
//	else if ((BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != ' ') &&
//		(BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != '1') &&
//		(BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != '0') &&
//		(BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != (char)219) &&
//		charWordBulletHold == false && charWordBullet == true)
//	{
//		charWordBullet = false;
//		switch (charWordBulletCharge)
//		{
//		case 0:
//		{
//			bossHealth -= 1;
//			break;
//		}
//		case 1:
//		{
//			bossHealth -= 3;
//			break;
//		}
//		case 2:
//		{
//			bossHealth -= 5;
//			break;
//		}
//		case 3:
//		{
//			bossHealth -= 8;
//			break;
//		}
//		case 4:
//		{
//			bossHealth -= 10;
//			break;
//		}
//		case 5:
//		{
//			bossHealth -= 15;
//			break;
//		}
//
//		}
//		g_Wordbullet.m_cLocation.X = g_sChar.m_cLocation.X;
//		g_Wordbullet.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
//	}
//
//	if (charWordBullet == true)
//	{
//		g_Wordbullet.m_cLocation.Y--;
//	}
//
//
//}
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
		g_eGameState = S_LOSE;
	}
}
