#include "game.h"
using namespace std;
int TurretBulletNumbert;
int TurretBulletNumberT;
bool turretbulletcheckt[2] = { false, };
bool turretbulletcheckT[3] = { false, };
int turretBtimet = 0;
int turretBtimeT = 0;

void turretshoott(SGameChar(&turret)[2], SGameChar(&g_turretbulletarray)[2], bool &aSomethingHappened, char **Maze, double &g_eBounceTime, double &g_eElapsedTime)
{
	turretBtimet++;
	if (turretBtimet > 3)
	{
		for (TurretBulletNumbert = 0; TurretBulletNumbert < 2; TurretBulletNumbert++)
		{
			g_turretbulletarray[TurretBulletNumbert].m_cLocation.X = turret[TurretBulletNumbert].m_cLocation.X;
			if (turretbulletcheckt[TurretBulletNumbert] == false)
			{
				g_turretbulletarray[TurretBulletNumbert].m_cLocation.Y = turret[TurretBulletNumbert].m_cLocation.Y + 1;
				turretbulletcheckt[TurretBulletNumbert] = true;
			}
			if ((turretbulletcheckt[TurretBulletNumbert] == true) && (Maze[g_turretbulletarray[TurretBulletNumbert].m_cLocation.Y][g_turretbulletarray[TurretBulletNumbert].m_cLocation.X] != (char)219))
			{
				g_turretbulletarray[TurretBulletNumbert].m_cLocation.Y++;

			}
			else
			{
				turretbulletcheckt[TurretBulletNumbert] = false;
			}
		}turretBtimet = 0;
	}
}
void turretshootT(SGameChar(&turret)[3], SGameChar(&g_turretbulletarray)[3], bool &aSomethingHappened, char **Maze, double &g_eBounceTime, double &g_eElapsedTime)
{
	turretBtimeT++;
	if (turretBtimeT > 3)
	{
		for (TurretBulletNumberT = 0; TurretBulletNumberT < 3; TurretBulletNumberT++)
		{
			g_turretbulletarray[TurretBulletNumberT].m_cLocation.Y = turret[TurretBulletNumberT].m_cLocation.Y;
			if (turretbulletcheckT[TurretBulletNumberT] == false)
			{
				g_turretbulletarray[TurretBulletNumberT].m_cLocation.X = turret[TurretBulletNumberT].m_cLocation.X + 1;
				turretbulletcheckT[TurretBulletNumberT] = true;
			}
			if ((turretbulletcheckT[TurretBulletNumberT] == true) && (Maze[g_turretbulletarray[TurretBulletNumberT].m_cLocation.Y][g_turretbulletarray[TurretBulletNumberT].m_cLocation.X + 1] != (char)219))
			{
				g_turretbulletarray[TurretBulletNumberT].m_cLocation.X++;

			}
			else
			{
				turretbulletcheckT[TurretBulletNumberT] = false;
			}
		}turretBtimeT = 0;
	}
}