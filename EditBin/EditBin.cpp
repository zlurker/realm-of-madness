// EditBin.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "EditBin.h"

#include "MainFrm.h"
#include "EditBinDoc.h"
#include "EditBinView.h"
#include "WatchOutput.h"  //april 2005
#include "ostream.h"  //april 2005
#include <fstream.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditBinApp

BEGIN_MESSAGE_MAP(CEditBinApp, CWinApp)
	//{{AFX_MSG_MAP(CEditBinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditBinApp construction

CEditBinApp::CEditBinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEditBinApp object

CEditBinApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEditBinApp initialization

BOOL CEditBinApp::InitInstance()
{
	BOOL rval;
	
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	//Start April 2005
	  hSTDOUT= ::GetStdHandle(STD_OUTPUT_HANDLE);
	  rval = CreatePipe(&hRead,&hWrite,0,0);
	  rval = SetStdHandle(STD_OUTPUT_HANDLE,hWrite);
	  //AllocConsole();

	  //Now assign hWrite to stdout, cout
	  //mk:@MSITStore:C:\Program%20Files\Microsoft%20Visual%20Studio\MSDN98\98VS\1033\kb.chm::/Source/win32sdk/q105305.htm
	  FILE *fp;
	  int hConHandle;
	  long lStdHandle;
	  lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	  hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	  fp = _fdopen( hConHandle, "w" );
	  // The stdout reassignment didn't seem to work
	  // *stdout = *fp;  // redefine the stdout handle to point to the pipe
      setvbuf( fp, NULL, _IONBF, 0 );
	  filebuf *fb = new filebuf(_fileno(fp  ) ); // Filebuf object attached to "test.dat"
      cout = fb;   
	  fprintf(stdout,_T("No error here.\r"));
	  
	//end April 2005

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CEditBinDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CEditBinView));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CEditBinApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CEditBinApp message handlers


int CEditBinApp::ExitInstance() //april 2005
{
	// TODO: Add your specialized code here and/or call the base class
	::SetStdHandle(STD_OUTPUT_HANDLE,hSTDOUT);  //april 2005
	return CWinApp::ExitInstance();
}


void CEditBinApp::ReceivingString( CString strMsg)
{
	//
}

