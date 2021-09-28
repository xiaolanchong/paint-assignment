// PaintDoc.cpp : implementation of the CPaintDoc class
//

#include "stdafx.h"
#include "Paint.h"

#include "PaintDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaintDoc

IMPLEMENT_DYNCREATE(CPaintDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaintDoc, CDocument)
	//{{AFX_MSG_MAP(CPaintDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaintDoc construction/destruction

CPaintDoc::CPaintDoc()
{
	// TODO: add one-time construction code here

}

CPaintDoc::~CPaintDoc()
{
}

BOOL CPaintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPaintDoc serialization

void CPaintDoc::Serialize(CArchive& ar)
{
	int nCounter;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		nCounter = m_listObject.GetCount();
		ar<<nCounter;
		POSITION pos = m_listObject.GetHeadPosition();
//		m_listObject.GetAt(pos)->Serialize(ar);
		for(int i=0;i<nCounter;i++)
			m_listObject.GetNext(pos)->Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		ar>>nCounter;
		for(int i=0;i<nCounter;i++)
		{
			auto po = std::make_unique<CPaintObject>();
			po->Serialize(ar);
			m_listObject.AddTail(std::move(po));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPaintDoc diagnostics

#ifdef _DEBUG
void CPaintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaintDoc commands
