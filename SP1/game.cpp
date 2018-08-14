
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
const int MAP_COLUMNS = 64;
const int MAP_ROWS = 32;
string line;
string aline;
int *Maze[MAP_ROWS];
//int *SplashMaze[32];
bool Bulletpos = false;
bool BulletposPRed = false;
bool BulletposPBlue = false;
int ShootDirection = 2;
int ShootDirectionFinal = 2;
int ShootDirectionFinalBlue  = 2;
int ShootDirectionEnemy = 2;
bool Door = true;
bool Portal = false;
int timer;
const int enemylocationX = 50;
const int enemylocationY = 29;

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
			Maze[i] = new int[Columns];
			getline(mapOne, line);
			for (int a = 0; a < MAP_COLUMNS; a++)
			{
				if ((line[a] == 43) || (line[a] == 124) || (line[a] == 45))
				{
					line[a] = (char)219;
				}
				else if (line[a] == 'a')
				{
					line[a] = (char)176;
				}
				else if (line[a] == 'A')
				{
					line[a] = (char)178;
				}
				Maze[i][a] = line[a];
			}
	
		}
		mapOne.close();
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
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_NUMPAD0] = isKeyPressed(VK_NUMPAD0);
	g_abKeyPressed[K_NUMPAD1] = isKeyPressed(VK_NUMPAD1);
	g_abKeyPressed[K_NUMPAD2] = isKeyPressed(VK_NUMPAD2);
	g_abKeyPressed[K_E] = isKeyPressed(69);

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

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_abKeyPressed[K_SPACE])
		g_bStartGame = true;
	if (g_bStartGame == true) // wait for 3 seconds to switch to game mode, else do nothing
		g_eGameState = S_GAME;
}


void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0xe2);
}

void renderSplashScreen()  // renders the splash screen
{
	if (g_bStartFrame < 40)
	{
		ifstream splashScreen("Gametitle.txt");
		if (splashScreen.is_open())
		{
			for (int i = 0; i < NUM_ROWS; i++)
			{
				int Columns = NUM_COLUMNS;
				//SplashMaze[i] = new int[Columns];
				getline(splashScreen, line);

				COORD c;
				c.X = 0;
				c.Y = i + 1;
				if (i < 8 && i > 2)
				{
					g_Console.writeToBuffer(c, line, 0x99f);
				}
				else
				{
					g_Console.writeToBuffer(c, line, 0xe2);
				}
			}
			splashScreen.close();
		}
	}
	else
	{
		ifstream splashScreen("Gametitle2.txt");
		if (splashScreen.is_open())
		{
			for (int i = 0; i < NUM_ROWS; i++)
			{
				int Columns = NUM_COLUMNS;
				//SplashMaze[i] = new int[Columns];
				getline(splashScreen, line);

				COORD c;
				c.X = 0;
				c.Y = i + 1;

				if (i < 9 && i > 3)
				{
					g_Console.writeToBuffer(c, line, 0x33f);
				}
				else if (i < MAP_COLUMNS && i > 19)
				{
					g_Console.writeToBuffer(c, line, 40);
				}
				else
				{
					g_Console.writeToBuffer(c, line, 0xe2);
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

		for (int a = 0; a < MAP_COLUMNS; a++)
		{
			c.X = 0;
			c.Y = i + 1;
			aline[a] = Maze[i][a];
			if (Door == true)
			{
				if (aline[a] == 'k')
				{
					aline[a] = (char)254;
				}
				else if (aline[a] == 'D')
				{
					aline[a] = (char)219;
				}
			}
			else
			{
				if ((aline[a] == 'k') || (aline[a] == 'D'))
				{
					aline[a] = ' ';
				}
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
		}
	}
}

void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0xe2;
	if (g_sChar.m_bActive)
	{
		charColor = 0xe2;
	}
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)3, charColor);
}
void renderenemy()
{
	// Draw the location of the character
	WORD enemyColor = 0x0C;
	if (g_enemy.m_bActive)
	{
		enemyColor = 0x0A;
	}
	g_Console.writeToBuffer(g_enemy.m_cLocation, (char)1, enemyColor);
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

void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
	moveenemy();				// sound can be played here too.
	shoot();
	movebullet();
	shootPRed();
	movebulletPRed();
	shootPBlue();
	movebulletPBlue();
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
			ShootDirection = 1;
		}
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		if (rightcheck(g_sChar))
		{
			g_sChar.m_cLocation.X++;
			ShootDirection = 2;
		}
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		if (downcheck(g_sChar))
		{
			g_sChar.m_cLocation.Y++;
			ShootDirection = 3;
		}
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		if (leftcheck(g_sChar))
		{
			g_sChar.m_cLocation.X--;
			ShootDirection = 4;
		}
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_E])
	{
		if ((Maze[g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'k') || 
			(Maze[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 1] == 'k') || 
			(Maze[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'k') || 
			(Maze[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 1] == 'k'))
		{
			Door = false;
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
	if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.0875; // 125ms should be enough
	}
}

void shoot()
{
	bool aSomethingHappened = false;
	if (g_eBounceTime > g_eElapsedTime)
		return;
	if (g_abKeyPressed[K_NUMPAD0])
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
				ShootDirectionFinal = ShootDirectionFinalBlue + 2;
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
				ShootDirectionFinal = ShootDirectionFinalBlue + 2;
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
				ShootDirectionFinal = ShootDirectionFinalBlue - 2;
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
				ShootDirectionFinal = ShootDirectionFinalBlue - 2;
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
	if (g_abKeyPressed[K_NUMPAD1])
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
		ShootDirectionFinal = ShootDirection;
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
	if (g_abKeyPressed[K_NUMPAD2])
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
		switch (ShootDirectionFinal)
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
				g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y - 2;
				g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X;
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
				g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
				g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X + 1;
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
				g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y;
				g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X;
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
				g_portalEntrance.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
				g_portalEntrance.m_cLocation.X = g_bulletP.m_cLocation.X - 1;
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
				g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y - 2;
				g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X;
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
				g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
				g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X + 1;
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
				g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y;
				g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X;
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
				g_portalExit.m_cLocation.Y = g_bulletP.m_cLocation.Y - 1;
				g_portalExit.m_cLocation.X = g_bulletP.m_cLocation.X - 1;
				BulletposPBlue = false;
			}
			break;
		}
		}
	}
}

bool upcheck(SGameChar Sprite)
{
	if ((Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == ' ') ||
		((Door == false) && ((Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == 'D') ||
		(Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == 'k'))))
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
		(Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == 'k'))))
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
		(Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == 'k'))))
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
		(Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == 'k')))))
	{
		return true;
	}
	else
	{
		return false;
	}
}
