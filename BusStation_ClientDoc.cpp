// BusStation_ClientDoc.cpp : implementation of the CBusStation_ClientDoc class
//

#include "stdafx.h"
#include "BusStation_Client.h"

#include "BusStation_ClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientDoc

IMPLEMENT_DYNCREATE(CBusStation_ClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CBusStation_ClientDoc, CDocument)
	//{{AFX_MSG_MAP(CBusStation_ClientDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientDoc construction/destruction

CBusStation_ClientDoc::CBusStation_ClientDoc()
{
	// TODO: add one-time construction code here

}

CBusStation_ClientDoc::~CBusStation_ClientDoc()
{
}

BOOL CBusStation_ClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientDoc serialization

void CBusStation_ClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientDoc diagnostics

#ifdef _DEBUG
void CBusStation_ClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBusStation_ClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientDoc commands
