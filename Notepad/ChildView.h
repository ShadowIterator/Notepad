
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

#include "kernal.h"
// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

//Text class
public:
	SITEXT* m_text;
public:
	void m_paintText(CPaintDC& dc);
	void m_paintCur(CPaintDC& dc);
};

