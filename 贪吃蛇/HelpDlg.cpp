// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "̰����.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// CHelpDlg �Ի���

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


// CHelpDlg ��Ϣ�������


BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str;
	str = _T("\r\n��ο�ʼ:\r\n\r\n����Ϸ����[��ʼ]���ɽ�����Ϸ��\r\n\r\n\r\n����ָ��:\r\n\r\nctrl+N\t����Ϸ\t\tctrl+S\t��ʼ \r\n\r\nctrl+P\t��ͣ\t\tctrl+I\t����\r\n\r\nctrl+H\t����\t\tAlt+F4\t�˳�\r\n\r\n\r\n��Ϸ����:\r\n\r\n��������̰������Ϸ���������ҷ��������̰�����ƶ�����\r\n\r\n\r\n��ϷĿ��:\r\n\r\n����̰���߳Ե������ܶ��ʳ�ÿ��һ��ʳ���ʮ�֡��Ե�Խ�࣬�÷־�Խ�ߣ�\r\n�����Խ��Ŷ~~\r\n���Ǽǵùܺ������ͷ���� ����ͷ����ǽ�ڻ��ǽӴ�������ʱ����Ϸ�ͽ����ˣ�");
	GetDlgItem(IDC_Ehelp)->SetWindowTextW(str);
	GetDlgItem(IDC_Ehelp)->EnableWindow(FALSE);
	/*
	// TODO:  �ڴ˸��� DC ���κ�����
	CFont font;
	font.CreateFont(20, 20, 0, 0, FW_BLACK, FALSE, FALSE,
		FALSE, GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN, _T("����"));
	// TODO:  �ڴ˸��� DC ���κ�����
	//pDC->SetTextColor(RGB(255, 0, 0)); //����ɫ
	 */
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


HBRUSH CHelpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
