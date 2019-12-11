// MButton.cpp : 实现文件
//

#include "stdafx.h"
//#include "NewListCtrl.h"
#include "MButton.h"


// CMButton

IMPLEMENT_DYNAMIC(CMButton, CButton)

CMButton::CMButton()
{
	m_inItem = 0;
	m_inSubItem = 0;
    ZeroMemory(m_rect, sizeof(CRect)) ;
	m_hParent = NULL;
	bEnable = FALSE;
}

CMButton::CMButton( int nItem, int nSubItem, CRect rect, HWND hParent )
{
	m_inItem = nItem;
	m_inSubItem = nSubItem;
	m_rect = rect;
	m_hParent = hParent;
	bEnable = TRUE;
}

CMButton::~CMButton()
{
}


BEGIN_MESSAGE_MAP(CMButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CMButton::OnBnClicked)
//ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CMButton 消息处理程序



void CMButton::OnBnClicked()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_BN_CLICK, m_inItem, m_inSubItem );   //-m_hParent
}

//BOOL CMButton::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	
//	return CButton::OnEraseBkgnd(pDC);
//}
