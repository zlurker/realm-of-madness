// EditBinDoc.cpp : implementation of the CEditBinDoc class
//

#include "stdafx.h"
#include "EditBin.h"

#include "EditBinDoc.h"
#include "CntrItem.h"
#include "WatchOutput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditBinDoc

IMPLEMENT_DYNCREATE(CEditBinDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CEditBinDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CEditBinDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditBinDoc construction/destruction

CEditBinDoc::CEditBinDoc()
{
	// TODO: add one-time construction code here

}

CEditBinDoc::~CEditBinDoc()
{
}

BOOL CEditBinDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CEditBinDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CEditBinCntrItem(preo, (CEditBinDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CEditBinDoc serialization

void CEditBinDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEditBinDoc diagnostics

#ifdef _DEBUG
void CEditBinDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CEditBinDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEditBinDoc commands
