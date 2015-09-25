// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BusStation_Client.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.cx = 710;
	cs.cy = 463;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	CFrameWnd::OnWindowPosChanging(lpwndpos);
	
	// TODO: Add your message handler code here
	int sx = GetSystemMetrics(SM_CXSCREEN);
	int sy = GetSystemMetrics(SM_CYSCREEN) - 30;
	
	LPWINDOWPOS wp = lpwndpos;
	
	int t = wp->x;
	
	if(t < 30 && t > -30)
		t = 0;
	if(t + wp->cx > sx - 30 && t + wp->cx < sx + 30)
		t = sx - wp->cx;
	wp->x = t;
	
	t = wp->y;
	
	if(t < 30 && t > -30)
		t = 0;
	if(t + wp->cy > sy - 30 && t + wp->cy < sy + 30)
		t = sy - wp->cy;
	wp->y = t;
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	LPMINMAXINFO lpminmax = (LPMINMAXINFO)lpMMI; 
	
	//여기서 최소값을 정해주면 그 크기 이하로 줄지 않는다. 
	lpminmax->ptMinTrackSize.x = 710; 
	lpminmax->ptMinTrackSize.y = 463; 
	//여기서 최대값을 정해주면 그 크기 이상으로 커지지 않는다. 
	lpminmax->ptMaxTrackSize.x = 710; 
	lpminmax->ptMaxTrackSize.y = 463;
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}
