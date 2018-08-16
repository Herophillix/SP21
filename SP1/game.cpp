
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

string line;
string aline;

char *Maze[MAP_ROWS];
char *SplashMaze[MAP_ROWS];

bool Bulletpos = false;
bool BulletposPRed = false;
bool BulletposPBlue = false;

int ShootDirection = 2;
int ShootDirectionFinal = 2;
int ShootDirectionFinalRed = 2;
int ShootDirectionFinalBlue  = 2;
int ShootDirectionEnemy = 2;
int d = 0;
int e = 0;
int q = 0;
int ItemNumber = 0;

bool Door = true;
bool Portal = false;

int timer;

const int enemylocationX = 50;
const int enemylocationY = 29;

int bulletcondition = 1;

PlayerInformation Player;
KDInformation Key, DoorA;

bool g_bStartGame = false;
int g_bStartFrame = 0;

double  g_dElapsedTime;
double  g_eElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar, g_enemy, g_bullet, g_bulletP, g_portalEntrance, g_portalExit;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime;
double  g_eBounceTime;// this is to prevent key bouncing, so we won't trigger keypresses more than once

const int NUM_COLUMNS = 120;
const int NUM_ROWS = 40;

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

	g_enemy.m_cLocation.X = enemylocationX;
	g_enemy.m_cLocation.Y = enemylocationY;
	g_enemy.m_bActive = true;

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
			int Columns = MAP_COLUMNS;
			Maze[i] = new char[Columns];
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
					/*switch (e)
					{
					case 0:
					{
						DoorA.Location[e].X = a;
						DoorA.Location[e].Y = i + 1;
						DoorA.id[e] = 0;
						break;
					}
					case 1:
					{
						DoorA.Location[e].X = a;
						DoorA.Location[e].Y = i + 1;
						DoorA.id[e] = 1;
						break;
					}
					case 2:
					{
						DoorA.Location[e].X = a;
						DoorA.Location[e].Y = i + 1;
						DoorA.id[e] = 3;
						break;
					}
					case 3:
					{
						DoorA.Location[e].X = a;
						DoorA.Location[e].Y = i + 1;
						DoorA.id[e] = 5;
						break;
					}
					case 4:
					{
						DoorA.Location[e].X = a;
						DoorA.Location[e].Y = i + 1;
						DoorA.id[e] = 6;
						break;
					}
					case 5:
					{
						DoorA.Location[e].X = a;
						DoorA.Location[e].Y = i + 1;
						DoorA.id[e] = 4;
						break;
					}
					case 6:
					{
						DoorA.Location[e].X = a;
						DoorA.Location[e].Y = i + 1;
						DoorA.id[e] = e;
						break;
					}*/
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
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_1] = isKeyPressed(0x31);
	g_abKeyPressed[K_2] = isKeyPressed(0x32);
	g_abKeyPressed[K_3] = isKeyPressed(0x33);
	g_abKeyPressed[K_NUMPAD0] = isKeyPressed(VK_NUMPAD0);
	g_abKeyPressed[K_NUMPAD1] = isKeyPressed(VK_NUMPAD1);
	g_abKeyPressed[K_NUMPAD2] = isKeyPressed(VK_NUMPAD2);
	g_abKeyPressed[K_E] = isKeyPressed(0x45);
	g_abKeyPressed[K_Q] = isKeyPressed(0x51);

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
							switch (line[a])
							{
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
	renderMap();        // renders the map to the buffer first 
	renderInfo();
	renderCharacter();  // renders the character into the buffer
	renderenemy();
	renderbullet();
	renderbulletPRed();
	renderbulletPBlue();
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
			if (q < NUM_OF_KEYS)
			{
				q++;
			}
			else
			{
				q = 0;
			}
		}
	}
}

void renderInfo()
{
	for (int i = 0; i < MAP_ROWS; i+=2)
	{
		COORD c;
		c.X = 66;
		c.Y = i + 1;
		string Info[4] = { "Player Health: ", "Points: ", "Current Weapon: ", "Keys: " };
		string Number[4] = { to_string(Player.Health), to_string(Player.Points), to_string(Player.CurrentWeapon), };
		if (i < 8)
		{
			g_Console.writeToBuffer(c, Info[i / 2], 0xe2);
			c.X += Info[i / 2].length();
			g_Console.writeToBuffer(c, Number[i / 2], 0xe2);
		}
	}

}

