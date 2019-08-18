#pragma once
#include<list>

#define MAPLENTH 19			//��ͼ��С
#define P_ROW 10			//�ҷ�λ��
#define P_ARRAY 9
#define E_ROW 8				//�ط�λ��
#define E_ARRAY 9			

using std::list;

//������ GMap
class GMap
{

protected:	
	static int LD;									//�ϰ���ߴ�
	static int PD;									//���Ӱ뾶
	void InitOP();									//��ʼ��
	bool mapData[MAPLENTH][MAPLENTH];				//�ϰ����߼���ͼ����
	bool peaMapData[MAPLENTH][MAPLENTH];			//�����߼���ͼ����
	COLORREF color;									//��ͼǽ��ɫ

public:
	GMap() {};
	virtual ~GMap();
	void DrawMap(HDC &hdc);
	void DrawPeas(HDC &hdc);
	friend class GObject;
	friend class PacMan;
};

//��һ�ص�ͼ
class Stage_1:public GMap
{
private:
	bool static initData[MAPLENTH][MAPLENTH];
public:
	Stage_1();
};

//�ڶ��ص�ͼ
class Stage_2 :public GMap
{
private:
	bool static initData[MAPLENTH][MAPLENTH];
public:
	Stage_2();
};

//�����ص�ͼ
class Stage_3 :public GMap
{
private:
	bool static initData[MAPLENTH][MAPLENTH];
public:
	Stage_3();
};