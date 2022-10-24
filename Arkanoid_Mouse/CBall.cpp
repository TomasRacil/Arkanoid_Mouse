#include "CBall.h"

CPozice CBall::GetPozice()
{
	return(m_Pozice);
}

CBall::CBall()
{
	m_Pozice.x = 20;
	m_Pozice.y = 24;

	m_OldPozice = m_Pozice;
	m_SmerHorizont = SMER_ROVNE;
}

void CBall::SetPozice(CPozice pos)
{
	m_Pozice = pos;
}

void CBall::Zobraz()
{
	PrintXYColor(m_OldPozice.x, m_OldPozice.y, 0, (char*)"*");
	PrintXYColor(m_Pozice.x, m_Pozice.y, BACKGROUND_RED | BACKGROUND_INTENSITY, (char*)"*");

}

void CBall::Pohni()
{
	m_OldPozice = m_Pozice;
	// smer pohybu micku
	if (m_SmerHorizont == SMER_VLEVO) m_Pozice.x--;
	if (m_SmerHorizont == SMER_VPRAVO) m_Pozice.x++;
	
	if (m_SmerVertical) m_Pozice.y--;
	else m_Pozice.y++;

	// kontrola na hranice plochy
	if ((m_Pozice.x < 1) && (m_SmerHorizont == SMER_VLEVO)) m_SmerHorizont = SMER_VPRAVO;
	if ((m_Pozice.x > 75) && (m_SmerHorizont == SMER_VPRAVO)) m_SmerHorizont = SMER_VLEVO;
	if ((m_Pozice.y > 24)) m_SmerVertical = true;
	if ((m_Pozice.y < 1)) m_SmerVertical = false;

}
