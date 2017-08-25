
// CreateMapDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CreateMap.h"
#include "CreateMapDlg.h"
#include "afxdialogex.h"
#include "OutPutDlg.h"
#include "PathMng.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCreateMapDlg 对话框



CCreateMapDlg::CCreateMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATEMAP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_EDIT8, m_edit);
}

BEGIN_MESSAGE_MAP(CCreateMapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCreateMapDlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CCreateMapDlg::OnLvnItemchangedList2)
	ON_BN_CLICKED(IDC_BUTTON2, &CCreateMapDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CCreateMapDlg::OnNMDblclkList)
	ON_BN_CLICKED(IDC_BUTTON3, &CCreateMapDlg::OnBnClickedButton3)
	//ON_EN_CHANGE(IDC_EDIT3, &CCreateMapDlg::OnEnChangeEdit3)
	//ON_EN_CHANGE(IDC_EDIT1, &CCreateMapDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON5, &CCreateMapDlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT4, &CCreateMapDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CCreateMapDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT7, &CCreateMapDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT6, &CCreateMapDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT8, &CCreateMapDlg::OnEnChangeEdit8)
END_MESSAGE_MAP()


// CCreateMapDlg 消息处理程序

BOOL CCreateMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | TVS_SHOWSELALWAYS);
	CString str;
	for (int i = 0;i <15;i++)
	{
		str.Format(_T("%d"),i);
		m_list.InsertColumn(i * 2 + 0, _T(""),LVCFMT_LEFT,26);
		m_list.InsertColumn(i*2+1,str.GetBuffer(),LVCFMT_LEFT,26);

	}
	int count = m_list.GetItemCount();
	m_list.RedrawItems(0, count);


	SetDlgItemText(IDC_EDIT5, "2");
	SetDlgItemText(IDC_EDIT7, "0");
	SetDlgItemText(IDC_EDIT4, "1");
	SetDlgItemText(IDC_EDIT6, "2");
	SetDlgItemText(IDC_EDIT3, "洛兰");


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCreateMapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCreateMapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCreateMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCreateMapDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nH = GetDlgItemInt(IDC_EDIT1);
	m_nV = GetDlgItemInt(IDC_EDIT2);
	m_list.DeleteAllItems();


	for (int i = 0;i <m_nH * 2 + 1; i++)
	{
		m_list.InsertItem(i, "");
		for (int j = 0;j <m_nV * 2+ 1;j++)
		{
			if (j % 2 == 0)
			{
				m_list.SetItemText(i,j,"0");
			} 
			else
			{
				if ( i % 2 == 0)
				{
					m_list.SetItemText(i, j, "0");
				} 
				else
				{
					m_list.SetItemText(i,j , "?");
				}
			}
		}
	}
	

}


void CCreateMapDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCreateMapDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	COutPutDlg outputdlg(&m_list,m_nV,m_nH);
	outputdlg.DoModal();
}


void CCreateMapDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int nCount = m_list.GetItemCount();
	LVHITTESTINFO ht;
	ht.pt = pNMItemActivate->ptAction;
	m_list.SubItemHitTest(&ht);

	CString str = m_list.GetItemText(ht.iItem, ht.iSubItem);
	if (str == "0" || str == "?")
	{
		m_list.SetItemText(ht.iItem, ht.iSubItem, _T("1"));
	} 
	else
	{
		if (ht.iSubItem % 2 == 0)
		{
			m_list.SetItemText(ht.iItem, ht.iSubItem, _T("0"));
		} 
		else
		{
			if (ht.iItem % 2 == 0)
			{
				m_list.SetItemText(ht.iItem, ht.iSubItem, "0");
			} 
			else
			{
				m_list.SetItemText(ht.iItem, ht.iSubItem, "?");
			}
		}
	}
}


void CCreateMapDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	

	CString str = PathMng::Ptr()->Test(boss_x, boss_y, self_x, self_y, "洛兰");

	m_edit.SetWindowTextA(str);
	m_edit.UpdateData(FALSE);
}







void CCreateMapDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	boss_x = GetDlgItemInt(IDC_EDIT5);
	boss_y = GetDlgItemInt(IDC_EDIT7);
	self_x = GetDlgItemInt(IDC_EDIT4);
	self_y = GetDlgItemInt(IDC_EDIT6);


	GetDlgItemText(IDC_EDIT3, strMapName);



}


void CCreateMapDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}


void CCreateMapDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CCreateMapDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CCreateMapDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CCreateMapDlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码


}
