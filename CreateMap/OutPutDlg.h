#pragma once


// COutPutDlg �Ի���

class COutPutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COutPutDlg)

public:
	COutPutDlg(CListCtrl* list,int W,int H,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COutPutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	int m_nH;
	int m_nV;
	CListCtrl* plist;
public:
	virtual BOOL OnInitDialog();
};
