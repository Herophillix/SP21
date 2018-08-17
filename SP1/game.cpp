
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
string bossmapline;
string aline;
string bossline;
char *Maze[32];
char *BossMap[32];
char *BossChar[27];
//int *SplashMaze[32];
bool Bulletpos = false;
bool BulletposPRed = false;
bool BulletposPBlue = false;
int ShootDirection = 2;
int ShootDirectionFinal = 2;
bool Door = true;
bool Portal = false;
int bossInterval = 0;
bool bossDirection = false;
int bossAttackMax = 0;
int bossAttackFrame = 0;
int k = 0;
bool charWordBullet = false;
int bossHealth = 100;

bool g_bStartGame = false;
int g_bStartFrame = 0;

double  g_dElapsedTime;
double  g_eElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar, g_bullet, g_bulletP, g_portalEntrance, g_portalExit, g_boss, g_bossMainGun ,g_bossSubGun1, g_bossSubGun2,g_Wordbullet;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EGAMEMODES  g_eGamemode = S_STAGEONE; /////// <---- Edit stageeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
double  g_dBounceTime;
double  g_eBounceTime;// this is to prevent key bouncing, so we won't trigger keypresses more than once

const int NUM_COLUMNS = 120;
const int NUM_ROWS = 40;

const int MAP_COLUMNS = 64;
const int MAP_ROWS = 32;

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

	g_sChar.m_cLocation.X = 2;
	g_sChar.m_cLocation.Y = 3;
	g_sChar.m_bActive = true;
	g_boss.m_cLocation.X = 10;
	g_boss.m_cLocation.Y = 2;


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
			BossChar[i] = new char [Columns];
			getline(bossChar, bossline);
			for (int a = 0; a < 27;a++)
			{
				BossChar[i][a] = bossline[a];
			}
		}
		bossChar.close();
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
	if (g_eGamemode == S_STAGEONE)
	{
		renderMap();        // renders the map to the buffer first 
		renderCharacter();  // renders the character into the buffer
		renderbullet();
		renderbulletPRed();
		renderbulletPBlue();
		renderBossChar();
	}
	else if (g_eGamemode == S_BOSSONE)
	{
		renderBossmap();
		renderCharacter();
		//renderbossattack();
		renderShootbossbullet();
		renderBossHealth();

	}
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
				g_Console.writeToBuffer(a, i + 1, aline[a], 0x60);
			}
			if (a == g_portalExit.m_cLocation.X && i == g_portalExit.m_cLocation.Y)
			{
				aline[a] = (char)177;
				g_Console.writeToBuffer(a, i + 1, aline[a], 0x1f);
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
void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0x04;
	if (g_sChar.m_bActive)
	{
		charColor = 0x04;
	}
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
	moveCharacter();    // moves the character, collision detection, physics, etc
						// sound can be played here too.
	shoot();
	movebullet();
	shootPRed();
	movebulletPRed();
	shootPBlue();
	movebulletPBlue();
}
void Bossone()
{
	bossMove();
	moveCharacter();
	charshootboss();
	processUserInput();
	bossAttackLazer();
	/*movecharbullet();*/
	
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

void renderBossChar()
{
	//render boss @ location onto first map 
	g_Console.writeToBuffer(4,3, (char)64);
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
					g_Console.writeToBuffer(20, c.Y, bossline[a-20], 0xFF);
					break;
				}
				case 41:
				{
					g_Console.writeToBuffer(a, c.Y, bossline[a-20], 0xFF);
					break;
				}
				default:
				{
					if ((bossHealth / 5) >= (a - 20))
					{
						g_Console.writeToBuffer(a, c.Y, bossline[a-20], 0x44);
					}
					else
					{
						g_Console.writeToBuffer(a, c.Y, bossline[a-20], 0x00);
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
	if ((g_sChar.m_cLocation.Y == 3) && (g_sChar.m_cLocation.X == 4))
	{
		g_eGamemode = S_BOSSONE;
		changeMap();
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
			else if (((g_bullet.m_cLocation.Y - 1 == 28) && (g_bullet.m_cLocation.X - 1 == 54)))
			{
				g_bullet.m_cLocation.X = 43;
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
		ShootDirectionFinal = ShootDirection;
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

void changeMap()
{
	switch (g_eGameState)
	{
	case S_BOSSONE:
		{
		g_sChar.m_cLocation.X = 32;
		g_sChar.m_cLocation.Y = 30;

			for (int i = 0; i < MAP_ROWS;i++)
			{
				for (int a = 0; a < MAP_COLUMNS;a++)
				{
					Maze[i][a] = BossMap[i][a];
				}
			}	
			break;
		}
	}
}

//void renderbossattack()
//{
//	bossAttackFrame++;
//	if (bossAttackFrame > 15)
//	{
//		if (bossAttackMax < 17)
//		{
//			bossAttackMax++;
//		}
//		bossAttackFrame = 0;
//		k--;
//		if (k == -1)
//		{
//			k = 7;
//		}
//	}
//	bool bossMoves[2] = { 1, 1 };
//	if (bossMoves[0] == true)
//	{
//		COORD c;
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
//					//switch (bossAttackBufferLine[a])
//					//{
//					//case '0':
//					//{
//					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 3, c.Y, bossAttackBufferLine[a], 0x40);
//					//	break;
//					//}
//					//case '1':
//					//{
//					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 3, c.Y, bossAttackBufferLine[a], 0xe0);
//					//	break;
//					//}
//					//}
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
//					//switch (bossAttackBufferLine[a])
//					//{
//					//case '0':
//					//{
//					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 2 + a, c.Y, bossAttackBufferLine[a], 0x40);
//					//	break;
//					//}
//					//case '1':
//					//{
//					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 2 + a, c.Y, bossAttackBufferLine[a], 0xe0);
//					//	break;
//					//}
//					//}
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
//					//switch (bossAttackBufferLine[a])
//					//{
//					//case '0':
//					//{
//					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 1 + a, c.Y, bossAttackBufferLine[a], 0x40);
//					//	break;
//					//}
//					//case '1':
//					//{
//					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 1 + a, c.Y, bossAttackBufferLine[a], 0xe0);
//					//	break;
//					//}
//					//}
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
//					//switch (bossAttackBufferLine[a])
//					//{
//					//case '0':
//					//{
//					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + a, c.Y, bossAttackBufferLine[a], 0x40);
//					//	break;
//					//}
//					//case '1':
//					//{
//					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + a, c.Y, bossAttackBufferLine[a], 0xe0);
//					//	break;
//					//}
//					//}
//				}
//			}
//			}
//		}
//	}
//	if (bossMoves[1] == true)
//	{
//		if (bossAttackFrame == 10)
//		{
//
//		}
//	}
//}

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
					//switch (bossAttackBufferLine[a])
					//{
					//case '0':
					//{
					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 3, c.Y, bossAttackBufferLine[a], 0x40);
					//	break;
					//}
					//case '1':
					//{
					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 3, c.Y, bossAttackBufferLine[a], 0xe0);
					//	break;
					//}
					//}
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
					//switch (bossAttackBufferLine[a])
					//{
					//case '0':
					//{
					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 2 + a, c.Y, bossAttackBufferLine[a], 0x40);
					//	break;
					//}
					//case '1':
					//{
					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 2 + a, c.Y, bossAttackBufferLine[a], 0xe0);
					//	break;
					//}
					//}
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
					//switch (bossAttackBufferLine[a])
					//{
					//case '0':
					//{
					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 1 + a, c.Y, bossAttackBufferLine[a], 0x40);
					//	break;
					//}
					//case '1':
					//{
					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + 1 + a, c.Y, bossAttackBufferLine[a], 0xe0);
					//	break;
					//}
					//}
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
					//switch (bossAttackBufferLine[a])
					//{
					//case '0':
					//{
					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + a, c.Y, bossAttackBufferLine[a], 0x40);
					//	break;
					//}
					//case '1':
					//{
					//	g_Console.writeToBuffer(g_bossMainGun.m_cLocation.X + a, c.Y, bossAttackBufferLine[a], 0xe0);
					//	break;
					//}
					//}
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
void movecharbullet()
{
	/*g_Wordbullet.m_cLocation.Y--;*/
}