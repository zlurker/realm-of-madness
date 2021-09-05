// WatchOutput.cpp: implementation of the CWatchOutput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "EditBin.h"
#include "WatchOutput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

char SharedBuf[300];  //April 2005

//Non-class routines  // April 2005
DWORD WINAPI ThreadProc(  LPVOID lpParameter)
{
	DWORD dwBytesRead;
    char buf[100];
	HANDLE hFile;
    CEditBinApp *m_app;

	m_app = (CEditBinApp *) lpParameter;
	hFile = m_app->hRead;
	while(1 ) // ::AfxGetApp();
	{
		buf[0]=0;
		dwBytesRead = 0;
		ReadFile( hFile,buf,100,&dwBytesRead,0);
		if( dwBytesRead>0 && dwBytesRead<100)
		{
			buf[dwBytesRead]=0;			
			strcpy(SharedBuf,buf);
			SendMessage(m_app->GetMainWnd()->m_hWnd ,WM_USERMSG,1,0);

		}

	}

	return 0 ;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWatchOutput::CWatchOutput()
{

}

CWatchOutput::~CWatchOutput()
{

}
