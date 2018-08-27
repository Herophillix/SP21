#include "game.h"

bool isKeyPressedMove[K_COUNT];
bool ChangeDirection = false;

void getInputmove()
{
	isKeyPressedMove[K_UP] = isKeyPressed(VK_UP);
	isKeyPressedMove[K_DOWN] = isKeyPressed(VK_DOWN);
	isKeyPressedMove[K_LEFT] = isKeyPressed(VK_LEFT);
	isKeyPressedMove[K_RIGHT] = isKeyPressed(VK_RIGHT);
	isKeyPressedMove[K_SPACE] = isKeyPressed(VK_SPACE);
	isKeyPressedMove[K_E] = isKeyPressed(0x45);
	isKeyPressedMove[K_NUMPAD0] = isKeyPressed(VK_NUMPAD0);
}

void moveCharacter(double &g_dBounceTime, double &g_dElapsedTime, SGameChar &g_sChar, Console &g_Console, KDInformation &Key, KDInformation &Door,
	char** Maze, PlayerInformation &Player, SGameChar &g_portalEntrance, SGameChar &g_portalExit, int &charbossX, int &charbossY, EGAMEMODES &g_eGamemode)
{
	getInputmove();
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (isKeyPressedMove[K_NUMPAD0])
	{
		ShootDirection = ShootDirection % 4 + 1;
		switch (ShootDirection)
		{
		case 1:
		{
			Player.Direction = "Up";
			break;
		}
		case 2:
		{
			Player.Direction = "Right";
			break;
		}
		case 3:
		{
			Player.Direction = "Down";
			break;
		}
		case 4:
		{
			Player.Direction = "Left";
			break;
		}
		}
		ChangeDirection = true;
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_UP] && g_sChar.m_cLocation.Y > 1)
	{
		//Beep(1440, 30);
		if ((upcheck(g_sChar, Maze, ' ')) ||
			(upcheck(g_sChar, Maze, 'I')) ||
			(upcheck(g_sChar, Maze, 'o')) ||
			(upcheck(g_sChar, Maze, 'b')) ||
			(upcheck(g_sChar, Maze, (char)240)))
		{
			g_sChar.m_cLocation.Y--;
		}
		else if (bridge == true)
		{
			if (upcheck(g_sChar, Maze, 'm'))
			{
				g_sChar.m_cLocation.Y--;
			}
		}
		else
		{
			if (upcheck(g_sChar, Maze, 'g'))
			{
				g_sChar.m_cLocation.Y--;
			}
		}
		ShootDirection = 1;
		Player.Direction = "Up";
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		if ((rightcheck(g_sChar, Maze, ' ')) ||
			(rightcheck(g_sChar, Maze, 'I')) ||
			(rightcheck(g_sChar, Maze, 'o')) ||
			(rightcheck(g_sChar, Maze, 'b')) ||
			(rightcheck(g_sChar, Maze, (char)240)))
		{
			g_sChar.m_cLocation.X++;
		}
		else if (bridge == true)
		{
			if (rightcheck(g_sChar, Maze, 'm'))
			{
				g_sChar.m_cLocation.X++;
			}
		}
		else
		{
			if (rightcheck(g_sChar, Maze, 'g'))
			{
				g_sChar.m_cLocation.X++;
			}
		}
		ShootDirection = 2;
		Player.Direction = "Right";
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		if ((downcheck(g_sChar, Maze, ' ')) ||
			(downcheck(g_sChar, Maze, 'I')) ||
			(downcheck(g_sChar, Maze, 'o')) ||
			(downcheck(g_sChar, Maze, 'b')) ||
			(downcheck(g_sChar, Maze, (char)240)))
		{
			g_sChar.m_cLocation.Y++;
		}
		else if (bridge == true)
		{
			if (downcheck(g_sChar, Maze, 'm'))
			{
				g_sChar.m_cLocation.Y++;
			}
		}
		else
		{
			if (downcheck(g_sChar, Maze, 'g'))
			{
				g_sChar.m_cLocation.Y++;
			}
		}
		ShootDirection = 3;
		Player.Direction = "Down";
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		if ((leftcheck(g_sChar, Maze, ' ')) ||
			(leftcheck(g_sChar, Maze, 'I')) ||
			(leftcheck(g_sChar, Maze, 'o')) ||
			(leftcheck(g_sChar, Maze, 'b')) ||
			(leftcheck(g_sChar, Maze, (char)240)))
		{
			g_sChar.m_cLocation.X--;
		}
		else if (bridge == true)
		{
			if (leftcheck(g_sChar, Maze, 'm'))
			{
				g_sChar.m_cLocation.X--;
			}
		}
		else
		{
			if (leftcheck(g_sChar, Maze, 'g'))
			{
				g_sChar.m_cLocation.X--;
			}
		}
		ShootDirection = 4;
		Player.Direction = "Left";
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_E])
	{
		for (int ItemNumber = 0; ItemNumber < NUM_OF_KEYS; ItemNumber++)
		{
			if (doorcheck(Key, ItemNumber, Key, g_sChar))
			{
				Key.Checker[Key.id[ItemNumber]] = true;
				Door.Checker[Key.id[ItemNumber]] = true;
				Maze[Key.Location[ItemNumber].Y - 1][Key.Location[ItemNumber].X] = ' ';
				Player.Key[Key.id[ItemNumber]] = true;
				ItemNumber = NUM_OF_KEYS;
			}
			else if (doorcheck(Door, ItemNumber, Key, g_sChar))
			{
				int Rows, Columns;
				switch (g_eGamemode)
				{
				case S_STAGEONE:
				{
					Rows = MAP_ROWS;
					Columns = MAP_COLUMNS;
					break;
				}
				case S_STAGETWO:
				{
					Rows = MAP2_ROWS;
					Columns = MAP2_COLUMNS;
					break;
				}
				case S_STAGETHREE:
				{
					Rows = MAP3_ROWS;
					Columns = MAP3_COLUMNS;
					break;
				}
				}
				for (int i = 0; i < Rows; i++)
				{
					for (int a = 0; a < Columns; a++)
					{
						if ((Door.Sides[Door.id[ItemNumber]].AdjacentSides[a].X != 0) && (Door.Sides[Door.id[ItemNumber]].AdjacentSides[a].Y != 0))
						{
							if (Key.Checker[ItemNumber] == Door.Checker[Door.id[ItemNumber]])
							{
								Maze[Door.Location[ItemNumber].Y - 1][Door.Location[ItemNumber].X] = ' ';
								Maze[Door.Sides[ItemNumber].AdjacentSides[a].Y][Door.Sides[ItemNumber].AdjacentSides[a].X] = ' ';
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
		if ((upcheck(g_sChar, Maze, 's')) || (rightcheck(g_sChar, Maze, 's')) || (downcheck(g_sChar, Maze, 's')) || (leftcheck(g_sChar, Maze, 's')))
		{
			if (bridge == false)
			{
				bridge = true;
			}
			else
			{
				bridge = false;
			}
			bSomethingHappened = true;
		}
		if ((upcheck(g_sChar, Maze, (char)3)) || (rightcheck(g_sChar, Maze, (char)3)) || (downcheck(g_sChar, Maze, (char)3)) || (leftcheck(g_sChar, Maze, (char)3)))
		{
			Player.Health++;
			health = false;
			bSomethingHappened = true;
		}
	}
	if ((g_sChar.m_cLocation.Y == charbossY) && (g_sChar.m_cLocation.X == charbossX))
	{
		bulletcondition = 1;
		switch (g_eGamemode)
		{
		case S_STAGEONE:
		{
			g_eGamemode = S_BOSSONE;
			break;
		}
		case S_STAGETWO:
		{
			g_eGamemode = S_BOSSTWO;
			break;
		}
		}
		g_bossElapsedTime = g_dElapsedTime;
		for (int ItemNumber = 0; ItemNumber < NUM_OF_KEYS; ItemNumber++)
		{
			Player.Key[ItemNumber] = false;
		}
		changeMap();
	}
	if (bSomethingHappened)
	{
		if (ChangeDirection == true)
		{
			g_dBounceTime = g_dElapsedTime + 0.25;
			ChangeDirection = false;
		}
		else
		{
			g_dBounceTime = g_dElapsedTime + 0.0875;  // 125ms should be enough
		}
		// set the bounce time to some time in the future to prevent accidental triggers
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
		if (upcheck(g_sChar, BossMap, ' ') ||
			upcheck(g_sChar, BossMap, '1') ||
			upcheck(g_sChar, BossMap, '0'))
		{
			g_sChar.m_cLocation.Y--;
		}
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		if (rightcheck(g_sChar, BossMap, ' ') ||
			rightcheck(g_sChar, BossMap, '1') ||
			rightcheck(g_sChar, BossMap, '0'))
		{
			g_sChar.m_cLocation.X++;
		}
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		if (downcheck(g_sChar, BossMap, ' ') ||
			downcheck(g_sChar, BossMap, '1') ||
			downcheck(g_sChar, BossMap, '0'))
		{
			g_sChar.m_cLocation.Y++;
		}
		bSomethingHappened = true;
	}
	if (isKeyPressedMove[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		if (leftcheck(g_sChar, BossMap, ' ') ||
			leftcheck(g_sChar, BossMap, '1') ||
			leftcheck(g_sChar, BossMap, '0'))
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
