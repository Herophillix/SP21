#include "game.h"

bool upcheck(SGameChar &Sprite, char** Maze, char Character)
{
	if (Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == Character)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool rightcheck(SGameChar &Sprite, char** Maze, char Character)
{
	if (Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == Character)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool downcheck(SGameChar &Sprite, char** Maze, char Character)
{
	if (Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == Character)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool leftcheck(SGameChar &Sprite, char** Maze, char Character)
{
	if (Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == Character)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool doorcheck(KDInformation &Item, int &ItemNumber, KDInformation &Key, SGameChar &g_sChar)
{
	if ((Item.Location[ItemNumber].Y == g_sChar.m_cLocation.Y - 1) && (Item.Location[ItemNumber].X == g_sChar.m_cLocation.X) ||
		(Item.Location[ItemNumber].Y == g_sChar.m_cLocation.Y) && (Item.Location[ItemNumber].X == g_sChar.m_cLocation.X + 1) ||
		(Item.Location[ItemNumber].Y == g_sChar.m_cLocation.Y + 1) && (Item.Location[ItemNumber].X == g_sChar.m_cLocation.X) ||
		(Item.Location[ItemNumber].Y == g_sChar.m_cLocation.Y) && (Item.Location[ItemNumber].X == g_sChar.m_cLocation.X - 1))
	{
		if (Item.isKey == true)
		{
			return true;
		}
		else if (Key.Checker[Item.id[ItemNumber]] == true)
		{
			return true;
		}
	}
	else
	{
		return false;
	}
	return false;
}