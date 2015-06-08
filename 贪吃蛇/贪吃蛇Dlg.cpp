
// 贪吃蛇Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "贪吃蛇.h"
#include "贪吃蛇Dlg.h"
#include "afxdialogex.h"
#include"HelpDlg.h"
#pragma comment(lib, "winmm.lib")
#include <Mmsystem.h>
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


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

 
 


// C贪吃蛇Dlg 对话框



C贪吃蛇Dlg::C贪吃蛇Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C贪吃蛇Dlg::IDD, pParent)
	, m_start(false)
	, m_pause(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C贪吃蛇Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C贪吃蛇Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_START, &C贪吃蛇Dlg::OnStart)
	ON_COMMAND(ID_PAUSE, &C贪吃蛇Dlg::OnPause)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_Internet, &C贪吃蛇Dlg::OnInternet)
	ON_COMMAND(ID_NewGame, &C贪吃蛇Dlg::OnNewgame)
	ON_COMMAND(ID_PlayMusic, &C贪吃蛇Dlg::OnPlaymusic)
	ON_COMMAND(ID_StopMumic, &C贪吃蛇Dlg::OnStopmumic)
	ON_COMMAND(ID_HELP, &C贪吃蛇Dlg::OnHelp)
END_MESSAGE_MAP()


// C贪吃蛇Dlg 消息处理程序

BOOL C贪吃蛇Dlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	PlaySound(_T("欢沁.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	//hAccTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE("IDR_ACCELERATOR1"));
	hAccTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	m_start = false;
	m_pause = false;
	//禁用编辑框
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	//显示当前时间
	CString str; //获取系统时间 　　
	tm = CTime::GetCurrentTime();
	str = tm.Format("%m月%d日%X");
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(str);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	//初始化蛇身
	snake.n = 4;  snake.direction = 2;  snake.sorce = 0;  snake.MaxSorce = 0;
	snake.body[0].x = 2; snake.body[0].y = 5;
	snake.body[1].x = 2; snake.body[1].y = 4;
	snake.body[2].x = 2; snake.body[2].y = 3;
	snake.body[3].x = 2; snake.body[3].y = 2;
	//初始化食物
	unsigned seed = time(NULL);
	srand(seed);
	do{
		Bean.x = rand() % 47+1;
		Bean.y = rand() % 47+1;
	} while (Isinsnake());
	// 将“关于...”菜单项添加到系统菜单中。
	::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 0, 0, 500, 600, SWP_NOZORDER);
	 
	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO:  在此添加额外的初始化代码
	
	//显示菜单
	CMenu m_Menu;
		m_Menu.LoadMenu(IDR_MENU1);
		SetMenu(&m_Menu);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C贪吃蛇Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C贪吃蛇Dlg::OnPaint()
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
// 画下边框
	pDc->MoveTo(0, 480);
   pDc->LineTo(480,480);
// 画左边框	
   pDc->MoveTo(0, 0);
	pDc->LineTo(0, 480);
//画上边框
	pDc->MoveTo(0, 1);
	pDc->LineTo(480,1);
//画右边框
	pDc->MoveTo(480,0);
	pDc->LineTo(480, 480);
	pDc->SelectObject(oldpen);
		//画蛇头
		bitmap.LoadBitmapW(IDB_BITMAP2);
		dc.SelectObject(&bitmap);
		pDc->StretchBlt(10 + 10 * snake.body[0].y, 10 + 10 * snake.body[0].x, 10, 10, &dc, 0, 0, 38, 38, SRCCOPY);
		bitmap.Detach();
		//画蛇身
		bitmap.LoadBitmapW(IDB_BITMAP3);
		dc.SelectObject(&bitmap);
		for (int i = 1; i < snake.n; i++)
			pDc->StretchBlt(10 + 10 * snake.body[i].y, 10 + 10 * snake.body[i].x, 10, 10, &dc, 0, 0, 38, 38, SRCCOPY);
		bitmap.Detach();
		//画食物
		bitmap.LoadBitmapW(IDB_BITMAP4);
		dc.SelectObject(&bitmap);
		pDc->StretchBlt(10 + 10 * Bean.y, 10 + 10 *Bean.x, 10, 10, &dc, 0, 0, 38, 38, SRCCOPY);
		bitmap.Detach();
		//更新分数
		CString strsorce,strmax;
		strsorce.Format(TEXT("%d"),snake.sorce*10);
		strmax.Format(TEXT("%d"), snake.MaxSorce*10);
		GetDlgItem(IDC_EDIT1)->SetWindowTextW(strsorce);
		GetDlgItem(IDC_EDIT3)->SetWindowTextW(strmax);
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C贪吃蛇Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void C贪吃蛇Dlg::OnStart()
{
	
	// TODO:  在此添加命令处理程序代码
	
	this->m_start = true;
	this->m_pause = false;
 
   SetTimer(1, 100, NULL);
}


void C贪吃蛇Dlg::OnPause()
{
	// TODO:  在此添加命令处理程序代码
	static int t = 1;
	if (t & 1){
		this->m_pause = true;
	}
	else {
		this->m_pause = false;
	}
	t++;
}


void C贪吃蛇Dlg::OnTimer(UINT_PTR nIDEvent)
{
	//更新当前时间
	CString str;
	tm = CTime::GetCurrentTime();
	str = tm.Format("%m月%d日%X");
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(str);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
//	CDC *cdc = GetDC();
	//CDC dc;
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
		//覆盖蛇尾
		bitmap.LoadBitmapW(IDB_BITMAP1);
		cdc.SelectObject(&bitmap);
		dc.StretchBlt(10 + 10 * temp.y, 10 + 10 * temp.x, 10, 10, &cdc, 0, 0, 40, 40, SRCCOPY);
		bitmap.Detach();
		//画蛇头
		bitmap.LoadBitmapW(IDB_BITMAP2);
		cdc.SelectObject(&bitmap);
		dc.StretchBlt(10 + 10 * snake.body[0].y, 10 +10 * snake.body[0].x, 10, 10, &cdc, 0, 0, 38, 38, SRCCOPY);
		bitmap.Detach();
	//画蛇身
		bitmap.LoadBitmapW(IDB_BITMAP3);
		cdc.SelectObject(&bitmap);
		for (int i = 1; i <snake.n; i++)
		dc.StretchBlt(10 + 10 * snake.body[i].y, 10 + 10 * snake.body[i].x, 10, 10, &cdc, 10,10, 38, 38, SRCCOPY);
		bitmap.Detach();
		if (Iseat()){
			//更新分数
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
			//画食物
			bitmap.LoadBitmapW(IDB_BITMAP4);
			cdc.SelectObject(&bitmap);
			dc.StretchBlt(10 + 10 * Bean.y, 10 + 10 * Bean.x, 10, 10, &cdc, 0, 0, 38, 38, SRCCOPY);
			bitmap.Detach();
		}
	}


	CDialogEx::OnTimer(nIDEvent);
}


