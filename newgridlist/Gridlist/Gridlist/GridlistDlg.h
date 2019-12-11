
// GridlistDlg.h: 头文件
//

#pragma once
#include "afxcmn.h"

#include "..\CGridListCtrlEx\CGridListCtrlGroups.h"
#include "CListCtrl_DataModel.h"


// CGridlistDlg 对话框
class CGridlistDlg : public CDialogEx
{
// 构造
public:
	CGridlistDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRIDLIST_DIALOG };
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
private:
	CGridListCtrlGroups m_ListCtrl;
	CListCtrl_DataModel m_DataModel;
	CImageList m_ImageList;

	CGridlistDlg(const CGridlistDlg&);
	CGridlistDlg& operator=(const CGridlistDlg&);
public:
	afx_msg LRESULT onBnCLick(WPARAM wParam, LPARAM lParam);
};
