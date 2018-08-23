
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
using namespace std;
int ShootDirection = 2;
int bulletcondition = 1;
bool g_abKeyPressed[K_COUNT];

string line;
string bossmapline;
string aline;
string bossline;
string pauseline;
string legendline;
string gunline;
string portalline;
string stagetwoline;
string loseline;

char *BaseMaze[MAP_ROWS];
char *Level1Maze[MAP_ROWS];
char *Level2Maze[MAP_ROWS];
char *SplashMaze[MAP_ROWS];
char *Pause[MAP_ROWS];
char *Lose[MAP_ROWS];
char *Legend[LEGEND_ROWS];
char *BossMap[MAP_ROWS];
char *BossChar[27];
char *GunInfo[GUN_ROWS];
char *PortalInfo[PORTAL_ROWS];

int bossInterval = 0;
bool bossDirection = false;
int bossAttackMax = 0;
int bossAttackFrame = 0;
int k = 0;
bool charWordBullet = false;
int bossHealth = 100;
int charbossX = 4;
int charbossY = 3;
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
KDInformation Key, DoorA;

bool g_bStartGame = false;
int g_bStartFrame = 0;

double  g_dElapsedTime;
double  g_eElapsedTime;
double  g_dDeltaTime;

// Game specific variables here
SGameChar   g_sChar, g_enemy, g_bullet, g_bulletP, g_portalEntrance, g_portalExit, g_boss, g_bossMainGun, g_bossSubGun1, g_bossSubGun2, g_Wordbullet;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EGAMEMODES  g_eGamemode = S_STAGEONE;
double  g_dBounceTime;
double  g_eBounceTime;// this is to prevent key bouncing, so we won't trigger keypresses more than once

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
	ifstream loseScreen("Losescreen.txt");
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
					loseline[a] = (char)219;
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
	ifstream mapTwo("map02.txt");
	if (mapTwo.is_open())
	{
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
	Player.Health = 3;
	Player.Points = 0;
	Player.CurrentWeapon = 1;
	Player.Key[NUM_OF_KEYS] = { 0, };
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
	case S_LOSE:playerlose();
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
	g_Console.clearBuffer(0xe2);
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
	else if (g_abKeyPressed[K_SPACE])
	{
		g_eGamemode = S_STAGEONE;
		init();
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
								g_Console.writeToBuffer(a, c.Y, line[a], 0xe2);
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
								g_Console.writeToBuffer(a, c.Y, line[a], 0xe2);
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
							g_Console.writeToBuffer(a, c.Y, line[a], 0xe2);
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
								g_Console.writeToBuffer(a, c.Y, line[a], 0xe2);
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
								g_Console.writeToBuffer(a, c.Y, line[a], 0xe2);
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
							g_Console.writeToBuffer(a, c.Y, line[a], 0xe2);
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
		if ((g_eGamemode == S_STAGEONE) || (g_eGamemode == S_STAGETWO))
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
	if (g_eGamemode == S_STAGEONE)
	{
		aline.resize(MAP_COLUMNS, ' ');
		for (int i = 0; i < MAP_ROWS; i++)
		{
			c.X = 0;
			c.Y = i + 1;
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				aline[a] = BaseMaze[i][a];
				if (aline[a] == 'D')
				{
					aline[a] = (char)219;
				}
			}
			g_Console.writeToBuffer(c, aline, 0xe2);
			for (int a = 0; a < MAP_COLUMNS; a++)
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
					g_Console.writeToBuffer(a, i + 1, aline[a], 0xe5);
				}
				if (aline[a] == 'd')
				{
					aline[a] = (char)219;
					g_Console.writeToBuffer(a, i + 1, aline[a], 0x06);
				}
			}
		}
	}
	else if (g_eGamemode == S_STAGETWO)
	{
		aline.resize(MAP2_COLUMNS, ' ');
		for (int i = 0; i < MAP2_ROWS; i++)
		{
			c.X = 0;
			c.Y = i + 1;
			for (int a = 0; a < MAP2_COLUMNS; a++)
			{
				aline[a] = BaseMaze[i][a];
				if (aline[a] == 'D')
				{
					aline[a] = (char)219;
				}
			}
			g_Console.writeToBuffer(c, aline, 0xe2);
			for (int a = 0; a < MAP2_COLUMNS; a++)
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
					g_Console.writeToBuffer(a, i + 1, aline[a], 0xe5);
				}
				if (aline[a] == 'd')
				{
					aline[a] = (char)219;
					g_Console.writeToBuffer(a, i + 1, aline[a], 0x06);
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
			g_Console.writeToBuffer(c, pauseline, 0xe2);
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
			g_Console.writeToBuffer(c, loseline, 0xe2);
		}
	}
}

