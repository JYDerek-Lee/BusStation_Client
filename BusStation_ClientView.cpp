// BusStation_ClientView.cpp : implementation of the CBusStation_ClientView class
//

#include "stdafx.h"
#include "BusStation_Client.h"

#include "BusStation_ClientDoc.h"
#include "BusStation_ClientView.h"

#include "SettingDlg.h"
#include <mmsystem.h>
#include "MemDC.h" // 더블버퍼링용 헤더파일

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT RecvMSG(void *arg);

/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientView

IMPLEMENT_DYNCREATE(CBusStation_ClientView, CView)

BEGIN_MESSAGE_MAP(CBusStation_ClientView, CView)
	//{{AFX_MSG_MAP(CBusStation_ClientView)
	ON_WM_TIMER()
	ON_COMMAND(ID_SETTING, OnSetting)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientView construction/destruction

CBusStation_ClientView::CBusStation_ClientView()
{
	// TODO: add construction code here
	m_setClient = 0;
	OnConnect();
}

CBusStation_ClientView::~CBusStation_ClientView()
{

}

BOOL CBusStation_ClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientView drawing

void CBusStation_ClientView::OnDraw(CDC* dc)
{
	CMemDC pDC(dc);
	CBusStation_ClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	int i=0;
	int j=0;
	int temp_time = 0;
	int temp=0;
	int beforeST=0;
	int recentTime[MAX_BUS];
	int rrTime[3];
	int rrPeople[3];
	CString BusInfo;
	CString TimeInfo[3];

	// Background Bitmap Image Printing by yhk
	CDC cdc;
	cdc.CreateCompatibleDC(pDC);
	cdc.SelectObject(&m_bCurImage);
	pDC->BitBlt(0,0,691,356,&cdc,0,0,SRCCOPY);

	for(i=0;i<MAX_BUS;i++){
		recentTime[i] = 100000;
	}

	// 버스 도착 예정 시간 안내 부분
	for(i=0;i<MAX_STATION;i++){
		for(j=0;j<MAX_BUS;j++){
			if(((MAX_STATION+m_setClient) - i)%MAX_STATION == m_insSet.myBus[j].intPos){
				if(m_insSet.myBus[j].whichIn == 1){
					temp_time = 0;
				}
				else if(m_insSet.myBus[j].whichIn == 2){
					temp_time = -2;
				}

				if(recentTime[j]>(temp_time+i*4)){
					recentTime[j] = temp_time+i*4;
				}
			}
		}
	}

	for(i=0;i<MAX_STATION;i++){
		if(recentTime[i] ==-2){
			recentTime[i] = (MAX_STATION-1)*4 +2;
		}
	}

	for(i=0;i<3;i++){
		rrTime[i] = 10000;
		rrPeople[i] = 0;
		for(j=0;j<MAX_BUS;j++){
			if(m_insSet.myBus[j].type == i+1){
				if(rrTime[i]>recentTime[j]){
					rrTime[i] = recentTime[j];
					rrPeople[i] = m_insSet.myBus[j].intPeople;
				}
			}
		}
	}

	for(i=0;i<3;i++){
		CDC ppl_cdc;
		ppl_cdc.CreateCompatibleDC(pDC);
		if(rrPeople[i]>=40){
			ppl_cdc.SelectObject(&m_pRed);
		}
		else if(rrPeople[i]>=20){
			ppl_cdc.SelectObject(&m_pYellow);
		}
		else{
			ppl_cdc.SelectObject(&m_pGreen);
		}
		pDC->BitBlt(380,45+(60*i),57,52,&ppl_cdc,0,0,SRCCOPY);
	}
	
	for(i=0;i<3;i++){
		CString people;
		people.Format("%d",rrPeople[i]);
		pDC->TextOut(375,90+(60*i),people);
	}

	TimeInfo[0].Format("일반 버스 도착 %d분 남았습니다.",rrTime[0]);
	if(rrTime[0]==0){
		TimeInfo[0].Format("일반 버스가 도착하였습니다.");
		SoundSwitch[0] = FALSE;
	}
	if(rrTime[0]==2 && SoundSwitch[0] == FALSE){
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
		SoundSwitch[0] = TRUE;
 	}
	pDC->TextOut(50,70,TimeInfo[0]);
	TimeInfo[1].Format("장애인 버스 도착 %d분 남았습니다.",rrTime[1]);
	if(rrTime[1]==0){
		TimeInfo[1].Format("장애인 버스가 도착하였습니다.");
		SoundSwitch[1] = FALSE;
	}
	if(rrTime[1]==2 && SoundSwitch[1] == FALSE){
		PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);
		SoundSwitch[1] = TRUE;
 	}
	pDC->TextOut(50,130,TimeInfo[1]);
	TimeInfo[2].Format("테마 버스 도착 %d분 남았습니다.",rrTime[2]);
	if(rrTime[2]==0){
		TimeInfo[2].Format("테마 버스가 도착하였습니다.");
		SoundSwitch[2] = FALSE;
	}
	if(rrTime[2]==2 && SoundSwitch[2] == FALSE){
		PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC);
		SoundSwitch[2] = TRUE;
 	}
	pDC->TextOut(50,190,TimeInfo[2]);

	for(i=0;i<MAX_BUS;i++){
		CDC bus_cdc;
		bus_cdc.CreateCompatibleDC(pDC);
		switch(m_insSet.myBus[i].type){
		case 1:
			bus_cdc.SelectObject(&m_bBlueBus);
			break;
		case 2:
			bus_cdc.SelectObject(&m_bGreenBus);
			break;
		case 3:
			bus_cdc.SelectObject(&m_bRedBus);
			break;
		default :
			bus_cdc.SelectObject(&m_bBlueBus);
			break;
		}
		

		switch(m_insSet.myBus[i].type){
		case 1:
			BusInfo = "일";
			break;
		case 2:
			BusInfo = "장";
			break;
		case 3:
			BusInfo = "테";
			break;
		default :
			BusInfo = "?";
			break;
		}

		if(m_setClient-2<0){
			temp = MAX_STATION + (m_setClient - 2);
		}
		else{
			temp = m_setClient - 2;
		}


		// 버스 이동 부분
		if(m_insSet.myBus[i].whichIn==1){
			if(temp == m_insSet.myBus[i].intPos){
				//pDC->TextOut(55,280,BusInfo);
				pDC->BitBlt(10,270,87,26,&bus_cdc,0,0,SRCCOPY);
				//pDC->Rectangle(35,280,45,290);
			}
			else if((temp+1)%MAX_STATION == m_insSet.myBus[i].intPos){
				//pDC->TextOut(355,280,BusInfo);
				pDC->BitBlt(305,270,87,26,&bus_cdc,0,0,SRCCOPY);
				//pDC->Rectangle(335,280,345,290);
			}
			else if((temp+2)%MAX_STATION == m_insSet.myBus[i].intPos){
				//pDC->TextOut(665,280,BusInfo);
				pDC->BitBlt(590,270,87,26,&bus_cdc,0,0,SRCCOPY);
				//pDC->Rectangle(645,280,655,290);
			}
		}
		else{
			if(temp == m_insSet.myBus[i].intPos){
				//pDC->TextOut(205,280,BusInfo);
				pDC->BitBlt(155,270,87,26,&bus_cdc,0,0,SRCCOPY);
				//pDC->Rectangle(185,280,195,290);
			}
			else if((temp+1)%MAX_STATION == m_insSet.myBus[i].intPos){
				//pDC->TextOut(535,280,BusInfo);
				pDC->BitBlt(480,270,87,26,&bus_cdc,0,0,SRCCOPY);
				//pDC->Rectangle(515,280,525,290);
			}
		}
	}

	CString intro;
	intro.Format("반갑습니다. 현재 %d번 정류장입니다.",m_setClient);
	pDC->TextOut(30,25,intro);

	CString moPoint;
	moPoint.Format("[%d,%d]",m_moPoint.x,m_moPoint.y);
	pDC->TextOut(m_moPoint.x,m_moPoint.y,moPoint);

	// 날씨 
	CString temp2;
	CDC wt;
 	wt.CreateCompatibleDC(pDC);

	switch(m_insSet.myWeather.type){
	case 1:
		wt.SelectObject(&m_wtSun);
		break;
	case 2:
		wt.SelectObject(&m_wtCloud);
		break;
	case 3:
		wt.SelectObject(&m_wtRain);
		break;
	case 4:
		wt.SelectObject(&m_wtSnow);
		break;
	}
	pDC->BitBlt(480,40,150,150,&wt,0,0,SRCCOPY);

	// LOGFONT로부터 글꼴을 생성
	CFont newFont, *pOldFont;
	newFont.CreateFontIndirect(&m_logFont);
	// 생성된 글꼴을 DC에 선택
	pOldFont = (CFont *)pDC->SelectObject(&newFont);
	// 텍스트의 전경색과 배경색 설정
	pDC->SetTextColor(m_colorText);
	// 배경 모드를 설정
	if(m_bTransparent) 
		pDC->SetBkMode(TRANSPARENT);
	else 
		pDC->SetBkMode(OPAQUE);
	
	CString temp3 = "현재 / 최고 / 최저";
	temp2.Format("%d℃  %d℃  %d℃", m_insSet.myWeather.temperature, m_insSet.myWeather.temperature2, m_insSet.myWeather.temperature3);
	pDC->TextOut(470, 175, temp3);
	pDC->TextOut(475, 200, temp2);

}

