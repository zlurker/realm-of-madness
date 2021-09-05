// CntrItem.cpp : implementation of the CEditBinCntrItem class
//

#include "stdafx.h"
#include "EditBin.h"

#include "EditBinDoc.h"
#include "EditBinView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditBinCntrItem implementation

IMPLEMENT_SERIAL(CEditBinCntrItem, CRichEditCntrItem, 0)

CEditBinCntrItem::CEditBinCntrItem(REOBJECT* preo, CEditBinDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CEditBinCntrItem::~CEditBinCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CEditBinCntrItem diagnostics

#ifdef _DEBUG
void CEditBinCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CEditBinCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
