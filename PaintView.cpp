// PaintView.cpp : implementation of the CPaintView class
//

#include "stdafx.h"
#include "Paint.h"

#include "PaintDoc.h"
#include "PaintView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaintView

IMPLEMENT_DYNCREATE(CPaintView, CScrollView)

BEGIN_MESSAGE_MAP(CPaintView, CScrollView)
	//{{AFX_MSG_MAP(CPaintView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_LINE, OnButtonLine)
	ON_COMMAND(ID_DOT, OnButtonDot)
	ON_COMMAND(ID_RECT, OnButtonRect)
	ON_COMMAND(ID_POLYGON, OnButtonPolygon)
	ON_COMMAND(ID_POLYLINE, OnButtonPolyline)
	ON_COMMAND(ID_ELLIPSE, OnButtonEllipse)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_COLORELLIPSE, OnButtonColorEllipse)
	ON_COMMAND(ID_COLORPOLYGON, OnButtonColorPolygon)
	ON_COMMAND(ID_COLORRECT, OnButtonColorRect)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaintView construction/destruction

CPaintView::CPaintView()
{
	// TODO: add construction code here
	m_pMemDC = new CDC();
	m_CurrentPO	= PO_NONE;
	m_CurrentMS	= MS_NONE;
	m_nObject	= -1;
	m_pptTrans	= NULL;
}

CPaintView::~CPaintView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CPaintView drawing

void CPaintView::OnDraw(CDC* pDC)
{
	CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	POSITION Pos = pDoc->m_listObject.GetHeadPosition();
	if(pDoc->m_listObject.GetHeadPosition() != NULL)
		pDoc->m_listObject.GetAt(Pos)->Draw(pDC);
	for (int i=0;i < pDoc->m_listObject.GetCount();i++)
	{
		pDoc->m_listObject.GetNext(Pos)->Draw(pDC);
	}
/*	if(m_nObject != -1)
		DrawDragObject(m_nObject, CSize(0,0), R2_NOTXORPEN);*/
}

/////////////////////////////////////////////////////////////////////////////
// CPaintView diagnostics

#ifdef _DEBUG
void CPaintView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPaintView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CPaintDoc* CPaintView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintDoc)));
	return (CPaintDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaintView message handlers

int CPaintView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CRect Rect;
	GetClientRect(&Rect);
	SetScrollSizes(MM_TEXT, CSize(GetSystemMetrics(SM_CXSCREEN),
									GetSystemMetrics(SM_CYSCREEN)));
	SetTimer(0, 100, NULL);
	return 0;
}

//////////////////////////////////////////////////////////////////

void CPaintView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcClient;
	CPoint ptTemp = point;
	ptTemp.x += GetScrollPos(SB_HORZ);
	ptTemp.y += GetScrollPos(SB_VERT);
	GetClientRect(&rcClient);
	ClientToScreen(&rcClient);
	if(m_CurrentMS != MS_PAINT)
	switch(m_CurrentPO)
	{
		case PO_NONE:
			break;
		case PO_DOT :
			m_ptPrev = m_ptStart =	point;
			m_CurrentMS	=	MS_PAINT;
			DrawObject(point, R2_COPYPEN, R2_COPYPEN);
			AddObject(PO_DOT, point, point);
			ClipCursor(&rcClient);
			break;
		case PO_LINE:
		case PO_RECT:
		case PO_ELLIPSE:
		case PO_COLORRECT:
		case PO_COLORELLIPSE:		
			m_ptPrev = m_ptStart =	point;
			m_CurrentMS	=	MS_PAINT;
			ClipCursor(&rcClient);
			break;
		case PO_POLYLINE :
		case PO_POLYGON :
		case PO_COLORPOLYGON:
			m_ptPrev = m_ptStart =	point;
			m_listTemp.AddTail(ptTemp);
			m_CurrentMS =	MS_PAINT;
			ClipCursor(&rcClient);
			break;
	}
	else
	CScrollView::OnLButtonDown(nFlags, point);
}

