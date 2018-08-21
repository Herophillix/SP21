
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

WORD Char = 0xe2;
WORD charColor = 0xe2;

char *Maze[MAP_ROWS];
char *SplashMaze[MAP_ROWS];
char *BossMap[32];
char *BossChar[27];

bool characterIsHit = false;
int playerIsHitFrame = 0;
int bossInterval = 0;
bool bossDirection = false;
int rollForBossAttack = 0;
int bossAttackMax = 0;
int bossAttackFrame[3] = {0, 0, 0};
int k = 0;
int bossAttackOn[3] = {false, };
int subBulletmax = 5;
int subBulletsCreated = 0;
int subBulletsCreated2 = 0;
bool subBulletsAllCreated = false;
bool subBulletsAllCreated2 = false;
bool bossLazerMaxReached = false;
bool charWordBullet = false;
bool charWordBulletHold = false;
int charWordBulletCharge = 0;
int bossHealth;
int bossMaxHealth = 300;
int charbossX = 4; // default 59
int charbossY = 3;

int d = 0;
int e = 0;
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
std::vector <SGameChar> g_bossSubBullet, g_bossSubBullet2;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EGAMEMODES  g_eGamemode = S_STAGEONE;
double  g_dBounceTime;
double  g_eBounceTime;// this is to prevent key bouncing, so we won't trigger keypresses more than once
double  g_bBounceTime[5];

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

	srand(time(NULL));
	bossHealth = bossMaxHealth;

	ifstream mapOne("map01.txt");
	if (mapOne.is_open())
	{
		for (int i = 0; i < MAP_ROWS; i++)
		{
			Maze[i] = new char[MAP_COLUMNS];
			getline(mapOne, line);
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				if ((line[a] == 43) || (line[a] == 124) || (line[a] == 45))
				{
					line[a] = (char)219;
				}
				Maze[i][a] = line[a];
			}
		}
		for (int i = 0; i < MAP_ROWS; i++)
		{
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				if (Maze[i][a] == 'k')
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
				else if (Maze[i][a] == 'd')
				{
					for (int g = i - 1; g > 0; g--) // Up // Check the fucking maze bitch
					{
						if (Maze[g][a] == 'D')
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
						if (Maze[i][f] == 'D')
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
						if (Maze[g][a] == 'D')
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
						if (Maze[i][f] == 'D')
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
			int Columns = MAP_COLUMNS;
			BossMap[i] = new char[Columns];
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
	}
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_abKeyPressed[K_SPACE])
	{
		g_bStartGame = true;
		g_eBounceTime += 2.0;
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
							g_Console.writeToBuffer(a, c.Y, line[a], 0xe2);
							break;
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
							g_Console.writeToBuffer(a, c.Y, line[a], 0xe2);
							break;
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
	if (g_eGamemode == S_STAGEONE)
	{
		renderMap();        // renders the map to the buffer first 
		renderInfo();
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
		renderCharacter();
		//renderbossattack();
		renderShootbossbullet();
		renderBossHealth();

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
			aline[a] = Maze[i][a];
			if (aline[a] == 'D')
			{
				aline[a] = (char)219;
			}
		}
		g_Console.writeToBuffer(c, aline, 0xe2);
		for (int a = 0; a < MAP_COLUMNS; a++)
		{
			aline[a] = Maze[i][a];
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
				g_Console.writeToBuffer(a, c.Y, abossline[a], 0x02);
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
	for (int i = 0; i < MAP_ROWS; i+=infoIncrement)
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
			if (i == 0)
			{
				for (int heartCounter = 0; heartCounter < Player.Health; heartCounter++)
				{
					g_Console.writeToBuffer(c.X + (heartCounter * 2), c.Y + 1, (char)3, 0xe4);
				}
			}
			c.X += Info[i / infoIncrement].length();
			g_Console.writeToBuffer(c, Number[i / infoIncrement], 0xe2);
			keySpacing += Info[3].length();
			for (int keyCounter = 0; keyCounter < NUM_OF_KEYS; keyCounter++)
			{
				if (Player.Key[keyCounter] == true)
				{
					g_Console.writeToBuffer(keySpacing + keyCounter, ((3 + 1) * infoIncrement - 2), (char)168, 0xe2);
					keySpacing += 1;
				}
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
		charColor = 0xe2;
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
					charColor = 0x00;
				}
				else
				{
					charColor = 0x02;
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
			charColor = 0x02;
		}
		break;
	}
	}
	
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)3, charColor);
}
void renderShootbossbullet()
{
	if (charWordBulletHold == true)
	{
		for (int i = 4; i >= -1;i--)
		{
			if (g_dElapsedTime > g_bBounceTime[i])
			{
				switch (i)
				{
				case 0:
				{
					Char = 0x03;
					charWordBulletCharge = i+1;
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
				}

				if (i==-1)
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
	moveenemy(Maze, g_enemy, g_sChar, timer, Direction);
	actionshoot(g_sChar, g_bullet, g_bulletP, g_portalEntrance, g_portalExit, aSomethingHappened, Maze, g_eBounceTime, g_eElapsedTime);
	moveCharacter(g_dBounceTime, g_dElapsedTime, g_sChar, g_Console, Key, DoorA, Maze,  Player, g_portalEntrance, g_portalExit, charbossX, charbossY, g_eGamemode);    // moves the character, collision detection, physics, etc, sound can be played here too.
	information();
}
void Bossone()
{
	bossMove();
	if (bossAttackOn[0] == true)
	{
		bossAttackLazer();
	}
	if (bossAttackOn[1] == true)
	{
		bossAttackMachineGunLeft();
	}
	if (bossAttackOn[2] == true)
	{
		bossAttackMachineGunRight();
	}
	moveCharacterInBoss(g_dBounceTime, g_eBounceTime, g_dElapsedTime, g_sChar, g_Console, BossMap, Player, characterIsHit);
	charshootboss();
	processUserInput();
	
	//bossAttackLazer();
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
			bossline = "   Boss HP (" + to_string(bossHealth) + "/" + to_string(bossMaxHealth) +")  ";
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
					if (((bossHealth* 20) / bossMaxHealth) >= (a - 20))
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
		}
		else
		{
			if (g_boss.m_cLocation.X > 30)
			{
				bossDirection = true;
			}
			g_boss.m_cLocation.X++;
		}
		rollForBossAttack = rand() % 3;
		switch (rollForBossAttack)
		{
		case 0:
		{	
			if (bossAttackOn[0] == false)
			{
			bossAttackOn[0] = true;
			}
			break;
		}
		case 1:
		{
			if (bossAttackOn[1] == false)
			{
				bossAttackOn[1] = true;
				break;
			}
		}
		case 2:
		{
			if (bossAttackOn[2] == false)
			{
				bossAttackOn[2] = true;
				break;
			}
		}
		}
		if (g_boss.m_cLocation.X < 5)
		{
			bossDirection = false;
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
bool upcheck(SGameChar Sprite)
{
	if ((Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == ' ') ||
		((Door == false) && ((Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == 'D') ||
		(Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == 'k') ||
		(Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == 'd'))))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool rightcheck(SGameChar Sprite)
{
	if ((Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == ' ') ||
		((Door == false) && ((Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == 'D') ||
		(Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == 'k') ||
			(Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == 'd'))))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool downcheck(SGameChar Sprite)
{
	if ((Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == ' ') ||
		((Door == false) && ((Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == 'D') ||
		(Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == 'k') ||
			(Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == 'd'))))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool leftcheck(SGameChar Sprite)
{
	if (((Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == ' ') ||
		((Door == false) && ((Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == 'D') ||
		(Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == 'k') ||
			(Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == 'd')))))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool upcheckB(SGameChar Sprite)
{
	if (Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == '.')
	{
		return true;
	}
	return false;
}
bool rightcheckB(SGameChar Sprite)
{
	if (Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == '.')
	{
		return true;
	}
	return false;
}
bool downcheckB(SGameChar Sprite)
{
	if (Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == '.')
	{
		return true;
	}
	return false;
}
bool leftcheckB(SGameChar Sprite)
{
	if (Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == '.')
	{
		return true;
	}
	return false;
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
	case S_BOSSONE:
	{
		Char = 0x02;
		delete[] *Maze;
		*Maze = new char[MAP_COLUMNS];
		g_sChar.m_cLocation.X = 32;
		g_sChar.m_cLocation.Y = 30;

		for (int i = 0; i < MAP_ROWS; i++)
		{
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				Maze[i][a] = BossMap[i][a];
			}
		}
		break;
	}
	}
}
void bossAttackLazer()
{
	g_bossMainGun.m_cLocation.X = g_boss.m_cLocation.X + 10;
	g_bossMainGun.m_cLocation.Y = g_boss.m_cLocation.Y + 13;

	bossAttackFrame[0]++;
	if (bossAttackFrame[0] > 15)
	{
		if (bossLazerMaxReached == true)
		{
			bossAttackMax--;
			if (bossAttackMax == 0)
			{
				bossLazerMaxReached = false;
				bossAttackOn[0] = false;
			}
		}
		else
		{
			if (bossAttackMax == 17)
			{
				bossLazerMaxReached = true;
			}
			if (bossAttackMax < 17)
			{
				bossAttackMax++;
			}
		}

		bossAttackFrame[0] = 0;
		k--;
		if (k == -1)
		{
			k = 7;
		}
	}

	COORD c;

	if (bossLazerMaxReached == true)
	{
		for (int i = 17 - bossAttackMax; i < 17; i++)
		{

			string bossAttackline = "0001111";
			string bossAttackBufferLine = "       ";
			c.Y = g_bossMainGun.m_cLocation.Y + i;
			for (int j = i; j < 7 + i; j++)
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
	else
	{
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

}

void bossAttackMachineGunLeft()
{
	g_bossSubGun1.m_cLocation.X = g_boss.m_cLocation.X + 4;
	g_bossSubGun1.m_cLocation.Y = g_boss.m_cLocation.Y + 8;

	bossAttackFrame[1]++;
	if (bossAttackFrame[1] % 10 == 0)
	{
		if (bossAttackFrame[1] > 50)
		{
			if (subBulletsAllCreated == false)
			{
				/*subBulletsToCreate++;
				for (; subBulletsCreated < subBulletsToCreate; subBulletsCreated++)
				{
					g_bossSubBullet.push_back(createBossSubBullet(g_bossSubGun1));
				}*/
				g_bossSubBullet.push_back(createBossSubBullet(g_bossSubGun1));
				subBulletsCreated++;
				if (subBulletsCreated == subBulletmax)
				{
					subBulletsAllCreated = true;
				}
			}
			bossAttackFrame[1] = 0;
		}
		for (int bulletCount = 0; bulletCount < subBulletsCreated; bulletCount++)
		{
			if (BossMap[g_bossSubBullet[bulletCount].m_cLocation.Y][g_bossSubBullet[bulletCount].m_cLocation.X] == (char)219)
			{
				g_bossSubBullet.erase(g_bossSubBullet.begin());
				subBulletsCreated--;

				if (subBulletsCreated == 0)
				{
					bossAttackOn[1] = false;
					subBulletsAllCreated = false;
					return;
				}
			}
			else
			{
				g_bossSubBullet[bulletCount].m_cLocation.Y++;
			}
		}
	}
	for (int bulletCount = 0; bulletCount < subBulletsCreated; bulletCount++)
	{
		BossMap[g_bossSubBullet[bulletCount].m_cLocation.Y - 1][g_bossSubBullet[bulletCount].m_cLocation.X] = '0';
	}
}
void bossAttackMachineGunRight()
{
	g_bossSubGun2.m_cLocation.X = g_boss.m_cLocation.X + 21;
	g_bossSubGun2.m_cLocation.Y = g_boss.m_cLocation.Y + 8;

	bossAttackFrame[2]++;
	if (bossAttackFrame[2] % 10 == 0)
	{
		if (bossAttackFrame[2] > 50)
		{
			if (subBulletsAllCreated2 == false)
			{
				/*subBulletsToCreate++;
				for (; subBulletsCreated < subBulletsToCreate; subBulletsCreated++)
				{
				g_bossSubBullet.push_back(createBossSubBullet(g_bossSubGun1));
				}*/
				g_bossSubBullet2.push_back(createBossSubBullet(g_bossSubGun2));
				subBulletsCreated2++;
				if (subBulletsCreated2 == subBulletmax)
				{
					subBulletsAllCreated2 = true;
				}
			}
			bossAttackFrame[2] = 0;
		}
		for (int bulletCount = 0; bulletCount < subBulletsCreated2; bulletCount++)
		{
			if (BossMap[g_bossSubBullet2[bulletCount].m_cLocation.Y][g_bossSubBullet2[bulletCount].m_cLocation.X] == (char)219)
			{
				g_bossSubBullet2.erase(g_bossSubBullet2.begin());
				subBulletsCreated2--;

				if (subBulletsCreated2 == 0)
				{
					bossAttackOn[2] = false;
					subBulletsAllCreated2 = false;
					return;
				}
			}
			else
			{
				g_bossSubBullet2[bulletCount].m_cLocation.Y++;
			}
		}
	}
	for (int bulletCount = 0; bulletCount < subBulletsCreated2; bulletCount++)
	{
		BossMap[g_bossSubBullet2[bulletCount].m_cLocation.Y - 1][g_bossSubBullet2[bulletCount].m_cLocation.X] = '0';
	}
}
void charshootboss()
{
	int i = 0;
	double j = 0.2;
	if (g_abKeyPressed[K_SPACE])
	{
		g_Wordbullet.m_cLocation.X = g_sChar.m_cLocation.X;
		g_Wordbullet.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
		charWordBullet = true;
		charWordBulletCharge = 0;
		if (charWordBulletHold == false)
		{
			for (; i < 5; i++, j+=0.5)
			{
				g_bBounceTime[i] = g_dElapsedTime + j;
			}
		}
		charWordBulletHold = true;
	}
	else
	{
		charWordBulletHold = false;
	}
	if (BossMap[g_Wordbullet.m_cLocation.Y - 1][g_Wordbullet.m_cLocation.X] == (char)219)
	{
		charWordBullet = false;
	}
	else if ((BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != ' ') &&
		(BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != '1') &&
		(BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != '0') &&
		(BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != (char)219) &&
		charWordBulletHold == false && charWordBullet == true)
	{
		charWordBullet = false;
		switch (charWordBulletCharge)
		{
		case 0:
		{
			bossHealth -= 1;
			break;
		}
		case 1:
		{
			bossHealth -= 3;
			break;
		}
		case 2:
		{
			bossHealth -= 5;
			break;
		}
		case 3:
		{
			bossHealth -= 8;
			break;
		}
		case 4:
		{
			bossHealth -= 10;
			break;
		}
		case 5:
		{
			bossHealth -= 15;
			break;
		}

		}
		g_Wordbullet.m_cLocation.X = g_sChar.m_cLocation.X;
		g_Wordbullet.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
	}

	if (charWordBullet == true)
	{
		g_Wordbullet.m_cLocation.Y--;
	}

}

SGameChar createBossSubBullet(SGameChar &SubGunStart)
{
	SGameChar tempChar;
	tempChar.m_cLocation.X = SubGunStart.m_cLocation.X;
	tempChar.m_cLocation.Y = SubGunStart.m_cLocation.Y;
	return tempChar;
}