void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0xe2;
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)3, charColor);
}

void renderenemy()
{
	// Draw the location of the character
	WORD enemyColor = 0x0C;
	g_Console.writeToBuffer(g_enemy.m_cLocation, (char)1, enemyColor);
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
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
	moveenemy();				// sound can be played here too.
	bulletchoice();
	movebullet();
	movebulletPRed();
	movebulletPBlue();
	information();
}

void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 1)
	{
		//Beep(1440, 30);
		if (upcheck(g_sChar))
		{
			g_sChar.m_cLocation.Y--;
		}
		ShootDirection = 1;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		if (rightcheck(g_sChar))
		{
			g_sChar.m_cLocation.X++;
		}
		ShootDirection = 2;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		if (downcheck(g_sChar))
		{
			g_sChar.m_cLocation.Y++;
		}
		ShootDirection = 3;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		if (leftcheck(g_sChar))
		{
			g_sChar.m_cLocation.X--;
		}
		ShootDirection = 4;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_E])
	{
		for (int ItemNumber = 0; ItemNumber < NUM_OF_KEYS; ItemNumber++)
		{
			if (doorcheck(Key, ItemNumber))
			{
				Key.Checker[Key.id[ItemNumber]] = true;
				DoorA.Checker[Key.id[ItemNumber]] = true;
				Maze[Key.Location[ItemNumber].Y - 1][Key.Location[ItemNumber].X] = ' ';
				ItemNumber = NUM_OF_KEYS;
			}
			else if (doorcheck(DoorA, ItemNumber))
			{
				for (int i = 0; i < MAP_ROWS; i++)
				{
					for (int a = 0; a < MAP_COLUMNS; a++)
					{
 						if ((DoorA.Sides[DoorA.id[ItemNumber]].AdjacentSides[a].X != 0) && (DoorA.Sides[DoorA.id[ItemNumber]].AdjacentSides[a].Y != 0))
						{
							if (Key.Checker[ItemNumber] == DoorA.Checker[DoorA.id[ItemNumber]])
							{
								Maze[DoorA.Location[ItemNumber].Y - 1][DoorA.Location[ItemNumber].X] = ' ';
								Maze[DoorA.Sides[ItemNumber].AdjacentSides[a].Y][DoorA.Sides[ItemNumber].AdjacentSides[a].X] = ' ';
							}
						}
					}
				}
			}
		}
		if (((g_sChar.m_cLocation.Y - 2 == g_portalEntrance.m_cLocation.Y) && (g_sChar.m_cLocation.X == g_portalEntrance.m_cLocation.X)) ||
			((g_sChar.m_cLocation.Y - 1 == g_portalEntrance.m_cLocation.Y) && (g_sChar.m_cLocation.X + 1 == g_portalEntrance.m_cLocation.X)) ||
			((g_sChar.m_cLocation.Y == g_portalEntrance.m_cLocation.Y) && (g_sChar.m_cLocation.X == g_portalEntrance.m_cLocation.X)) ||
			((g_sChar.m_cLocation.Y - 1 == g_portalEntrance.m_cLocation.Y) && (g_sChar.m_cLocation.X - 1 == g_portalEntrance.m_cLocation.X)))
		{
			g_sChar.m_cLocation.Y = g_portalExit.m_cLocation.Y + 1;
			g_sChar.m_cLocation.X = g_portalExit.m_cLocation.X;
		}
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.0875; // 125ms should be enough
	}
}

