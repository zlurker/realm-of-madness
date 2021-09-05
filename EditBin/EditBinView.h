// EditBinView.h : interface of the CEditBinView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EditBinVIEW_H__4B3CB70E_0063_4DD7_A761_8113CEE64962__INCLUDED_)
#define AFX_EditBinVIEW_H__4B3CB70E_0063_4DD7_A761_8113CEE64962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEditBinCntrItem;

class CEditBinView : public CRichEditView
{
protected: // create from serialization only
	CEditBinView();
	DECLARE_DYNCREATE(CEditBinView)

// Attributes
public:
	CEditBinDoc* GetDocument();
	HANDLE hThread;  //April 2005
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditBinView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditBinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEditBinView)
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in EditBinView.cpp
inline CEditBinDoc* CEditBinView::GetDocument()
   { return (CEditBinDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EditBinVIEW_H__4B3CB70E_0063_4DD7_A761_8113CEE64962__INCLUDED_)
