#include "game.h"
#include "alphabet.h"

bool g_abAlphaPressed[A_COUNT];
double g_InputElapsedTime;
int alphabetPressed;
bool alphabetTaken = false;

void getAlphabet(void)
{
	g_abAlphaPressed[A_A] = isKeyPressed(0x41);
	g_abAlphaPressed[A_B] = isKeyPressed(0x42);
	g_abAlphaPressed[A_C] = isKeyPressed(0x43);
	g_abAlphaPressed[A_D] = isKeyPressed(0x44);
	g_abAlphaPressed[A_E] = isKeyPressed(0x45);
	g_abAlphaPressed[A_F] = isKeyPressed(0x46);
	g_abAlphaPressed[A_G] = isKeyPressed(0x47);
	g_abAlphaPressed[A_H] = isKeyPressed(0x48);
	g_abAlphaPressed[A_I] = isKeyPressed(0x49);
	g_abAlphaPressed[A_J] = isKeyPressed(0x4A);
	g_abAlphaPressed[A_K] = isKeyPressed(0x4B);
	g_abAlphaPressed[A_L] = isKeyPressed(0x4C);
	g_abAlphaPressed[A_M] = isKeyPressed(0x4D);
	g_abAlphaPressed[A_N] = isKeyPressed(0x4E);
	g_abAlphaPressed[A_O] = isKeyPressed(0x4F);
	g_abAlphaPressed[A_P] = isKeyPressed(0x50);
	g_abAlphaPressed[A_Q] = isKeyPressed(0x51);
	g_abAlphaPressed[A_R] = isKeyPressed(0x52);
	g_abAlphaPressed[A_S] = isKeyPressed(0x53);
	g_abAlphaPressed[A_T] = isKeyPressed(0x54);
	g_abAlphaPressed[A_U] = isKeyPressed(0x55);
	g_abAlphaPressed[A_V] = isKeyPressed(0x56);
	g_abAlphaPressed[A_W] = isKeyPressed(0x57);
	g_abAlphaPressed[A_X] = isKeyPressed(0x58);
	g_abAlphaPressed[A_Y] = isKeyPressed(0x59);
	g_abAlphaPressed[A_Z] = isKeyPressed(0x5A);
	g_abAlphaPressed[A_BACKSPACE] = isKeyPressed(VK_BACK);
}

void currentNameInput(double &g_dElapsedTime, char(&topInitials)[3])
{
	if (g_InputElapsedTime > g_dElapsedTime)
		return;
	getAlphabet();

	if ((topInitials[0] != '#') && (g_abAlphaPressed[A_BACKSPACE]))
	{
		if ((topInitials[1] != '#') && (g_abAlphaPressed[A_BACKSPACE]))
		{
			if ((topInitials[2] != '#') && (g_abAlphaPressed[A_BACKSPACE]))
			{
				topInitials[2] = '#';
				g_InputElapsedTime = g_dElapsedTime + 0.1;
			}
			else
			{
				topInitials[1] = '#';
				g_InputElapsedTime = g_dElapsedTime + 0.1;
			}
		}
		else
		{
			topInitials[0] = '#';
			g_InputElapsedTime = g_dElapsedTime + 0.1;
		}
	}

	for (int i = 0; i < 26; i++)
	{
		if (g_abAlphaPressed[i])
		{
			alphabetPressed = i;
			alphabetTaken = true;
			g_InputElapsedTime = g_dElapsedTime + 0.2;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if ((topInitials[i] == '#') && (alphabetTaken == true))
		{
			topInitials[i] = (char)(alphabetPressed + 65);
			alphabetTaken = false;
			i = 3;
		}
	}
}