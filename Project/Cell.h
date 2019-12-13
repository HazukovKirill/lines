//---------------------------------------------------------------------------
/**!
	\file Cell
 	\defgroup \c Constants
 @{
*/
#ifndef CellH
#define CellH
#include <iostream>
/// ���������� �������� � ����� �������� (��������� ��������).
#define ANIMITER 20
//---------------------------------------------------------------------------
class Cell{
	int _i, _j; /// ���������� ������ � �������.
    int _x, _y; /// ���������� ������ �� ����.
	TImage* _image; /// ����������� ������.
    TImage* _ballImage; /// ���������� ������.
	bool _isActive; /// ���������� ������.
	int _crrntBall; /// ����� �������� ������.
	int _sizeCf; /// ����������� ������� ������.
    TPicture* *_actPctrs; /// ������ ����������� ��������� ������
	TPicture* *_ballPctrs; /// ������ ����������� �������
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
