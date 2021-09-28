// PaintObject.cpp: implementation of the CPaintObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Paint.h"
#include "PaintObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CPaintObject, CObject, 1)

CPaintObject::CPaintObject()
{
	m_clBack	= RGB(255,255,255);
	m_clFront	= RGB(0,0,0);
	m_dwWidth	= 1;
	m_ID		= PO_NONE;
	m_nPenStyle = PS_SOLID;
	m_bChange	= FALSE;
}

CPaintObject::~CPaintObject()
{

}

//////////////////////////////////////////////////////////////////

void CPaintObject::Draw(CDC* pDC, int nROP)
{
	CPen	Pen, *pPrevPen;
	CBrush	Brush, *pPrevBrush;
	CPoint point;
	std::vector<CPoint> points;
	int nPrevROP = pDC->SetROP2( nROP );
	if(m_bChange)
		Pen.CreatePen(PS_DASH, 1, m_clFront);
	else
		Pen.CreatePen(m_nPenStyle, m_dwWidth, m_clFront);
	Brush.CreateSolidBrush(m_clBack);
	pPrevPen = pDC->SelectObject(&Pen);
	POSITION Pos = m_listPoint.GetHeadPosition();
	switch(m_ID)
	{
		case PO_DOT:
			point = m_listPoint.GetNext(Pos);
			if(m_dwWidth == 1)
				pDC->SetPixel(point, m_clFront);
			else
			pDC->Ellipse(point.x, point.y,
						 point.x + m_dwWidth + 1, 
						 point.y + m_dwWidth + 1);
			break;
		case PO_LINE :
			pDC->MoveTo(m_listPoint.GetAt(Pos));
			for (int i=0;i < m_listPoint.GetCount();i++)
				pDC->LineTo(m_listPoint.GetNext(Pos));
			break;
		case PO_RECT :
			pPrevBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
			pDC->Rectangle( m_listPoint.GetHead().x, 
							m_listPoint.GetHead().y,
							m_listPoint.GetTail().x,
							m_listPoint.GetTail().y );
			if(m_bChange)
			{
				pDC->Ellipse(	m_listPoint.GetHead().x-2, 
								m_listPoint.GetHead().y-2,
								m_listPoint.GetHead().x+2,
								m_listPoint.GetHead().y+2);
				pDC->Ellipse(	m_listPoint.GetTail().x-2, 
								m_listPoint.GetTail().y-2,
								m_listPoint.GetTail().x+2,
								m_listPoint.GetTail().y+2);
			}
			pDC->SelectObject(pPrevBrush);
			break;
		case PO_ELLIPSE :
			pPrevBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
			pDC->Ellipse(	m_listPoint.GetHead().x, 
							m_listPoint.GetHead().y,
							m_listPoint.GetTail().x,
							m_listPoint.GetTail().y );
			if(m_bChange)
			{
				pDC->Ellipse(	m_listPoint.GetHead().x-2, 
								m_listPoint.GetHead().y-2,
								m_listPoint.GetHead().x+2,
								m_listPoint.GetHead().y+2);
				pDC->Ellipse(	m_listPoint.GetTail().x-2, 
								m_listPoint.GetTail().y-2,
								m_listPoint.GetTail().x+2,
								m_listPoint.GetTail().y+2);
			}
			pDC->SelectObject(pPrevBrush);
			break;
		case PO_POLYLINE :
			pDC->MoveTo(m_listPoint.GetAt(Pos));
			for (int i=0;i < m_listPoint.GetCount();i++)
				pDC->LineTo(m_listPoint.GetNext(Pos));
			break;
		case PO_POLYGON :
			pDC->MoveTo(m_listPoint.GetAt(Pos));
			for (int i=0;i < m_listPoint.GetCount();i++)
				pDC->LineTo(m_listPoint.GetNext(Pos));
			pDC->LineTo(m_listPoint.GetHead());
			break;
		case PO_COLORRECT:
			pPrevBrush = pDC->SelectObject(&Brush);
			pDC->Rectangle( m_listPoint.GetHead().x, 
							m_listPoint.GetHead().y,
							m_listPoint.GetTail().x,
							m_listPoint.GetTail().y );
			if(m_bChange)
			{
				pDC->Ellipse(	m_listPoint.GetHead().x-2, 
								m_listPoint.GetHead().y-2,
								m_listPoint.GetHead().x+2,
								m_listPoint.GetHead().y+2);
				pDC->Ellipse(	m_listPoint.GetTail().x-2, 
								m_listPoint.GetTail().y-2,
								m_listPoint.GetTail().x+2,
								m_listPoint.GetTail().y+2);
			}
			pDC->SelectObject(pPrevBrush);
			break;
		case PO_COLORELLIPSE :
			pPrevBrush = pDC->SelectObject(&Brush);
			pDC->Ellipse(	m_listPoint.GetHead().x, 
							m_listPoint.GetHead().y,
							m_listPoint.GetTail().x,
							m_listPoint.GetTail().y );
			if(m_bChange)
			{
				pDC->Ellipse(	m_listPoint.GetHead().x-2, 
								m_listPoint.GetHead().y-2,
								m_listPoint.GetHead().x+2,
								m_listPoint.GetHead().y+2);
				pDC->Ellipse(	m_listPoint.GetTail().x-2, 
								m_listPoint.GetTail().y-2,
								m_listPoint.GetTail().x+2,
								m_listPoint.GetTail().y+2);
			}
			pDC->SelectObject(pPrevBrush);
			break;
		case PO_COLORPOLYGON :
			pPrevBrush = pDC->SelectObject(&Brush);
			points.resize(m_listPoint.GetCount());
			POSITION pos = m_listPoint.GetHeadPosition();
			points[0] = m_listPoint.GetAt(pos);
			for(int i=0;i<m_listPoint.GetCount();i++)
			{
				points[i] = m_listPoint.GetNext(pos);
			}
			pDC->Polygon(&points[0], m_listPoint.GetCount());
			pDC->SelectObject(pPrevBrush);
			break;
			
	}
	pDC->SelectObject(pPrevPen);
	pDC->SetROP2( nPrevROP );
}

