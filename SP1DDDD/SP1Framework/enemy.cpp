#include "game.h"
using namespace std;
//bool moveleft = false;
// Game specific variables here
// Console object
int timer = 0;
int timer1 = 0;
int timer2 = 0;
int Direction = 2;
int Direction3 = 2;
int Direction4 = 2;
int Direction5 = 2;
int Direction6 = 2;
int Direction7 = 2;
int one = 1;
int two = 1;

void moveenemy(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &timer, int &Direction, PlayerInformation &Player, SGameChar &g_bullet, EGAMEMODES &g_eGameMode)
{

	ShootEnemy(g_bullet, g_enemy, Player);
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
				track(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
			}
			else if ((g_enemy.m_cLocation.X >= 39 && g_enemy.m_cLocation.Y >= 20) && (g_eGameMode == S_STAGEONE))
			{
				switch (Direction)
				{
				case 1:
				{
					Direction = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				}
				if (g_enemy.m_cLocation.X == 39)
				{
					rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
				}
				if (g_enemy.m_cLocation.Y == 19)
				{
					downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
				}
			}
			else
			{
				switch (Direction)
				{
				case 1:
				{
					Direction = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}
}
int upenemy(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction, PlayerInformation &Player, SGameChar &g_bullet)
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
			else if (g_eBounceTime < e_dElapsedTime)
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
	return Direction;
}
int rightenemy(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction, PlayerInformation &Player, SGameChar &g_bullet)
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
			else if (g_eBounceTime < e_dElapsedTime)
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
	return Direction;
}
int downenemy(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction, PlayerInformation &Player, SGameChar &g_bullet)
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
			else if (g_eBounceTime < e_dElapsedTime)
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
	return Direction;
}
int leftenemy(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction, PlayerInformation &Player, SGameChar &g_bullet)
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
			else if (g_eBounceTime < e_dElapsedTime)
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
	return Direction;
}
void track(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy, SGameChar &g_sChar, int &Direction, PlayerInformation &Player, SGameChar &g_bullet)
{
	if (g_enemy.m_bActive == true)
	{
		if (((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X <= g_sChar.m_cLocation.X)) && (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X + 1] == ' '))
		{
			//g_enemy.m_cLocation.X++;
			rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
		}
		else if ((g_enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X >= g_sChar.m_cLocation.X) && (Maze[g_enemy.m_cLocation.Y - 1][g_enemy.m_cLocation.X - 1] == ' '))
		{
			//g_enemy.m_cLocation.X--;
			leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
		}
		else if ((g_enemy.m_cLocation.Y >= g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X) && (Maze[g_enemy.m_cLocation.Y - 2][g_enemy.m_cLocation.X] == ' '))
		{
			//g_enemy.m_cLocation.Y--;
			upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
		}
		else if ((g_enemy.m_cLocation.Y <= g_sChar.m_cLocation.Y) && (g_enemy.m_cLocation.X == g_sChar.m_cLocation.X) && (Maze[g_enemy.m_cLocation.Y][g_enemy.m_cLocation.X] == ' '))
		{
			//g_enemy.m_cLocation.Y++;
			downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy, g_sChar, Direction, Player, g_bullet);
		}
	}
}
void moveenemy1(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy1, SGameChar &g_sChar, int &timer1, int &one, PlayerInformation &Player, SGameChar &g_bullet)
{

	timer1++;
	ShootEnemy(g_bullet, g_enemy1, Player);
	if (timer1 > 5)
	{
		if ((g_enemy1.m_cLocation.Y == g_bullet.m_cLocation.Y) && (g_enemy1.m_cLocation.X + 1 == g_bullet.m_cLocation.X) || (g_enemy1.m_cLocation.Y == g_bullet.m_cLocation.Y) && (g_enemy1.m_cLocation.X - 1 == g_bullet.m_cLocation.X))
		{
			g_enemy1.m_bActive = false;
			renderenemy();
		}
		if (g_enemy1.m_bActive == true)
		{
			if (one == 1 && Maze[g_enemy1.m_cLocation.Y - 1][g_enemy1.m_cLocation.X + 1] == ' '/*&& g_enemy1.m_cLocation.X >= 41*/)
			{
				if (!((g_enemy1.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy1.m_cLocation.X + 1 == g_sChar.m_cLocation.X)))
				{
					g_enemy1.m_cLocation.X++;
				}
				if (Maze[g_enemy1.m_cLocation.Y - 1][g_enemy1.m_cLocation.X + 1] !=' ')
				{
					one++;
				}
				else if ((g_enemy1.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy1.m_cLocation.X + 1 == g_sChar.m_cLocation.X) && (g_eBounceTime < e_dElapsedTime))
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
			else if (one == 2 && (Maze[g_enemy1.m_cLocation.Y - 1][g_enemy1.m_cLocation.X - 1] == ' ') /*&& g_enemy1.m_cLocation.X <= 219*/)
			{
				if (!((g_enemy1.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy1.m_cLocation.X - 1 == g_sChar.m_cLocation.X)))
				{
					g_enemy1.m_cLocation.X--;
				}
				if (Maze[g_enemy1.m_cLocation.Y - 1][g_enemy1.m_cLocation.X - 1] != ' ')
				{
					one--;
				}
				else if ((g_enemy1.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy1.m_cLocation.X - 1 == g_sChar.m_cLocation.X) && (g_eBounceTime < e_dElapsedTime))
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
void moveenemy2(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy2, SGameChar &g_sChar, int &timer2, int &two, PlayerInformation &Player, SGameChar &g_bullet)
{
	timer2++;
	ShootEnemy(g_bullet, g_enemy2, Player);
	if (timer2 > 5)
	{
		if ((g_enemy2.m_cLocation.Y == g_bullet.m_cLocation.Y) && (g_enemy2.m_cLocation.X + 1 == g_bullet.m_cLocation.X) || (g_enemy2.m_cLocation.Y == g_bullet.m_cLocation.Y) && (g_enemy2.m_cLocation.X - 1 == g_bullet.m_cLocation.X))
		{
			g_enemy2.m_bActive = false;
			renderenemy();
		}
		if (g_enemy2.m_bActive == true)
		{
			if (two == 2 && Maze[g_enemy2.m_cLocation.Y - 1][g_enemy2.m_cLocation.X + 1] == ' ')
			{
				if (!((g_enemy2.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy2.m_cLocation.X + 1 == g_sChar.m_cLocation.X)))
				{
					g_enemy2.m_cLocation.X++;
				}
				if (Maze[g_enemy2.m_cLocation.Y - 1][g_enemy2.m_cLocation.X + 1] != ' ')
				{
					two--;
				}
				else if ((g_enemy2.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy2.m_cLocation.X + 1 == g_sChar.m_cLocation.X) && (g_eBounceTime < e_dElapsedTime))
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
			else if (two == 1 && (Maze[g_enemy2.m_cLocation.Y - 1][g_enemy2.m_cLocation.X - 1] == ' ') || (Maze[g_enemy2.m_cLocation.Y - 1][g_enemy2.m_cLocation.X - 1] == 'k'))
			{
				if (!((g_enemy2.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy2.m_cLocation.X - 1 == g_sChar.m_cLocation.X)))
				{
					g_enemy2.m_cLocation.X--;
				}
				if (Maze[g_enemy2.m_cLocation.Y - 1][g_enemy2.m_cLocation.X - 1] != ' ')
				{
					two++;
				}
				else if ((g_enemy2.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy2.m_cLocation.X - 1 == g_sChar.m_cLocation.X) && (g_eBounceTime < e_dElapsedTime))
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
void moveenemy3(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy3, SGameChar &g_sChar, int &timer, int &Direction3, PlayerInformation &Player, SGameChar &g_bullet, EGAMEMODES &g_eGameMode)
{
	ShootEnemy(g_bullet, g_enemy3, Player);

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
						Direction3 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
						break;
					}
					case 2:
					{
						Direction3 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
						break;
					}
					case 3:
					{
						Direction3 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
						break;
					}
					case 4:
					{
						Direction3 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
						break;
					}
					break;
					}
				}
				else
				{
					track(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
				}
			}
			else if ((g_enemy3.m_cLocation.X >= 45 && g_enemy3.m_cLocation.Y >= 3) && (g_eGameMode == S_STAGEONE))
			{
				switch (Direction3)
				{
				case 1:
				{
					Direction3 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction3 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction3 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction3 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
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
					Direction3 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction3 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction3 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction3 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy3, g_sChar, Direction3, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}
}
void moveenemy4(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy4, SGameChar &g_sChar, int &timer, int &Direction4, PlayerInformation &Player, SGameChar &g_bullet, EGAMEMODES &g_eGameMode)
{
	ShootEnemy(g_bullet, g_enemy4, Player);

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
						Direction4 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
						break;
					}
					case 2:
					{
						Direction4 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
						break;
					}
					case 3:
					{
						Direction4 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
						break;
					}
					case 4:
					{
						Direction4 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
						break;
					}
					break;
					}
				}
				else
				{
					track(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
				}
			}
			else if ((g_enemy4.m_cLocation.X >= 45 && g_enemy4.m_cLocation.Y >= 3) && (g_eGameMode == S_STAGEONE))
			{
				switch (Direction4)
				{
				case 1:
				{
					Direction4 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction4 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction4 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction4 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
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
					Direction4 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction4 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction4 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction4 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy4, g_sChar, Direction4, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}
}
void moveenemy5(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy5, SGameChar &g_sChar, int &timer, int &Direction5, PlayerInformation &Player, SGameChar &g_bullet, EGAMEMODES &g_eGameMode)
{
	ShootEnemy(g_bullet, g_enemy5, Player);

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
						Direction5 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
						break;
					}
					case 2:
					{
						Direction5 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
						break;
					}
					case 3:
					{
						Direction5 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
						break;
					}
					case 4:
					{
						Direction5 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
						break;
					}
					break;
					}
				}
				else
				{
					track(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
				}
			}
			else if ((g_enemy5.m_cLocation.X >= 45 && g_enemy5.m_cLocation.Y <= 3) && (g_eGameMode == S_STAGEONE))
			{
				switch (Direction5)
				{
				case 1:
				{
					Direction5 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction5 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction5 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction5 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
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
					Direction5 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction5 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction5 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction5 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy5, g_sChar, Direction5, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}
}
void moveenemy6(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy6, SGameChar &g_sChar, int &timer, int &Direction6, PlayerInformation &Player, SGameChar &g_bullet, EGAMEMODES &g_eGameMode)
{
	ShootEnemy(g_bullet, g_enemy6, Player);
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
						Direction6 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
						break;
					}
					case 2:
					{
						Direction6 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
						break;
					}
					case 3:
					{
						Direction6 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
						break;
					}
					case 4:
					{
						Direction6 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
						break;
					}
					break;
					}
				}
				else
				{
					track(g_eBounceTime, e_dElapsedTime, Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
				}
			}
			else
			{
				switch (Direction6)
				{
				case 1:
				{
					Direction6 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction6 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction6 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction6 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy6, g_sChar, Direction6, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}
}
void moveenemy7(double& g_eBounceTime, double& e_dElapsedTime, char **Maze, SGameChar &g_enemy7, SGameChar &g_sChar, int &timer, int &Direction7, PlayerInformation &Player, SGameChar &g_bullet, EGAMEMODES &g_eGameMode)
{
	ShootEnemy(g_bullet, g_enemy7, Player);
	if (g_enemy7.m_bActive == true)
	{
		timer++;
		if (timer > 10)
		{
			if ((g_enemy7.m_cLocation.Y >= g_sChar.m_cLocation.Y) && (g_enemy7.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy7.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy7.m_cLocation.X <= g_sChar.m_cLocation.X) ||
				(g_enemy7.m_cLocation.Y <= g_sChar.m_cLocation.Y) && (g_enemy7.m_cLocation.X == g_sChar.m_cLocation.X) ||
				(g_enemy7.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_enemy7.m_cLocation.X >= g_sChar.m_cLocation.X))
			{
				if ((Maze[g_enemy7.m_cLocation.Y - 1][g_enemy7.m_cLocation.X - 1] != ' ') || (Maze[g_enemy7.m_cLocation.Y - 1][g_enemy7.m_cLocation.X + 1] != ' ') ||
					(Maze[g_enemy7.m_cLocation.Y][g_enemy7.m_cLocation.X] != ' ') || (Maze[g_enemy7.m_cLocation.Y - 2][g_enemy7.m_cLocation.X] != ' '))
				{
					switch (Direction7)
					{
					case 1:
					{
						Direction7 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy7, g_sChar, Direction7, Player, g_bullet);
						break;
					}
					case 2:
					{
						Direction7 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy7, g_sChar, Direction7, Player, g_bullet);
						break;
					}
					case 3:
					{
						Direction7 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy7, g_sChar, Direction7, Player, g_bullet);
						break;
					}
					case 4:
					{
						Direction7 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy7, g_sChar, Direction7, Player, g_bullet);
						break;
					}
					break;
					}
				}
				else
				{
					track(g_eBounceTime, e_dElapsedTime, Maze, g_enemy7, g_sChar, Direction7, Player, g_bullet);
				}
			}
			else
			{
				switch (Direction7)
				{
				case 1:
				{
					Direction7 = upenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy7, g_sChar, Direction7, Player, g_bullet);
					break;
				}
				case 2:
				{
					Direction7 = rightenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy7, g_sChar, Direction7, Player, g_bullet);
					break;
				}
				case 3:
				{
					Direction7 = downenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy7, g_sChar, Direction7, Player, g_bullet);
					break;
				}
				case 4:
				{
					Direction7 = leftenemy(g_eBounceTime, e_dElapsedTime, Maze, g_enemy7, g_sChar, Direction7, Player, g_bullet);
					break;
				}
				}
			}
			timer = 0;
		}
	}
}

void ShootEnemy(SGameChar &g_bullet, SGameChar &g_Enemy, PlayerInformation& Player)
{
	if ((g_Enemy.m_bActive == true) && (g_bullet.m_cLocation.X == g_Enemy.m_cLocation.X) && (g_bullet.m_cLocation.Y == g_Enemy.m_cLocation.Y))
	{
		Player.Points += 75;
		g_Enemy.m_bActive = false;

	}
}