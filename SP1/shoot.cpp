#include "game.h"
#include "shoot.h"
#include "Framework\console.h"
bool isKeyPressedShoot[K_COUNT];

 bool Bulletpos = false;
 bool BulletposPRed = false;
 bool BulletposPBlue = false;

 int ShootDirectionFinal = 2;
 int ShootDirectionFinalRed = 2;
 int ShootDirectionFinalBlue = 2;
 int ShootDirectionEnemy = 2;
void actionshoot(SGameChar &g_sChar, SGameChar &g_bullet, SGameChar &g_bulletP, SGameChar &g_portalEntrance, SGameChar &g_portalExit, bool &aSomethingHappened,
	char **Maze, double &g_eBounceTime, double &g_eElapsedTime)
{
	getInputshoot();
	if (isKeyPressedShoot[K_1])
	{
		bulletcondition = 1;
	}
	else if (isKeyPressedShoot[K_2])
	{
		bulletcondition = 2;
	}
	else if (isKeyPressedShoot[K_3])
	{
		bulletcondition = 3;
	}
	else if (isKeyPressedShoot[K_Q])
	{
		if (g_eBounceTime > g_eElapsedTime)
			return;
		bulletcondition = bulletcondition % 3 + 1;
		g_eBounceTime = g_eElapsedTime + 0.25;
	}
	if ((bulletcheck(' ', Maze, g_sChar)) || (bulletcheck((char)219, Maze, g_sChar)))
	{
		switch (bulletcondition)
		{
		case 1:
		{
			shoot(aSomethingHappened, g_eBounceTime, g_eElapsedTime, g_bullet, g_sChar);
			break;
		}
		case 2:
		{
			shootPRed(aSomethingHappened, g_eBounceTime, g_eElapsedTime, g_bulletP, g_sChar);
			break;
		}
		case 3:
		{
			shootPBlue(aSomethingHappened, g_eBounceTime, g_eElapsedTime, g_bulletP, g_sChar);
			break;
		}
		}
	}
	movebullet(g_bullet, g_portalEntrance, g_portalExit);
	movebulletPRed(g_bulletP, g_portalEntrance, g_sChar, Maze);
	movebulletPBlue(g_bulletP, g_portalExit, g_sChar, Maze);
}

void getInputshoot(void)
{
	isKeyPressedShoot[K_UP] = isKeyPressed(VK_UP);
	isKeyPressedShoot[K_DOWN] = isKeyPressed(VK_DOWN);
	isKeyPressedShoot[K_LEFT] = isKeyPressed(VK_LEFT);
	isKeyPressedShoot[K_RIGHT] = isKeyPressed(VK_RIGHT);
	isKeyPressedShoot[K_SPACE] = isKeyPressed(VK_SPACE);
	isKeyPressedShoot[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	isKeyPressedShoot[K_1] = isKeyPressed(0x31);
	isKeyPressedShoot[K_2] = isKeyPressed(0x32);
	isKeyPressedShoot[K_3] = isKeyPressed(0x33);
	isKeyPressedShoot[K_NUMPAD0] = isKeyPressed(VK_NUMPAD0);
	isKeyPressedShoot[K_NUMPAD1] = isKeyPressed(VK_NUMPAD1);
	isKeyPressedShoot[K_NUMPAD2] = isKeyPressed(VK_NUMPAD2);
	isKeyPressedShoot[K_E] = isKeyPressed(0x45);
	isKeyPressedShoot[K_Q] = isKeyPressed(0x51);
}

void shoot(bool &aSomethingHappened, double &g_eBounceTime, double &g_eElapsedTime, SGameChar &g_bullet , SGameChar &g_sChar)
{
	aSomethingHappened = false;
	if (g_eBounceTime > g_eElapsedTime)
		return;
	if (isKeyPressedShoot[K_SPACE])
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

void movebullet(SGameChar &g_bullet, SGameChar &g_portalEntrance, SGameChar &g_portalExit)
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

void shootPRed(bool &aSomethingHappened, double &g_eBounceTime, double &g_eElapsedTime, SGameChar &g_bulletP, SGameChar &g_sChar)
{
	aSomethingHappened = false;
	if (g_eBounceTime > g_eElapsedTime)
		return;
	if (isKeyPressedShoot[K_SPACE])
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

void shootPBlue(bool &aSomethingHappened, double &g_eBounceTime, double &g_eElapsedTime, SGameChar &g_bulletP, SGameChar &g_sChar)
{
	aSomethingHappened = false;
	if (g_eBounceTime > g_eElapsedTime)
		return;
	if (isKeyPressedShoot[K_SPACE])
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

void movebulletPRed(SGameChar &g_bulletP, SGameChar &g_portalEntrance, SGameChar &g_sChar, char **Maze)
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

void movebulletPBlue(SGameChar &g_bulletP, SGameChar &g_portalExit, SGameChar &g_sChar, char **Maze)
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

bool bulletcheck(char Character, char **Maze, SGameChar &g_sChar)
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