//////////////////////////////////////////////////////////////////

void CPaintObject::Serialize(CArchive &ar)
{
	int nID;
	int nCount;
	CPoint point;
	if(ar.IsStoring())
	{
		nID = (int)m_ID;
		nCount = m_listPoint.GetCount();
		ar<<nID<<m_dwWidth<<m_clFront<<m_clBack<<m_nPenStyle;
		ar<<nCount;
		POSITION pos = m_listPoint.GetHeadPosition();
		point = m_listPoint.GetAt(pos);
		for(int i=0;i<nCount;i++)
		{
			point = m_listPoint.GetNext(pos);
			ar<<point.x<<point.y;
		}		
	}
	else
	{
		ar>>nID>>m_dwWidth>>m_clFront>>m_clBack>>m_nPenStyle;
		m_ID = (OBJECT)nID;
		ar>>nCount;
		for(int i=0;i<nCount;i++)
		{
			ar>>point.x>>point.y;
			m_listPoint.AddTail(point);
		}	
	}
}

//////////////////////////////////////////////////////////////////

BOOL CPaintObject::PtInObject(CPoint point)
{
	CRgn rgn;
	CPoint pt;
	int i;
	switch(m_ID)
	{
		case PO_DOT:
			pt = m_listPoint.GetHead();
			rgn.CreateEllipticRgn(	pt.x - m_dwWidth-3, 
									pt.y - m_dwWidth-3,
									pt.x + m_dwWidth+3,
									pt.y + m_dwWidth+3);
			return rgn.PtInRegion(point);
		case PO_LINE :
		{
			CPoint ppt[4] = {};
			ppt[0] = ppt[1] = m_listPoint.GetHead();
			ppt[2] = ppt[3] = m_listPoint.GetTail();
			ppt[0] += CSize(10, 10);
			ppt[1] -= CSize(0, 10);
			ppt[2] -= CSize(10, 0);
			ppt[3] += CSize(10, 10);
			rgn.CreatePolygonRgn(ppt, 4, ALTERNATE);
			return rgn.PtInRegion(point);
		}
		case PO_RECT :
		case PO_COLORRECT:
		{
			CPoint ppt[2] = {};
			ppt[0] = m_listPoint.GetHead();
			ppt[1] = m_listPoint.GetTail();
			rgn.CreateRectRgn(ppt[0].x, ppt[0].y,
				ppt[1].x, ppt[1].y);
			return rgn.PtInRegion(point);
		}
		case PO_ELLIPSE :
		case PO_COLORELLIPSE :
		{
			CPoint ppt[2] = {};
			ppt[0] = m_listPoint.GetHead();
			ppt[1] = m_listPoint.GetTail();
			rgn.CreateEllipticRgn(ppt[0].x, ppt[0].y,
				ppt[1].x, ppt[1].y);
			return rgn.PtInRegion(point);
			break;
		}
		
		case PO_POLYLINE :
		case PO_POLYGON :
		case PO_COLORPOLYGON :
		{
			std::vector<CPoint> ppt(m_listPoint.GetCount());
			POSITION pos = m_listPoint.GetHeadPosition();
			for (i = 0; i < m_listPoint.GetCount(); i++)
				ppt[i] = m_listPoint.GetNext(pos);

			rgn.CreatePolygonRgn(&ppt[0], m_listPoint.GetCount(), ALTERNATE);
			return rgn.PtInRegion(point);
		}
	}
	return FALSE;
}

CPoint*	CPaintObject::GetPoint(CPoint ptMouse)
{
	POSITION pos = m_listPoint.GetHeadPosition();
	CPoint	pt;
	CRect	rect;
	if( m_ID == PO_DOT) return NULL;
	for (int i=0;i < m_listPoint.GetCount();i++)
	{
		pt = m_listPoint.GetAt(pos);
		rect.TopLeft()	= pt - CSize(8, 8); 
		rect.BottomRight() = pt + CSize(8, 8); 
		if(rect.PtInRect(ptMouse))
			return &m_listPoint.GetAt(pos);
		m_listPoint.GetNext(pos);
	}
	return NULL;
}

void	CPaintObject::Drag(CSize size)
{
	POSITION pos = m_listPoint.GetHeadPosition();
	CPoint pt;
	for (int i=0;i < m_listPoint.GetCount();i++)
		m_listPoint.GetNext(pos) += size;
}