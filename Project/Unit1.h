//---------------------------------------------------------------------------
/**!
	\file Unit1
 	\defgroup \c Constants

 @{
*/
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
/// Размер длины и ширины клетки
#define CELLSIZE 68
/// Отступ между клетками по x
#define OFFSETX 12
/// Отступ между клетками по y
#define OFFSETY 11
/// Количество уникальных цветов щариков
#define BALLSCOUNT 7
/// Путь до изображения с активной клеткой
#define activeCellWay "resources/activeCell.bmp"
/// Путь до изображения с неактивной клеткой
#define cellWay "resources/Cell.bmp"
/// Путь до файла с изображением шарика
#define ballWay "resources/Ball.bmp"
/// Путь до файла с информацией о игре.
#define WAYTOHELP "help.txt"
/// Путь до информации о разработчике
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
	Cell* _cells[9][9]; /**< Массив клеток */
	Cell* _activeCell; /// Указатель на активную клетку.
	vector<Cell*> _freeCells; /// Массив свободных клеток.
    TPicture* _actPctrs[2]; /// Массив изображений состояний клетки.
	TPicture* _ballPctrs[BALLSCOUNT]; /// Массив уникальных изображений шариков.
    //--Animation--
	int _animCfSetBall; /// Текущий коэффициент анимации появления шариков.
	int _animCfDeleteBall; /// Текущий коэффициент анимации удаления шариков.
    int _wayField[9][9]; /// Массив для хранения пути между клетками.
	int _animIndxBallWay; /// Индекс анимации перемещения шарика.
	int _animNBallWay; /// Цвет шарика анимации перемещения.
	vector<Cell*> _animDeleteCells; /// Вектор клеток для анимации удаления шариков.
	vector<Cell*> _animSetCells; /// Вектор клеток для анимации появления шариков.
	vector<Cell*> _animWay; /// Вектор клеток составляющих путь шарика.
	vector<Cell*> _burst; /// Вектор клеток для обработки лопанья.
	Cell* _targetBall; /// Выбранная клетка.
	//--Info--
	int _score; /// Очки пользователя.
    int _nextBalls[3]; /// Массив трех шариков.
    TImage* _nextBallsImgs[3]; /// Массив изображений трех шариков.
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
/** @} */
