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
	this->_image = img;
}
void Cell::SetPicture(TPicture* pic){
	this->_image->Picture = pic;
}
void Cell::LoadActPctrs(TPicture* *pics){
	_actPctrs = pics;
}
void Cell::LoadBallPctrs(TPicture* *balls){
	_ballPctrs = balls;
}

void Cell::SetActive(bool a){
	_isActive = a;
	_image->Picture = _actPctrs[(int)_isActive];
}

