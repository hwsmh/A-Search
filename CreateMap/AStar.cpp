#include "StdAfx.h"
#include "AStar.h"
#include "BinaryHeap.h"

//{-1,-1} {0,-1} {1,-1}
//{-1,0} {0,0} {1,0}
//{-1,1}{0,1}{1,1}
					//"←" "↖"	  "↑"   "↗"  "↙"    "↓"   "↘"   "→"
int dir_8[8][2] = {{-1,0},{-1,-1},{0,-1},{1,-1},{-1,1},{0,1},{1,1},{1,0}} ;
ASTART_DIR_8 dir_state_8[8]={ASD_LEFT,ASD_LEFT_UP,ASD_UP,ASD_RIGHT_UP,ASD_LEFT_DOWN,ASD_DOWN,ASD_RIGHT_DOWN,ASD_RIGHT};

//char dir_ch[8][3] = { "←","↖","↑","↗","↙","↓","↘","→" } ;

int dir_4[4][2] = {{-1,0},{0,-1},{0,1},{1,0}} ;
//char dir_ch[8][3] = { "←","↑","↓",,"→" } 
ASTART_DIR_8 dir_state_4[4]={ASD_LEFT,ASD_UP,ASD_DOWN,ASD_RIGHT};

int cost[8] = { 10, 14, 10, 14, 14, 10, 14, 10 } ;
AStar::AStar(void)
{
}

AStar::~AStar(void)
{
}

bool AStar::IsValidPos ( int x, int y )
{
	if ( x < 0 || x >= m_cur_size.x )
		return false ;
	if ( y < 0 || y >= m_cur_size.y )
		return false ;
	return true ;
}

bool  AStar::AStar_GetShortestPath(int** pathmap,APoint size,APoint start,APoint end,ASTART_DIR_STATE dir,vector<MOVE_POINT>& path)
{
	if ( start.x < 0 || start.y < 0 || end.x < 0 || end.y < 0)
	{
		return false;
	}
	bool pFinf = false;
	CBinaryHeap OPEN ;
	MAP** map = new MAP*[size.x]; 
	for(int i=0;i<size.x;++i) 
	{
		map[i] = new MAP[size.y];
	}

	CString Str;
	CString StrBuf;

	for ( int i = 0; i < size.x; i++ )
	{
		for ( int j = 0; j < size.y; j++ )
		{
			map[i][j].type = pathmap[i][j];
			map[i][j].dir_parent = 9 ;
		}
	}
	OPEN.BHSetMap(map);
	//for ( int i = 0; i < size.x; i++ )
	//{
	//	for ( int j = 0; j < size.y;j++ )
	//	{
	//		StrBuf.Format("%d ",map[i][j].type);
	//		OutputDebugString(StrBuf);
	//	}
	//	OutputDebugString("\r\n");
	//}
	//OutputDebugString("\r\n");

	m_cur_size.x = size.x;
	m_cur_size.y = size.y;
	int lx = size.x, ly = size.y ;  //长宽
	int nStartX = start.x, nStartY = start.y ;    //起点
	int nEndX = end.x, nEndY = end.y ;  //终点
	OPEN.BHAddNew ( nStartX, nStartY, 3 ) ;

	map[nStartX][nStartY].status = 1 ;
	map[nStartX][nStartY].index = 0 ;
	while ( OPEN.BHGetNum() > 0 )
	{
		NODE TopNode = OPEN.BHGetTop () ;
		if ( TopNode.x == nEndX && TopNode.y == nEndY )
			break ;

		map[TopNode.x][TopNode.y].status = 2 ;
		OPEN.BHDelTop ();

		int count;
		int sub_num;
		if ( dir == ASD_4 )
		{
			count = 4;
			sub_num = 3;
		}
		else
		{
			count = 8;
			sub_num = 7;
		}
		for ( int i = 0; i < count; i++ )
		{

			int h = 0;
			int dirx,diry;
			if ( dir == ASD_4 )
			{
				h = 10;
				dirx = dir_4[i][0];
				diry = dir_4[i][1];
			}
			else
			{
				h = cost[i];
				dirx = dir_8[i][0];
				diry = dir_8[i][1];
			}

			//char dir_ch[8][3] = { "←","↑","↓",,"→" } 
			int a = TopNode.x + dirx ;
			int b = TopNode.y + diry ;
			if ( IsValidPos(a,b) == false || map[a][b].type >0 )
				continue ;

			// 计算当前消费g(n)
			//f(n) = g(n) + h(n)

			int cur_cost = map[TopNode.x][TopNode.y].g + h ;

			// 若该结点首次被访问
			if ( map[a][b].status == 0 )
			{
				map[a][b].status = 1 ;
				map[a][b].dir_parent = sub_num - i ;
				map[a][b].g = cur_cost ;
				map[a][b].h = ( nEndX - a ) + ( nEndY - b ) ;	// 只在首次访问时估价h(n)
				OPEN.BHAddNew ( a, b, map[a][b].g + map[a][b].h ) ;
			}
			else if ( cur_cost < map[a][b].g )
			{
				map[a][b].dir_parent = sub_num - i ;
				map[a][b].g = cur_cost ;
				if ( map[a][b].status == 1 )
				{
					OPEN.BHAdjustByIndex ( map[a][b].index, map[a][b].g + map[a][b].h );
				}
				else if ( map[a][b].status == 2 )
				{
					OPEN.BHAddNew ( a, b, map[a][b].g + map[a][b].h );
				}
				map[a][b].status = 1;
			}
		} // for
	} // while 

	int sx = nEndX, sy = nEndY, cur_dir = 0 ;
	while ( true ) 
	{
		MOVE_POINT move;
		cur_dir = map[sx][sy].dir_parent ;

		int dirx,diry;
		int sub_num;
		if ( dir == ASD_4 )
		{
			dirx = dir_4[cur_dir][0];
			diry = dir_4[cur_dir][1];
			sub_num = 3;
		}
		else
		{
			dirx = dir_8[cur_dir][0];
			diry = dir_8[cur_dir][1];
			sub_num = 7;
		}

		sx += dirx ;
		sy += diry ;

		if ( IsValidPos ( sx, sy ) == false )
		{
			break;
		}
		
		move.dir = sub_num-cur_dir;
		move.pos.x = sx;
		move.pos.y = sy;
		path.push_back(move);
		if ( sx == start.x && sy == start.y )
		{
			pFinf = true;
			break ;
		}
	}

	for(int i=0;i<size.x;++i) 
		delete[] map[i]; 
	delete[] map; 

	return pFinf ;
}
