// OutPutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CreateMap.h"
#include "OutPutDlg.h"
#include "afxdialogex.h"


// COutPutDlg �Ի���

IMPLEMENT_DYNAMIC(COutPutDlg, CDialogEx)

COutPutDlg::COutPutDlg(CListCtrl* list, int W, int H, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	,plist(list)
{
	m_nH = H;
	m_nV = W;
}

COutPutDlg::~COutPutDlg()
{
}

void COutPutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COutPutDlg, CDialogEx)
END_MESSAGE_MAP()


// COutPutDlg ��Ϣ�������


BOOL COutPutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString str;
	CString buf;
	str.Format("int map[%d][%d]={\r\n",m_nH * 2 + 1,m_nV * 2 + 1);

	if (plist != NULL)
	{
		int count = plist->GetItemCount();
		for (int i = 0; i<count ;i++)
		{
			str += " {";
			for (int j = 0;j <m_nV * 2 + 1;j++)
			{
				buf = plist->GetItemText(i, j);
				if (buf == "?")
				{
					str += "0";
				} 
				else
				{
					str += buf;
				}
				str += ",";
			}
			str += "},\r\n";
		}
	}

	str += "};";
	SetDlgItemText(IDC_EDIT1, str);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
