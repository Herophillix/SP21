#include "game.h"

using namespace std;

//bool moveleft = false;

// Game specific variables here


// Console object

void moveenemy(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &timer, int &Direction , PlayerInformation &Player, SGameChar &g_bullet)
{
	
	ShootEnemy(g_bullet,g_enemy);
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
	if (g_enemy.m_bActive == true)
	{
		timer++;
		if (timer > 10)
		{
			if ((g_enemy.m_cLocation.Y >= g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X <= g_sChar.m_cLocation.X) ||
				(g_enemy.m_cLocation.Y <= g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X >= g_sChar.m_cLocation.X))
			{
				track(Maze, g_enemy, g_sChar,Direction,Player, g_bullet);

			}
			else if ((g_enemy.m_cLocation.X >= 39 && g_enemy.m_cLocation.Y >= 20)/*&&g_enemy.m_cLocation.X <58*/)
			{
				switch (Direction)
				{
				case 1:
				{
					Direction = upenemy(Maze, g_enemy, g_sChar, Direction,Player,g_bullet);
					break;
				}
				case 2:
				{
					Direction = rightenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction = downenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction = leftenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				}
				if (g_enemy.m_cLocation.X == 39)
				{
					rightenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
				}
				if (g_enemy.m_cLocation.Y == 19)
				{
					downenemy(Maze, g_enemy, g_sChar, Direction,Player, g_bullet);
				}

			}
			else
			{
				switch (Direction)
				{
				case 1:
				{
					Direction = upenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction = rightenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction = downenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction = leftenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}

}
int upenemy(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction, PlayerInformation &Player, SGameChar &g_bullet)
{
	if (g_enemy.m_bActive == true)
	{
		if (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == ' ')
		{
			if (!((g_enemy.m_cLocation.Y - 1 == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X)))
			{
				g_enemy.m_cLocation.Y--;
				Direction = 1;
			}
			else
			{
				Player.Health -= 1;
				if (Player.Health == 0)
				{
					//	init();
				}
				else if (Player.Health < 3 && Player.Health != 0)
				{
					renderCharacter();
				}
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
}
int rightenemy(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction, PlayerInformation &Player, SGameChar &g_bullet)
{
	
	if (g_enemy.m_bActive == true)
	{
		if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == ' ')
		{
			if (!((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X + 1 == g_sChar.m_cLocation.X)))
			{
				g_enemy.m_cLocation.X++;
				Direction = 2;
			}
			else
			{
				Player.Health -= 1;
				if (Player.Health == 0)
				{
					//	init();
				}
				else if (Player.Health < 3 && Player.Health != 0)
				{
					renderCharacter();
				}
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
}
int downenemy(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction, PlayerInformation &Player , SGameChar &g_bullet)
{
	
	if (g_enemy.m_bActive == true)
	{
		if (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] == ' ')
		{
			if (!((g_enemy.m_cLocation.Y + 1 == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X)))
			{
				g_enemy.m_cLocation.Y++;
				Direction = 3;
			}
			else
			{
				Player.Health -= 1;
				if (Player.Health == 0)
				{
					//	init();
				}
				else if (Player.Health < 3 && Player.Health != 0)
				{
					renderCharacter();
				}
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
}
int leftenemy(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction, PlayerInformation &Player, SGameChar &g_bullet)
{
	
	if (g_enemy.m_bActive == true)
	{
		if (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] == ' ')
		{
			if (!((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X - 1 == g_sChar.m_cLocation.X)))
			{
				g_enemy.m_cLocation.X--;
				Direction = 4;
			}
			else
			{
				Player.Health -= 1;
				if (Player.Health == 0)
				{
					//	init();
				}
				else if (Player.Health < 3 && Player.Health != 0)
				{
					renderCharacter();
				}
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
}
void track(char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction, PlayerInformation &Player, SGameChar &g_bullet)
{
	if (g_enemy.m_bActive == true)
	{
		if (((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X <= g_sChar.m_cLocation.X)) && (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == ' '))
		{
			//g_enemy.m_cLocation.X++;
			rightenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
		}
		else if ((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X >= g_sChar.m_cLocation.X) && (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] == ' '))
		{
			//g_enemy.m_cLocation.X--;
			leftenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
		}
		else if ((g_enemy.m_cLocation.Y >= g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X) && (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == ' '))
		{
			//g_enemy.m_cLocation.Y--;
			upenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
		}
		else if ((g_enemy.m_cLocation.Y <= g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X) && (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] == ' '))
		{
			//g_enemy.m_cLocation.Y++;
			downenemy(Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
		}
	}
}

void moveenemy1(char **Maze, SGameChar &g_enemy1, SGameChar &g_sChar, int &timer1, int &one, PlayerInformation &Player, SGameChar &g_bullet)
{
	
	timer1++;
	ShootEnemy(g_bullet, g_enemy1);
		if (timer1 > 5)
		{
			if ((g_enemy1.m_cLocation.Y == g_bullet.m_cLocation.Y) && (g_enemy1.m_cLocation.X + 1 == g_bullet.m_cLocation.X) || (g_enemy1.m_cLocation.Y == g_bullet.m_cLocation.Y) && (g_enemy1.m_cLocation.X - 1 == g_bullet.m_cLocation.X))
			{
				g_enemy1.m_bActive == false;
				renderenemy();
			}
			if (g_enemy1.m_bActive == true)
			{
			if (one == 1 && Maze[g_enemy1.m_cLocation.Y - 1][g_enemy1.m_cLocation.X + 1] == ' '&& g_enemy1.m_cLocation.X >= 41)
			{
				if (!((g_enemy1.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy1.m_cLocation.X + 1 == g_sChar.m_cLocation.X)))
				{
					g_enemy1.m_cLocation.X++;
				}
				if (g_enemy1.m_cLocation.X == 60)
				{
					one++;
				}
				else if ((g_enemy1.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy1.m_cLocation.X + 1 == g_sChar.m_cLocation.X))
				{
					Player.Health -= 1;
					if (Player.Health == 0)
					{
						//	init();
					}
					else if (Player.Health < 3 && Player.Health != 0)
					{
						renderCharacter();
					}
				}
			}
			else if (one == 2 && (Maze[g_enemy1.m_cLocation.Y - 1][g_enemy1.m_cLocation.X - 1] == ' ') && g_enemy1.m_cLocation.X <= 60)
			{
				if (!((g_enemy1.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy1.m_cLocation.X - 1 == g_sChar.m_cLocation.X)))
				{
					g_enemy1.m_cLocation.X--;
				}
				if (g_enemy1.m_cLocation.X == 41)
				{
					one--;
				}
				else if ((g_enemy1.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy1.m_cLocation.X - 1 == g_sChar.m_cLocation.X))
				{
					Player.Health -= 1;
					if (Player.Health == 0)
					{
						//	init();
					}
					else if (Player.Health < 3 && Player.Health != 0)
					{
						renderCharacter();
					}
				}
			}timer1 = 0;
		}
	}
};

void moveenemy2(char **Maze, SGameChar &g_enemy2, SGameChar &g_sChar, int &timer2, int &two, PlayerInformation &Player, SGameChar &g_bullet)
{
	timer2++;
	ShootEnemy(g_bullet, g_enemy2);
	if (timer2 > 5)
	{
		if ((g_enemy2.m_cLocation.Y == g_bullet.m_cLocation.Y) && (g_enemy2.m_cLocation.X + 1 == g_bullet.m_cLocation.X) || (g_enemy2.m_cLocation.Y == g_bullet.m_cLocation.Y) && (g_enemy2.m_cLocation.X - 1 == g_bullet.m_cLocation.X))
		{
			g_enemy2.m_bActive = false;
			renderenemy();
		}
		if (g_enemy2.m_bActive == true)
		{
			if (two == 2 && Maze[g_enemy2.m_cLocation.Y - 1][g_enemy2.m_cLocation.X + 1] == ' '&& g_enemy2.m_cLocation.X >= 41)
			{
				if (!((g_enemy2.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy2.m_cLocation.X + 1 == g_sChar.m_cLocation.X)))
				{
					g_enemy2.m_cLocation.X++;
				}
				if (g_enemy2.m_cLocation.X == 60)
				{
					two--;
				}
				else if ((g_enemy2.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy2.m_cLocation.X + 1 == g_sChar.m_cLocation.X))
				{
					Player.Health -= 1;
					if (Player.Health == 0)
					{
						//	init();
					}
					else if (Player.Health < 3 && Player.Health != 0)
					{
						renderCharacter();
					}
				}
			}
			else if (two == 1 && (Maze[g_enemy2.m_cLocation.Y - 1][g_enemy2.m_cLocation.X - 1] == ' ') || (Maze[g_enemy2.m_cLocation.Y - 1][g_enemy2.m_cLocation.X - 1] == 'k') && g_enemy2.m_cLocation.X <= 60)
			{
				if (!((g_enemy2.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy2.m_cLocation.X - 1 == g_sChar.m_cLocation.X)))
				{
					g_enemy2.m_cLocation.X--;
				}
				if (g_enemy2.m_cLocation.X == 41)
				{
					two++;
				}
				else if ((g_enemy2.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy2.m_cLocation.X - 1 == g_sChar.m_cLocation.X))
				{
					Player.Health -= 1;
					if (Player.Health == 0)
					{
						//	init();
					}
					else if (Player.Health < 3 && Player.Health != 0)
					{
						renderCharacter();
					}
				}
			}timer2 = 0;
		}
	}
}; 

void moveenemy3(char **Maze, SGameChar &g_enemy3, SGameChar &g_sChar, int &timer, int &Direction3, PlayerInformation &Player, SGameChar &g_bullet)
{
	ShootEnemy(g_bullet, g_enemy3);
	
	if (g_enemy3.m_bActive == true)
	{
		timer++;
		if (timer > 10)
		{
			if ((g_enemy3.m_cLocation.Y >= g_sChar.m_cLocation.Y) && (g_enemy3.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy3.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy3.m_cLocation.X <= g_sChar.m_cLocation.X) ||
				(g_enemy3.m_cLocation.Y <= g_sChar.m_cLocation.Y) && (g_enemy3.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy3.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy3.m_cLocation.X >= g_sChar.m_cLocation.X))
			{
				if ((Maze[g_enemy3.m_cLocation.Y - 1][g_enemy3.m_cLocation.X - 1] != ' ') || (Maze[g_enemy3.m_cLocation.Y - 1][g_enemy3.m_cLocation.X + 1] != ' ') ||
					(Maze[g_enemy3.m_cLocation.Y][g_enemy3.m_cLocation.X] != ' ') || (Maze[g_enemy3.m_cLocation.Y - 2][g_enemy3.m_cLocation.X] != ' '))
				{
					switch (Direction3)
					{
					case 1:
					{
						Direction3 = upenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
						break;
					}
					case 2:
					{
						Direction3 = rightenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
						break;
					}
					case 3:
					{
						Direction3 = downenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
						break;
					}
					case 4:
					{
						Direction3 = leftenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
						break;
					}
					break;
					}
				}
				else
				{
					track(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
				}
			}
			else if ((g_enemy3.m_cLocation.X >= 45 && g_enemy3.m_cLocation.Y >= 3))
			{
				switch (Direction3)
				{
				case 1:
				{
					Direction3 = upenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction3 = rightenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction3 = downenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction3 = leftenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				}

			}
			else
			{
				switch (Direction3)
				{
				case 1:
				{
					Direction3 = upenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction3 = rightenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction3 = downenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction3 = leftenemy(Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}

}


void moveenemy4(char **Maze, SGameChar &g_enemy4, SGameChar &g_sChar, int &timer, int &Direction4, PlayerInformation &Player, SGameChar &g_bullet)
{
	ShootEnemy(g_bullet, g_enemy4);
	
	if (g_enemy4.m_bActive == true)
	{
		timer++;
		if (timer > 10)
		{
			if ((g_enemy4.m_cLocation.Y >= g_sChar.m_cLocation.Y) && (g_enemy4.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy4.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy4.m_cLocation.X <= g_sChar.m_cLocation.X) ||
				(g_enemy4.m_cLocation.Y <= g_sChar.m_cLocation.Y) && (g_enemy4.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy4.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy4.m_cLocation.X >= g_sChar.m_cLocation.X))
			{
				if ((Maze[g_enemy4.m_cLocation.Y - 1][g_enemy4.m_cLocation.X - 1] != ' ') || (Maze[g_enemy4.m_cLocation.Y - 1][g_enemy4.m_cLocation.X + 1] != ' ') ||
					(Maze[g_enemy4.m_cLocation.Y][g_enemy4.m_cLocation.X] != ' ') || (Maze[g_enemy4.m_cLocation.Y - 2][g_enemy4.m_cLocation.X] != ' '))
				{
					switch (Direction4)
					{
					case 1:
					{
						Direction4 = upenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
						break;
					}
					case 2:
					{
						Direction4 = rightenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
						break;
					}
					case 3:
					{
						Direction4 = downenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
						break;
					}
					case 4:
					{
						Direction4 = leftenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
						break;
					}
					break;
					}
				}
				else
				{
					track(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
				}
			}
			else if ((g_enemy4.m_cLocation.X >= 45 && g_enemy4.m_cLocation.Y >= 3))
			{
				switch (Direction4)
				{
				case 1:
				{
					Direction4 = upenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction4 = rightenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction4 = downenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction4 = leftenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				}

			}
			else
			{
				switch (Direction4)
				{
				case 1:
				{
					Direction4 = upenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction4 = rightenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction4 = downenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction4 = leftenemy(Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}

}


void moveenemy5(char **Maze, SGameChar &g_enemy5, SGameChar &g_sChar, int &timer, int &Direction5, PlayerInformation &Player, SGameChar &g_bullet)
{
	ShootEnemy(g_bullet, g_enemy5);
	
	if (g_enemy5.m_bActive == true)
	{
		timer++;
		if (timer > 10)
		{
			if ((g_enemy5.m_cLocation.Y >= g_sChar.m_cLocation.Y) && (g_enemy5.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy5.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy5.m_cLocation.X <= g_sChar.m_cLocation.X) ||
				(g_enemy5.m_cLocation.Y <= g_sChar.m_cLocation.Y) && (g_enemy5.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy5.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy5.m_cLocation.X >= g_sChar.m_cLocation.X))
			{
				if ((Maze[g_enemy5.m_cLocation.Y - 1][g_enemy5.m_cLocation.X - 1] != ' ') || (Maze[g_enemy5.m_cLocation.Y - 1][g_enemy5.m_cLocation.X + 1] != ' ') ||
					(Maze[g_enemy5.m_cLocation.Y][g_enemy5.m_cLocation.X] != ' ') || (Maze[g_enemy5.m_cLocation.Y - 2][g_enemy5.m_cLocation.X] != ' '))
				{
					switch (Direction5)
					{
					case 1:
					{
						Direction5 = upenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
						break;
					}
					case 2:
					{
						Direction5 = rightenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
						break;
					}
					case 3:
					{
						Direction5 = downenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
						break;
					}
					case 4:
					{
						Direction5 = leftenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
						break;
					}
					break;
					}
				}
				else
				{
					track(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
				}
			}
			else if ((g_enemy5.m_cLocation.X >= 45 && g_enemy5.m_cLocation.Y <= 3))
			{
				switch (Direction5)
				{
				case 1:
				{
					Direction5 = upenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction5 = rightenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction5 = downenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction5 = leftenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				}

			}
			else
			{
				switch (Direction5)
				{
				case 1:
				{
					Direction5 = upenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction5 = rightenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction5 = downenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction5 = leftenemy(Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}

}

void moveenemy6(char **Maze, SGameChar &g_enemy6, SGameChar &g_sChar, int &timer, int &Direction6, PlayerInformation &Player, SGameChar &g_bullet)
{
	ShootEnemy(g_bullet, g_enemy6);
	if (g_enemy6.m_bActive == true)
	{
		timer++;
		if (timer > 10)
		{
			if ((g_enemy6.m_cLocation.Y >= g_sChar.m_cLocation.Y) && (g_enemy6.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy6.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy6.m_cLocation.X <= g_sChar.m_cLocation.X) ||
				(g_enemy6.m_cLocation.Y <= g_sChar.m_cLocation.Y) && (g_enemy6.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy6.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy6.m_cLocation.X >= g_sChar.m_cLocation.X))
			{
				if ((Maze[g_enemy6.m_cLocation.Y - 1][g_enemy6.m_cLocation.X - 1] != ' ') || (Maze[g_enemy6.m_cLocation.Y - 1][g_enemy6.m_cLocation.X + 1] != ' ') ||
					(Maze[g_enemy6.m_cLocation.Y][g_enemy6.m_cLocation.X] != ' ') || (Maze[g_enemy6.m_cLocation.Y - 2][g_enemy6.m_cLocation.X] != ' '))
				{
					switch (Direction6)
					{
					case 1:
					{
						Direction6 = upenemy(Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
						break;
					}
					case 2:
					{
						Direction6 = rightenemy(Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
						break;
					}
					case 3:
					{
						Direction6 = downenemy(Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
						break;
					}
					case 4:
					{
						Direction6 = leftenemy(Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
						break;
					}
					break;
					}
				}
					/*for (int checkwall = 0; checkwall < (abs(g_enemy6.m_cLocation.X - g_sChar.m_cLocation.X)); checkwall++)
					{
						if (Maze[g_enemy6.m_cLocation.Y - 1][g_enemy6.m_cLocation.X - checkwall] != ' ')
						{
							moveleft = false;
							leftenemy(Maze, g_enemy6, g_sChar, Direction6, Player);
							break;
						}
						else
						{
							moveleft = true;
						}
					}*/
					else/*if (moveleft == true)*/
					{
						track(Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
					}
					/*else
					{
						switch (Direction6)
						{
						case 1:
						{
							Direction6 = upenemy(Maze, g_enemy6, g_sChar, Direction6, Player);
							break;
						}
						case 2:
						{
							Direction6 = rightenemy(Maze, g_enemy6, g_sChar, Direction6, Player);
							break;
						}
						case 3:
						{
							Direction6 = downenemy(Maze, g_enemy6, g_sChar, Direction6, Player);
							break;
						}
						case 4:
						{
							Direction6 = leftenemy(Maze, g_enemy6, g_sChar, Direction6, Player);
							break;
						}
						}
					}*/
			}
			else
			{
				switch (Direction6)
				{
				case 1:
				{
					Direction6 = upenemy(Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction6 = rightenemy(Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction6 = downenemy(Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction6 = leftenemy(Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}
}

void ShootEnemy(SGameChar &g_bullet, SGameChar &g_Enemy)
{
	if ((g_bullet.m_cLocation.X == g_Enemy.m_cLocation.X) && (g_bullet.m_cLocation.Y == g_Enemy.m_cLocation.Y))
	{
  		g_Enemy.m_bActive = false;
	}
}