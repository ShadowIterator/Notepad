#pragma once
#include "afxcolorbutton.h"
#include "ChildView.h"
#include "kernal.h"
#include "m_back_color.h"
#include "MainFrm.h"
#include "Notepad.h"

// m_back_color �Ի���

class m_back_color : public CDialogEx
{
	DECLARE_DYNAMIC(m_back_color)

public:
	m_back_color(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~m_back_color();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BACKGROND_COLOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

//color
public:
	COLORREF color;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMfccolorbutton1();
	CMFCColorButton m_colorPicker;
};
