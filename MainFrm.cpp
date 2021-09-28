// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Paint.h"
#include <windowsx.h>

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_STATICFRONT		1234
#define IDC_STATICBACK		1235
#define IDC_COMBOWIDTH		1236
#define IDC_COMBOSTYLE		1237

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
//	ON_COMMAND(ID_FOREGROUND, OnForeground)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar1\n");
		return -1;      // fail to create
	}


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_BOTTOM|CBRS_ALIGN_TOP);
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolFigure.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT);
	m_wndToolFigure.LoadToolBar(IDR_FIGURE);
	m_wndToolColorFigure.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT);
	m_wndToolColorFigure.LoadToolBar(IDR_COLORFIGURE);

	m_wndToolBar.SetButtonInfo(7, ID_SEPARATOR, TBBS_SEPARATOR, 10);
	m_wndToolBar.SetButtonInfo(8, ID_SEPARATOR, TBBS_SEPARATOR, 50);
	m_wndToolBar.SetButtonInfo(9, ID_SEPARATOR, TBBS_SEPARATOR, 10);
	m_wndToolBar.SetButtonInfo(10, ID_SEPARATOR, TBBS_SEPARATOR, 50);
	m_wndToolBar.SetButtonInfo(11, ID_SEPARATOR, TBBS_SEPARATOR, 10);
	m_wndToolBar.SetButtonInfo(12, ID_SEPARATOR, TBBS_SEPARATOR, 50);
	m_wndToolBar.SetButtonInfo(13, ID_SEPARATOR, TBBS_SEPARATOR, 10);
	m_wndToolBar.SetButtonInfo(14, ID_SEPARATOR, TBBS_SEPARATOR, 50);
	m_wndToolBar.SetButtonInfo(15, ID_SEPARATOR, TBBS_SEPARATOR, 10);

	m_dlgFont.CreatePointFont(10 * 8, _T("MS Shell Dlg"));

	CRect rect;
	m_wndToolBar.GetItemRect(8, &rect);
	m_wndFrontColor.Create(_T("Front"),
			WS_VISIBLE|WS_CHILD|WS_BORDER,
			rect, &m_wndToolBar, IDC_STATICFRONT);
	m_wndToolBar.GetItemRect(10, &rect);
	m_wndBackColor.Create(_T("Back"),
							WS_VISIBLE|WS_CHILD|WS_BORDER,
							rect, &m_wndToolBar, IDC_STATICBACK);
	m_wndFrontColor.m_clBack = RGB(0,0,0);
	lstrcpy(m_wndFrontColor.m_szName, _T("Front"));
	m_wndBackColor.m_clBack = RGB(255,255,255);
	lstrcpy(m_wndBackColor.m_szName, _T("Back"));
///////
	m_wndToolBar.GetItemRect(12, &rect);
	rect.bottom += 100;
	m_wndWidthBox.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_VSCROLL,
							rect,&m_wndToolBar,IDC_COMBOWIDTH); 
	m_wndWidthBox.SetFont(&m_dlgFont);
	m_wndWidthBox.AddString(_T("1"));
	m_wndWidthBox.AddString(_T("2"));
	m_wndWidthBox.AddString(_T("3"));
	m_wndWidthBox.AddString(_T("4"));
	m_wndWidthBox.AddString(_T("5"));
	m_wndWidthBox.AddString(_T("6"));
	m_wndWidthBox.AddString(_T("7"));
	m_wndWidthBox.AddString(_T("8"));
	m_wndWidthBox.SetCurSel(0);
///////
	m_wndToolBar.GetItemRect(14, &rect);
	rect.bottom += 100;
	m_wndStyleBox.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST,
							rect,&m_wndToolBar,IDC_COMBOWIDTH);
	m_wndStyleBox.SetFont(&m_dlgFont);
	m_wndStyleBox.AddString(_T("_______"));
	m_wndStyleBox.AddString(_T("_ _ _ _"));
	m_wndStyleBox.AddString(_T("..........."));
	m_wndStyleBox.AddString(_T("_._._._"));
	m_wndStyleBox.AddString(_T("_.._.._.."));
	m_wndStyleBox.SetCurSel(0);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

