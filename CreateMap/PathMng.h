#pragma once
#include "singleton.h"
#include "LuaPlus.h"

struct PATHNODE
{
	PATHNODE(int x = 0,int y = 0)
	{
		nX = x;
		nY = y;
		nW = 0;
		nH = 0;
		dir = 0;
	}

	int nX;
	int nY;
	int nW;
	int nH;
	int dir;
};


class PathMng : public Pattern::Singleton<PathMng>
{
private:
public:
	int** m_pHomePath;
	int m_nHomeX;
	int m_nHomeY;
	int m_nBiLi;
	PATHNODE m_noffset;
	std::string m_strCurMapName;
	int** m_pMap;
	int m_nMapY;
	int m_nMapX;
	int m_nPointX;
	int m_nPointY;
public:
	PathMng(void);
public:
	~PathMng(void);
public:
	CString GetNextHomeDir(const char* szHomeName, int& dir, int& mini_boss_x, int& mini_boss_y, int& mini_self_x, int& mini_self_y);
	CString Test(int& mini_boss_x, int& mini_boss_y, int& mini_self_x, int& mini_self_y, const char* szHomeName);
	bool LuaDoFile(const char* name, LuaStateOwner& state);
};