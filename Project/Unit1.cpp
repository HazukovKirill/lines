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
    InitNextBallImgs();
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
//---------------------------------------------------------------------------
void TForm1::InitNextBallImgs(){
	for (int i = 0; i < 3; i++) {
		_nextBallsImgs[i] = new TImage(this);
		_nextBallsImgs[i]->Parent = this;
		_nextBallsImgs[i]->Top = 176;
		_nextBallsImgs[i]->Left = 634 + 48*i;
		_nextBallsImgs[i]->Height = 24;
		_nextBallsImgs[i]->Width = 24;
		_nextBallsImgs[i]->Transparent = true;
		_nextBallsImgs[i]->Stretch = true;
	}

}
//---------------------------------------------------------------------------
void TForm1::GenNextBalls(){
	for (int i = 0; i < 3; i++) {
		_nextBalls[i] = rand()%BALLSCOUNT;
		_nextBallsImgs[i]->Picture = _ballPctrs[_nextBalls[i]];
	}
}
//---------------------------------------------------------------------------
void TForm1::PutBall(int nNextBall){
	int randCell = rand()%_freeCells.size();
	int nball = _nextBalls[nNextBall];
	SetBall(_freeCells[randCell]->GetI(),
			_freeCells[randCell]->GetJ(),
			nball
	);
}
//---------------------------------------------------------------------------
bool TForm1::PutBalls(){
	for(int i = 0; i < 3; i++){
		PutBall(i);
		if(_freeCells.size() == 0)
			return false;
	}
	GenNextBalls();
	return true;
}
//---------------------------------------------------------------------------
void TForm1::SetBall(int i, int j, int nball, bool target){
	_cells[i][j]->SetBall(nball);
	_animSetCells.push_back(_cells[i][j]);
	if(!target)
		_burst.push_back(_cells[i][j]);
	_cells[i][j]->SetBallSize(0);
	_freeCells.erase(
		remove(_freeCells.begin(), _freeCells.end(), _cells[i][j]), _freeCells.end()
	);
	//Timer1->Enabled = true;
	_animCfSetBall = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::nextStepClick(TObject *Sender)
{
    PutBalls();
}
//---------------------------------------------------------------------------

