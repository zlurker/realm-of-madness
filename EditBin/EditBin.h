// EditBin.h : main header file for the EditBin application
//

#if !defined(AFX_EditBin_H__3DEDFA90_A8F3_4275_BF2E_B827BA5D45E7__INCLUDED_)
#define AFX_EditBin_H__3DEDFA90_A8F3_4275_BF2E_B827BA5D45E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_USERMSG    WM_USER +10
extern char SharedBuf[];
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "WatchOutput.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CEditBinApp:
// See EditBin.cpp for the implementation of this class
//

class CEditBinApp : public CWinApp
{
public:
	CWatchOutput m_watcher;
	CEditBinApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditBinApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEditBinApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
//	HANDLE hThread;
	HANDLE hSTDOUT;
	HANDLE hRead;
	HANDLE hWrite;
	void ReceivingString( CString strMsg);
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EditBin_H__3DEDFA90_A8F3_4275_BF2E_B827BA5D45E7__INCLUDED_)
