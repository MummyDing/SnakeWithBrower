
// ̰����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "̰����.h"
#include "̰����Dlg.h"
#include "afxdialogex.h"
#include"HelpDlg.h"
#pragma comment(lib, "winmm.lib")
#include <Mmsystem.h>
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_str;
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Ehelp, m_str);
}

 
 


// C̰����Dlg �Ի���



C̰����Dlg::C̰����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C̰����Dlg::IDD, pParent)
	, m_start(false)
	, m_pause(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C̰����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C̰����Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_START, &C̰����Dlg::OnStart)
	ON_COMMAND(ID_PAUSE, &C̰����Dlg::OnPause)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_Internet, &C̰����Dlg::OnInternet)
	ON_COMMAND(ID_NewGame, &C̰����Dlg::OnNewgame)
	ON_COMMAND(ID_PlayMusic, &C̰����Dlg::OnPlaymusic)
	ON_COMMAND(ID_StopMumic, &C̰����Dlg::OnStopmumic)
	ON_COMMAND(ID_HELP, &C̰����Dlg::OnHelp)
END_MESSAGE_MAP()


// C̰����Dlg ��Ϣ�������

BOOL C̰����Dlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	PlaySound(_T("����.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	//hAccTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE("IDR_ACCELERATOR1"));
	hAccTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	m_start = false;
	m_pause = false;
	//���ñ༭��
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	//��ʾ��ǰʱ��
	CString str; //��ȡϵͳʱ�� ����
	tm = CTime::GetCurrentTime();
	str = tm.Format("%m��%d��%X");
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(str);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	//��ʼ������
	snake.n = 4;  snake.direction = 2;  snake.sorce = 0;  snake.MaxSorce = 0;
	snake.body[0].x = 2; snake.body[0].y = 5;
	snake.body[1].x = 2; snake.body[1].y = 4;
	snake.body[2].x = 2; snake.body[2].y = 3;
	snake.body[3].x = 2; snake.body[3].y = 2;
	//��ʼ��ʳ��
	unsigned seed = time(NULL);
	srand(seed);
	do{
		Bean.x = rand() % 47+1;
		Bean.y = rand() % 47+1;
	} while (Isinsnake());
	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 0, 0, 500, 600, SWP_NOZORDER);
	 
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	
	//��ʾ�˵�
	CMenu m_Menu;
		m_Menu.LoadMenu(IDR_MENU1);
		SetMenu(&m_Menu);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C̰����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C̰����Dlg::OnPaint()
{
	
	CDC *pDc=GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pDc);
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	dc.SelectObject(&bitmap);
	for (int i = 0; i < 48; i++){
		for (int j = 0; j < 48; j++){
			pDc->StretchBlt(10 * i, 10 * j, 10, 10, &dc, 0, 0, 88, 88,SRCCOPY);
		}
	}
	bitmap.Detach();
	CPen pen(PS_SOLID, 3, RGB(0, 120, 0));
	CPen *oldpen = pDc->SelectObject(&pen);
// ���±߿�
	pDc->MoveTo(0, 480);
   pDc->LineTo(480,480);
// ����߿�	
   pDc->MoveTo(0, 0);
	pDc->LineTo(0, 480);
//���ϱ߿�
	pDc->MoveTo(0, 1);
	pDc->LineTo(480,1);
//���ұ߿�
	pDc->MoveTo(480,0);
	pDc->LineTo(480, 480);
	pDc->SelectObject(oldpen);
		//����ͷ
		bitmap.LoadBitmapW(IDB_BITMAP2);
		dc.SelectObject(&bitmap);
		pDc->StretchBlt(10 + 10 * snake.body[0].y, 10 + 10 * snake.body[0].x, 10, 10, &dc, 0, 0, 38, 38, SRCCOPY);
		bitmap.Detach();
		//������
		bitmap.LoadBitmapW(IDB_BITMAP3);
		dc.SelectObject(&bitmap);
		for (int i = 1; i < snake.n; i++)
			pDc->StretchBlt(10 + 10 * snake.body[i].y, 10 + 10 * snake.body[i].x, 10, 10, &dc, 0, 0, 38, 38, SRCCOPY);
		bitmap.Detach();
		//��ʳ��
		bitmap.LoadBitmapW(IDB_BITMAP4);
		dc.SelectObject(&bitmap);
		pDc->StretchBlt(10 + 10 * Bean.y, 10 + 10 *Bean.x, 10, 10, &dc, 0, 0, 38, 38, SRCCOPY);
		bitmap.Detach();
		//���·���
		CString strsorce,strmax;
		strsorce.Format(TEXT("%d"),snake.sorce*10);
		strmax.Format(TEXT("%d"), snake.MaxSorce*10);
		GetDlgItem(IDC_EDIT1)->SetWindowTextW(strsorce);
		GetDlgItem(IDC_EDIT3)->SetWindowTextW(strmax);
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C̰����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void C̰����Dlg::OnStart()
{
	
	// TODO:  �ڴ���������������
	
	this->m_start = true;
	this->m_pause = false;
 
   SetTimer(1, 100, NULL);
}


void C̰����Dlg::OnPause()
{
	// TODO:  �ڴ���������������
	static int t = 1;
	if (t & 1){
		this->m_pause = true;
	}
	else {
		this->m_pause = false;
	}
	t++;
}


void C̰����Dlg::OnTimer(UINT_PTR nIDEvent)
{
	//���µ�ǰʱ��
	CString str;
	tm = CTime::GetCurrentTime();
	str = tm.Format("%m��%d��%X");
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(str);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
//	CDC *cdc = GetDC();
	//CDC dc;
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
 	if (m_start&&!m_pause)
	{
		CPoint temp;
		::CClientDC dc(this);
		CDC cdc;
		cdc.CreateCompatibleDC(&dc);
		CBitmap bitmap;
		switch (snake.direction){
		case 1:
			temp = snake.ForsnakeUp();
			break;
		case 2:temp=snake.ForsnakeRight();
			break;
		case 3:temp=snake.ForsnakeDown();
			break;
		case 4:temp=snake.ForsnakeLeft();
			break;
		}
		if (IsGameOver()){
			restart();
		}
		//������β
		bitmap.LoadBitmapW(IDB_BITMAP1);
		cdc.SelectObject(&bitmap);
		dc.StretchBlt(10 + 10 * temp.y, 10 + 10 * temp.x, 10, 10, &cdc, 0, 0, 40, 40, SRCCOPY);
		bitmap.Detach();
		//����ͷ
		bitmap.LoadBitmapW(IDB_BITMAP2);
		cdc.SelectObject(&bitmap);
		dc.StretchBlt(10 + 10 * snake.body[0].y, 10 +10 * snake.body[0].x, 10, 10, &cdc, 0, 0, 38, 38, SRCCOPY);
		bitmap.Detach();
	//������
		bitmap.LoadBitmapW(IDB_BITMAP3);
		cdc.SelectObject(&bitmap);
		for (int i = 1; i <snake.n; i++)
		dc.StretchBlt(10 + 10 * snake.body[i].y, 10 + 10 * snake.body[i].x, 10, 10, &cdc, 10,10, 38, 38, SRCCOPY);
		bitmap.Detach();
		if (Iseat()){
			//���·���
			snake.sorce++;
			CString strsorce;
			strsorce.Format(TEXT("%d"), snake.sorce*10);
			GetDlgItem(IDC_EDIT1)->SetWindowTextW(strsorce);

			snake.n++;
			snake.body[snake.n-1] = temp;
			dc.StretchBlt(10 + 10 * snake.body[snake.n - 1].y, 10 + 10 * snake.body[snake.n - 1].x, 10, 10, &cdc, 10, 10, 38, 38, SRCCOPY);
			bitmap.Detach();
			do{
				Bean.x = rand() % 46+1;
				Bean.y = rand() % 46+1;
			} while (Isinsnake());
			//��ʳ��
			bitmap.LoadBitmapW(IDB_BITMAP4);
			cdc.SelectObject(&bitmap);
			dc.StretchBlt(10 + 10 * Bean.y, 10 + 10 * Bean.x, 10, 10, &cdc, 0, 0, 38, 38, SRCCOPY);
			bitmap.Detach();
		}
	}


	CDialogEx::OnTimer(nIDEvent);
}


void C̰����Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nChar == VK_UP&&snake.direction!=1){
		snake.direction = 1;
	}
	if (nChar == VK_RIGHT&&snake.direction != 2){
		snake.direction = 2;
	}
	if (nChar == VK_DOWN&&snake.direction != 3){
		snake.direction = 3;
	}
	if (nChar == VK_LEFT&&snake.direction != 4){
		snake.direction = 4;
	}


	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}



//BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO:  �ڴ����ר�ô����/����û���
//	
//	return CDialogEx::PreTranslateMessage(pMsg);
//}


BOOL C̰����Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYFIRST <= pMsg->message&&pMsg->message <= WM_KEYLAST)
	{
		HACCEL hAccel =  hAccTable;
		if (hAccel && ::TranslateAccelerator(m_hWnd, hAccel, pMsg))
			return TRUE;
	}
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_UP&&snake.direction!=3)
		{
			snake.direction = 1;
		}
		if (pMsg->wParam == VK_RIGHT&&snake.direction != 4)
		{
			snake.direction = 2;
		}
		if (pMsg->wParam == VK_DOWN&&snake.direction != 1)
		{
			snake.direction = 3;
		}
		if (pMsg->wParam == VK_LEFT&&snake.direction != 2)
		{
			snake.direction = 4;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


bool C̰����Dlg::Isinsnake()
{
	for (int i = 0; i < snake.n; i++){
		if (Bean == snake.body[i])
			return true;
	}
	return false;
}


bool C̰����Dlg::Iseat()
{

	if (snake.body[0] == Bean)
		return true;
	return false;
}


bool C̰����Dlg::IsGameOver()
{
	if (snake.body[0].x == -2|| snake.body[0].x == 47|| snake.body[0].y == -2 || snake.body[0].y == 47 || Istoach())
		return true;
		return false;
}


bool C̰����Dlg::Istoach()
{
	for (int i = 1; i < snake.n;i++)
	if (snake.body[0] == snake.body[i])
		return true;
	return false;
}


void C̰����Dlg::restart()
{
	/*
	::CClientDC dc(this);
	CDC cdc;
	cdc.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	cdc.SelectObject(&bitmap);
	for (int i = 0; i < 28; i++){
		for (int j = 0; j < 28; j++){
			dc.StretchBlt(10 * i, 10 * j, 10, 10, &cdc, 0, 0, 88, 88, SRCCOPY);
		}
	}
	bitmap.Detach();
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen *oldpen = cdc.SelectObject(&pen);
	dc.MoveTo(0, 280);
	dc.LineTo(280, 280);
	dc.SelectObject(oldpen);

 */
	CString string;
 
	
	//��ʼ������
	snake.n = 4;  snake.direction = 2;
	snake.body[0].x = 2; snake.body[0].y = 5;
	snake.body[1].x = 2; snake.body[1].y = 4;
	snake.body[2].x = 2; snake.body[2].y = 3;
	snake.body[3].x = 2; snake.body[3].y = 2;
	//��ʼ��ʳ��
	unsigned seed = time(NULL);
	srand(seed);
	do{
		Bean.x = rand() % 46 + 1;
		Bean.y = rand() % 46 + 1;
	} while (Isinsnake());
	/*
	//��ʳ��
	bitmap.LoadBitmapW(IDB_BITMAP4);
	cdc.SelectObject(&bitmap);
	dc.StretchBlt(10 + 10 * Bean.y, 10 + 10 * Bean.x, 10, 10, &cdc, 0, 0, 38, 38, SRCCOPY);
	bitmap.Detach();*/
	m_start = false;
	m_pause = false;
	//������ʷ��߷�
	int tempmax = snake.MaxSorce*10, tempsorce = snake.sorce*10;
	if (snake.MaxSorce < snake.sorce)
		snake.MaxSorce = snake.sorce;
	snake.sorce = 0;
	OnPaint();

	string.Format(_T("\t���ε÷�:%d   \n\n\t��ʷ��߷�:%d"),tempsorce, tempmax); //��������װ���ַ�����
	MessageBox(string, _T("��Ϸ��������"), 1);


}


void C̰����Dlg::OnInternet()
{
	CMyDlg  *dlg = new CMyDlg;
	dlg->Create(IDD_Brower, this);                //��һ�������ǶԻ���ID��
	dlg->ShowWindow(SW_SHOW);
	PlaySound(NULL, NULL, SND_FILENAME);
}


void C̰����Dlg::OnNewgame()
{
	// TODO:  �ڴ���������������
	restart();
}


void C̰����Dlg::OnPlaymusic()
{
	// TODO:  �ڴ���������������
	PlaySound(_T("����.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}


void C̰����Dlg::OnStopmumic()
{
	// TODO:  �ڴ���������������
	PlaySound(NULL, NULL, SND_FILENAME);
}


void C̰����Dlg::OnHelp()
{
	// TODO:  �ڴ���������������
	CHelpDlg  *dlg = new CHelpDlg;
	dlg->Create(IDD_ABOUTBOX, this);                //��һ�������ǶԻ���ID��
	dlg->ShowWindow(SW_SHOW);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
