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
int TForm1::Burst(int i, int j, int nball){
	return ControlLines(i,j,nball);
}
//---------------------------------------------------------------------------
int TForm1::ControlLines(int i, int j, int nball){
//Возвращает количество лупнутых шаров
	int cnt = 0;
	cnt += ControlLine(i, j, nball, [](int& i, int& j, int k){
		i += k;
	});
	cnt += ControlLine(i, j, nball, [](int& i, int& j, int k){
		i += k;
		j += k;
	});
	cnt += ControlLine(i, j, nball, [](int& i, int& j, int k){
		j += k;
	});
	cnt += ControlLine(i, j, nball, [](int& i, int& j, int k){
		i += k;
		j -= k;
	});
	if(cnt == 0){
        return 0;
	}
	DeleteBall(i, j);
    return cnt + 1;
}
//---------------------------------------------------------------------------
int TForm1::ControlLine(int i, int j, int nball, void(*iter)(int&,int&,int)){
//Проходится по шарикам в линии, используя итерационную функцию
//Если длина линии > 5 удаляет все шарики на этой линии, кроме начального
//Возвращает количество лопнутых шариков, не включая начальный
	int strt_i = i, strt_j = j;
	int cnt = 0;
	iter(i,j,1);
    if(i >=0 && i <=8 && j >=0 && j <=8)
	while(_cells[i][j]->GetBall() == nball){
		cnt++;
		iter(i,j,1);
		if(i < 0 || i >8 || j < 0 || j >8){
			break;
		}
	}
	i = strt_i; j = strt_j;
	iter(i,j,-1);
    if(i >=0 && i <=8 && j >=0 && j <=8)
	while(_cells[i][j]->GetBall() == nball){
		cnt++;
        iter(i,j,-1);
        if(i < 0 || i >8 || j < 0 || j >8){
			break;
		}
	}
	//cnt - количество нужных шариков на линнии, не включая начальный
	if(cnt < 4){
		return 0;
	}
	//Теперь нужно удалить все шары
	iter(i,j,1);//шаг вперед, т.к. необходимо начать с нужной клетки
	while(_cells[i][j]->GetBall() == nball){
		if( (i != strt_i || j != strt_j) &&
			find(_burst.begin(), _burst.end(), _cells[i][j]) == _burst.end() )
		{
			DeleteBall(i, j);
		}
		iter(i,j,1);
		if(i < 0 || i >8 || j < 0 || j >8){
			break;
		}
	}
    return cnt;
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
void TForm1::GameOver(){
	nextStep->Enabled = false;
	ItemMenuSaveGame->Enabled = false;
	stringstream ss;
	ss << "Игра окончена.\nВаш счет: " <<_score ;
	UnicodeString s = ss.str().c_str();
	Application->MessageBox(
		s.c_str(),
		L"Игра окончена",
		MB_OK
	);
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
	ItemMenuSaveGame->Enabled = true;
}
//---------------------------------------------------------------------------
void TForm1::SaveGame(string filename){
	ofstream fout;
	fout.open(filename, ios_base::out);
	int key = 223;

	for(int i = 0; i < 9; i++)
	for(int j = 0; j < 9; j++)
	{
		fout<< (_cells[i][j]->GetBall()^key) << " ";
	}
	fout<<_score;
	fout.close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ItemMenuSaveGameClick(TObject *Sender)
{
	//Спросить не хочет ли он сохранить текущую игру
	//или чтото в этом роде
	UnicodeString  saveNameString = "";
	bool Answer = InputQuery (
		"Сохранение игры" ,
		"Пожалуйста, введите название сохранения:" ,
		saveNameString
	);
	if(!Answer){
        return;
	}
	if(saveNameString == ""){
		Application->MessageBox(
			L"Пожалуйста, заполните поле.",
			L"Ошибка",
			MB_OK
		);
		ItemMenuSaveGameClick(Sender);
		return;
	}
	string filename = AnsiString(saveNameString).c_str();
	filename = "user\\" + filename + ".lns";

	if(CheckFile(filename)){
		int Answer = Application->MessageBox(
			L"Сохранение с таким названием уже существует, хотите перезаписать?",
			L"Предупреждение",
			MB_OKCANCEL
		);
		if(Answer != IDOK)
            return;
	}
	SaveGame(filename);
	Application->MessageBox(
		L"Игра успешно сохранена.",
		L"Сообщение",
		MB_OK
	);
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
bool TForm1::CheckFile(string filename){
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
void TForm1::BurstBalls(){
	if(Timer1->Enabled || Timer2->Enabled || Timer4->Enabled){
		return;
	}
	if(_freeCells.size() == 0){
		GameOver();
        return;
	}
	int cnt = 0;
	for(auto o:_burst){
		cnt += ControlLines(o->GetI(), o->GetJ(), o->GetBall());
	}

	Timer3->Enabled = true;
	_score += 2*cnt;
	_burst.clear();

    cnt = 0;
	if(_targetBall == nullptr){
        return;
	}
	cnt += 2*ControlLines(
		_targetBall->GetI(),
		_targetBall->GetJ(),
		_targetBall->GetBall()
	);
    _targetBall = nullptr;
	if(cnt != 0){
        _score += cnt;
		return;
	}
	PutBalls();
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
bool TForm1::GetWay(int strt_i, int strt_j, int fnsh_i, int fnsh_j){
	for (int i = 0; i < 9; i++)
	for (int j = 0; j < 9; j++)
		_wayField[i][j] = -1;

	_wayField[strt_i][strt_j] = 0;

	int f1 = 0, f2 = 1;
	vector<Cell*> v[2];
	v[f1].push_back(_cells[strt_i][strt_j]);

	auto iter = [this, &v, &f2](int i, int j, int k){
		if(_wayField[i][j] == -1 && _cells[i][j]->GetBall() < 0) {
			_wayField[i][j] = k + 1;
			v[f2].push_back(_cells[i][j]);
		}
	};

	bool flag = false;
	int k;
	while(v[f1].size() != 0){
	   for(auto p: v[f1]){
		  if(p->GetI() == fnsh_i && p->GetJ() == fnsh_j){
			flag = true;
			break;
		  }

		  k = _wayField[p->GetI()][p->GetJ()];
		  if(p->GetJ() - 1 > -1)
			 iter(p->GetI(), p->GetJ() - 1, k);

		  if(p->GetJ() + 1 < 9)
			 iter(p->GetI(), p->GetJ() + 1, k);

		  if(p->GetI() - 1 > -1)
			 iter(p->GetI() - 1, p->GetJ(), k);

		  if(p->GetI() + 1 < 9)
			 iter(p->GetI() + 1, p->GetJ(), k);

	   }
	   v[f1].clear();
	   f2 = f1;
	   f1 = 1 - f1;
	}

	if(_wayField[fnsh_i][fnsh_j] == -1){
		return false;
	}

	Cell* cur = _cells[fnsh_i][fnsh_j];
	k = _wayField[fnsh_i][fnsh_j];
	_animWay.clear();

	int i, j;
	while(k != 0){
		k--;
		i = cur->GetI();
		j = cur->GetJ();
		_animWay.insert(_animWay.begin(), cur);
		if(j - 1 > -1)
		if(_wayField[i][j - 1] == k){
			cur = _cells[i][j - 1];
			continue;
		}
		if(j + 1 < 9)
		if(_wayField[i][j + 1] == k){
			cur = _cells[i][j + 1];
			continue;
		}
		if(i - 1 > -1)
		if(_wayField[i - 1][j] == k){
			cur = _cells[i - 1][j];
			continue;
		}
		if(i + 1 > -1)
		if(_wayField[i + 1][j] == k){
			cur = _cells[i + 1][j];
			continue;
		}
	}
	_animWay.insert(_animWay.begin(), cur);

	return true;
}
//---------------------------------------------------------------------------
void TForm1::LoadGame(string filename){
	ifstream in;
	in.open(filename);
	int key = 223;
    _freeCells.clear();
	for(int i = 0; i < 9; i++)
	for(int j = 0; j < 9; j++)
	{
		int nball;
		in>> nball;
        nball = nball^key;
		if( nball == -1 ){
			_cells[i][j]->SetBall(-1);
			_freeCells.push_back(_cells[i][j]);
		}else{
			SetBall(i, j, nball);
        }
	}
	in >> _score;
	in.close();

    ItemMenuSaveGame->Enabled = true;
	nextStep->Enabled = true;
	_targetBall = nullptr;
	_burst.clear();
	Label1->Caption = _score;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadGameClick(TObject *Sender)
{
	OpenTextFileDialog1->InitialDir = "user\\\\";
	if(OpenTextFileDialog1->Execute()){
		if (FileExists(OpenTextFileDialog1->FileName))
			LoadGame(AnsiString(OpenTextFileDialog1->FileName).c_str());
	}
}
