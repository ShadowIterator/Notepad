
// Notepad.h : Notepad Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CNotepadApp:
// �йش����ʵ�֣������ Notepad.cpp
//

class CNotepadApp : public CWinApp
{
public:
	CNotepadApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNotepadApp theApp;
