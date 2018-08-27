#ifndef _BOSS_H
#define _BOSS_H

extern int playerIsHitFrame;
extern int bossInterval;
extern bool bossDirection;
extern int rollForBossAttack;
extern int bossAttackMax;
extern int bossAttackFrame[3];
extern int k;
extern bool bossAttackOn[3];
extern int subBulletmax;
extern int subBulletsCreated;
extern int subBulletsCreated2;
extern bool subBulletsAllCreated;
extern bool subBulletsAllCreated2;
extern bool bossLazerMaxReached;
extern bool charWordBullet;
extern bool charWordBulletHold;
extern bool charWordBulletTimeout;
extern int charWordBulletCharge;
extern int bossHealth;
extern int bossMaxHealth;
extern int charbossX;
extern int charbossY;

#endif // !_BOSS_H
