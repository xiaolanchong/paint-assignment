// Paint.h : main header file for the PAINT application
//

#if !defined(AFX_PAINT_H__959B2E41_FACA_49F6_B443_19A9530FFE5A__INCLUDED_)
#define AFX_PAINT_H__959B2E41_FACA_49F6_B443_19A9530FFE5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaintApp:
// See Paint.cpp for the implementation of this class
//

class CPaintApp : public CWinApp
{
public:
	CPaintApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaintApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPaintApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAINT_H__959B2E41_FACA_49F6_B443_19A9530FFE5A__INCLUDED_)
