// EditBinDoc.h : interface of the CEditBinDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EditBinDOC_H__4A529818_FAD7_45D6_ADC3_6ADBE95E4F55__INCLUDED_)
#define AFX_EditBinDOC_H__4A529818_FAD7_45D6_ADC3_6ADBE95E4F55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEditBinDoc : public CRichEditDoc
{
protected: // create from serialization only
	CEditBinDoc();
	DECLARE_DYNCREATE(CEditBinDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditBinDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CEditBinDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEditBinDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EditBinDOC_H__4A529818_FAD7_45D6_ADC3_6ADBE95E4F55__INCLUDED_)
