// m_back_color.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Notepad.h"
#include "m_back_color.h"
#include "afxdialogex.h"


// m_back_color �Ի���

IMPLEMENT_DYNAMIC(m_back_color, CDialogEx)

m_back_color::m_back_color(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BACKGROND_COLOR, pParent)
{
}

m_back_color::~m_back_color()
{
}

void m_back_color::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_colorPicker);
}


BEGIN_MESSAGE_MAP(m_back_color, CDialogEx)
	ON_BN_CLICKED(IDOK, &m_back_color::OnBnClickedOk)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &m_back_color::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// m_back_color ��Ϣ�������


void m_back_color::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void m_back_color::OnBnClickedMfccolorbutton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	color = m_colorPicker.GetColor();
	if (color == -1)
	{
		color = m_colorPicker.GetAutomaticColor();
	}
}
