// BusStation_ClientView.h : interface of the CBusStation_ClientView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUSSTATION_CLIENTVIEW_H__7592649B_2BEA_40F3_87C6_4E0CB1DD3040__INCLUDED_)
#define AFX_BUSSTATION_CLIENTVIEW_H__7592649B_2BEA_40F3_87C6_4E0CB1DD3040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_BUS 10
#define MAX_STATION 38

typedef struct Bus{
	int type;
	int whichIn;
	int intPos;
	int intPeople;
}stBus;

typedef struct Weather{
	int type;
	int temperature;
	int temperature2;
	int temperature3;
}stWeather;

typedef struct InsSet{
	stBus myBus[MAX_BUS];
	stWeather myWeather;
}stINSSET;

class CBusStation_ClientView : public CView
{
protected: // create from serialization only
	CBusStation_ClientView();
	DECLARE_DYNCREATE(CBusStation_ClientView)

// Attributes
public:
	CBusStation_ClientDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBusStation_ClientView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	CPoint m_moPoint;
	CBitmap m_bCurImage;
	CBitmap m_bBlueBus;
	CBitmap m_bGreenBus;
	CBitmap m_bRedBus;
	CBitmap m_pGreen;
	CBitmap m_pYellow;
	CBitmap m_pRed;
	CBitmap m_wtSun;
	CBitmap m_wtCloud;
	CBitmap m_wtRain;
	CBitmap m_wtSnow;
	int m_setClient;
	stINSSET m_insSet;
	SOCKET g_ClientSocket;
	char servIP[15];
	char str[128];
	CWinThread *hThread;
	CString m_test[MAX_BUS];
	void OnConnect();
	BOOL SoundSwitch[3];

	BOOL m_bTransparent; // 텍스트의 배경을 투명하게 할 것인지
	COLORREF m_colorText; // 텍스트 전경색
	LOGFONT m_logFont;  // 텍스트를 출력할 논리적 글꼴
	COLORREF m_bkText; // 텍스트 전경색


	virtual ~CBusStation_ClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBusStation_ClientView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSetting();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BusStation_ClientView.cpp
inline CBusStation_ClientDoc* CBusStation_ClientView::GetDocument()
   { return (CBusStation_ClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUSSTATION_CLIENTVIEW_H__7592649B_2BEA_40F3_87C6_4E0CB1DD3040__INCLUDED_)
