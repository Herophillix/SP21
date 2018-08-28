#include "game.h"
bool isKeyPressedCreate[K_COUNT];
void getInputCreate()
{
	isKeyPressedCreate[K_UP] = isKeyPressed(VK_UP);
	isKeyPressedCreate[K_DOWN] = isKeyPressed(VK_DOWN);
	isKeyPressedCreate[K_LEFT] = isKeyPressed(VK_LEFT);
	isKeyPressedCreate[K_RIGHT] = isKeyPressed(VK_RIGHT);
	isKeyPressedCreate[K_E] = isKeyPressed(0x45);
}
void changeCharacter(WORD &charColor, unsigned char &charIcon, int &charOption, int &charDetail, double &g_createBounceTime, double &g_dElapsedTime, bool &isDetail, EGAMEMODES &g_eGamemode)
{
	if (isDetail == true)
	{
		changeDetail(charColor, charIcon, charOption, charDetail, g_createBounceTime, g_dElapsedTime, isDetail, g_eGamemode);
		return;
	}
	bool didSomething = false;
	if (g_createBounceTime > g_dElapsedTime)
		return;
	getInputCreate();
	if (isKeyPressedCreate[K_UP])
	{
		charOption--;
		if (charOption == -1)
		{
			charOption = 2;
		}
		didSomething = true;
	}
	if (isKeyPressedCreate[K_DOWN])
	{
		charOption++;
		charOption %= 3;
		didSomething = true;
	}
	if (isKeyPressedCreate[K_E])
	{
		charDetail = 0;
		isDetail = true;
		didSomething = true;
	}
	if (didSomething == true)
	{
		g_createBounceTime = g_dElapsedTime + 0.15;
		didSomething = false;
	}
}
void changeDetail(WORD &charColor, unsigned char &charIcon, int &charOption, int &charDetail, double &g_createBounceTime, double &g_dElapsedTime, bool &isDetail, EGAMEMODES &g_eGamemode)
{
	bool didSomething = false;
	if (g_createBounceTime > g_dElapsedTime)
		return;
	getInputCreate();
	if (isKeyPressedCreate[K_UP])
	{
		charDetail--;
		if (charOption == 2)
		{
			if (charDetail == -1)
			{
				charDetail = 1;
			}
		}
		else
		{
			if (charDetail == -1)
			{
				charDetail = 3;
			}
		}
		didSomething = true;
	}
	if (isKeyPressedCreate[K_DOWN])
	{
		charDetail++;
		if (charOption == 2)
		{
			charDetail %= 2;
		}
		else
		{
			charDetail %= 4;
		}
		didSomething = true;
	}
	if (isKeyPressedCreate[K_E])
	{
		if (charOption == 0)
		{
			switch (charDetail)
			{
			case 0:
			{
				charColor = 0x04;
				break;
			}
			case 1:
			{
				charColor = 0x0b;
				break;
			}
			case 2:
			{
				charColor = 0x02;
				break;
			}
			case 3:
			{
				charColor = 0x06;
				break;
			}
			}
		}
		if (charOption == 1)
		{
			switch (charDetail)
			{
			case 0:
			{
				charIcon = (char)6;
				break;
			}
			case 1:
			{
				charIcon = (char)234;
				break;
			}
			case 2:
			{
				charIcon = (char)237;
				break;
			}
			case 3:
			{
				charIcon = (char)250;
				break;
			}
			}
		}
		if (charOption == 2)
		{
			if (charDetail == 0)
			{
				g_eGamemode = S_STAGEONE;
			}
		}
		isDetail = false;
		didSomething = true;
	}
	if (didSomething == true)
	{
		g_createBounceTime = g_dElapsedTime + 0.15;
		didSomething = false;
	}
}