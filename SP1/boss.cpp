#include "game.h"
#include <vector>
bool isKeyPressedBoss[K_COUNT];

bool characterIsHit = false;
int playerIsHitFrame = 0;
int bossInterval = 0;
bool bossDirection = false;
int rollForBossAttack = 0;
int bossAttackMax = 0;
int bossAttackFrame[3] = { 0, 0, 0 };
int k = 0;
bool bossAttackOn[3] = { false, };
int subBulletmax = 5;
int subBulletsCreated = 0;
int subBulletsCreated2 = 0;
bool subBulletsAllCreated = false;
bool subBulletsAllCreated2 = false;
bool bossLazerMaxReached = false;
bool charWordBullet = false;
bool charWordBulletHold = false;
bool charWordBulletTimeout = false;
int charWordBulletCharge = 0;
int bossHealth = 10;
int bossMaxHealth = 10;
int charbossX = 4;
int charbossY = 3;

void getInputBoss()
{
	isKeyPressedBoss[K_SPACE] = isKeyPressed(VK_SPACE);
	isKeyPressedBoss[K_1] = isKeyPressed(0x31);
}

void BossoneVar(double &g_dBounceTime, double &g_eBounceTime, double &g_dElapsedTime, SGameChar &g_sChar,
	Console &g_Console, char** BossMap, PlayerInformation &Player, SGameChar &g_bossMainGun, SGameChar &g_boss,
	SGameChar &g_bossSubGun1, SGameChar &g_bossSubGun2,
	SGameChar &g_Wordbullet, bool &charWordBullet, double (&g_bBounceTime)[6], vector<SGameChar> &g_bossSubBullet, vector<SGameChar> &g_bossSubBullet2)
{
	getInputBoss();
	bossMove(g_boss);
	if (bossAttackOn[0] == true)
	{
		bossAttackLazer(g_bossMainGun, g_boss, BossMap);
	}
	if (bossAttackOn[1] == true)
	{
		bossAttackMachineGunLeft(g_bossSubGun1, g_boss, BossMap, g_bossSubBullet);
	}
	if (bossAttackOn[2] == true)
	{
		bossAttackMachineGunRight(g_bossSubGun2, g_boss, BossMap, g_bossSubBullet2);
	}
	moveCharacterInBoss(g_dBounceTime, g_eBounceTime, g_dElapsedTime, g_sChar, g_Console, BossMap, Player, characterIsHit);
	charshootboss(g_Wordbullet, g_sChar, charWordBullet, g_bBounceTime, g_dElapsedTime, BossMap);
	processUserInput();
	checkhealth();

}
void bossMove(SGameChar& g_boss)
{
	bossInterval++;
	if (bossInterval > 20)
	{
		if (bossDirection)
		{
			g_boss.m_cLocation.X--;
		}
		else
		{
			if (g_boss.m_cLocation.X > 30)
			{
				bossDirection = true;
			}
			g_boss.m_cLocation.X++;
		}
		rollForBossAttack = rand() % 3;
		switch (rollForBossAttack)
		{
		case 0:
		{
			if (bossAttackOn[0] == false)
			{
				bossAttackOn[0] = true;
			}
			break;
		}
		case 1:
		{
			if (bossAttackOn[1] == false)
			{
				bossAttackOn[1] = true;
				break;
			}
		}
		case 2:
		{
			if (bossAttackOn[2] == false)
			{
				bossAttackOn[2] = true;
				break;
			}
		}
		}
		if (g_boss.m_cLocation.X < 5)
		{
			bossDirection = false;
		}
		bossInterval = 0;
	}
}
void bossAttackLazer(SGameChar &g_bossMainGun, SGameChar &g_boss, char** BossMap)
{
	g_bossMainGun.m_cLocation.X = g_boss.m_cLocation.X + 10;
	g_bossMainGun.m_cLocation.Y = g_boss.m_cLocation.Y + 13;

	bossAttackFrame[0]++;
	if (bossAttackFrame[0] > 15)
	{
		if (bossLazerMaxReached == true)
		{
			bossAttackMax--;
			if (bossAttackMax == 0)
			{
				bossLazerMaxReached = false;
				bossAttackOn[0] = false;
			}
		}
		else
		{
			if (bossAttackMax == 17)
			{
				bossLazerMaxReached = true;
			}
			if (bossAttackMax < 17)
			{
				bossAttackMax++;
			}
		}

		bossAttackFrame[0] = 0;
		k--;
		if (k == -1)
		{
			k = 7;
		}
	}

	COORD c;

	if (bossLazerMaxReached == true)
	{
		for (int i = 17 - bossAttackMax; i < 17; i++)
		{

			string bossAttackline = "0001111";
			string bossAttackBufferLine = "       ";
			c.Y = g_bossMainGun.m_cLocation.Y + i;
			for (int j = i; j < 7 + i; j++)
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
				}
			}
			}
		}
	}
	else
	{
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
				}
			}
			}
		}
	}

}
void bossAttackMachineGunLeft(SGameChar &g_bossSubGun1, SGameChar &g_boss, char** BossMap, vector<SGameChar> &g_bossSubBullet)
{
	g_bossSubGun1.m_cLocation.X = g_boss.m_cLocation.X + 4;
	g_bossSubGun1.m_cLocation.Y = g_boss.m_cLocation.Y + 8;

	bossAttackFrame[1]++;
	if (bossAttackFrame[1] % 10 == 0)
	{
		if (bossAttackFrame[1] > 50)
		{
			if (subBulletsAllCreated == false)
			{
				/*subBulletsToCreate++;
				for (; subBulletsCreated < subBulletsToCreate; subBulletsCreated++)
				{
				g_bossSubBullet.push_back(createBossSubBullet(g_bossSubGun1));
				}*/
				g_bossSubBullet.push_back(createBossSubBullet(g_bossSubGun1));
				subBulletsCreated++;
				if (subBulletsCreated == subBulletmax)
				{
					subBulletsAllCreated = true;
				}
			}
			bossAttackFrame[1] = 0;
		}
		for (int bulletCount = 0; bulletCount < subBulletsCreated; bulletCount++)
		{
			if (BossMap[g_bossSubBullet[bulletCount].m_cLocation.Y][g_bossSubBullet[bulletCount].m_cLocation.X] == (char)219)
			{
				g_bossSubBullet.erase(g_bossSubBullet.begin());
				subBulletsCreated--;

				if (subBulletsCreated == 0)
				{
					bossAttackOn[1] = false;
					subBulletsAllCreated = false;
					return;
				}
			}
			else
			{
				g_bossSubBullet[bulletCount].m_cLocation.Y++;
			}
		}
	}
	for (int bulletCount = 0; bulletCount < subBulletsCreated; bulletCount++)
	{
		BossMap[g_bossSubBullet[bulletCount].m_cLocation.Y - 1][g_bossSubBullet[bulletCount].m_cLocation.X] = '0';
	}
}
void bossAttackMachineGunRight(SGameChar &g_bossSubGun2, SGameChar &g_boss, char** BossMap, vector<SGameChar> &g_bossSubBullet2)
{
	g_bossSubGun2.m_cLocation.X = g_boss.m_cLocation.X + 21;
	g_bossSubGun2.m_cLocation.Y = g_boss.m_cLocation.Y + 8;

	bossAttackFrame[2]++;
	if (bossAttackFrame[2] % 10 == 0)
	{
		if (bossAttackFrame[2] > 50)
		{
			if (subBulletsAllCreated2 == false)
			{
				/*subBulletsToCreate++;
				for (; subBulletsCreated < subBulletsToCreate; subBulletsCreated++)
				{
				g_bossSubBullet.push_back(createBossSubBullet(g_bossSubGun1));
				}*/
				g_bossSubBullet2.push_back(createBossSubBullet(g_bossSubGun2));
				subBulletsCreated2++;
				if (subBulletsCreated2 == subBulletmax)
				{
					subBulletsAllCreated2 = true;
				}
			}
			bossAttackFrame[2] = 0;
		}
		for (int bulletCount = 0; bulletCount < subBulletsCreated2; bulletCount++)
		{
			if (BossMap[g_bossSubBullet2[bulletCount].m_cLocation.Y][g_bossSubBullet2[bulletCount].m_cLocation.X] == (char)219)
			{
				g_bossSubBullet2.erase(g_bossSubBullet2.begin());
				subBulletsCreated2--;

				if (subBulletsCreated2 == 0)
				{
					bossAttackOn[2] = false;
					subBulletsAllCreated2 = false;
					return;
				}
			}
			else
			{
				g_bossSubBullet2[bulletCount].m_cLocation.Y++;
			}
		}
	}
	for (int bulletCount = 0; bulletCount < subBulletsCreated2; bulletCount++)
	{
		BossMap[g_bossSubBullet2[bulletCount].m_cLocation.Y - 1][g_bossSubBullet2[bulletCount].m_cLocation.X] = '0';
	}
}
void bossAttackMachineGun(SGameChar &g_bossSubGun1, SGameChar &g_bossSubGun2, SGameChar &g_boss)
{
	g_bossSubGun1.m_cLocation.X = g_boss.m_cLocation.X + 4;
	g_bossSubGun1.m_cLocation.Y = g_boss.m_cLocation.Y + 8;
	g_bossSubGun2.m_cLocation.X = g_boss.m_cLocation.X + 17;
	g_bossSubGun2.m_cLocation.Y = g_boss.m_cLocation.Y + 8;
}
void charshootboss(SGameChar &g_Wordbullet, SGameChar &g_sChar, bool &charWordBullet, double(&g_bBounceTime)[6], double &g_dElapsedTime, char** BossMap)
{
	int i = 0;
	double j = 0.2;
	if (isKeyPressedBoss[K_SPACE])
	{
		if (charWordBulletTimeout == false)
		{
			g_Wordbullet.m_cLocation.X = g_sChar.m_cLocation.X;
			g_Wordbullet.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
			charWordBullet = true;
			charWordBulletCharge = 0;
			if (charWordBulletHold == false)
			{
				for (; i < 6; i++, j += 0.5)
				{
					if (i == 5)
					{
						g_bBounceTime[i] = g_dElapsedTime + 3;
					}
					else
					{
						g_bBounceTime[i] = g_dElapsedTime + j;
					}
				}
			}
			charWordBulletHold = true;
		}
	}
	else
	{
		charWordBulletTimeout = false;
		charWordBulletHold = false;
	}
	if (BossMap[g_Wordbullet.m_cLocation.Y - 1][g_Wordbullet.m_cLocation.X] == (char)219)
	{
		charWordBullet = false;
	}
	else if ((BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != ' ') &&
		(BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != '1') &&
		(BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != '0') &&
		(BossMap[g_Wordbullet.m_cLocation.Y - 2][g_Wordbullet.m_cLocation.X] != (char)219) &&
		charWordBulletHold == false && charWordBullet == true)
	{
		charWordBullet = false;
		switch (charWordBulletCharge)
		{
		case 0:
		{
			bossHealth -= 1;
			break;
		}
		case 1:
		{
			bossHealth -= 3;
			break;
		}
		case 2:
		{
			bossHealth -= 5;
			break;
		}
		case 3:
		{
			bossHealth -= 8;
			break;
		}
		case 4:
		{
			bossHealth -= 10;
			break;
		}
		case 5:
		{
			bossHealth -= 15;
			break;
		}

		}
		g_Wordbullet.m_cLocation.X = g_sChar.m_cLocation.X;
		g_Wordbullet.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
	}

	if (charWordBullet == true)
	{
		g_Wordbullet.m_cLocation.Y--;
	}


}
SGameChar createBossSubBullet(SGameChar &SubGunStart)
{
	SGameChar tempChar;
	tempChar.m_cLocation.X = SubGunStart.m_cLocation.X;
	tempChar.m_cLocation.Y = SubGunStart.m_cLocation.Y;
	return tempChar;
}