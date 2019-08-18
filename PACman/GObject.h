#include"stdafx.h"
#include<time.h>
#include"Gmap.h"

#define PLAYERSPEED 6
#define ENERMYSPEED 4
#define LEGCOUNTS 5
#define DISTANCE 10
#define BLUE_ALERT 8
#define D_OFFSET 2
#define RD (DISTANCE + D_OFFSET)


enum TWARDS			//�ƶ�״̬
{
	UP,		//��
	DOWN,	//��
	LEFT,	//��
	RIGHT,	//��
	OVER,	//��Ϸ����
};

class GObject
{
public:
	//GObject();
	//~GObject();
public:
	GObject(int Row, int Array)
	{
		//֡��
		m_nFrame = 1;

		//��ǰ�ؿ�
		pStage = NULL;

		this->m_nRow = Row;
		this->m_nArray = Array;

		//����λ��
		this->m_ptCenter.x = m_nRow * pStage->LD + pStage->LD / 2;
		this->m_ptCenter.y = m_nArray * pStage->LD + pStage->LD / 2;

		this->m_nX = m_ptCenter.x;
		this->m_nY = m_ptCenter.y;
	}

	//����λ��
	void SetPosition(int Row, int Array);

	//���հ�
	void DrawBlank(HDC &hdc);
	void virtual Draw(HDC &hdc) = 0;	//���ƶ���
	void virtual action() = 0;			//���ݱ���ı���

	int GetRow();
	int GetArray();

	static GMap *pStage;//ָ���ͼ���ָ�룬����Ϊ��̬��ʹ���������������ͬ�ĵ�ͼ




protected:
	int m_nX;
	int m_nY;

	//ָ���
	TWARDS m_cmd;

	//��������
	POINT m_ptCenter;

	//�߼��ᣬ������
	int m_nRow;
	int m_nArray;
	//�ٶ�
	int m_nSpeed;

	//����
	TWARDS m_dir;

	//֡��
	int m_nFrame;

	//�ж������Ƿ񵽴��߼�����λ��
	bool Achive();
	//�߼���ײ��⣬���������ں���λ��
	bool Collision();

	//��ʵ������ת��Ϊ�߼�����
	int PtTransform(int k);

	//�����߼��� ��������
	virtual void AchiveCtrl();

};

//��Ҷ���
class PacMan :public GObject
{
protected:
	virtual void AchiveCtrl();

public:
	POINT GetPos();
	bool IsOver();	//�ж���Ϸ�Ƿ����
	bool IsWin();	//�Ƿ�Ӯ����Ϸ
	void Draw(HDC& hdc);
	void SetTwCommand(TWARDS command);
	PacMan(int x, int y) :GObject(x, y)
	{
		this->m_nSpeed = PLAYERSPEED;
		m_cmd = m_dir = LEFT;
	}
	void action();
	void SetOver();
};

class Enermy :public GObject
{
protected:
	void Catch();
	void virtual MakeDecision(bool b) = 0;
	COLORREF color;

public:
	static std::shared_ptr<PacMan> player;
	void virtual Draw(HDC &hdc);
	Enermy(int x, int y) :GObject(x, y)
	{
		this->m_nSpeed = ENERMYSPEED;
		m_dir = LEFT;
		m_cmd = UP;
	}
	void virtual action();
};

//���ֵ���
class RedOne : public Enermy
{
protected:
	void virtual MakeDecision(bool b);
public:
	void Draw(HDC &hdc);
	RedOne(int x, int y) : Enermy(x, y)
	{
		color = RGB(255, 0, 0);
	}
};

class BlueOne : public RedOne
{
protected:
	void virtual MakeDecision(bool b);
public:
	void Draw(HDC &hdc);
	BlueOne(int x, int y) : RedOne(x, y)
	{
		color = RGB(0, 0, 255);
	}
};

class YellowOne : public RedOne
{
protected:
	void virtual MakeDecision(bool b);
public:
	void Draw(HDC &hdc);
	YellowOne(int x, int y) : RedOne(x, y)
	{
		color = RGB(200, 200,200);
	}
};

