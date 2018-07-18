
// SU_auto2Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CSU_auto2Dlg ��ȭ ����
class CSU_auto2Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSU_auto2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SU_AUTO2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox ModeCombo;
	CComboBox InputCombo;
	CComboBox SizeCombo;
	CComboBox ColorMode;
	CComboBox ResolutionCombo;
	CComboBox PrintSizeCombo;
	CComboBox DataTypeCombo;
	afx_msg void AddValueButton();
	CListBox ListBox;
	afx_msg void DeleteButton();
	afx_msg void OnBnClickedOk();
	//bool FirstInstance();
	CWnd FirstInstance();
	LRESULT CSU_auto2Dlg::OnMSG(WPARAM wParam, LPARAM lParam);
};
