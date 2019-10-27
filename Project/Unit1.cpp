//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TForm1 *Form1;
//---------------------------------------------------------------------------
void __fastcall TForm1::PostClick(TObject* Sender){

}

//---------------------------------------------------------------------------
void TForm1::InitCells(){
	TImage* img;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			img = new TImage(this);
			img->Parent = this;
			img->OnClick = this->PostClick;
			img->Left = j * CELLSIZE;
			img->Top = i * CELLSIZE;
			_cells[i][j] = new Cell(img, i, j, OFFSETX, OFFSETY);
			_cells[i][j]->LoadActPctrs(_actPctrs);
			_cells[i][j]->LoadBallPctrs(_ballPctrs);
            _cells[i][j]->SetActive(false);
			_freeCells.push_back(_cells[i][j]);
		}
	}
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
	srand(time(NULL));
	_activeCell = nullptr;
	InitPictures();
	InitCells();
}
//---------------------------------------------------------------------------
void TForm1::InitPictures(){
	_actPctrs[0] = new TPicture();
	_actPctrs[0]->LoadFromFile(cellWay);
	_actPctrs[1] = new TPicture();
	_actPctrs[1]->LoadFromFile(activeCellWay);

	stringstream ss;
	string str;
	for (int i = 0; i < BALLSCOUNT; i++) {
		ss << (i+1);
		ss >> str;
		ss.clear();
		_ballPctrs[i] = new TPicture();
		auto g = ("resources/" + str + ".png");
		_ballPctrs[i]->LoadFromFile(g.c_str());
	}
}



