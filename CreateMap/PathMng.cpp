#include "StdAfx.h"
#include "PathMng.h"
#include "AStar.h"
#include <vector>

PathMng::PathMng()
{
}


PathMng::~PathMng()
{
}

void __cdecl DbgPrint(char* lpszFormat,...)
{
	va_list args;
	int nBuf;
	CHAR szBuffer[sizeof(CHAR) * 2048] = {0};

	va_start(args,lpszFormat);
	nBuf = vsprintf(szBuffer,lpszFormat,args);
	va_end(args);

	OutputDebugStringA(szBuffer);
}



bool GetPath(OUT char* path)
{
	TCHAR sFilename[_MAX_PATH];
	TCHAR sDrive[_MAX_DRIVE];
	TCHAR sDir[_MAX_DIR];
	TCHAR sFname[_MAX_FNAME];
	TCHAR sExt[_MAX_EXT];
	GetModuleFileName(NULL,sFilename,_MAX_PATH);
	_splitpath_s(sFilename, sDrive, sDir, sFname, sExt);
	sprintf_s(path,_MAX_PATH,"%s%s\\data",sDrive,sDir);
	return true;
}


bool PathMng::LuaDoFile(const char* name,LuaStateOwner& state)
{
	TCHAR sFilename[_MAX_PATH];
	GetPath(sFilename);
	char path[MAX_PATH] = {'\0'};
	sprintf_s(path,"%s\\Script\\%s.lua",sFilename,name);
	if (state->DoFile(path) != 0)
	{
		DbgPrint("Debug:%s 读取失败",path);
		return false;
	}
	return true;
}


CString PathMng::GetNextHomeDir(const char* szHomeName, int& dir, int& mini_boss_x, int& mini_boss_y, int& mini_self_x, int& mini_self_y)
{
	string strName = szHomeName;
	m_nPointX = mini_boss_x;
	m_nPointY = mini_boss_y;
	LuaStateOwner state;
	if (!LuaDoFile("地图",state))
	{
		return false;
	}

	LuaObject pObject = state->GetGlobal(strName.c_str());

	if (pObject.IsNil())
	{
		DbgPrint("Debug:没有找到 %s 信息 \r\n", strName.c_str());
		return false;
	}

	LuaObject pMap = pObject["地图"];
	if (pMap.IsNil())
	{
		return false;
	}
	int x, y;
	y = pMap.GetCount();
	x = pMap[1].GetCount();

	int** map = new int*[x];

	for (int i = 0;i < x;++i)
	{
		map[i] = new int[y];
		for (int j = 0;j < y;j++)
		{
			map[i][j] = pMap[j + 1][i + 1].ToInteger() == 1 ? 0 : 1;
		}
	}

	AStar star;
	vector<MOVE_POINT> path;
	int start_x = mini_self_x * 2 + 1;
	int start_y = mini_self_y * 2 + 1;
	int boss_x  = mini_boss_x * 2 + 1;
	int boss_y  = mini_boss_y * 2 + 1;
	bool b = star.AStar_GetShortestPath((int**)map,
		APoint(x, y),
		APoint(start_x, start_y),
		APoint(boss_x,boss_y),ASD_4,path);

	


	if (path.size() > 0)
	{
		dir = path[(path.size() - 1)/2].dir;
	}
	int next_home_x, next_home_y;
	DbgPrint("Debug:%d\r\n", dir);
	switch (dir)
	{
	case 0:
		next_home_x = mini_self_x - 1;
		next_home_y = mini_self_y;
		break;
	case 1:
		next_home_x = mini_self_x;
		next_home_y = mini_self_y - 1;
		break;
	case 2:
		next_home_x = mini_self_x;
		next_home_y = mini_self_y + 1;
		break;
	case 3:
		next_home_x = mini_self_x + 1;
		next_home_y = mini_self_y;
		break;
	default:
		next_home_x = mini_self_x;
		next_home_y = mini_self_y;
		break;
	}

	
	DbgPrint("Debug:下一个房间的X: %d Y: %d \r\n", next_home_x, next_home_y);

	for (int i = 0; i < x;i++)
	{
		delete[] map[i];
	}

	delete[] map;

	CString   s;
	s.Format("下一个房间的X: %d Y: %d \r\n", next_home_x, next_home_y);
	
// 	if (b)
// 	{
// 		if (mini_self_x == m_nPointX && mini_self_y == m_nPointY)
// 		{
// 			DbgPrint("到达 %d:%d\r\n", mini_self_x, mini_self_y);
// 		}
// 	}
// 	else
// 	{
// 
// 		DbgPrint("Debug: %d %d \r\n", mini_self_x, mini_self_y);
// 	}
	return s;
}



CString PathMng::Test(int& mini_boss_x,int& mini_boss_y,int& mini_self_x,int& mini_self_y,const char* szHomeName)
{
	int dir = -1;
	CString   s;
	s = PathMng::Ptr()->GetNextHomeDir(szHomeName,dir, mini_boss_x, mini_boss_y, mini_self_x,mini_self_y);
// 	switch (dir)
// 	{
// 	case 0:
// 		DbgPrint("Debug:←\n");
// 		break;
// 	case 1:
// 		DbgPrint("Debug:↑\n");
// 		break;
// 	case 2:
// 		DbgPrint("Debug:↓\n");
// 		break;
// 	case 3:
// 		DbgPrint("Debug:→\n");
// 		break;
// 	default:
// 		break;
// 	}
	return s;
}