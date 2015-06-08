
// 贪吃蛇Dlg.h : 头文件
//
#include "Csnake.h"
#include"Oxy.h"
#include"MyDlg.h"
#pragma once


// C贪吃蛇Dlg 对话框
class C贪吃蛇Dlg : public CDialogEx
{
// 构造
public:
	C贪吃蛇Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	bool m_start;
	bool m_pause;
public:
	afx_msg void OnStart();
	afx_msg void OnPause();
	Csnake snake;
	CPoint Bean;
	CTime tm;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool Isinsnake();
	bool Iseat();
	bool IsGameOver();
	bool Istoach();
	void restart();
	afx_msg void OnInternet();
	HACCEL hAccTable;
	afx_msg void OnNewgame();
	afx_msg void OnPlaymusic();
	afx_msg void OnStopmumic();
	afx_msg void OnHelp();
};
