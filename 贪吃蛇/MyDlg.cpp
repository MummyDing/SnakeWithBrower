// MyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "贪吃蛇.h"
#include "MyDlg.h"
#include "afxdialogex.h"
#pragma comment(lib, "winmm.lib")
#include <Mmsystem.h>

// CMyDlg 对话框

IMPLEMENT_DYNAMIC(CMyDlg, CDialog)

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	m_brush.CreateSolidBrush(RGB(177, 200, 200));
	
}

CMyDlg::~CMyDlg()
{

}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_URL);
	DDX_Control(pDX, IDC_EXPLORER1, m_Brower);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDlg::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CMyDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyDlg::OnBnClickedButton4)
//	ON_WM_INITMENU()
ON_BN_CLICKED(IDC_BUTTON5, &CMyDlg::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON6, &CMyDlg::OnBnClickedButton6)
ON_BN_CLICKED(IDC_BUTTON7, &CMyDlg::OnBnClickedButton7)
ON_BN_CLICKED(IDC_BUTTON9, &CMyDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CMyDlg 消息处理程序


void CMyDlg::OnBnClickedButton1()
{
	  UpdateData(true);
	  CString str;
	  m_URL.GetWindowTextW(str);
		m_Brower.Navigate(str,NULL,NULL,NULL,NULL);
		str = _T("");
		GetDlgItem(IDC_EDIT1)->SetWindowTextW(str);   //清空地址栏
	// TODO:  在此添加控件通知处理程序代码
}


void CMyDlg::OnPaint()
{
 
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CDC    dcMem;
	dcMem.CreateCompatibleDC(&dc);    // 创建 内存dc
	CBitmap    bmp;
	bmp.LoadBitmap(IDB_BITMAP5);     //加载 图片

	BITMAP   bitmap;     //用这个对象 是因为可以得到图片的宽, 高, 看最后一句话
	bmp.GetBitmap(&bitmap);

	dcMem.SelectObject(&bmp);     // 把图片加载到 内存 dc
	CRect rect(0,0,3000,3000);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);     // 把内存dc里的内容 全部复制到 当前dc里来
}


HBRUSH CMyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_EDIT1 || pWnd->GetDlgCtrlID() == IDC_STATIC || pWnd->GetDlgCtrlID() == IDC_EXPLORER1)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_brush;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CMyDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Brower.GoBack();
}


void CMyDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Brower.GoForward();
}


void CMyDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Brower.GoHome();
}


//void CMyDlg::OnInitMenu(CMenu* pMenu)
//{
//	CDialog::OnInitMenu(pMenu);
//
//	// TODO:  在此处添加消息处理程序代码
//}


//BOOL CMyDlg::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//
//	// TODO:  在此添加额外的初始化
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// 异常:  OCX 属性页应返回 FALSE
//}


BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_Brower.Navigate(_T("baidu.com"), NULL, NULL, NULL, NULL);
	// TODO:  在此添加额外的初始化
	hAccTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR2));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CMyDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Brower.Refresh();
}


void CMyDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Brower.Stop();
}


void CMyDlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Brower.GoSearch();
}


BOOL CMyDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类

	if (WM_KEYFIRST <= pMsg->message&&pMsg->message <= WM_KEYLAST)
	{
		HACCEL hAccel = hAccTable;
		if (hAccel && ::TranslateAccelerator(m_hWnd, hAccel, pMsg))
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CMyDlg::OnBnClickedButton9()
{
	// TODO:  在此添加控件通知处理程序代码
	static int t = 1;
	if (t%2)
	PlaySound(_T("小苹果.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	else 
		PlaySound(NULL, NULL, SND_FILENAME);
	t++;
}
