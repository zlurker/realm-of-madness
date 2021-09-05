// CntrItem.h : interface of the CEditBinCntrItem class
//

#if !defined(AFX_CNTRITEM_H__CD2BF2E5_05AE_4A8A_A686_60DD6EA4AC62__INCLUDED_)
#define AFX_CNTRITEM_H__CD2BF2E5_05AE_4A8A_A686_60DD6EA4AC62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEditBinDoc;
class CEditBinView;

class CEditBinCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CEditBinCntrItem)

// Constructors
public:
	CEditBinCntrItem(REOBJECT* preo = NULL, CEditBinDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CEditBinDoc* GetDocument()
		{ return (CEditBinDoc*)CRichEditCntrItem::GetDocument(); }
	CEditBinView* GetActiveView()
		{ return (CEditBinView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditBinCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CEditBinCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__CD2BF2E5_05AE_4A8A_A686_60DD6EA4AC62__INCLUDED_)
