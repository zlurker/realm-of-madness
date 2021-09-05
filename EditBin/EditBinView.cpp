// EditBinView.cpp : implementation of the CEditBinView class
//

#include "stdafx.h"
#include "EditBin.h"

#include "EditBinDoc.h"
#include "CntrItem.h"
#include "EditBinView.h"
#include <afxdisp.h>
#include "WatchOutput.h"  //april 2005
#include "ostream.h"  //april 2005

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DWORD WINAPI ThreadProc(  LPVOID lpParameter   ); //April 2005

/////////////////////////////////////////////////////////////////////////////
// CEditBinView

IMPLEMENT_DYNCREATE(CEditBinView, CRichEditView)

BEGIN_MESSAGE_MAP(CEditBinView, CRichEditView)
	//{{AFX_MSG_MAP(CEditBinView)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditBinView construction/destruction

CEditBinView::CEditBinView()
{
	// TODO: add construction code here
}

CEditBinView::~CEditBinView()
{
}

BOOL CEditBinView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CEditBinView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();
	DWORD m_id;
	SetTimer(1,10000,0);  //April 2005

     hThread = CreateThread(0,0, ThreadProc,(void *)::AfxGetApp(),CREATE_SUSPENDED,&m_id); //april 2005

	ResumeThread(hThread);  //April 2005
 


	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CEditBinView printing

BOOL CEditBinView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CEditBinView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.

   CRichEditView::OnDestroy();
   KillTimer(1);  // April 2005
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CEditBinView diagnostics

#ifdef _DEBUG
void CEditBinView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CEditBinView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CEditBinDoc* CEditBinView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditBinDoc)));
	return (CEditBinDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEditBinView message handlers


//April 2005 -- add timer to demonstrate the pipe access
void CEditBinView::OnTimer(UINT nIDEvent) 
{
	CString strTitle;
	COleDateTime ole;   //April 2005 test code disabled
	ole = COleDateTime::GetCurrentTime();
	strTitle = ole.Format();
	// April 2005
		DWORD dwBytesWritten;
    char buf[100];
	HANDLE hFile;
    CEditBinApp *m_app;
//	CString strMsg(_T("Wow\r\n"));

	m_app = (CEditBinApp *) ::AfxGetApp ();
	hFile = m_app->hWrite;
//	WriteFile(hFile,strMsg,strMsg.GetLength(),&dwBytesWritten,0);
	cout << strTitle << endl;   //This will hopefully be picked up by the Pipe  April 2005
//	fprintf(stdout, _T("%s\r"), (LPCTSTR)strTitle);
	
	CRichEditView::OnTimer(nIDEvent);
}



