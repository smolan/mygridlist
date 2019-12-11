#pragma once


// CMButton


#define  WM_BN_CLICK  WM_USER + 100
#define  WM_Menu_CLICK  WM_USER + 101
#define  USE_TOPINDEX_BUTTON


class CMButton : public CButton
{
	DECLARE_DYNAMIC(CMButton)

public:
	CMButton();
	CMButton( int nItem, int nSubItem, CRect rect, HWND hParent );
	virtual ~CMButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
public:
	int m_inItem;
	int m_inSubItem;
	CRect m_rect;
	HWND m_hParent;
	BOOL bEnable;

//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


