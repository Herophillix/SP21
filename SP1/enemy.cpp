#include "game.h"

using namespace std;

// Game specific variables here


// Console object

void moveenemy(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &timer, int &Direction)
{

	timer++;

	/*int num = rand() % 4 +1;
	if (timer > 10)
	{
	if (num == 1 && g_enemy.m_cLocation.Y > 1)
	{

	if (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] != (char)219)
	{
	g_enemy.m_cLocation.Y--;

	}
	}
	else if (num == 2 && g_enemy.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
	if (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] != (char)219)
	{
	g_enemy.m_cLocation.Y++;

	}
	}
	else if (num == 3 && g_enemy.m_cLocation.X > 0)
	{
	if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] != (char)219)
	{
	g_enemy.m_cLocation.X--;

	}
	}
	else if (num == 4 && g_enemy.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
	if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] != (char)219)
	{
	g_enemy.m_cLocation.X++;

	}
	timer = 0;
	}
	}*/
	//^crazy ai

	/*if (g_enemy.m_bActive = true)
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

	}*/

	/*if (g_enemy.m_bActive = true)
	{
	if (timer > 10)
	{
	if (one == 1 && g_enemy.m_cLocation.X >= 39 && g_enemy.m_cLocation.X != 57)
	{
	if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] != (char)219)
	{
	g_enemy.m_cLocation.X++;
	}
	if (g_enemy.m_cLocation.X == 57)
	{
	one++;
	}
	}
	else if (one == 2 && g_enemy.m_cLocation.X <= 57 && g_enemy.m_cLocation.X != 39)
	{
	if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] != (char)219)
	{
	g_enemy.m_cLocation.X--;
	}
	if (g_enemy.m_cLocation.X == 39)
	{
	one--;
	}
	}
	if (two == 1 && g_enemy.m_cLocation.Y <= 29 && g_enemy.m_cLocation.Y != 19)
	{
	if (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] != (char)219)
	{
	g_enemy.m_cLocation.Y--;
	}
	if (g_enemy.m_cLocation.Y == 20)
	{
	two++;
	}
	}
	else if (two == 2 && g_enemy.m_cLocation.Y >= 20 && g_enemy.m_cLocation.Y  !=30)
	{
	if (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] != (char)219)
	{
	g_enemy.m_cLocation.Y++;
	}
	if (g_enemy.m_cLocation .Y ==29)
	{
	two--;
	}
	}
	timer = 0;
	}
	}*/
	/*if (g_enemy.m_bActive = true)
	{
	if (timer > 10)
	{
	if (one == 1 && g_enemy.m_cLocation.X >= 39 && g_enemy.m_cLocation.X != 57)
	{
	if ((Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] != (char)219))
	{
	if (!((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X + 1 == g_sChar.m_cLocation.X)))
	{
	g_enemy.m_cLocation.X++;
	}
	}
	if (g_enemy.m_cLocation.X == 52 || g_enemy.m_cLocation.X == 42)
	{
	two=1;
	}
	if (g_enemy.m_cLocation.X == 46)
	{
	two = 2;
	}
	}
	else if (one == 2 && g_enemy.m_cLocation.X <= 57 && g_enemy.m_cLocation.X != 39)
	{
	if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] != (char)219)
	{
	if (!((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X - 1 == g_sChar.m_cLocation.X)))
	{
	g_enemy.m_cLocation.X--;
	}
	}
	if (g_enemy.m_cLocation.X == 39)
	{
	one--;
	}
	if (g_enemy.m_cLocation.X == 55 && g_enemy.m_cLocation.Y==29)
	{
	two++;
	}
	if ( g_enemy.m_cLocation.X == 52 || g_enemy.m_cLocation.X == 40)
	{
	two=2;
	one = 0;
	}
	if (g_enemy.m_cLocation.X == 45)
	{
	two = 1;
	}
	}
	if (two == 1 && g_enemy.m_cLocation.Y <= 29 && g_enemy.m_cLocation.Y != 19)
	{
	if (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] != (char)219)
	{
	if (!((g_enemy.m_cLocation.Y-1 == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X)))
	{
	g_enemy.m_cLocation.Y--;
	}
	}
	if (g_enemy.m_cLocation.Y == 20 && g_enemy.m_cLocation.X == 57)
	{
	two++;
	}

	}
	else if (two == 2 && g_enemy.m_cLocation.Y >= 20 && g_enemy.m_cLocation.Y  !=30)
	{
	if (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] != (char)219)
	{
	if (!((g_enemy.m_cLocation.Y + 1 == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X)))
	{
	g_enemy.m_cLocation.Y++;
	}
	}
	if (g_enemy.m_cLocation.Y == 29)
	{
	two = 0;
	one = 2;
	}
	if (g_enemy.m_cLocation.Y == 29 && g_enemy.m_cLocation.X == 48)
	{
	two = 0;
	one = 1;
	}
	}
	timer = 0;
	}
	}*/
	/*if (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == (char)219)
	{
	if (Random == 0)
	{
	if (!(Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == (char)219))
	{
	g_enemy.m_cLocation.X++;
	Random = 1;
	}
	}
	else
	{
	if (!(Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] == (char)219))
	{
	g_enemy.m_cLocation.X--;
	Random = 0;
	}
	}
	}
	else if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == (char)219)
	{
	if (Random == 0)
	{
	if (!(Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] == (char)219))
	{
	g_enemy.m_cLocation.Y++;
	Random = 1;
	}
	}
	else
	{
	if (!(Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == (char)219))
	{
	g_enemy.m_cLocation.Y--;
	Random = 0;
	}
	}
	}
	else if (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] == (char)219)
	{
	if (Random == 0)
	{
	if (!(Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == (char)219))
	{
	g_enemy.m_cLocation.X++;
	Random = 1;
	}
	}
	else
	{
	if (!(Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] == (char)219))
	{
	g_enemy.m_cLocation.X--;
	Random = 0;
	}
	}
	}
	else if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] == (char)219)
	{
	if (Random == 0)
	{
	if (!(Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] == (char)219))
	{
	g_enemy.m_cLocation.Y++;
	Random = 1;
	}
	}
	else
	{
	if (!(Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == (char)219))
	{
	g_enemy.m_cLocation.Y--;
	Random = 0;
	}
	}
	}
	else
	{
	g_enemy.m_cLocation.X++;
	}*/
	/*else if (one == 2 && g_enemy.m_cLocation.X <= 57 && g_enemy.m_cLocation.X != 39)
	{
	if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] != (char)219)
	{
	if (!((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X - 1 == g_sChar.m_cLocation.X)))
	{
	g_enemy.m_cLocation.X--;
	}
	}
	if (g_enemy.m_cLocation.X == 39)
	{
	one--;
	}
	if (g_enemy.m_cLocation.X == 55 && g_enemy.m_cLocation.Y == 29)
	{
	two++;
	}
	if (g_enemy.m_cLocation.X == 52 || g_enemy.m_cLocation.X == 40)
	{
	two = 2;
	one = 0;
	}
	if (g_enemy.m_cLocation.X == 45)
	{
	two = 1;
	}
	}
	if (two == 1 && g_enemy.m_cLocation.Y <= 29 && g_enemy.m_cLocation.Y != 19)
	{
	if (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] != (char)219)
	{
	if (!((g_enemy.m_cLocation.Y - 1 == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X)))
	{
	g_enemy.m_cLocation.Y--;
	}
	}
	if (g_enemy.m_cLocation.Y == 20 && g_enemy.m_cLocation.X == 57)
	{
	two++;
	}

	}
	else if (two == 2 && g_enemy.m_cLocation.Y >= 20 && g_enemy.m_cLocation.Y != 30)
	{
	if (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] != (char)219)
	{
	if (!((g_enemy.m_cLocation.Y + 1 == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X)))
	{
	g_enemy.m_cLocation.Y++;
	}
	}
	if (g_enemy.m_cLocation.Y == 29)
	{
	two = 0;
	one = 2;
	}
	if (g_enemy.m_cLocation.Y == 29 && g_enemy.m_cLocation.X == 48)
	{
	two = 0;
	one = 1;
	}
	}*/
	if (g_enemy.m_bActive = true)
	{
		if (timer > 10)
		{
			if ((g_enemy.m_cLocation.Y >= g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X <= g_sChar.m_cLocation.X) ||
				(g_enemy.m_cLocation.Y <= g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X >= g_sChar.m_cLocation.X))
			{
				track(Maze, g_enemy, g_sChar);

			}
			else if ((g_enemy.m_cLocation.X >= 39 && g_enemy.m_cLocation.Y >= 20)/*&&g_enemy.m_cLocation.X <58*/)
			{
				switch (Direction)
				{
				case 1:
				{
					Direction = upenemy(Maze, g_enemy, g_sChar, Direction);
					break;
				}
				case 2:
				{
					Direction = rightenemy(Maze, g_enemy, g_sChar, Direction);
					break;
				}
				case 3:
				{
					Direction = downenemy(Maze, g_enemy, g_sChar, Direction);
					break;
				}
				case 4:
				{
					Direction = leftenemy(Maze, g_enemy, g_sChar, Direction);
					break;
				}
				}
				if (g_enemy.m_cLocation.X == 39)
				{
					rightenemy(Maze, g_enemy, g_sChar, Direction);
				}
				if (g_enemy.m_cLocation.Y == 19)
				{
					downenemy(Maze, g_enemy, g_sChar, Direction);
				}

			}
			else
			{
				switch (Direction)
				{
				case 1:
				{
					Direction = upenemy(Maze, g_enemy, g_sChar, Direction);
					break;
				}
				case 2:
				{
					Direction = rightenemy(Maze, g_enemy, g_sChar, Direction);
					break;
				}
				case 3:
				{
					Direction = downenemy(Maze, g_enemy, g_sChar, Direction);
					break;
				}
				case 4:
				{
					Direction = leftenemy(Maze, g_enemy, g_sChar, Direction);
					break;
				}
				}
			}
			timer = 0;
		}
	}

}
int upenemy(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction)
{
	if (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == ' ')
	{
		if (!((g_enemy.m_cLocation.Y - 1 == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X)))
		{
			g_enemy.m_cLocation.Y--;
			Direction = 1;
		}
	}
	else
	{
		if ((Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] == ' ') && (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == ' '))
		{
			if (rand() % 2 == 1)
			{
				return 2;
			}
			else
			{
				return 4;
			}
		}
		else if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == ' ')
		{
			return 2;
		}
		else
		{
			return 4;
		}
	}
	return Direction;
}
int rightenemy(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction)
{
	if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == ' ')
	{
		if (!((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X + 1 == g_sChar.m_cLocation.X)))
		{
			g_enemy.m_cLocation.X++;
			Direction = 2;
		}
	}
	else
	{
		if ((Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == ' ') &&
			(Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] == ' '))
		{
			if (rand() % 2 == 1)
			{
				return 1;
			}
			else
			{
				return 3;
			}
		}
		else if (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == ' ')
		{
			return 1;
		}
		else
		{
			return 3;
		}

	}
	return Direction;
}
int downenemy(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction)
{
	if (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] == ' ')
	{
		if (!((g_enemy.m_cLocation.Y + 1 == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X)))
		{
			g_enemy.m_cLocation.Y++;
			Direction = 3;
		}
	}
	else
	{
		if ((Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] == ' ') && (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == ' '))
		{
			if (rand() % 2 == 1)
			{
				return 2;
			}
			else
			{
				return 4;
			}
		}
		else if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == ' ')
		{
			return 2;
		}
		else
		{
			return 4;
		}
	}
	return Direction;
}
int leftenemy(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction)
{
	if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] == ' ')
	{
		if (!((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X - 1 == g_sChar.m_cLocation.X)))
		{
			g_enemy.m_cLocation.X--;
			Direction = 4;
		}
	}
	else
	{
		if ((Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == ' ') &&
			(Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] == ' '))
		{
			if (rand() % 2 == 1)
			{
				return 1;
			}
			else
			{
				return 3;
			}
		}
		else if (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == ' ')
		{
			return 1;
		}
		else
		{
			return 3;
		}
	}
	return Direction;
}
void track(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar)
{
	if (((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X <= g_sChar.m_cLocation.X)) && (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] != (char)219))
	{
		g_enemy.m_cLocation.X++;
	}
	else if ((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X >= g_sChar.m_cLocation.X) && (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] != (char)219))
	{
		g_enemy.m_cLocation.X--;
	}
	else if ((g_enemy.m_cLocation.Y >= g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X) && (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] != (char)219))
	{
		g_enemy.m_cLocation.Y--;
	}
	else if ((g_enemy.m_cLocation.Y <= g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X) && (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] != (char)219))
	{
		g_enemy.m_cLocation.Y++;
	}
}