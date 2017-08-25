#pragma once


// COutPutDlg 对话框

class COutPutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COutPutDlg)

public:
	COutPutDlg(CListCtrl* list,int W,int H,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COutPutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	int m_nH;
	int m_nV;
	CListCtrl* plist;
public:
	virtual BOOL OnInitDialog();
};
