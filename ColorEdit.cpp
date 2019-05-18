// ColorEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Paint.h"
#include "ColorEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorEdit

CColorStatic::CColorStatic():m_clBack(RGB(0 ,0 ,0))
{
	ZeroMemory(m_szName, sizeof(m_szName));
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorEdit)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorEdit message handlers

void CColorStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CBrush brush;
	RECT rcClient = {0,0,100,100};
	GetClientRect(&rcClient);
	brush.CreateSolidBrush(m_clBack);
	dc.FillRect(&rcClient, &brush);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(0x00FFFFFF^m_clBack);
	dc.DrawText(m_szName, lstrlen(m_szName), &rcClient, DT_CENTER);
	// Do not call CEdit::OnPaint() for painting messages
}

BOOL CColorStatic::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= SS_NOTIFY;
	return CStatic::PreCreateWindow(cs);
}

void CColorStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CColorDialog dlg;
//	dlg.m_cc.rgbResult = 
	if(dlg.DoModal() == IDOK)
	{
		m_clBack = dlg.m_cc.rgbResult;
		Invalidate();
	}
	CStatic::OnLButtonDown(nFlags, point);
}
