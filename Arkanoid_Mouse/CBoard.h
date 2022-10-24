#pragma once
#include "Pozice.h"
#include "printxy.h"
#include <Windows.h>

#define ZASAH_NULA 0
#define ZASAH_VLEVO 1
#define ZASAH_VPRAVO 2
#define ZASAH_STRED 3

class CBoard
{
public:
	CPozice m_Pozice;
	CPozice m_OldPozice;

	CBoard();
	void Zobraz();
	void Pohni(int x, int y);
	int ZkontrolujBall(CPozice ball);

};

