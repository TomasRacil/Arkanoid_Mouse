#pragma once
#include "Pozice.h"
#include "printxy.h"
#include <Windows.h>

#define SMER_VLEVO 0
#define SMER_VPRAVO 1
#define SMER_ROVNE 2


class CBall
{
public:
	CPozice m_Pozice;
	CPozice m_OldPozice;
	int m_SmerHorizont;
	bool m_SmerVertical;
	

	CBall();
	void SetPozice(CPozice pos);
	CPozice GetPozice();
	void Zobraz();
	void Pohni();


};