void moveenemy()
{
	timer++;
	//int num = rand() % 4 +1;
	//if (timer > 10)
	//{
	//	if (num == 1 && g_enemy.m_cLocation.Y > 1)
	//	{

	//	if (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] != (char)219)
	//	{
	//	g_enemy.m_cLocation.Y--;
	//	ShootDirection = 1;
	//	}
	//	}
	//	else if (num == 2 && g_enemy.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	//	{
	//	if (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] != (char)219)
	//	{
	//	g_enemy.m_cLocation.Y++;
	//	ShootDirection = 3;
	//	}
	//	}
	//	else if (num == 3 && g_enemy.m_cLocation.X > 0)
	//	{
	//	if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] != (char)219)
	//	{
	//	g_enemy.m_cLocation.X--;
	//	ShootDirection = 4;
	//	}
	//	}
	//	else if (num == 4 && g_enemy.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	//	{
	//	if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] != (char)219)
	//	{
	//	g_enemy.m_cLocation.X++;
	//	ShootDirection = 2;
	//	}
	//	timer = 0;
	//	}
	//}
	//^crazy ai

	if (g_enemy.m_bActive = true)
	{
		if (timer > 10)
		{
			if (g_enemy.m_cLocation.Y == enemylocationY && g_enemy.m_cLocation.X != enemylocationX + 2)
			{
				g_enemy.m_cLocation.X++;
				ShootDirectionEnemy = 2;
			}
			else if (g_enemy.m_cLocation.X == enemylocationX + 2 && g_enemy.m_cLocation.Y != enemylocationY - 1)
			{
				g_enemy.m_cLocation.Y--;
				ShootDirectionEnemy = 1;
			}
			else if (g_enemy.m_cLocation.Y == enemylocationY - 1 && g_enemy.m_cLocation.X != enemylocationX - 5)
			{
				g_enemy.m_cLocation.X--;
				ShootDirectionEnemy = 4;
			}
			else
			{
				g_enemy.m_cLocation.Y++;
				ShootDirectionEnemy = 3;
			}
			timer = 0;
		}

	}
}

void bulletchoice()
{
	if (g_abKeyPressed[K_1])
	{
		bulletcondition = 1;
	}
	else if (g_abKeyPressed[K_2])
	{
		bulletcondition = 2;
	}
	else if (g_abKeyPressed[K_3])
	{
		bulletcondition = 3;
	}
	else if (g_abKeyPressed[K_Q])
	{
		if (g_eBounceTime > g_eElapsedTime)
			return;
		bulletcondition = bulletcondition % 3 + 1;
		g_eBounceTime = g_eElapsedTime + 0.25;
	}
	switch (bulletcondition)
	{
	case 1:
	{
		shoot();
		break;
	}
	case 2:
	{
		shootPRed();
		break;
	}
	case 3:
	{
		shootPBlue();
		break;
	}
	}
}
 
void shoot()
{
	bool aSomethingHappened = false;
	if (g_eBounceTime > g_eElapsedTime)
		return;
	if (g_abKeyPressed[K_SPACE])
	{
		switch (ShootDirection)
		{
		case 1:
		{
			g_bullet.m_cLocation.X = g_sChar.m_cLocation.X;
			g_bullet.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
			break;
		}
		case 2:
		{
			g_bullet.m_cLocation.X = g_sChar.m_cLocation.X + 1;
			g_bullet.m_cLocation.Y = g_sChar.m_cLocation.Y;
			break;
		}
		case 3:
		{
			g_bullet.m_cLocation.X = g_sChar.m_cLocation.X;
			g_bullet.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;
			break;
		}
		case 4:
		{
			g_bullet.m_cLocation.X = g_sChar.m_cLocation.X - 1;
			g_bullet.m_cLocation.Y = g_sChar.m_cLocation.Y;
			break;
		}
		}
		ShootDirectionFinal = ShootDirection;
		aSomethingHappened = true;
		Bulletpos = true;
	}
	if (aSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_eBounceTime = g_eElapsedTime + 1.0; // 125ms should be enough
	}
}

