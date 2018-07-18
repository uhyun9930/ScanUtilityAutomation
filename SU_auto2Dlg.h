
// SU_auto2Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CSU_auto2Dlg 대화 상자
class CSU_auto2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CSU_auto2Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SU_AUTO2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
