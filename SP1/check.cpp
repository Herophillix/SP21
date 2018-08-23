#include "game.h"

bool upcheck(SGameChar Sprite, char** Maze)
{
	if (Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == ' ')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool rightcheck(SGameChar Sprite, char** Maze)
{
	if (Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == ' ')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool downcheck(SGameChar Sprite, char** Maze)
{
	if (Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == ' ')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool leftcheck(SGameChar Sprite, char** Maze)
{
	if (Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == ' ')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool upcheckB(SGameChar Sprite, char** Maze)
{
	if (Maze[Sprite.m_cLocation.Y - 2][Sprite.m_cLocation.X] == '.')
	{
		return true;
	}
	return false;
}
bool rightcheckB(SGameChar Sprite, char** Maze)
{
	if (Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X + 1] == '.')
	{
		return true;
	}
	return false;
}
bool downcheckB(SGameChar Sprite, char** Maze)
{
	if (Maze[Sprite.m_cLocation.Y][Sprite.m_cLocation.X] == '.')
	{
		return true;
	}
	return false;
}
bool leftcheckB(SGameChar Sprite, char** Maze)
{
	if (Maze[Sprite.m_cLocation.Y - 1][Sprite.m_cLocation.X - 1] == '.')
	{
		return true;
	}
	return false;
}