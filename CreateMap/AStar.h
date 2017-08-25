#pragma once
#include "BinaryHeap.h"
#include <vector>
using namespace std;
struct APoint 
{
	APoint()
	{
		x = 0;
		y = 0;
	}
	APoint(int x,int y)
	{
		this->x = x;
		this->y = y;
	}
	int x;
	int y;
};
enum ASTART_DIR_STATE
{
	ASD_4,
	ASD_8,
};

enum ASTART_DIR_8
{
	ASD_UP,
	ASD_DOWN,
	ASD_LEFT,
	ASD_RIGHT,
	ASD_LEFT_UP,
	ASD_RIGHT_UP,
	ASD_LEFT_DOWN,
	ASD_RIGHT_DOWN,
};

struct MOVE_POINT
{
	APoint pos;
	int dir;
};
class AStar
{
public:
	AStar(void);
public:
	~AStar(void);
public:
	bool  AStar_GetShortestPath(int** pathmap,APoint size,APoint start,APoint end,ASTART_DIR_STATE dir,vector<MOVE_POINT>& path);

	bool IsValidPos ( int x, int y );

	APoint m_cur_size;

public:
};
