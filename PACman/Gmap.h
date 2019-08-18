#pragma once
#include<list>

#define MAPLENTH 19			//地图大小
#define P_ROW 10			//我方位置
#define P_ARRAY 9
#define E_ROW 8				//地方位置
#define E_ARRAY 9			

using std::list;

//抽象类 GMap
class GMap
{

protected:	
	static int LD;									//障碍物尺寸
	static int PD;									//豆子半径
	void InitOP();									//初始化
	bool mapData[MAPLENTH][MAPLENTH];				//障碍物逻辑地图点阵
	bool peaMapData[MAPLENTH][MAPLENTH];			//豆子逻辑地图点阵
	COLORREF color;									//地图墙颜色

public:
	GMap() {};
	virtual ~GMap();
	void DrawMap(HDC &hdc);
	void DrawPeas(HDC &hdc);
	friend class GObject;
	friend class PacMan;
};

//第一关地图
class Stage_1:public GMap
{
private:
	bool static initData[MAPLENTH][MAPLENTH];
public:
	Stage_1();
};

//第二关地图
class Stage_2 :public GMap
{
private:
	bool static initData[MAPLENTH][MAPLENTH];
public:
	Stage_2();
};

//第三关地图
class Stage_3 :public GMap
{
private:
	bool static initData[MAPLENTH][MAPLENTH];
public:
	Stage_3();
};