void CPaintView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptTemp = point;
	ClipCursor(NULL);
	if(m_CurrentMS == MS_PAINT)
		switch(m_CurrentPO)
		{
			case PO_NONE:
				m_CurrentMS = MS_NONE;
				break;
			case PO_DOT :
				m_CurrentMS	= MS_NONE;
				
				break;
			case PO_LINE:
			case PO_RECT:
			case PO_ELLIPSE:
			case PO_COLORRECT:
			case PO_COLORELLIPSE:
				if((nFlags&MK_SHIFT) != 0)
					ptTemp.y = m_ptStart.y + point.x - m_ptStart.x;
				DrawObject(ptTemp, R2_NOTXORPEN, R2_COPYPEN);	
				AddObject(m_CurrentPO, m_ptStart, ptTemp);
				m_CurrentMS = MS_NONE;
				ClipCursor(NULL);
				break;
			case PO_POLYLINE :
			case PO_POLYGON :
			case PO_COLORPOLYGON:
				m_ptStart = m_ptPrev = point;
				ptTemp.x += GetScrollPos(SB_HORZ);
				ptTemp.y += GetScrollPos(SB_VERT);
				m_listTemp.AddTail(ptTemp);
				break;
		}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CPaintView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptTemp = point;
	ptTemp.x += GetScrollPos(SB_HORZ);
	ptTemp.y += GetScrollPos(SB_VERT);
	CPaintObject* po;
	if(m_nObject != -1)
		po = GetDocument()->m_listObject.GetAt(GetDocument()->m_listObject.FindIndex(m_nObject));
	if(m_CurrentMS == MS_PAINT)
		switch(m_CurrentPO)
		{
			case PO_NONE:
				break;
			case PO_DOT :
				DrawObject(point,R2_COPYPEN, R2_COPYPEN);
				AddObject(PO_DOT, point, point);
				break;
			case PO_LINE:
			case PO_RECT:
			case PO_ELLIPSE:
			case PO_COLORRECT:
			case PO_COLORELLIPSE:
				if((nFlags&MK_SHIFT) != 0)
				{
					ptTemp.y = m_ptStart.y + point.x - m_ptStart.x;	
					ptTemp.x = point.x;
				}
				DrawObject(point,R2_NOTXORPEN, R2_NOTXORPEN);
				break;
			case PO_POLYLINE: 
			case PO_POLYGON:
			case PO_COLORPOLYGON:
				DrawObject(point, R2_NOTXORPEN, R2_NOTXORPEN);
				break;
		}	
	if(m_CurrentMS == MS_DRAG)
	{
		DrawTransObject(m_nObject, R2_NOTXORPEN);
		po->Drag(ptTemp - m_ptPrev);
		DrawTransObject(m_nObject, R2_NOTXORPEN);
		m_ptPrev = ptTemp;
	}
	if( m_CurrentMS == MS_TRANS )
	{
		DrawTransObject( m_nObject, R2_NOTXORPEN );
		*m_pptTrans	+=	ptTemp - m_ptPrev;
		m_ptPrev	=	ptTemp;
		DrawTransObject( m_nObject, R2_NOTXORPEN );
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CPaintView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptTemp = point;
	ptTemp.x += GetScrollPos(SB_HORZ);
	ptTemp.y += GetScrollPos(SB_VERT);
	if(m_CurrentMS == MS_PAINT && 
		m_CurrentPO == PO_POLYLINE  )
	{
		m_listTemp.AddTail(ptTemp);
		m_CurrentMS = MS_NONE;
		ClipCursor(NULL);
		AddObject(PO_POLYLINE, point, point);
	}
	if(m_CurrentMS == MS_PAINT && 
		m_CurrentPO == PO_POLYGON  )
	{
		m_listTemp.AddTail(ptTemp);
		ClipCursor(NULL);
		m_CurrentPO = PO_LINE;
		m_ptStart.x = m_ptPrev.x = m_listTemp.GetHead().x-GetScrollPos(SB_HORZ);
		m_ptStart.y = m_ptPrev.y = m_listTemp.GetHead().y-GetScrollPos(SB_VERT);
		DrawObject(point, R2_NOTXORPEN, R2_COPYPEN); 
		m_CurrentPO = PO_POLYGON;
		AddObject(PO_POLYGON, point, point);
		m_CurrentMS = MS_NONE;
	}
	if(m_CurrentMS == MS_PAINT && 
		m_CurrentPO == PO_COLORPOLYGON  )
	{
		m_listTemp.AddTail(ptTemp);
		ClipCursor(NULL);
		m_CurrentPO = PO_COLORPOLYGON2;
//		m_ptStart.x = m_ptPrev.x = m_listTemp.GetHead().x-GetScrollPos(SB_HORZ);
//		m_ptStart.y = m_ptPrev.y = m_listTemp.GetHead().y-GetScrollPos(SB_VERT);
		DrawObject(point, R2_NOTXORPEN, R2_COPYPEN); 
		m_CurrentPO = PO_COLORPOLYGON;
		AddObject(PO_COLORPOLYGON, point, point);
		m_CurrentMS = MS_NONE;
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

//////////////////////////////////////////////////////////////////

void CPaintView::AddObject(OBJECT object, 
						    CPoint ptStart,CPoint ptEnd)
{
	ptEnd.x	+= GetScrollPos(SB_HORZ);
	ptEnd.y	+= GetScrollPos(SB_VERT);
	ptStart.x += GetScrollPos(SB_HORZ);
	ptStart.y += GetScrollPos(SB_VERT);
	CPaintObject* po = new CPaintObject;
	po->m_clFront = static_cast<CMainFrame*>(AfxGetMainWnd())->GetFrontColor();
	po->m_clBack  = static_cast<CMainFrame*>(AfxGetMainWnd())->GetBackColor();
	po->m_ID	  = object;
	po->m_dwWidth = static_cast<CMainFrame*>(AfxGetMainWnd())->GetWidth();
	po->m_nPenStyle = static_cast<CMainFrame*>(AfxGetMainWnd())->GetPenStyle();
	switch(object)
	{
		case PO_DOT :
			po->m_listPoint.AddTail(ptStart);
			break;
		case PO_LINE:
		case PO_RECT:
		case PO_ELLIPSE:
		case PO_COLORELLIPSE:
		case PO_COLORRECT:
			po->m_listPoint.AddTail(ptStart);
			po->m_listPoint.AddTail(ptEnd);
			break;
		case PO_POLYLINE:
/*		case PO_POLYGON:
		case PO_COLORPOLYGON:*/
			m_listTemp.RemoveHead();
			m_listTemp.RemoveTail();
			po->m_listPoint.AddTail(&m_listTemp);
			break;
		case PO_POLYGON:
		case PO_COLORPOLYGON:
			m_listTemp.RemoveHead();
			m_listTemp.RemoveTail();
			po->m_listPoint.AddTail(&m_listTemp);
			
			break;
		default: return;
	}
	m_listTemp.RemoveAll();
	GetDocument()->m_listObject.AddTail(po);
	GetDocument()->SetModifiedFlag(TRUE);
}

//////////////////////////////////////////////////////////////////

void CPaintView::DrawObject(CPoint point, int nROP1, int nROP2)
{
	CDC* pDC = GetDC();
	COLORREF clPen;
	COLORREF clBrush;
	DWORD	dwWidth;
	int		nPenStyle;
	if( m_CurrentMS == MS_PAINT )
	{
		clPen = static_cast<CMainFrame*>(AfxGetMainWnd())->GetFrontColor();
		clBrush = static_cast<CMainFrame*>(AfxGetMainWnd())->GetBackColor();
		dwWidth = static_cast<CMainFrame*>(AfxGetMainWnd())->GetWidth();
		nPenStyle = static_cast<CMainFrame*>(AfxGetMainWnd())->GetPenStyle();
	}
	CPen	pen;
	CBrush	Brush, *pPrevBrush;
	pen.CreatePen(nPenStyle, dwWidth, clPen);
	Brush.CreateSolidBrush(clBrush);
	CPen* pPrevPen = pDC->SelectObject(&pen);
	CPoint points[5];
	if(m_CurrentMS == MS_PAINT || MS_DRAG)
	{
		switch(m_CurrentPO) 
		{
		case PO_DOT:
			pDC->SetROP2(R2_COPYPEN);
			if(dwWidth == 1)
				pDC->SetPixel(point, clPen);
			else
				pDC->Ellipse(point.x, point.y,
								point.x + dwWidth+1, 
								point.y + dwWidth+1);
			break;
		case PO_LINE :			
		case PO_POLYLINE:
		case PO_POLYGON:
		case PO_COLORPOLYGON:
			pDC->SetROP2(nROP1);
			pDC->MoveTo(m_ptStart);
			pDC->LineTo(m_ptPrev);
			pDC->SetROP2(nROP2);
			pDC->MoveTo(m_ptStart);
			pDC->LineTo(point);		
			m_ptPrev = point;
			break;
		case PO_RECT :	
			pPrevBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
			pDC->SetROP2(nROP1);
			pDC->Rectangle( m_ptStart.x, m_ptStart.y,
							m_ptPrev.x, m_ptPrev.y );
			pDC->SetROP2(nROP2);
			pDC->Rectangle( m_ptStart.x, m_ptStart.y,
							point.x, point.y );
			pDC->SelectObject(pPrevBrush);
			m_ptPrev = point;
			break;
		case PO_ELLIPSE :	
			pPrevBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
			pDC->SetROP2(nROP1);
			pDC->Ellipse( m_ptStart.x, m_ptStart.y,
							m_ptPrev.x, m_ptPrev.y);
			pDC->SetROP2(nROP2);
			pDC->Ellipse( m_ptStart.x, m_ptStart.y,
							point.x, point.y);
			pDC->SelectObject(pPrevBrush);
			m_ptPrev = point;
			break;
		case PO_COLORRECT :	
			pPrevBrush = pDC->SelectObject(&Brush);
			pDC->SetROP2(nROP1);
			pDC->Rectangle( m_ptStart.x, m_ptStart.y,
							m_ptPrev.x, m_ptPrev.y );
			pDC->SetROP2(nROP2);
			pDC->Rectangle( m_ptStart.x, m_ptStart.y,
							point.x, point.y );
			pDC->SelectObject(pPrevBrush);
			m_ptPrev = point;
			break;
		case PO_COLORELLIPSE :	
			pPrevBrush = pDC->SelectObject(&Brush);
			pDC->SetROP2(nROP1);
			pDC->Ellipse( m_ptStart.x, m_ptStart.y,
							m_ptPrev.x, m_ptPrev.y);
			pDC->SetROP2(nROP2);
			pDC->Ellipse( m_ptStart.x, m_ptStart.y,
							point.x, point.y);
			pDC->SelectObject(pPrevBrush);
			m_ptPrev = point;
			break;
		case PO_COLORPOLYGON2 :
			CPoint* points = new CPoint[m_listTemp.GetCount()];
			pPrevBrush = pDC->SelectObject(&Brush);
			POSITION pos = m_listTemp.GetHeadPosition();
			for(int i=0;i<m_listTemp.GetCount();i++)
			{
				points[i] = m_listTemp.GetNext(pos);
				points[i].x -= GetScrollPos(SB_HORZ);
				points[i].y -= GetScrollPos(SB_VERT);
			}
			pDC->Polygon(points, m_listTemp.GetCount());
			pDC->SelectObject(pPrevBrush);
			m_ptPrev = point;
			delete points;
			break;
		}
	}
	pDC->SelectObject(pPrevPen);
	ReleaseDC(pDC);
}

//////////////////////////////////////////////////////////////////

void CPaintView::OnButtonDot() 
{
	// TODO: Add your command handler code here
	m_CurrentPO = PO_DOT;
}	

void CPaintView::OnButtonLine() 
{
	// TODO: Add your command handler code here
	m_CurrentPO = PO_LINE;
}

void CPaintView::OnButtonRect() 
{
	// TODO: Add your command handler code here
	m_CurrentPO = PO_RECT;
}

void CPaintView::OnButtonPolygon() 
{
	// TODO: Add your command handler code here
	m_CurrentPO = PO_POLYGON;
}

void CPaintView::OnButtonPolyline() 
{
	// TODO: Add your command handler code here
	m_CurrentPO = PO_POLYLINE;
}

void CPaintView::OnButtonEllipse() 
{
	// TODO: Add your command handler code here
	m_CurrentPO = PO_ELLIPSE;
}

void CPaintView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!bActivate)
	{
		::ClipCursor(NULL);
		m_CurrentMS = MS_NONE;
		m_listTemp.RemoveAll();
		Invalidate();
	}
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}