/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientView diagnostics

#ifdef _DEBUG
void CBusStation_ClientView::AssertValid() const
{
	CView::AssertValid();
}

void CBusStation_ClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBusStation_ClientDoc* CBusStation_ClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBusStation_ClientDoc)));
	return (CBusStation_ClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBusStation_ClientView message handlers

void CBusStation_ClientView::OnConnect()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

    //소켓 생성
    g_ClientSocket = socket(PF_INET, SOCK_STREAM, 0);
    //if(g_ClientSocket == INVALID_SOCKET)     AddStringToList(g_hwndList, "Socket Error");
 
     //서버주소 초기화
     SOCKADDR_IN  servAddr;
     memset(&servAddr, 0, sizeof(servAddr));
     servAddr.sin_family = AF_INET;
     servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
     servAddr.sin_port = htons(atoi("9000"));
 
     if(connect(g_ClientSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR){
	 }
 
	hThread = AfxBeginThread(RecvMSG, this, THREAD_PRIORITY_NORMAL, 0 , CREATE_SUSPENDED);
	hThread->ResumeThread();

}


UINT RecvMSG(void *arg)
{
	CBusStation_ClientView* pArg = (CBusStation_ClientView*)arg;
	while(1)
	{
		recv(pArg->g_ClientSocket, (char*)&(pArg->m_insSet), sizeof(stINSSET), 0);
	}
	return 0;
}

void CBusStation_ClientView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	CView::OnTimer(nIDEvent);
}

