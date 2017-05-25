#pragma once

#include "ChildView.h"
#include "kernal.h"
#include "MainFrm.h"
#include "Notepad.h"
#include "resource.h"
// M_PARA_DIA �Ի���

class M_PARA_DIA : public CDialogEx
{
	DECLARE_DYNAMIC(M_PARA_DIA)

public:
	M_PARA_DIA(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~M_PARA_DIA();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARA_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnUpdateLine();
	afx_msg void OnEnUpdateCharac();
	afx_msg void OnBnClickedOk();
	int m_linespace;
	int m_charaspace;
};
