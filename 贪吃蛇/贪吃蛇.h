
// 贪吃蛇.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// C贪吃蛇App: 
// 有关此类的实现，请参阅 贪吃蛇.cpp
//

class C贪吃蛇App : public CWinApp
{
public:
	C贪吃蛇App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	afx_msg void OnInternet();
};

extern C贪吃蛇App theApp;