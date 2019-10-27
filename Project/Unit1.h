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
private:	// User declarations
	Cell* _cells[9][9];
	Cell* _activeCell;
	vector<Cell*> _freeCells;
    TPicture* _actPctrs[2];
	TPicture* _ballPctrs[BALLSCOUNT];
	//--Info--
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall PostClick(TObject*);
	void InitCells();
	void InitPictures();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
