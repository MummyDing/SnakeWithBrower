// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "贪吃蛇.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelpDlg::IDD, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序


BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str;
	str = _T("\r\n如何开始:\r\n\r\n打开游戏后点击[开始]即可进行游戏。\r\n\r\n\r\n操作指南:\r\n\r\nctrl+N\t新游戏\t\tctrl+S\t开始 \r\n\r\nctrl+P\t暂停\t\tctrl+I\t上网\r\n\r\nctrl+H\t帮助\t\tAlt+F4\t退出\r\n\r\n\r\n游戏介绍:\r\n\r\n经典好玩的贪吃蛇游戏。上下左右方向键控制贪吃蛇移动方向。\r\n\r\n\r\n游戏目标:\r\n\r\n控制贪吃蛇吃到尽可能多的食物，每吃一个食物得十分。吃的越多，得分就越高，\r\n蛇身就越长哦~~\r\n但是记得管好你的蛇头！！ 当蛇头碰到墙壁或是接触到身体时，游戏就结束了！");
	GetDlgItem(IDC_Ehelp)->SetWindowTextW(str);
	GetDlgItem(IDC_Ehelp)->EnableWindow(FALSE);
	/*
	// TODO:  在此更改 DC 的任何特性
	CFont font;
	font.CreateFont(20, 20, 0, 0, FW_BLACK, FALSE, FALSE,
		FALSE, GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN, _T("隶书"));
	// TODO:  在此更改 DC 的任何特性
	//pDC->SetTextColor(RGB(255, 0, 0)); //改颜色
	 */
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CHelpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
