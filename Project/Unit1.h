//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "Cell.h"
#include <algorithm>
#define CELLSIZE 68
#define OFFSETX 12
#define OFFSETY 11
#define BALLSCOUNT 7
#define activeCellWay "resources/activeCell.bmp"
#define cellWay "resources/Cell.bmp"
#define ballWay "resources/Ball.bmp"
#define WAYTOHELP "help.txt"
#define WAYTOREF "ref.txt"
using namespace std;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *nextStep;
	TTimer *Timer1;
	TTimer *Timer2;
	TTimer *Timer3;
	TTimer *Timer4;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *ItemMenuSaveGame;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TOpenTextFileDialog *OpenTextFileDialog1;
	//TMenuItem *ItemMenuSaveGame;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Timer3Timer(TObject *Sender);
	void __fastcall Timer4Timer(TObject *Sender);
	void __fastcall nextStepClick(TObject *Sender);
	void __fastcall NewGame(TObject *Sender);
	void __fastcall LoadGameClick(TObject *Sender);
    void __fastcall ItemMenuSaveGameClick(TObject *Sender);
	void __fastcall ExitClick(TObject *Sender);
	void __fastcall ItemMenuHelpClick(TObject *Sender);
	void __fastcall ItemMenuRefClick(TObject *Sender);
private:	// User declarations
	Cell* _cells[9][9];
	Cell* _activeCell;
	vector<Cell*> _freeCells;
    TPicture* _actPctrs[2];
	TPicture* _ballPctrs[BALLSCOUNT];
    //--Animation--
	int _animCfSetBall;
	int _animCfDeleteBall;
    int _wayField[9][9];
	int _animIndxBallWay;
	int _animNBallWay;
	vector<Cell*> _animDeleteCells;
	vector<Cell*> _animSetCells;
	vector<Cell*> _animWay;
	vector<Cell*> _burst;
	Cell* _targetBall;
	//--Info--
	int _score;
    int _nextBalls[3];
    TImage* _nextBallsImgs[3];
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall PostClick(TObject*);
	bool GetWay(int,int,int,int);
	int ControlLines(int,int, int);
	int ControlLine(int, int, int, void(*f)(int&,int&,int));
	void GameOver();
	int Burst(int,int,int);
	void BurstBalls();
	void InitCells();
	void InitPictures();
	bool PutBalls();
	void SetBall(int, int, int, bool=false);
	void PutBall(int);
	void InitNextBallImgs();
	void SaveGame(string);
	void GenNextBalls();
	bool CheckFile(string);
	void ShowMessageByFile(string,string);
	void DeleteBall(int,int);
	void LoadGame(string);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