void movebullet()
{
	if (Bulletpos == true)
	{
		switch (ShootDirectionFinal)
		{
		case 1:
		{
			if (upcheck(g_bullet))
			{
				g_bullet.m_cLocation.Y--;
			}
			else if (((g_bullet.m_cLocation.Y - 2 == g_portalEntrance.m_cLocation.Y) && (g_bullet.m_cLocation.X == g_portalEntrance.m_cLocation.X)))
			{
				ShootDirectionFinal = bulletAfterPortal();
				g_bullet.m_cLocation.Y = g_portalExit.m_cLocation.Y + 1;
				g_bullet.m_cLocation.X = g_portalExit.m_cLocation.X;
			}
			else
			{
				Bulletpos = false;
			}
			break;
		}
		case 2:
		{
			if (rightcheck(g_bullet))
			{
				g_bullet.m_cLocation.X++;
			}
			else if (((g_bullet.m_cLocation.Y - 1 == g_portalEntrance.m_cLocation.Y) && (g_bullet.m_cLocation.X + 1 == g_portalEntrance.m_cLocation.X)))
			{
				ShootDirectionFinal = bulletAfterPortal();
				g_bullet.m_cLocation.Y = g_portalExit.m_cLocation.Y + 1;
				g_bullet.m_cLocation.X = g_portalExit.m_cLocation.X;
			}
			else
			{
				Bulletpos = false;
			}
			break;
		}
		case 3:
		{
			if (downcheck(g_bullet))
			{
				g_bullet.m_cLocation.Y++;
			}
			else if (((g_bullet.m_cLocation.Y == g_portalEntrance.m_cLocation.Y) && (g_bullet.m_cLocation.X == g_portalEntrance.m_cLocation.X)))
			{
				ShootDirectionFinal = bulletAfterPortal();
				g_bullet.m_cLocation.Y = g_portalExit.m_cLocation.Y + 1;
				g_bullet.m_cLocation.X = g_portalExit.m_cLocation.X;
			}
			else
			{
				Bulletpos = false;
			}
			break;
		}
		case 4:
		{
			if (leftcheck(g_bullet))
			{
				g_bullet.m_cLocation.X--;
			}
			else if (((g_bullet.m_cLocation.Y - 1 == g_portalEntrance.m_cLocation.Y) && (g_bullet.m_cLocation.X - 1 == g_portalEntrance.m_cLocation.X)))
			{
				ShootDirectionFinal = bulletAfterPortal();
				g_bullet.m_cLocation.Y = g_portalExit.m_cLocation.Y + 1;
				g_bullet.m_cLocation.X = g_portalExit.m_cLocation.X;
			}
			else
			{
				Bulletpos = false;
			}
			break;
		}
		}
	}
}

void shootPRed()
{
	bool aSomethingHappened = false;
	if (g_eBounceTime > g_eElapsedTime)
		return;
	if (g_abKeyPressed[K_SPACE])
	{
		switch (ShootDirection)
		{
		case 1:
		{
			g_bulletP.m_cLocation.X = g_sChar.m_cLocation.X;
			g_bulletP.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
			break;
		}
		case 2:
		{
			g_bulletP.m_cLocation.X = g_sChar.m_cLocation.X + 1;
			g_bulletP.m_cLocation.Y = g_sChar.m_cLocation.Y;
			break;
		}
		case 3:
		{
			g_bulletP.m_cLocation.X = g_sChar.m_cLocation.X;
			g_bulletP.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;
			break;
		}
		case 4:
		{
			g_bulletP.m_cLocation.X = g_sChar.m_cLocation.X - 1;
			g_bulletP.m_cLocation.Y = g_sChar.m_cLocation.Y;
			break;
		}
		}
		ShootDirectionFinalRed = ShootDirection;
		aSomethingHappened = true;
		BulletposPRed = true;
	}
	if (aSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_eBounceTime = g_eElapsedTime + 1.0; // 125ms should be enough
	}
}

void shootPBlue()
{
	bool aSomethingHappened = false;
	if (g_eBounceTime > g_eElapsedTime)
		return;
	if (g_abKeyPressed[K_SPACE])
	{
		switch (ShootDirection)
		{
		case 1:
		{
			g_bulletP.m_cLocation.X = g_sChar.m_cLocation.X;
			g_bulletP.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
			break;
		}
		case 2:
		{
			g_bulletP.m_cLocation.X = g_sChar.m_cLocation.X + 1;
			g_bulletP.m_cLocation.Y = g_sChar.m_cLocation.Y;
			break;
		}
		case 3:
		{
			g_bulletP.m_cLocation.X = g_sChar.m_cLocation.X;
			g_bulletP.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;
			break;
		}
		case 4:
		{
			g_bulletP.m_cLocation.X = g_sChar.m_cLocation.X - 1;
			g_bulletP.m_cLocation.Y = g_sChar.m_cLocation.Y;
			break;
		}
		}
		ShootDirectionFinalBlue = ShootDirection;
		aSomethingHappened = true;
		BulletposPBlue = true;
	}
	if (aSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_eBounceTime = g_eElapsedTime + 1.0; // 125ms should be enough
	}
}

