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
	if(Timer1->Enabled || Timer2->Enabled){
        return;
	}
	int i, j;
	TImage* img;
	if(!(img = dynamic_cast<TImage*>(Sender))){
        return;
	}
	i = img->Top / CELLSIZE;
	j = img->Left / CELLSIZE;

	if(_activeCell == nullptr){
		_cells[i][j]->SetActive(true);
		_activeCell = _cells[i][j];
        return;
	}

	if(_activeCell == _cells[i][j]){
		_cells[i][j]->SetActive(false);
		_activeCell = nullptr;
		return;
	}

	if(_activeCell->GetBall() < 0 || _cells[i][j]->GetBall() >= 0){
		_activeCell->SetActive(false);
		_cells[i][j]->SetActive(true);
		_activeCell = _cells[i][j];
		return;
	}

	int ball_i = _activeCell->GetI();
	int ball_j = _activeCell->GetJ();
	if(!GetWay(ball_i, ball_j, i, j)){
        return;
	}

	int nball =_activeCell->GetBall();
	_activeCell->SetActive(false);
	_activeCell = nullptr;

	_animNBallWay = nball;
	Timer4->Enabled = true;
	_animIndxBallWay = 0;

	_targetBall = _cells[i][j];
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
	Timer1->Enabled = true;
	_animCfSetBall = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::nextStepClick(TObject *Sender)
{
    PutBalls();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NewGame(TObject *Sender)
{
	_score = 0;
	Label1->Caption = _score;
	_targetBall = nullptr;
	_burst.clear();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			_freeCells.push_back(_cells[i][j]);
			_cells[i][j]->SetBall(-1);
		}
	}
	GenNextBalls();
	PutBalls();
	nextStep->Enabled = true;
	//ItemMenuSaveGame->Enabled = true; READIX pls FIX this *****
	//there nothing to FIX, just implement button
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ExitClick(TObject *Sender)
{
	int Answer = Application->MessageBox(
		L"Вы уверены, что хотите выйти ? Шарики сами себя не лопнут!",
		L"Выход",
		MB_OKCANCEL
	);

	if(Answer == IDOK )
		exit(0);
}
//---------------------------------------------------------------------------
void TForm1::ShowMessageByFile(string mbname, string fileway){
	ifstream in;
	in.open(fileway);
	if(!in){
		in.close();
		Application->MessageBox(
			L"Произошла ошибка чтения файла.",
			L"Ошибка",
			MB_OK
		);
		return;
	}
	string ref, bf;
	while(getline(in,bf)){
	   ref += bf + "\n";
	}
	in.close();
	Application->MessageBox(
		((UnicodeString)ref.c_str()).c_str(),
		((UnicodeString)mbname.c_str()).c_str(),
		MB_OK
	 );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ItemMenuHelpClick(TObject *Sender)
{
	ShowMessageByFile("Помощь", WAYTOHELP);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ItemMenuRefClick(TObject *Sender)
{
	ShowMessageByFile("Справка", WAYTOREF);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	int iter;
	for(auto cell: _animSetCells){
		iter = cell->GetBallSize();
		if(iter == ANIMITER){
			_animSetCells.erase(
				remove(
					_animSetCells.begin(),
					_animSetCells.end(),
					cell
				),
				_animSetCells.end()
			);
			continue;
		}
		cell->SetBallSize(++iter);
	}
	if(_animSetCells.size() != 0){
		return;
	}
	Timer1->Enabled = false;
	BurstBalls();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	int iter;
	for(auto cell: _animDeleteCells){
		if(find(
				_animSetCells.begin(),
				_animSetCells.end(),
				cell
			) != _animSetCells.end()){
			continue;
		}
		iter = cell->GetBallSize();
		if(iter == -1){
			cell->SetBall(-1);
			_animDeleteCells.erase(
				remove(
					_animDeleteCells.begin(),
					_animDeleteCells.end(),
					cell
				),
				_animDeleteCells.end()
			);
			continue;
		}
		cell->SetBallSize(--iter);
	}
	if(_animDeleteCells.size() != 0){
		return;
	}
	Timer2->Enabled = false;
	BurstBalls();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
	if(Label1->Caption.ToInt() == _score){
		Timer3->Enabled = false;
		return;
	}
	Label1->Caption = Label1->Caption.ToInt() + 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer4Timer(TObject *Sender)
{
	Cell* cur = _animWay[_animIndxBallWay++];
	DeleteBall(cur->GetI(), cur->GetJ());
	Cell* next = _animWay[_animIndxBallWay];
	SetBall(next->GetI(), next->GetJ(), _animNBallWay, true);
	if(_animIndxBallWay == _animWay.size() - 1){
		_animWay.clear();
		Timer4->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void TForm1::DeleteBall(int i, int j){
	_freeCells.push_back(_cells[i][j]);
	_animDeleteCells.push_back(_cells[i][j]);
	Timer2->Enabled = true;
	_animCfDeleteBall = ANIMITER;
}
//---------------------------------------------------------------------------
void TForm1::BurstBalls(){
	//TODO
	//Handle balls from _burst
}
//---------------------------------------------------------------------------
bool TForm1::GetWay(int strt_i, int strt_j, int fnsh_i, int fnsh_j){
	//TODO
}
