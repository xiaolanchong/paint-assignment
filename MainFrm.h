// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__84C43FBD_C70D_45E9_8A3D_C0854926DAA1__INCLUDED_)
#define AFX_MAINFRM_H__84C43FBD_C70D_45E9_8A3D_C0854926DAA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ColorEdit.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	inline COLORREF GetFrontColor();
	inline COLORREF GetBackColor();
	inline DWORD	GetWidth();
	inline int		GetPenStyle();
	inline void		EnableStyle(BOOL bEnable = TRUE );
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar		m_wndStatusBar;
	CToolBar		m_wndToolBar;
	CToolBar		m_wndToolFigure;
	CToolBar		m_wndToolColorFigure;
	CColorStatic	m_wndFrontColor;
	CColorStatic	m_wndBackColor;
	CComboBox		m_wndWidthBox;
	CComboBox		m_wndStyleBox;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

COLORREF CMainFrame::GetFrontColor()
{
	return m_wndFrontColor.m_clBack;
}

COLORREF CMainFrame::GetBackColor()
{
	return m_wndBackColor.m_clBack;
}

DWORD CMainFrame::GetWidth()
{
	return m_wndWidthBox.GetCurSel()+1;
}

int CMainFrame::GetPenStyle()
{
	switch(m_wndStyleBox.GetCurSel())
	{
		case 0 : return PS_SOLID;
		case 1 : return PS_DASH;
		case 2 : return PS_DOT;
		case 3 : return PS_DASHDOT;
		case 4 : return PS_DASHDOTDOT;
	}
	return PS_SOLID;
}

void CMainFrame::EnableStyle(BOOL bEnable)
{
	if(!bEnable)
		m_wndStyleBox.SetCurSel(0);
	m_wndStyleBox.EnableWindow(bEnable);
}
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__84C43FBD_C70D_45E9_8A3D_C0854926DAA1__INCLUDED_)
