#if !defined(AFX_COLOREDIT_H__F17EF841_32E5_4075_A035_89CA18DBDA93__INCLUDED_)
#define AFX_COLOREDIT_H__F17EF841_32E5_4075_A035_89CA18DBDA93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorEdit window

class CColorStatic : public CStatic
{
// Construction
public:
	CColorStatic();

// Attributes
public:
	COLORREF	m_clBack;
	TCHAR		m_szName[16];
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorEdit)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorEdit)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CFont m_dlgFont;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOREDIT_H__F17EF841_32E5_4075_A035_89CA18DBDA93__INCLUDED_)
