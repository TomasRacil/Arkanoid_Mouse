// Arkanoid_Mouse.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "CBall.h"
#include "CBoard.h"


HANDLE  hConsoleOut;                   /* Handle ke konzolovemu oknu */
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;   /* informace o konzolovem okne */
HANDLE hConsoleIn; /* handle ke vstupu z konzole */

CBall g_Ball;
CBoard g_Board;

void PrintXYColor(int x, int y, WORD attribute, char* str) {
	COORD coord;
	DWORD written;

	coord.X = x;
	coord.Y = y;
	WORD* attribfield = (WORD*) malloc(strlen(str) * sizeof(WORD)); //*** vytvorime pole atributu textu podle delky textu
	for (int i = 0; i < strlen(str); i++) attribfield[i] = attribute; // vyplnime jej hodnotami atributu textu

	WriteConsoleOutputAttribute(hConsoleOut, attribfield, (DWORD)strlen(str), coord, &written);
	WriteConsoleOutputCharacter(hConsoleOut, str, (DWORD)strlen(str), coord, &written);
	free(attribfield);
}

// *** smaze konzolovou obrazovku
void ClearScreen(void)
{
	DWORD    dummy;
	COORD    Home = { 0, 0 };
	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
}


int main()
{
	/* Otevreme konzolove okno a ziskame informace o jejich parametrech.*/
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	WORD OldConsoleAttributes = csbiInfo.wAttributes; //*** zapamatujeme si puvodni atributy textu - barvy

	hConsoleIn = GetStdHandle(STD_INPUT_HANDLE); //*** otevreme vstup standardni konzole
	INPUT_RECORD  InputRecord[128]; // struktura obsahujici udalosti predavane z windows do konzole - klavesice, mys, systemove info, ...
	DWORD Events; // pocet udalosti predanych

	SetConsoleMode(hConsoleIn, ENABLE_EXTENDED_FLAGS); //nastavime vlasntosti konzole

	SetConsoleMode(hConsoleIn, ENABLE_PROCESSED_INPUT | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT); // nastavime co chceme prijimat

	

	ClearScreen();
	bool konec = false;

	int PoziceX = 20;
	int PozoiceXOld = 20;

	PrintXYColor(20, 5, BACKGROUND_BLUE | BACKGROUND_GREEN  | FOREGROUND_RED, (char*)"Welcome into colored world!");


	do {
		GetNumberOfConsoleInputEvents(hConsoleIn, &Events);
		if (Events > 0) {
			ReadConsoleInput(hConsoleIn, InputRecord, 128, &Events); //precteme aktualni udalosti co jsou ve fronte

			for (int i = 0; i < Events; i++) { // zpracujeme celou frontu udalosti - v cyklu jednu po druhe
				switch (InputRecord[i].EventType) {
				case KEY_EVENT: //udalosti z klavesnice - stisky klaves
					switch (InputRecord[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_ESCAPE:
						konec = true;
						break;
					case VK_LEFT: //sipka vlevo
						PoziceX--;
						break;
					case VK_RIGHT:
						PoziceX++;
						break;
					}
					break;
				case MOUSE_EVENT: //udalosti mysi
					g_Board.Pohni(InputRecord[i].Event.MouseEvent.dwMousePosition.X, 23); // X ova pozice
					switch (InputRecord[i].Event.MouseEvent.dwButtonState) {
					case FROM_LEFT_1ST_BUTTON_PRESSED: //stisknuto leve tlacitko mysi
						break;
					}
				}
			}
			FlushConsoleInputBuffer(hConsoleIn);
		}

		g_Ball.Pohni();
		g_Ball.Zobraz();
		// podle zasahu palky zmenime pozici micku
		if (g_Board.ZkontrolujBall(g_Ball.GetPozice()) == ZASAH_VLEVO) {
			g_Ball.m_SmerHorizont = SMER_VLEVO;
			g_Ball.m_SmerVertical = true;
		}
		if (g_Board.ZkontrolujBall(g_Ball.GetPozice()) == ZASAH_VPRAVO) {
			g_Ball.m_SmerHorizont = SMER_VPRAVO;
			g_Ball.m_SmerVertical = true;
		}
		if (g_Board.ZkontrolujBall(g_Ball.GetPozice()) == ZASAH_STRED) {
			g_Ball.m_SmerHorizont = SMER_ROVNE;
			g_Ball.m_SmerVertical = true;
		}

		//zobrazime palku
		g_Board.Zobraz();
		Sleep(100);
	} while (konec == false);

	SetConsoleTextAttribute(hConsoleOut, OldConsoleAttributes); //*** nastavime puvodni atributy textu - barvy

	printf("Stiskni cokoliv pro ukonceni aplikace ...\n");
	while (!_kbhit());


	return 0;
}





