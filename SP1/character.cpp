#include "game.h"
#include "move.h"
#include "Framework\console.h"
bool isKeyPressedMove[K_COUNT];

void getInputmove()
{
	isKeyPressedMove[K_UP] = isKeyPressed(VK_UP);
	isKeyPressedMove[K_DOWN] = isKeyPressed(VK_DOWN);
	isKeyPressedMove[K_LEFT] = isKeyPressed(VK_LEFT);
	isKeyPressedMove[K_RIGHT] = isKeyPressed(VK_RIGHT);
	isKeyPressedMove[K_SPACE] = isKeyPressed(VK_SPACE);
	isKeyPressedMove[K_E] = isKeyPressed(0x45);
}

void moveCharacter(double &g_dBounceTime, double &g_dElapsedTime,SGameChar &g_sChar, Console &g_Console, KDInformation &Key, KDInformation &DoorA,
	char **Maze, PlayerInformation &Player, SGameChar &g_portalEntrance, SGameChar &g_portalExit, int &charbossX, int &charbossY, EGAMEMODES &g_eGamemode)
{
	getInputmove();
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (isKeyPressedMove[K_UP] && g_sChar.m_cLocation.Y > 1)
	{
		//Beep(1440, 30);
		if (upcheck(g_sChar, Maze))
		{
			g_sChar.m_cLocation.Y--;
		}
		ShootDirection = 1;
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		if (rightcheck(g_sChar, Maze))
		{
			g_sChar.m_cLocation.X++;
		}
		ShootDirection = 2;
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		if (downcheck(g_sChar, Maze))
		{
			g_sChar.m_cLocation.Y++;
		}
		ShootDirection = 3;
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		if (leftcheck(g_sChar, Maze))
		{
			g_sChar.m_cLocation.X--;
		}
		ShootDirection = 4;
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_E])
	{
		for (int ItemNumber = 0; ItemNumber < NUM_OF_KEYS; ItemNumber++)
		{
			if (doorcheck(Key, ItemNumber))
			{
				Key.Checker[Key.id[ItemNumber]] = true;
				DoorA.Checker[Key.id[ItemNumber]] = true;
				Maze[Key.Location[ItemNumber].Y - 1][Key.Location[ItemNumber].X] = ' ';
				Player.Key[Key.id[ItemNumber]] = true;
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
	if ((g_sChar.m_cLocation.Y == charbossY) && (g_sChar.m_cLocation.X == charbossX))
	{
		bulletcondition = 1;
		g_eGamemode = S_BOSSONE;
		for (int ItemNumber = 0; ItemNumber < NUM_OF_KEYS; ItemNumber++)
		{
			Player.Key[ItemNumber] = false;
		}
		changeMap();
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.0875; // 125ms should be enough
	}
}

void moveCharacterInBoss(double &g_dBounceTime, double &g_eBounceTime, double &g_dElapsedTime, SGameChar &g_sChar, Console &g_Console, char **BossMap, PlayerInformation &Player, bool &CharacterisHit)
{
	getInputmove();
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (isKeyPressedMove[K_UP] && g_sChar.m_cLocation.Y > 14)
	{
		//Beep(1440, 30);
		if (upcheck(g_sChar, BossMap))
		{
			g_sChar.m_cLocation.Y--;
		}
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		if (rightcheck(g_sChar, BossMap))
		{
			g_sChar.m_cLocation.X++;
		}
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		if (downcheck(g_sChar, BossMap))
		{
			g_sChar.m_cLocation.Y++;
		}
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		if (leftcheck(g_sChar, BossMap))
		{
			g_sChar.m_cLocation.X--;
			//if (((BossMap[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 1] == '1') ||
			//	(BossMap[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 1] == '0'))&&(g_eBounceTime < g_dElapsedTime))
			//{
			//	Player.Health--;
			//	CharacterisHit = true;
			//	g_eBounceTime = g_dElapsedTime + 2;// immunity time after getting hit by boss
			//}
		}
		bSomethingHappened = true;
	}

	if (((BossMap[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == '1') ||
		(BossMap[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == '0')) && (g_eBounceTime < g_dElapsedTime))
	{
		Player.Health--;
		CharacterisHit = true;
		g_eBounceTime = g_dElapsedTime + 2;// immunity time after getting hit by boss
	}

	//if ((g_sChar.m_cLocation.Y == charbossY) && (g_sChar.m_cLocation.X == charbossX))
	//{
	//	g_eGamemode = S_BOSSONE;
	//	changeMap();
	//}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.0875; // 125ms should be enough
	}
}