void CPaintView::OnButtonColorEllipse() 
{
	// TODO: Add your command handler code here
	m_CurrentPO = PO_COLORELLIPSE;
}

void CPaintView::OnButtonColorPolygon() 
{
	// TODO: Add your command handler code here
	m_CurrentPO = PO_COLORPOLYGON;
}

void CPaintView::OnButtonColorRect() 
{
	// TODO: Add your command handler code here
	m_CurrentPO = PO_COLORRECT;
}

//////////////////////////////////////////////////////////////////

void CPaintView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint pt = point;
	pt.x += GetScrollPos(SB_HORZ);
	pt.y += GetScrollPos(SB_VERT);
	m_ptPrev = m_ptStart = point;
	CPaintDoc* pDoc = (CPaintDoc*)GetDocument();
	CPaintObject* po;
	POSITION pos;
	if(m_nObject != -1)
	{
		pos = GetDocument()->m_listObject.FindIndex(m_nObject);
		po = GetDocument()->m_listObject.GetAt(pos);
		po->m_bChange = FALSE;
		m_nObject = -1;
	}
	POSITION Pos = pDoc->m_listObject.GetHeadPosition();
	
	CRect rcClient;
	GetClientRect(&rcClient);
	ClientToScreen(&rcClient);
	ClipCursor(&rcClient);
	switch(m_CurrentMS)
	{
		case MS_PAINT:
			m_CurrentMS = MS_NONE;
	
			Invalidate();
			break;
		case MS_NONE:
			for (int i=0;i < pDoc->m_listObject.GetCount();i++)
			{
				if(pDoc->m_listObject.GetAt(Pos)->PtInObject(pt))
				{
					m_CurrentMS = MS_DRAG;				
					m_nObject = i;
					m_ptStart = m_ptPrev = pt;
					pDoc->SetModifiedFlag();
				}
				if( (m_pptTrans = pDoc->m_listObject.GetAt(Pos)->GetPoint(pt)) != NULL)
				{
					m_CurrentMS = MS_TRANS;
					m_nObject = i;
					m_ptStart = m_ptPrev = pt;
					pDoc->SetModifiedFlag();
					break;
				}
				pDoc->m_listObject.GetNext(Pos);
			}
			if(m_nObject != -1)
			{
				DrawTransObject(m_nObject, R2_NOTXORPEN );
				CPaintObject* po = pDoc->m_listObject.GetAt(pDoc->m_listObject.FindIndex(m_nObject));
				po->m_bChange = TRUE;
			}
//			Invalidate();
	}		
	CScrollView::OnRButtonDown(nFlags, point);
}

