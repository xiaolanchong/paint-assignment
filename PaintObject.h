// PaintObject.h: interface for the CPaintObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAINTOBJECT_H__8EE764BA_94E4_44DA_98D0_04E666B6CF0F__INCLUDED_)
#define AFX_PAINTOBJECT_H__8EE764BA_94E4_44DA_98D0_04E666B6CF0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

enum OBJECT {	PO_NONE	= 0, 
				PO_DOT	= 1  , 
				PO_LINE	= 2, 
				PO_RECT	= 3, 
				PO_POLYLINE = 4, 
				PO_ELLIPSE = 5, 
				PO_POLYGON = 6,
				PO_COLORRECT = 7, 
				PO_COLORELLIPSE = 8, 
				PO_COLORPOLYGON	= 9,
				PO_COLORPOLYGON2	= 10};




class CPaintObject : public CObject  
{
	DECLARE_SERIAL(CPaintObject);
public:
	CPaintObject();
	virtual ~CPaintObject();
	void	Draw(CDC* pDC, int nROP = R2_COPYPEN);
	CPoint*	GetPoint(CPoint ptMouse);
	virtual void Serialize(CArchive &ar);
	BOOL	PtInObject(CPoint point);
	void	Drag(CSize size);

public:
	OBJECT					m_ID;
	CList<CPoint,CPoint>	m_listPoint;
	COLORREF				m_clFront;
	COLORREF				m_clBack;
	DWORD					m_dwWidth;
	int						m_nPenStyle;
	BOOL					m_bChange;
};


#endif // !defined(AFX_PAINTOBJECT_H__8EE764BA_94E4_44DA_98D0_04E666B6CF0F__INCLUDED_)
