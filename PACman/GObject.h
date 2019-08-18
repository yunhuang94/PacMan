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


enum TWARDS			//移动状态
{
	UP,		//上
	DOWN,	//下
	LEFT,	//左
	RIGHT,	//右
	OVER,	//游戏结束
};

class GObject
{
public:
	//GObject();
	//~GObject();
public:
	GObject(int Row, int Array)
	{
		//帧数
		m_nFrame = 1;

		//当前关卡
		pStage = NULL;

		this->m_nRow = Row;
		this->m_nArray = Array;

		//中心位置
		this->m_ptCenter.x = m_nRow * pStage->LD + pStage->LD / 2;
		this->m_ptCenter.y = m_nArray * pStage->LD + pStage->LD / 2;

		this->m_nX = m_ptCenter.x;
		this->m_nY = m_ptCenter.y;
	}

	//设置位置
	void SetPosition(int Row, int Array);

	//画空白
	void DrawBlank(HDC &hdc);
	void virtual Draw(HDC &hdc) = 0;	//绘制对象
	void virtual action() = 0;			//数据变更的表现

	int GetRow();
	int GetArray();

	static GMap *pStage;//指向地图类的指针，设置为静态，使所有类对象都是用相同的地图




protected:
	int m_nX;
	int m_nY;

	//指令缓存
	TWARDS m_cmd;

	//中心坐标
	POINT m_ptCenter;

	//逻辑横，纵坐标
	int m_nRow;
	int m_nArray;
	//速度
	int m_nSpeed;

	//朝向
	TWARDS m_dir;

	//帧数
	int m_nFrame;

	//判断物体是否到达逻辑坐标位置
	bool Achive();
	//逻辑碰撞检测，将物体置于合理位置
	bool Collision();

	//将实际坐标转换为逻辑坐标
	int PtTransform(int k);

	//到达逻辑点 更新数据
	virtual void AchiveCtrl();

};

//玩家对象
class PacMan :public GObject
{
protected:
	virtual void AchiveCtrl();

public:
	POINT GetPos();
	bool IsOver();	//判断游戏是否结束
	bool IsWin();	//是否赢得游戏
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

//三种敌人
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

