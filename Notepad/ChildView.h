
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

#include "kernal.h"
#include "M_PARA_DIA.h"
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

//keyboard message map
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	inline bool is_input(UINT nChar);


//changed so need repaint
public:
	inline void m_changed();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

//flags
private:
	bool LBuDown;

//other key messages
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