void movebulletPRed()
{
	if (BulletposPRed == true)
	{
		switch (ShootDirectionFinalRed)
		{
		case 1:
		{
			if (upcheck(g_bulletP))
			{
				g_bulletP.m_cLocation.Y--;
			}
			else if (Maze[g_bulletP.m_cLocation.Y - 2][g_bulletP.m_cLocation.X] != (char)219) 
			{
				BulletposPRed = false;
			}
			else
			{ 
				if (Maze[g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] != (char)219)
				{
					g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y - 2;
					g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X;
				}
				else
				{
					g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X;
				}
				BulletposPRed = false;
			}
			break;
		}
		case 2:
		{
			if (rightcheck(g_bulletP))
			{
				g_bulletP.m_cLocation.X++;
			}
			else if (Maze[g_bulletP.m_cLocation.Y - 1][g_bulletP.m_cLocation.X + 1] != (char)219)
			{
				BulletposPRed = false;
			}
			else
			{
				if (Maze[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 1] != (char)219)
				{
					g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X + 1;
				}
				else
				{
					g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X;
				}
				BulletposPRed = false;
			}
			break;
		}
		case 3:
		{
			if (downcheck(g_bulletP))
			{
				g_bulletP.m_cLocation.Y++;
			}
			else if (Maze[g_bulletP.m_cLocation.Y][g_bulletP.m_cLocation.X] != (char)219)
			{
				BulletposPRed = false;
			}
			else
			{
				if (Maze[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] != (char)219)
				{
					g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y;
					g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X;
				}
				else
				{
					g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X;
				}
				BulletposPRed = false;
			}
			break;
		}
		case 4:
		{
			if (leftcheck(g_bulletP))
			{
				g_bulletP.m_cLocation.X--;
			}
			else if (Maze[g_bulletP.m_cLocation.Y - 1][g_bulletP.m_cLocation.X - 1] != (char)219)
			{
				BulletposPRed = false;
			}
			else
			{
				if (Maze[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 1] != (char)219)
				{
					g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X - 1;
				}
				else
				{
					g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X;
				}
				BulletposPRed = false;
			}
			break;
		}
		}
	}
}

void movebulletPBlue()
{
	if (BulletposPBlue == true)
	{
		switch (ShootDirectionFinalBlue)
		{
		case 1:
		{
			if (upcheck(g_bulletP))
			{
				g_bulletP.m_cLocation.Y--;
			}
			else if (Maze[g_bulletP.m_cLocation.Y - 2][g_bulletP.m_cLocation.X] != (char)219)
			{
				BulletposPBlue = false;
			}
			else
			{
				if (Maze[g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] != (char)219)
				{
					g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y - 2;
					g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X;
				}
				else
				{
					g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X;
				}
				BulletposPBlue = false;
			}
			break;
		}
		case 2:
		{
			if (rightcheck(g_bulletP))
			{
				g_bulletP.m_cLocation.X++;
			}
			else if (Maze[g_bulletP.m_cLocation.Y - 1][g_bulletP.m_cLocation.X + 1] != (char)219)
			{
				BulletposPBlue = false;
			}
			else
			{
				if (Maze[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 1] != (char)219)
				{
					g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X + 1;
				}
				else
				{
					g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X;
				}
				BulletposPBlue = false;
			}
			break;
		}
		case 3:
		{
			if (downcheck(g_bulletP))
			{
				g_bulletP.m_cLocation.Y++;
			}
			else if (Maze[g_bulletP.m_cLocation.Y][g_bulletP.m_cLocation.X] != (char)219)
			{
				BulletposPBlue = false;
			}
			else
			{
if (Maze[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] != (char)219)
{
	g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y;
	g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X;
}
else
{
	g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
	g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X;
}
BulletposPBlue = false;
			}
			break;
		}
		case 4:
		{
			if (leftcheck(g_bulletP))
			{
				g_bulletP.m_cLocation.X--;
			}
			else if (Maze[g_bulletP.m_cLocation.Y - 1][g_bulletP.m_cLocation.X - 1] != (char)219)
			{
				BulletposPBlue = false;
			}
			else
			{
				if (Maze[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 1] != (char)219)
				{
					g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X - 1;
				}
				else
				{
					g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
					g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X;
				}
				BulletposPBlue = false;
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

int bulletAfterPortal()
{
	int BulletDirection = ShootDirectionFinalBlue;
	switch (BulletDirection)
	{
	case 1:
	{
		BulletDirection += 2;
		break;
	}
	case 2:
	{
		BulletDirection += 2;
		break;
	}
	case 3:
	{
		BulletDirection -= 2;
		break;
	}
	case 4:
	{
		BulletDirection -= 2;
		break;
	}
	}
	return BulletDirection;
}
