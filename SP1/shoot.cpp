#include "game.h"
#include "Framework\console.h"
bool add[K_COUNT];
void actionshoot(SGameChar &g_sChar, SGameChar &g_bullet, SGameChar &g_bulletP, SGameChar &g_portalEntrance, SGameChar &g_portalExit, bool &aSomethingHappened,
	int &bulletcondition, int &ShootDirection, int &ShootDirectionFinal, bool &Bulletpos, int &ShootDirectionFinalRed, bool &BulletposPRed, int &ShootDirectionFinalBlue, 
	bool &BulletposPBlue, char **Maze, double &g_eBounceTime, double &g_eElapsedTime, bool g_abKeyPressed[K_COUNT])
{
	asdf();
	if (add[K_1])
	{
		bulletcondition = 1;
	}
	else if (add[K_2])
	{
		bulletcondition = 2;
	}
	else if (add[K_3])
	{
		bulletcondition = 3;
	}
	else if (add[K_Q])
	{
		if (g_eBounceTime > g_eElapsedTime)
			return;
		bulletcondition = bulletcondition % 3 + 1;
		g_eBounceTime = g_eElapsedTime + 0.25;
	}
	if ((bulletcheck(' ', ShootDirection, Maze, g_sChar)) || (bulletcheck((char)219, ShootDirection, Maze, g_sChar)))
	{
		switch (bulletcondition)
		{
		case 1:
		{
			shoot(aSomethingHappened, g_eBounceTime, g_eElapsedTime, ShootDirection, g_bullet, g_sChar, ShootDirectionFinal, Bulletpos, &g_abKeyPressed[K_COUNT]);
			break;
		}
		case 2:
		{
			shootPRed(aSomethingHappened, g_eBounceTime, g_eElapsedTime, ShootDirection, g_bulletP, g_sChar, ShootDirectionFinalRed, BulletposPRed, &g_abKeyPressed[K_COUNT]);
			break;
		}
		case 3:
		{
			shootPBlue(aSomethingHappened, g_eBounceTime, g_eElapsedTime, ShootDirection, g_bulletP, g_sChar, ShootDirectionFinalBlue, BulletposPBlue, &g_abKeyPressed[K_COUNT]);
			break;
		}
		}
	}
	movebullet(Bulletpos, ShootDirectionFinal, g_bullet, g_portalEntrance, g_portalExit);
	movebulletPRed(BulletposPRed, ShootDirectionFinalRed, g_bulletP, g_portalEntrance, g_sChar, Maze);
	movebulletPBlue(BulletposPBlue, ShootDirectionFinalBlue, g_bulletP, g_portalExit, g_sChar, Maze);
}

void asdf(void)
{
	add[K_UP] = isKeyPressed(VK_UP);
	add[K_DOWN] = isKeyPressed(VK_DOWN);
	add[K_LEFT] = isKeyPressed(VK_LEFT);
	add[K_RIGHT] = isKeyPressed(VK_RIGHT);
	add[K_SPACE] = isKeyPressed(VK_SPACE);
	add[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	add[K_1] = isKeyPressed(0x31);
	add[K_2] = isKeyPressed(0x32);
	add[K_3] = isKeyPressed(0x33);
	add[K_NUMPAD0] = isKeyPressed(VK_NUMPAD0);
	add[K_NUMPAD1] = isKeyPressed(VK_NUMPAD1);
	add[K_NUMPAD2] = isKeyPressed(VK_NUMPAD2);
	add[K_E] = isKeyPressed(0x45);
	add[K_Q] = isKeyPressed(0x51);
}

void shoot(bool &aSomethingHappened, double &g_eBounceTime, double &g_eElapsedTime, int &ShootDirection, SGameChar &g_bullet , SGameChar &g_sChar, int &ShootDirectionFinal, bool &Bulletpos, bool g_abKeyPressed[K_COUNT])
{
	aSomethingHappened = false;
	if (g_eBounceTime > g_eElapsedTime)
		return;
	if (add[K_SPACE])
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

void movebullet(bool &Bulletpos, int &ShootDirectionFinal, SGameChar &g_bullet, SGameChar &g_portalEntrance, SGameChar &g_portalExit)
{
	if (Bulletpos == true)
	{
		switch (ShootDirectionFinal)
		{
		case 1:
		{
			if (upcheck(g_bullet) || upcheckB(g_bullet))
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
			if (rightcheck(g_bullet) || rightcheckB(g_bullet))
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
			if (downcheck(g_bullet) || downcheckB(g_bullet))
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
			if (leftcheck(g_bullet) || leftcheckB(g_bullet))
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

void shootPRed(bool &aSomethingHappened, double &g_eBounceTime, double &g_eElapsedTime, int &ShootDirection, SGameChar &g_bulletP, SGameChar &g_sChar, int &ShootDirectionFinalRed, bool &BulletposPRed, bool g_abKeyPressed[K_COUNT])
{
	aSomethingHappened = false;
	if (g_eBounceTime > g_eElapsedTime)
		return;
	if (add[K_SPACE])
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

void shootPBlue(bool &aSomethingHappened, double &g_eBounceTime, double &g_eElapsedTime, int &ShootDirection, SGameChar &g_bulletP, SGameChar &g_sChar, int &ShootDirectionFinalBlue , bool &BulletposPBlue, bool g_abKeyPressed[K_COUNT])
{
	aSomethingHappened = false;
	if (g_eBounceTime > g_eElapsedTime)
		return;
	if (add[K_SPACE])
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

void movebulletPRed(bool &BulletposPRed, int &ShootDirectionFinalRed, SGameChar &g_bulletP, SGameChar &g_portalEntrance, SGameChar &g_sChar, char **Maze)
{
	if (BulletposPRed == true)
	{
		switch (ShootDirectionFinalRed)
		{
		case 1:
		{
			if (upcheck(g_bulletP) || upcheckB(g_bulletP))
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
			if (rightcheck(g_bulletP) || rightcheckB(g_bulletP))
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
			if (downcheck(g_bulletP) || downcheckB(g_bulletP))
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
			if (leftcheck(g_bulletP) || leftcheckB(g_bulletP))
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

void movebulletPBlue(bool &BulletposPBlue, int &ShootDirectionFinalBlue, SGameChar &g_bulletP, SGameChar &g_portalExit, SGameChar &g_sChar, char **Maze)
{
	if (BulletposPBlue == true)
	{
		switch (ShootDirectionFinalBlue)
		{
		case 1:
		{
			if (upcheck(g_bulletP) || upcheckB(g_bulletP))
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
			if (rightcheck(g_bulletP) || rightcheckB(g_bulletP))
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
			if (downcheck(g_bulletP) || downcheckB(g_bulletP))
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
			if (leftcheck(g_bulletP) || leftcheckB(g_bulletP))
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

bool bulletcheck(char Character, int &ShootDirection, char **Maze, SGameChar &g_sChar)
{
	switch (ShootDirection)
	{
	case 1:
	{
		if (Maze[g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == Character)
		{
			return true;
		}
		break;
	}
	case 2:
	{
		if (Maze[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 1] == Character)
		{
			return true;
		}
		break;
	}
	case 3:
	{
		if (Maze[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == Character)
		{
			return true;
		}
		break;
	}
	case 4:
	{
		if (Maze[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 1] == Character)
		{
			return true;
		}
		break;
	}
	}
	return false;
}