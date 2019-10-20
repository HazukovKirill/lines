//---------------------------------------------------------------------------

#ifndef CellH
#define CellH
#include <iostream>
#define ANIMITER 20
//---------------------------------------------------------------------------
class Cell{
	int _i, _j;
    int _x, _y;
	TImage* _image;
    TImage* _ballImage;
	bool _isActive;
	int _crrntBall;
	int _sizeCf;
public:
	Cell(TImage*,int,int,int,int);
	void SetPicture(TPicture*);
	bool GetActive(){return _isActive;}
	void SetActive(bool a);
	void LoadActPctrs(TPicture* *pics);
	void LoadBallPctrs(TPicture* *balls);
	int GetI(){return _i;}
	int GetJ(){return _j;}
};
#endif