void C贪吃蛇Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
//	// TODO:  在此添加专用代码和/或调用基类
//	
//	return CDialogEx::PreTranslateMessage(pMsg);
//}


BOOL C贪吃蛇Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYFIRST <= pMsg->message&&pMsg->message <= WM_KEYLAST)
	{
		HACCEL hAccel =  hAccTable;
		if (hAccel && ::TranslateAccelerator(m_hWnd, hAccel, pMsg))
			return TRUE;
	}
	// TODO:  在此添加专用代码和/或调用基类
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


bool C贪吃蛇Dlg::Isinsnake()
{
	for (int i = 0; i < snake.n; i++){
		if (Bean == snake.body[i])
			return true;
	}
	return false;
}


bool C贪吃蛇Dlg::Iseat()
{

	if (snake.body[0] == Bean)
		return true;
	return false;
}


bool C贪吃蛇Dlg::IsGameOver()
{
	if (snake.body[0].x == -2|| snake.body[0].x == 47|| snake.body[0].y == -2 || snake.body[0].y == 47 || Istoach())
		return true;
		return false;
}


bool C贪吃蛇Dlg::Istoach()
{
	for (int i = 1; i < snake.n;i++)
	if (snake.body[0] == snake.body[i])
		return true;
	return false;
}


void C贪吃蛇Dlg::restart()
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
 
	
	//初始化蛇身
	snake.n = 4;  snake.direction = 2;
	snake.body[0].x = 2; snake.body[0].y = 5;
	snake.body[1].x = 2; snake.body[1].y = 4;
	snake.body[2].x = 2; snake.body[2].y = 3;
	snake.body[3].x = 2; snake.body[3].y = 2;
	//初始化食物
	unsigned seed = time(NULL);
	srand(seed);
	do{
		Bean.x = rand() % 46 + 1;
		Bean.y = rand() % 46 + 1;
	} while (Isinsnake());
	/*
	//画食物
	bitmap.LoadBitmapW(IDB_BITMAP4);
	cdc.SelectObject(&bitmap);
	dc.StretchBlt(10 + 10 * Bean.y, 10 + 10 * Bean.x, 10, 10, &cdc, 0, 0, 38, 38, SRCCOPY);
	bitmap.Detach();*/
	m_start = false;
	m_pause = false;
	//更新历史最高分
	int tempmax = snake.MaxSorce*10, tempsorce = snake.sorce*10;
	if (snake.MaxSorce < snake.sorce)
		snake.MaxSorce = snake.sorce;
	snake.sorce = 0;
	OnPaint();

	string.Format(_T("\t本次得分:%d   \n\n\t历史最高分:%d"),tempsorce, tempmax); //将变量组装到字符串中
	MessageBox(string, _T("游戏结束！！"), 1);


}


void C贪吃蛇Dlg::OnInternet()
{
	CMyDlg  *dlg = new CMyDlg;
	dlg->Create(IDD_Brower, this);                //第一个参数是对话框ID号
	dlg->ShowWindow(SW_SHOW);
	PlaySound(NULL, NULL, SND_FILENAME);
}


void C贪吃蛇Dlg::OnNewgame()
{
	// TODO:  在此添加命令处理程序代码
	restart();
}


void C贪吃蛇Dlg::OnPlaymusic()
{
	// TODO:  在此添加命令处理程序代码
	PlaySound(_T("欢心.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}


void C贪吃蛇Dlg::OnStopmumic()
{
	// TODO:  在此添加命令处理程序代码
	PlaySound(NULL, NULL, SND_FILENAME);
}


void C贪吃蛇Dlg::OnHelp()
{
	// TODO:  在此添加命令处理程序代码
	CHelpDlg  *dlg = new CHelpDlg;
	dlg->Create(IDD_ABOUTBOX, this);                //第一个参数是对话框ID号
	dlg->ShowWindow(SW_SHOW);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