void CPaintView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPaintObject* po;
	POSITION pos;
	if(m_nObject != -1)
	{
		pos = GetDocument()->m_listObject.FindIndex(m_nObject);
		po = GetDocument()->m_listObject.GetAt(pos);
	}
	ClipCursor(NULL);
	switch(m_CurrentMS)
	{
		case MS_PAINT:
			break;
		case MS_NONE:
			break;
		case MS_DRAG:
		case MS_TRANS:
			DrawTransObject(m_nObject, R2_NOTXORPEN );
			DrawTransObject(m_nObject, R2_COPYPEN);
			Invalidate();
			m_CurrentMS = MS_NONE;
			break;
	}
	Invalidate();
	CScrollView::OnRButtonUp(nFlags, point);
}

void CPaintView::OnEditCut() 
{
	// TODO: Add your command handler code here
	if(m_nObject != -1)
	{
		GetDocument()->m_listObject.RemoveAt(GetDocument()->m_listObject.FindIndex(m_nObject));
		m_nObject = -1;
		Invalidate();
	}
}

//////////////////////////////////////////////////////////////////

void CPaintView::DrawTransObject(int nIndex, int nRop)
{
	CDC* pDC = GetDC();
	CPaintDoc* pDoc = GetDocument();
	POSITION Pos = pDoc->m_listObject.FindIndex(nIndex);
	CPaintObject* po = pDoc->m_listObject.GetAt(Pos);
	po->Drag(CSize( -GetScrollPos(SB_HORZ), -GetScrollPos(SB_VERT)));
	po->Draw( pDC, nRop);
	po->Drag(CSize( GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT)));
	ReleaseDC(pDC);

}

