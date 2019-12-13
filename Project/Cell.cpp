//---------------------------------------------------------------------------

#pragma hdrstop

#include "Cell.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*!
	\brief Конструктор клетки
	\param img Картинка фона клетки
	\param i i-ая координата клетки
	\param j j-ая координата клетки
	\param offx Отступ клетки по x
	\param offy Отступ клетки по y

	Инициализирует все поля клетки
*/
Cell::Cell(TImage* img, int i, int j, int offx, int offy)
{
	_i = i; _j = j;
	_crrntBall = -1;
	_isActive = false;
	this->_image = img;
	_x = img->Left + offx;
	_y = img->Top + offy;
	_ballImage = new TImage(img->Parent);
	_ballImage->Parent = img->Parent;
	_ballImage->Left = img->Left + offx;
	_ballImage->Top = img->Top + offy;
	_ballImage->Enabled = false;
	_ballImage->Transparent = true;
	_ballImage->Stretch = true;
	_ballImage->BringToFront();
}
/*!
	\brief Сеттер для картинки клетки
	\param pic Картинка
*/
void Cell::SetPicture(TPicture* pic)
{
	this->_image->Picture = pic;
}
/*!
	\brief Устанавливает массив анимаций шарика для клетки
	\param pics массив картинок
*/
void Cell::LoadActPctrs(TPicture* *pics)
{
	_actPctrs = pics;
}
/*!
	\brief Загружает изображения шариков
	\param  balls массив изображжений
*/
void Cell::LoadBallPctrs(TPicture* *balls)
{
	_ballPctrs = balls;
}
/*!
	\brief Устанавливает активность клетки
*/
void Cell::SetActive(bool a)
{
	_isActive = a;
	_image->Picture = _actPctrs[(int)_isActive];
}
/*!
	\brief Устанавливает шарик на клетке
	\param ball уникальный номер шарика
*/
void Cell::SetBall(int ball)
{
 _crrntBall = ball;
	if(_crrntBall < 0)
	{
		_ballImage->Picture = nullptr;
		return;
	}
	_ballImage->Picture = _ballPctrs[_crrntBall];
	int h = _ballImage->Height;
	int w = _ballImage->Width;
}
/*!
	\brief Устанавливает размер шарика на клетке
	\param k коэффициент размера
*/
void Cell::SetBallSize(int k){
   //k - коэффициент, характеризующий размер шарика
    _sizeCf = k;
	int add = (ANIMITER-k)*22.5/ANIMITER;
	int len = 45*k/ANIMITER;
	_ballImage->Height = len;
	_ballImage->Width = len;
	_ballImage->Left = _x + add;
	_ballImage->Top = _y + add;
}

