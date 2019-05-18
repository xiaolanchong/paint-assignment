// PaintView.h : interface of the CPaintView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAINTVIEW_H__96A2AC6F_33E5_4D6B_BFFE_BC9E8C943EAC__INCLUDED_)
#define AFX_PAINTVIEW_H__96A2AC6F_33E5_4D6B_BFFE_BC9E8C943EAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PaintObject.h"

enum MOUSESTATE { MS_NONE, MS_PAINT, MS_PAINTPOLY, MS_DRAG, MS_TRANS };

class CPaintView : public CScrollView
{
protected: // create from serialization only
	CPaintView();
	DECLARE_DYNCREATE(CPaintView)

// Attributes
public:
	CPaintDoc*	GetDocument();
	void		AddObject(OBJECT object, 
							CPoint ptStart, CPoint ptEnd);
	void		DrawObject(CPoint point, int nROP1, int nROP2);
	void		DrawTransObject(int nIndex, int nRop);

///////
	CPoint					m_ptPrev;
	CPoint					m_ptStart;
	CPoint*					m_pptTrans;
	OBJECT					m_CurrentPO;
	CList<CPoint,CPoint>	m_listTemp;
	MOUSESTATE				m_CurrentMS;
	CDC*					m_pMemDC;
	int						m_nObject;
	CPaintObject			m_TempObj;


///////

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaintView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPaintView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButtonLine();
	afx_msg void OnButtonDot();
	afx_msg void OnButtonRect();
	afx_msg void OnButtonPolygon();
	afx_msg void OnButtonPolyline();
	afx_msg void OnButtonEllipse();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnButtonColorEllipse();
	afx_msg void OnButtonColorPolygon();
	afx_msg void OnButtonColorRect();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditCut();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PaintView.cpp
inline CPaintDoc* CPaintView::GetDocument()
   { return (CPaintDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAINTVIEW_H__96A2AC6F_33E5_4D6B_BFFE_BC9E8C943EAC__INCLUDED_)
