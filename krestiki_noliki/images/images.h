#pragma once

#include "../krestiki_noliki.h"

extern BYTE pbLeraLuchayaImageArray[/*2790*/];
extern BYTE pbZeroImageArray[/*90113*/];
extern BYTE pbCrossImageArray[/*2790*/];

//programm used: File to aByte

namespace images
{
	extern std::map<std::string, LPDIRECT3DTEXTURE9>pmTextureData;
	void Initialization(LPDIRECT3DDEVICE9 g_pd3dDevice);
}




