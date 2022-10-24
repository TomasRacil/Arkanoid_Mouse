#pragma once

class CPozice
{
public: 
	int x,y;

public:
	CPozice(void);
	~CPozice(void);
	bool operator==(CPozice pozice);
};
