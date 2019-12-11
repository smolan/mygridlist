// MButton.cpp : ʵ���ļ�
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



// CMButton ��Ϣ�������



void CMButton::OnBnClicked()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_BN_CLICK, m_inItem, m_inSubItem );   //-m_hParent
}

//BOOL CMButton::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	
//	return CButton::OnEraseBkgnd(pDC);
//}
