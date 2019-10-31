//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Cell.h"
#define CELLSIZE 68
#define OFFSETX 12
#define OFFSETY 11
#define BALLSCOUNT 7
#define activeCellWay "resources/activeCell.bmp"
#define cellWay "resources/Cell.bmp"
#define ballWay "resources/Ball.bmp"
using namespace std;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	void __fastcall nextStepClick(TObject *Sender);
private:	// User declarations
	Cell* _cells[9][9];
	Cell* _activeCell;
	vector<Cell*> _freeCells;
    TPicture* _actPctrs[2];
	TPicture* _ballPctrs[BALLSCOUNT];
    //--Animation--
    int _animCfSetBall;
	vector<Cell*> _animSetCells;
    vector<Cell*> _burst;
	//--Info--
    int _nextBalls[3];
    TImage* _nextBallsImgs[3];
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall PostClick(TObject*);
	void InitCells();
	void InitPictures();
	bool PutBalls();
	void SetBall(int, int, int, bool=false);
	void PutBall(int);
	void InitNextBallImgs();
    void GenNextBalls();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