//////////////////////////////////////////////////////////////////

void CPaintView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	static COLORREF clFront = RGB(0,0,0);
	static COLORREF clPen	= RGB(0,0,0);
	static COLORREF clBrush = RGB(255,255,255);
	static DWORD	dwWidth = 1;
	static	int	nPenStyle	= PS_SOLID;
	POSITION pos;
	CPaintObject* po;
	if( static_cast<CMainFrame*>(AfxGetMainWnd())->GetWidth() != 1 )
		static_cast<CMainFrame*>(AfxGetMainWnd())->EnableStyle(FALSE);
	else
		static_cast<CMainFrame*>(AfxGetMainWnd())->EnableStyle(TRUE);
	if(m_nObject != -1)
	{
		pos = GetDocument()->m_listObject.FindIndex(m_nObject);
		po = GetDocument()->m_listObject.GetAt(pos);
		if(clPen != static_cast<CMainFrame*>(AfxGetMainWnd())->GetFrontColor())
		{
			clPen = static_cast<CMainFrame*>(AfxGetMainWnd())->GetFrontColor();
			po->m_clFront = clPen;
			Invalidate();
		}
		if(clBrush != static_cast<CMainFrame*>(AfxGetMainWnd())->GetBackColor())
		{
			clBrush = static_cast<CMainFrame*>(AfxGetMainWnd())->GetBackColor();
			po->m_clBack = clBrush;
			Invalidate();
		}
		if(dwWidth != static_cast<CMainFrame*>(AfxGetMainWnd())->GetWidth())
		{
			dwWidth = static_cast<CMainFrame*>(AfxGetMainWnd())->GetWidth();
			po->m_dwWidth = dwWidth;
			Invalidate();
		}
		if(nPenStyle != static_cast<CMainFrame*>(AfxGetMainWnd())->GetPenStyle())
		{
			nPenStyle = static_cast<CMainFrame*>(AfxGetMainWnd())->GetPenStyle();
			po->m_nPenStyle = nPenStyle;
			Invalidate();
		}
	}
	CScrollView::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////