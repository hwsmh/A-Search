
// CreateMapDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CCreateMapDlg 对话框
class CCreateMapDlg : public CDialogEx
{
// 构造
public:
	CCreateMapDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATEMAP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_list;
	afx_msg void OnBnClickedButton2();
private:
	int m_nH;
	int m_nV;
	int boss_x;
	int boss_y;
	int self_x;
	int self_y;
	CString strMapName;
public:
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton3();
	//afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit8();
	CEdit m_edit;
};
