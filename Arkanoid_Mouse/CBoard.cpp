#include "CBoard.h"

CBoard::CBoard()
{
	m_Pozice.x = 20;
	m_Pozice.y = 24;

	m_OldPozice = m_Pozice;
}

void CBoard::Zobraz()
{
	 // vykreslime palku, ale symetricky od stredu pozice
	PrintXYColor(m_OldPozice.x-3, m_OldPozice.y, 0, (char*)"       ");
	PrintXYColor(m_Pozice.x-3, m_Pozice.y, BACKGROUND_BLUE | BACKGROUND_INTENSITY, (char*)"       ");
}

void CBoard::Pohni(int x, int y)
{
	m_OldPozice = m_Pozice;
	m_Pozice.x = x;
	m_Pozice.y = y;
}

int CBoard::ZkontrolujBall(CPozice ball) // zkontrolujeme kde jsme zasahli mickem palku
{
	if (ball.y == m_Pozice.y-1) { // kontrolujeme pozici tesne pred palkou, pokud tam je micek kontroluje horizontalni pozici
		if ((ball.x >= m_Pozice.x - 3) && (ball.x <= m_Pozice.x - 1)) return(ZASAH_VLEVO);
		if ((ball.x >= m_Pozice.x + 1) && (ball.x <= m_Pozice.x + 3)) return(ZASAH_VPRAVO);
		if (ball.x == m_Pozice.x) return(ZASAH_STRED);
	}
	return(ZASAH_NULA);
}
