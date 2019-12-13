//---------------------------------------------------------------------------
/**!
	\file Cell
 	\defgroup \c Constants
 @{
*/
#ifndef CellH
#define CellH
#include <iostream>
/// Количество итераций в одной анимации (плавность анимации).
#define ANIMITER 20
//---------------------------------------------------------------------------
class Cell{
	int _i, _j; /// Координаты клетки в массиве.
    int _x, _y; /// Координаты клетки на поле.
	TImage* _image; /// Изображение клетки.
    TImage* _ballImage; /// Координаты шарика.
	bool _isActive; /// Активность клетки.
	int _crrntBall; /// Номер текущего шарика.
	int _sizeCf; /// Коэффициент размера шарика.
    TPicture* *_actPctrs; /// Массив изображений состояний клетки
	TPicture* *_ballPctrs; /// Массив изображений шариков
public:
	Cell(TImage*,int,int,int,int);
	void SetPicture(TPicture*);
	bool GetActive(){return _isActive;}
	void SetActive(bool a);
	void LoadActPctrs(TPicture* *pics);
	void LoadBallPctrs(TPicture* *balls);
    int GetBall(){return _crrntBall;}
	int GetI(){return _i;}
	int GetJ(){return _j;}
    void SetBall(int);
	void SetBallSize(int);
	int GetBallSize(){ return _sizeCf;};
};
#endif
/** @} */
