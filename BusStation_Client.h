// BusStation_Client.h : main header file for the BUSSTATION_CLIENT application
//

#if !defined(AFX_BUSSTATION_CLIENT_H__1242DDD3_97FA_48F3_B110_0AD3DF67C9FB__INCLUDED_)
#define AFX_BUSSTATION_CLIENT_H__1242DDD3_97FA_48F3_B110_0AD3DF67C9FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientApp:
// See BusStation_Client.cpp for the implementation of this class
//

class CBusStation_ClientApp : public CWinApp
{
public:
	CBusStation_ClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBusStation_ClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBusStation_ClientApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUSSTATION_CLIENT_H__1242DDD3_97FA_48F3_B110_0AD3DF67C9FB__INCLUDED_)
