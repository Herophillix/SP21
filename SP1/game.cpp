
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

char *BaseMaze[MAP_ROWS];
char *Level1Maze[MAP_ROWS];
char *SplashMaze[MAP_ROWS];
char *Pause[MAP_ROWS];
char *Legend[LEGEND_ROWS];
char *BossMap[MAP_ROWS];
char *BossChar[27];

int bossInterval = 0;
bool bossDirection = false;
int bossAttackMax = 0;
int bossAttackFrame = 0;
int k = 0;
bool charWordBullet = false;
int bossHealth = 100;
int charbossX = 59;
int charbossY = 3;
bool pausetoggle = false;

int d = 0;
int e = 0;
int q = 0;
int ItemNumber = 0;
char Character;

bool Door = true;
bool Portal = false;
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
					Key.Location[d].X = a;
					Key.Location[d].Y = i + 1;
					switch (d)
					{
					case 0:
					{
						Key.id[d] = 0;
						break;
					}
					case 1:
					{
						Key.id[d] = 1;
						break;
					}
					case 2:
					{
						Key.id[d] = 5;
						break;
					}
					case 3:
					{
						Key.id[d] = 4;
						break;
					}
					case 4:
					{
						Key.id[d] = 2;
						break;
					}
					case 5:
					{
						Key.id[d] = 6;
						break;
					}
					case 6:
					{
						Key.id[d] = 3;
						break;
					}
					}
					Key.isKey = true;
					d++;
				}
				else if (BaseMaze[i][a] == 'd')
				{
					for (int g = i - 1; g > 0; g--) // Up // Check the fucking maze bitch
					{
						if (BaseMaze[g][a] == 'D')
						{
							DoorA.Sides[e].AdjacentSides[g].X = a;
							DoorA.Sides[e].AdjacentSides[g].Y = g;
							DoorA.Checker[e] = false;
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
							DoorA.Sides[e].AdjacentSides[f].X = f;
							DoorA.Sides[e].AdjacentSides[f].Y = i;
							DoorA.Checker[e] = false;
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
							DoorA.Sides[e].AdjacentSides[g].X = a;
							DoorA.Sides[e].AdjacentSides[g].Y = g;
							DoorA.Checker[e] = false;
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
							DoorA.Sides[e].AdjacentSides[f].X = f;
							DoorA.Sides[e].AdjacentSides[f].Y = i;
							DoorA.Checker[e] = false;
						}
						else
						{
							break;
						}
					}
					DoorA.Location[e].X = a;
					DoorA.Location[e].Y = i + 1;
					DoorA.id[e] = e;
					DoorA.Checker[e] = false;
					e++;
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
				changeMap();
			}
			else
			{
				pausetoggle = false;
				g_eGameState = S_GAME;
				changeMap();
			}
			g_eBounceTime = g_dElapsedTime + 0.125;
		}
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
		if (g_eGamemode == S_STAGEONE)
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
		renderMap();
		renderInfo();
		renderLegend();
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
				g_Console.writeToBuffer(a, i, abossline[a], 0xe0);
				break;
			}
			case '1':
			{
				g_Console.writeToBuffer(a, i, abossline[a], 0x40);
				break;
			}
			default:
			{
				g_Console.writeToBuffer(a, i, abossline[a], 0x02);
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
	for (int i = 0; i < MAP_ROWS; i += infoIncrement)
	{
		COORD c;
		c.X = MAP_COLUMNS + 2;
		int keySpacing = c.X;
		c.Y = i + 1;
		string Info[infoSize] = { "Player Health: ", "Points: ", "Current Weapon: ", "Keys: " };
		string Number[infoSize] = { to_string(Player.Health), to_string(Player.Points), to_string(Player.CurrentWeapon), };
		if (i < infoSize * infoIncrement)
		{
			g_Console.writeToBuffer(c, Info[i / infoIncrement], 0xe2);
			c.X += Info[i / infoIncrement].length();
			keySpacing += Info[3].length();
			g_Console.writeToBuffer(c, Number[i / infoIncrement], 0xe2);
			for (int keyCounter = 0; keyCounter < NUM_OF_KEYS; keyCounter++)
			{
				if (Player.Key[keyCounter] == true)
				{
					g_Console.writeToBuffer(keySpacing + keyCounter, (3 + 1) * infoIncrement - 2, (char)168, 0xe2);
					keySpacing += 1;
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
	}
}
void Stageone()
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveenemy(BaseMaze, g_enemy, g_sChar, timer, Direction);
	actionshoot(g_sChar, g_bullet, g_bulletP, g_portalEntrance, g_portalExit, aSomethingHappened, BaseMaze, g_eBounceTime, g_eElapsedTime);
	moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key, DoorA, BaseMaze,  Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode);    // moves the character, collision detection, physics, etc, sound can be played here too.
	information();
}
void Bossone()
{
	bossMove();
	moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key, DoorA, BaseMaze, Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode);
	charshootboss();
	processUserInput();
	bossAttackLazer();
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
	for (int i = 1; i < 4; i++)
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
//void moveCharacter()
//{
//	bool bSomethingHappened = false;
//	if (g_dBounceTime > g_dElapsedTime)
//		return;
//	// Updating the location of the character based on the key press
//	// providing a beep sound whenver we shift the character
//	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 1)
//	{
//		//Beep(1440, 30);
//		if (upcheck(g_sChar))
//		{
//			g_sChar.m_cLocation.Y--;
//		}
//		ShootDirection = 1;
//		bSomethingHappened = true;
//	}
//	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
//	{
//		//Beep(1440, 30);
//		if (rightcheck(g_sChar))
//		{
//			g_sChar.m_cLocation.X++;
//		}
//		ShootDirection = 2;
//		bSomethingHappened = true;
//	}
//	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
//	{
//		//Beep(1440, 30);
//		if (downcheck(g_sChar))
//		{
//			g_sChar.m_cLocation.Y++;
//		}
//		ShootDirection = 3;
//		bSomethingHappened = true;
//	}
//	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
//	{
//		//Beep(1440, 30);
//		if (leftcheck(g_sChar))
//		{
//			g_sChar.m_cLocation.X--;
//		}
//		ShootDirection = 4;
//		bSomethingHappened = true;
//	}
//	if (g_abKeyPressed[K_E])
//	{
//		for (int ItemNumber = 0; ItemNumber < NUM_OF_KEYS; ItemNumber++)
//		{
//			if (doorcheck(Key, ItemNumber))
//			{
//				Key.Checker[Key.id[ItemNumber]] = true;
//				DoorA.Checker[Key.id[ItemNumber]] = true;
//				Maze[Key.Location[ItemNumber].Y - 1][Key.Location[ItemNumber].X] = ' ';
//				Player.Key[Key.id[ItemNumber]] = true;
//				ItemNumber = NUM_OF_KEYS;
//			}
//			else if (doorcheck(DoorA, ItemNumber))
//			{
//				for (int i = 0; i < MAP_ROWS; i++)
//				{
//					for (int a = 0; a < MAP_COLUMNS; a++)
//					{
// 						if ((DoorA.Sides[DoorA.id[ItemNumber]].AdjacentSides[a].X != 0) && (DoorA.Sides[DoorA.id[ItemNumber]].AdjacentSides[a].Y != 0))
//						{
//							if (Key.Checker[ItemNumber] == DoorA.Checker[DoorA.id[ItemNumber]])
//							{
//								Maze[DoorA.Location[ItemNumber].Y - 1][DoorA.Location[ItemNumber].X] = ' ';
//								Maze[DoorA.Sides[ItemNumber].AdjacentSides[a].Y][DoorA.Sides[ItemNumber].AdjacentSides[a].X] = ' ';
//							}
//						}
//					}
//				}
//			}
//		}
//		if (((g_sChar.m_cLocation.Y - 2 == g_portalEntrance.m_cLocation.Y) && (g_sChar.m_cLocation.X == g_portalEntrance.m_cLocation.X)) ||
//			((g_sChar.m_cLocation.Y - 1 == g_portalEntrance.m_cLocation.Y) && (g_sChar.m_cLocation.X + 1 == g_portalEntrance.m_cLocation.X)) ||
//			((g_sChar.m_cLocation.Y == g_portalEntrance.m_cLocation.Y) && (g_sChar.m_cLocation.X == g_portalEntrance.m_cLocation.X)) ||
//			((g_sChar.m_cLocation.Y - 1 == g_portalEntrance.m_cLocation.Y) && (g_sChar.m_cLocation.X - 1 == g_portalEntrance.m_cLocation.X)))
//		{
//			g_sChar.m_cLocation.Y = g_portalExit.m_cLocation.Y + 1;
//			g_sChar.m_cLocation.X = g_portalExit.m_cLocation.X;
//		}
//	}
//	if ((g_sChar.m_cLocation.Y == charbossY) && (g_sChar.m_cLocation.X == charbossX))
//	{
//		g_eGamemode = S_BOSSONE;
//		changeMap();
//	}
//	if (bSomethingHappened)
//	{
//		// set the bounce time to some time in the future to prevent accidental triggers
//		g_dBounceTime = g_dElapsedTime + 0.0875; // 125ms should be enough
//	}
//}

void information()
{
	Player.CurrentWeapon = bulletcondition;
}

//Condition function
//bool upcheck(SGameChar Sprite)
//{
//	if ((Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == ' ') ||
//		((Door == false) && ((Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == 'D') ||
//		(Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == 'k') ||
//		(Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == 'd'))))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//bool rightcheck(SGameChar Sprite)
//{
//	if ((Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == ' ') ||
//		((Door == false) && ((Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == 'D') ||
//		(Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == 'k') ||
//			(Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == 'd'))))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//bool downcheck(SGameChar Sprite)
//{
//	if ((Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == ' ') ||
//		((Door == false) && ((Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == 'D') ||
//		(Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == 'k') ||
//			(Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == 'd'))))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//bool leftcheck(SGameChar Sprite)
//{
//	if (((Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == ' ') ||
//		((Door == false) && ((Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == 'D') ||
//		(Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == 'k') ||
//			(Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == 'd')))))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//bool upcheckB(SGameChar Sprite)
//{
//	if (Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == '.')
//	{
//		return true;
//	}
//	return false;
//}
//bool rightcheckB(SGameChar Sprite)
//{
//	if (Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == '.')
//	{
//		return true;
//	}
//	return false;
//}
//bool downcheckB(SGameChar Sprite)
//{
//	if (Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == '.')
//	{
//		return true;
//	}
//	return false;
//}
//bool leftcheckB(SGameChar Sprite)
//{
//	if (Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == '.')
//	{
//		return true;
//	}
//	return false;
//}
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
	case S_PAUSE:
	{
		delete[] * BaseMaze;
		*BaseMaze = new char[MAP_COLUMNS];
		for (int i = 0; i < MAP_ROWS; i++)
		{
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				BaseMaze[i][a] = Pause[i][a];
			}
		}
		break;
	}
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