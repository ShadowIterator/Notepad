
// Notepad.h : Notepad Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "kernal.h"

// CNotepadApp:
// �йش����ʵ�֣������ Notepad.cpp
//

class CNotepadApp : public CWinApp
{
public:
	CNotepadApp();
	CMainFrame* mainp;

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

//font dialoge
public:
	afx_msg void OnFont();
//para dialoge
public:
	afx_msg void OnPara();

//cut/copy/paste
public:
	afx_msg void OnCut();
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	afx_msg void OnBackColor();
	SIRANGE m_cutBoard;

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNotepadApp theApp;