void CBusStation_ClientView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
		
	// TODO: Add your specialized code here and/or call the base class
	SetTimer(1,100,NULL);
	CBusStation_ClientDoc* pDoc;
	pDoc = (CBusStation_ClientDoc*)GetDocument();
		
	// Background Bitmap Image Printing by yhk
	m_bCurImage.LoadBitmap(IDB_BACKGROUND);
	m_bBlueBus.LoadBitmap(IDB_BLUEBUS);
	m_bGreenBus.LoadBitmap(IDB_GREENBUS);
	m_bRedBus.LoadBitmap(IDB_REDBUS);
	m_pGreen.LoadBitmap(IDB_PGREEN);
	m_pYellow.LoadBitmap(IDB_PYELLOW);
	m_pRed.LoadBitmap(IDB_PRED);

	m_wtSun.LoadBitmap(IDB_BITMAP2);
	m_wtCloud.LoadBitmap(IDB_BITMAP4);
	m_wtRain.LoadBitmap(IDB_BITMAP3);
	m_wtSnow.LoadBitmap(IDB_BITMAP1);

	SoundSwitch[0] = FALSE;
	SoundSwitch[1] = FALSE;
	SoundSwitch[2] = FALSE;

	m_bTransparent = TRUE;
	
	m_colorText = RGB(0, 0, 255);
	m_logFont.lfHeight  = 30;
	m_logFont.lfWidth  = 0;
	m_logFont.lfEscapement = 0;
	m_logFont.lfOrientation = 0;
	m_logFont.lfWeight  = FW_NORMAL;
	m_logFont.lfItalic  = FALSE;
	m_logFont.lfUnderline = FALSE;
	m_logFont.lfStrikeOut = FALSE;
	m_logFont.lfCharSet  = DEFAULT_CHARSET;
	m_logFont.lfOutPrecision = OUT_CHARACTER_PRECIS;
	m_logFont.lfClipPrecision = CLIP_CHARACTER_PRECIS;
	m_logFont.lfQuality  = DEFAULT_QUALITY;
	m_logFont.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
	strcpy(m_logFont.lfFaceName, _T("맑은 고딕"));
	m_bkText = RGB(224, 192, 0);
	
}

void CBusStation_ClientView::OnSetting() 
{
	// TODO: Add your command handler code here
	CSettingDlg myDlg;
	myDlg.m_setSTNum = m_setClient;
	if(myDlg.DoModal() == IDOK){
		m_setClient = myDlg.m_setSTNum;
		Invalidate();
	}
	
}

void CBusStation_ClientView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	m_moPoint = point;
//	Invalidate(FALSE);
	CView::OnLButtonDown(nFlags, point);
}

BOOL CBusStation_ClientView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return FALSE;
}

void CBusStation_ClientView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnRButtonDown(nFlags, point);
}