void renderBossmap()
{
	COORD c;
	string abossline;
	abossline.resize(MAP_COLUMNS, ' ');

	for (int i = 0; i < 11; i++)
	{
		for (int a = 0; a < 27; a++)
		{
			BossMap[i + g_boss.m_cLocation.Y][a + g_boss.m_cLocation.X] = BossChar[i][a];
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
				g_Console.writeToBuffer(a, c.Y, abossline[a], 0x02);
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
		if (g_eGamemode == S_STAGEONE || g_eGamemode == S_BOSSONE)
		{
			c.X = MAP_COLUMNS + 2;
		}
		else if (g_eGamemode == S_STAGETWO)
		{
			c.X = MAP2_COLUMNS + 2;
		}
		c.Y = i + 1;
		int keySpacing = c.X + Info[3].length();
		for (int a = 0; a < infoSize; a++)
		{
			if (i == SpriteRow[a])
			{
				g_Console.writeToBuffer(c, Info[a], 0xe2);
				c.X += Info[a].length();
				g_Console.writeToBuffer(c, Number[a], 0xe2);
			}
		}
		for (int keyCounter = 0; keyCounter < NUM_OF_KEYS; keyCounter++)
		{
			if (Player.Key[keyCounter] == true)
			{
				g_Console.writeToBuffer(keySpacing + keyCounter, SpriteRow[3] + 1, (char)168, 0xe2);
				keySpacing += 1;
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
	if (bulletcondition == 1)
	{
		for (int b = 0; b < GUN_ROWS; b++)
		{
			if (g_eGamemode == S_STAGEONE )
			{
				a.X = MAP_COLUMNS + 2;
			}
			else if (g_eGamemode == S_STAGETWO)
			{
				a.X = MAP2_COLUMNS + 2;
			}
			a.Y = SpriteRow[2] + 1;
			for (int yt = 0; yt < GUN_COLUMNS; yt++)
			{
				gunline[yt] = GunInfo[b][yt];
				g_Console.writeToBuffer(a.X + yt, a.Y + b + 1, gunline[yt], 0xe2);
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
				g_Console.writeToBuffer(a.X + yt, a.Y + b + 1, portalline[yt], 0xe2);
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
		c.X = 0;
		c.Y = MAP_ROWS + i + 2;
		legendline.resize(LEGEND_COLUMNS, ' ');
		for (int a = 0; a < LEGEND_COLUMNS; a++)
		{
			legendline[a] = Legend[i][a];
			g_Console.writeToBuffer(c, legendline, 0xe2);
		}
		for (int a = 0; a < LEGEND_COLUMNS; a++)
		{
			legendline[a] = Legend[i][a];
			if (legendline[a] == '1')
			{
				legendline[a] = (char)3;
				g_Console.writeToBuffer(c.X, c.Y, legendline[a], 0xe2);
			}
			else if (legendline[a] == '2')
			{
				legendline[a] = (char)168;
				g_Console.writeToBuffer(c.X, c.Y, legendline[a], 0xe5);
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
				g_Console.writeToBuffer(c.X + a, c.Y, legendline[a], 0xe2);
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
	WORD charColor = 0xe2;
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)3, charColor);
}

void renderShootbossbullet()
{
	WORD Char = 0x02;
	if (charWordBullet == true)
	{
		g_Console.writeToBuffer(g_Wordbullet.m_cLocation, (char)254, Char);
	}
}

void renderbullet()
{
	if (Bulletpos == true)
	{
		WORD Char = 0xe2;
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
	case S_STAGEONE: Stageone();
		break;
	case S_BOSSONE: Bossone();
		break;
	case S_STAGETWO: Stageone();
		break;
	}
}
void Stageone()
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveenemy(BaseMaze, g_enemy, g_sChar, timer, Direction);
	actionshoot(g_sChar, g_bullet, g_bulletP, g_portalEntrance, g_portalExit, aSomethingHappened, BaseMaze, g_eBounceTime, g_eElapsedTime);
	moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key, DoorA, BaseMaze,  Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode);    // moves the character, collision detection, physics, etc, sound can be played here too.
	information();
	checkhealth();
}
void Bossone()
{
	bossMove();
	moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key, DoorA, BaseMaze, Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode);
	charshootboss();
	processUserInput();
	bossAttackLazer();
	checkhealth();
	/*movecharbullet();*/

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
	for (int i = 1; i < 5 ; i++)
	{
		bossline.resize(22, ' ');
		c.Y = i + 1;
		switch (i)
		{
		case 1:
		{
			bossline = "   Boss HP (" + to_string(bossHealth) + "/100)  ";
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
					if ((bossHealth / 5) >= (a - 20))
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
			if (bossHealth == 0)
			{
    				g_eGamemode = S_STAGETWO;
				g_sChar.m_cLocation.X = 2;
				g_sChar.m_cLocation.Y = 3;
				changeMap();
			}
			break;
			
		}
		}

	}
}
void bossMove()
{
	bossInterval++;
	if (bossInterval > 20)
	{
		if (bossDirection)
		{
			g_boss.m_cLocation.X--;
			if (g_boss.m_cLocation.X < 10)
			{
				bossDirection = false;
			}
		}
		else
		{
			if (g_boss.m_cLocation.X > 25)
			{
				bossDirection = true;
			}
			g_boss.m_cLocation.X++;
		}
		bossInterval = 0;
	}
}

void information()
{
	Player.CurrentWeapon = bulletcondition;
}

bool doorcheck(KDInformation Item, int ItemNumber)
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
					BaseMaze[i][a] = BossMap[i + 1][a];
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
void bossAttackLazer()
{
	g_bossMainGun.m_cLocation.X = g_boss.m_cLocation.X + 10;
	g_bossMainGun.m_cLocation.Y = g_boss.m_cLocation.Y + 13;

	bossAttackFrame++;
	if (bossAttackFrame > 15)
	{
		if (bossAttackMax < 17)
		{
			bossAttackMax++;
		}
		bossAttackFrame = 0;
		k--;
		if (k == -1)
		{
			k = 7;
		}
	}
	bool bossMoves[2] = { 1, 1 };
	if (bossMoves[0] == true)
	{
		COORD c;
		for (int i = 0; i < bossAttackMax; i++)
		{

			string bossAttackline = "0001111";
			string bossAttackBufferLine = "       ";
			c.Y = g_bossMainGun.m_cLocation.Y + i;
			for (int j = i; j < bossAttackMax + i; j++)
			{
				bossAttackBufferLine[(j - i) % 7] = bossAttackline[(j + k) % 7];
			}
			switch (i)
			{
			case 0:
			{
				bossAttackBufferLine = bossAttackBufferLine.substr(4, 1);
				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 2] = ' ';
				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 4] = ' ';
				for (int a = 0; a < 1; a++)
				{
					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 3] = bossAttackBufferLine[a];
				}
				break;
			}
			case 1:
			{
				bossAttackBufferLine = bossAttackBufferLine.substr(3, 3);
				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 1] = ' ';
				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 5] = ' ';
				for (int a = 0; a < 3; a++)
				{
					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 2 + a] = bossAttackBufferLine[a];
				}
				break;
			}
			case 2:
			{
				bossAttackBufferLine = bossAttackBufferLine.substr(1, 5);
				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X] = ' ';
				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 6] = ' ';
				for (int a = 0; a < 5; a++)
				{
					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 1 + a] = bossAttackBufferLine[a];
				}
				break;
			}
			default:
			{
				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X - 1] = ' ';
				BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + 7] = ' ';
				for (int a = 0; a < 7; a++)
				{
					BossMap[c.Y - 1][g_bossMainGun.m_cLocation.X + a] = bossAttackBufferLine[a];
				}
			}
			}
		}
	}
	if (bossMoves[1] == true)
	{
		if (bossAttackFrame == 10)
		{

		}
	}
}

void bossAttackMachineGun()
{
	g_bossSubGun1.m_cLocation.X = g_boss.m_cLocation.X + 4;
	g_bossSubGun1.m_cLocation.Y = g_boss.m_cLocation.Y + 8;
	g_bossSubGun2.m_cLocation.X = g_boss.m_cLocation.X + 17;
	g_bossSubGun2.m_cLocation.Y = g_boss.m_cLocation.Y + 8;
}
void charshootboss()
{
	if (g_abKeyPressed[K_SPACE])
	{
		g_Wordbullet.m_cLocation.X = g_sChar.m_cLocation.X;
		g_Wordbullet.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
		charWordBullet = true;
	}
	if (BossMap[g_Wordbullet.m_cLocation.Y - 1][g_Wordbullet.m_cLocation.X] == (char)219)
	{
		charWordBullet = false;
	}
	else if (BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != ' ')
	{
		charWordBullet = false;
		bossHealth -= 1;
		g_Wordbullet.m_cLocation.X = g_sChar.m_cLocation.X;
		g_Wordbullet.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
	}

	if (charWordBullet == true)
	{
		g_Wordbullet.m_cLocation.Y--;
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
		g_eGameState = S_LOSE;
	}
}