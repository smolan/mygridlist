
// GridlistDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Gridlist.h"
#include "GridlistDlg.h"
#include "afxdialogex.h"


#include "..\CGridListCtrlEx\CGridColumnTraitDateTime.h"
#include "..\CGridListCtrlEx\CGridColumnTraitEdit.h"
#include "..\CGridListCtrlEx\CGridColumnTraitCombo.h"
#include "..\CGridListCtrlEx\CGridColumnTraitHyperLink.h"
#include "..\CGridListCtrlEx\CGridRowTraitXP.h"
#include "..\CGridListCtrlEx\ViewConfigSection.h"

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


// CGridlistDlg 对话框



CGridlistDlg::CGridlistDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRIDLIST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGridlistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CGridlistDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_BN_CLICK, onBnCLick)
END_MESSAGE_MAP()


// CGridlistDlg 消息处理程序

BOOL CGridlistDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
		// Create and attach image list
	m_ImageList.Create(16, 16, ILC_COLOR16 | ILC_MASK, 1, 0);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	int nStateImageIdx = CGridColumnTraitDateTime::AppendStateImages(m_ListCtrl, m_ImageList);	// Add checkboxes

	m_ListCtrl.SetImageList(&m_ImageList, LVSIL_SMALL);

	// Give better margin to editors
	m_ListCtrl.SetCellMargin(2);
	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
	m_ListCtrl.SetDefaultRowTrait(pRowTrait);
	m_ListCtrl.EnableVisualStyles(true);

	// Create Columns
	m_ListCtrl.InsertHiddenLabelColumn();	// Requires one never uses column 0

	for (int col = 0; col < m_DataModel.GetColCount(); ++col)
	{
		const CString& title = m_DataModel.GetColTitle(col);
		CGridColumnTrait* pTrait = NULL;
		if (col == 0)	// Country
		{
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
			const vector<CString>& countries = m_DataModel.GetCountries();
			for (size_t i = 0; i < countries.size(); ++i)
				pComboTrait->AddItem((DWORD_PTR)i, countries[i]);
			pTrait = pComboTrait;
		}
		if (col == 1)	// City
		{
			pTrait = new CGridColumnTraitEdit;
		}
		if (col == 2)	// Year won
		{
			CGridColumnTraitDateTime* pDateTimeTrait = new CGridColumnTraitDateTime;
			pDateTimeTrait->AddImageIndex(nStateImageIdx, _T(""), false);		// Unchecked (and not editable)
			pDateTimeTrait->AddImageIndex(nStateImageIdx + 1, COleDateTime(1970, 1, 1, 0, 0, 0).Format(), true);	// Checked (and editable)
			pDateTimeTrait->SetToggleSelection(true);
			pTrait = pDateTimeTrait;
		}
		if (col == 3)	// Year won
		{
			CGridColumnTraitHyperLink* pHyperLinkTrait = new CGridColumnTraitHyperLink;
			pHyperLinkTrait->SetShellFilePrefix(_T("http://en.wikipedia.org/wiki/UEFA_Euro_"));
			pTrait = pHyperLinkTrait;
		}

		m_ListCtrl.InsertColumnTrait(col + 1, title, LVCFMT_LEFT, 100, col, pTrait);
	}
	const CString& title = _T("按钮");
	CGridColumnTrait* pTrait = NULL;
	m_ListCtrl.InsertColumnTrait(5, title, LVCFMT_LEFT, 100, 4, pTrait);
	// Insert data into list-control by copying from datamodel
	int nItem = 0;
	for (size_t rowId = 0; rowId < m_DataModel.GetRowIds(); ++rowId)
	{

		nItem = m_ListCtrl.InsertItem(++nItem, m_DataModel.GetCellText(rowId, 0));
		m_ListCtrl.SetItemData(nItem, rowId);
		for (int col = 0; col < m_DataModel.GetColCount(); ++col)
		{
			int nCellCol = col + 1;	// +1 because of hidden column
			const CString& strCellText = m_DataModel.GetCellText(rowId, col);
			m_ListCtrl.SetItemText(nItem, nCellCol, strCellText);
			if (nCellCol == 3)
			{
				if (strCellText == _T(""))
					m_ListCtrl.SetCellImage(nItem, nCellCol, nStateImageIdx);	// unchecked
				else
					m_ListCtrl.SetCellImage(nItem, nCellCol, nStateImageIdx + 1);	// checked
			}
		}
		m_ListCtrl.createItemButton(rowId, 5, GetParent()->GetSafeHwnd());
		m_ListCtrl.SetCellImage(nItem, 1, nItem); // Assign flag-images

	}
	CViewConfigSectionWinApp* pColumnProfile = new CViewConfigSectionWinApp(_T("Sample List"));
	pColumnProfile->AddProfile(_T("Default"));
	pColumnProfile->AddProfile(_T("Special"));
	m_ListCtrl.SetupColumnConfig(pColumnProfile);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGridlistDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGridlistDlg::OnPaint()
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
HCURSOR CGridlistDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CGridlistDlg::onBnCLick(WPARAM wParam, LPARAM lParam)
{
	int nRow = (int)wParam;
	int nCol = (int)lParam;

#ifdef USE_TOPINDEX_BUTTON

	int iTopIndex = m_ListCtrl.GetTopIndex();
	TRACE(L"move:before:iTopIndex = %d, nRow = %d\n", iTopIndex, nRow);
	nRow = iTopIndex + nRow;
#endif
	CString str;
	str.Format(_T("nRow =%d, nCol = %d"), nRow, nCol);
	AfxMessageBox(str);
	return 0;
}