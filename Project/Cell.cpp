//---------------------------------------------------------------------------

#pragma hdrstop

#include "Cell.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Cell::Cell(TImage* img, int i, int j, int offx, int offy){
	_i = i; _j = j;
	_crrntBall = -1;
	_isActive = false;
}
void Cell::SetPicture(TPicture* pic){
}
void Cell::LoadActPctrs(TPicture* *pics){
}
void Cell::LoadBallPctrs(TPicture* *balls){
}

void Cell::SetActive(bool a){
}

