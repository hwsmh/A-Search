
// CreateMapDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCreateMapDlg �Ի���



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


// CCreateMapDlg ��Ϣ�������

BOOL CCreateMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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
	SetDlgItemText(IDC_EDIT3, "����");


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCreateMapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCreateMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCreateMapDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCreateMapDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	COutPutDlg outputdlg(&m_list,m_nV,m_nH);
	outputdlg.DoModal();
}


void CCreateMapDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	

	CString str = PathMng::Ptr()->Test(boss_x, boss_y, self_x, self_y, "����");

	m_edit.SetWindowTextA(str);
	m_edit.UpdateData(FALSE);
}







void CCreateMapDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	boss_x = GetDlgItemInt(IDC_EDIT5);
	boss_y = GetDlgItemInt(IDC_EDIT7);
	self_x = GetDlgItemInt(IDC_EDIT4);
	self_y = GetDlgItemInt(IDC_EDIT6);


	GetDlgItemText(IDC_EDIT3, strMapName);



}


void CCreateMapDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}


void CCreateMapDlg::OnEnChangeEdit5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCreateMapDlg::OnEnChangeEdit7()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCreateMapDlg::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCreateMapDlg::OnEnChangeEdit8()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������


}
