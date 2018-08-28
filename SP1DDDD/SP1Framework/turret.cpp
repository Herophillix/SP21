#include "game.h"
using namespace std;
int TurretBulletNumbert;
int TurretBulletNumberT;
//bool turretbulletcheckt[2] = { false, };
//bool turretbulletcheckT[3] = { false, };
int turretBtimet = 0;
int turretBtimeT = 0;

void turretshoott(TurretInformation &Map, bool &aSomethingHappened, char **Maze, double &g_eBounceTime, double &g_eElapsedTime, SGameChar &g_sChar, SGameChar &g_bullet, PlayerInformation &Player, bool &CharacterisHit, int &currentHealth)
{	
	Shootturret(g_bullet, Map.array_T, Map.array_t, Player);
	turretBtimet++;
	if (turretBtimet > 4)
	{
		for (TurretBulletNumbert = 0; TurretBulletNumbert < MAX_NUM_OF_TURRETS_DOWN; TurretBulletNumbert++)
		{
			Map.array_tbullet[TurretBulletNumbert].m_bActive = true;
			if (Map.array_t[TurretBulletNumbert].m_bActive == true)
			{
				Map.array_tbullet[TurretBulletNumbert].m_cLocation.X = Map.array_t[TurretBulletNumbert].m_cLocation.X;
				if ((Map.array_tbullet[TurretBulletNumbert].m_cLocation.Y + 1 == g_sChar.m_cLocation.Y) && (Map.array_tbullet[TurretBulletNumbert].m_cLocation.X == g_sChar.m_cLocation.X) && (g_eBounceTime < g_eElapsedTime))
				{
					Player.Health -= 1;
				}
				if (Map.array_tcheck[TurretBulletNumbert] == false)
				{
					Map.array_tbullet[TurretBulletNumbert].m_cLocation.Y = Map.array_t[TurretBulletNumbert].m_cLocation.Y + 1;
					Map.array_tcheck[TurretBulletNumbert] = true;
				}
				if ((Map.array_tcheck[TurretBulletNumbert] == true) && (Maze[Map.array_tbullet[TurretBulletNumbert].m_cLocation.Y][Map.array_tbullet[TurretBulletNumbert].m_cLocation.X] != (char)219))
				{
					Map.array_tbullet[TurretBulletNumbert].m_cLocation.Y++;
				}
				else
				{
					Map.array_tcheck[TurretBulletNumbert] = false;
				}
			}
			else if (Map.array_t[TurretBulletNumbert].m_bActive == false)
			{
				Map.array_tbullet[TurretBulletNumbert].m_bActive = false;
				renderTbullet(Map);
			}
		}
		turretBtimet = 0;
	}
}
void turretshootT(TurretInformation &Map, bool &aSomethingHappened, char **Maze, double &g_eBounceTime, double &g_eElapsedTime, SGameChar &g_sChar, SGameChar &g_bullet, PlayerInformation &Player, bool &CharacterisHit, int &currentHealth)
{
	Shootturret(g_bullet, Map.array_T, Map.array_t, Player);
	turretBtimeT++;
	if (turretBtimeT > 4)
	{
		for (TurretBulletNumberT = 0; TurretBulletNumberT < MAX_NUM_OF_TURRETS_RIGHT; TurretBulletNumberT++)
		{
			Map.array_Tbullet[TurretBulletNumberT].m_bActive = true;
			if (Map.array_T[TurretBulletNumberT].m_bActive == true)
			{
				Map.array_Tbullet[TurretBulletNumberT].m_cLocation.Y = Map.array_T[TurretBulletNumberT].m_cLocation.Y;
				if ((Map.array_Tbullet[TurretBulletNumberT].m_cLocation.Y == g_sChar.m_cLocation.Y) && (Map.array_Tbullet[TurretBulletNumberT].m_cLocation.X + 1 == g_sChar.m_cLocation.X) && (g_eBounceTime < g_eElapsedTime))
				{
					Player.Health -= 1;
				}
				if (Map.array_Tcheck[TurretBulletNumberT] == false)
				{
					Map.array_Tbullet[TurretBulletNumberT].m_cLocation.X = Map.array_T[TurretBulletNumberT].m_cLocation.X + 1;
					Map.array_Tcheck[TurretBulletNumberT] = true;
				}
				if ((Map.array_Tcheck[TurretBulletNumberT] == true) && (Maze[Map.array_Tbullet[TurretBulletNumberT].m_cLocation.Y][Map.array_Tbullet[TurretBulletNumberT].m_cLocation.X + 1] != (char)219))
				{
					Map.array_Tbullet[TurretBulletNumberT].m_cLocation.X++;
				}
				else
				{
					Map.array_Tcheck[TurretBulletNumberT] = false;
				}
			}
			else if (Map.array_T[TurretBulletNumberT].m_bActive == false)
			{
				Map.array_Tbullet[TurretBulletNumberT].m_bActive = false;
				renderTbullet(Map);
			}
		}
		turretBtimeT = 0;
	}
}

void Shootturret(SGameChar &g_bullet, SGameChar(&turretT)[MAX_NUM_OF_TURRETS_RIGHT], SGameChar(&turrett)[MAX_NUM_OF_TURRETS_DOWN], PlayerInformation& Player)
{
	for (int i = 0; i < 3; i++)
	{
		if ((turretT[i].m_bActive == true) && (g_bullet.m_cLocation.X == turretT[i].m_cLocation.X) && (g_bullet.m_cLocation.Y == turretT[i].m_cLocation.Y))
		{
			Player.Points += 75;
			turretT[i].m_bActive = false;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if ((turrett[i].m_bActive == true) && (g_bullet.m_cLocation.X == turrett[i].m_cLocation.X) && (g_bullet.m_cLocation.Y == turrett[i].m_cLocation.Y))
		{
			Player.Points += 75;
			turrett[i].m_bActive = false;

		}
	}
}