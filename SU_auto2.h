
// SU_auto2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSU_auto2App:
// �� Ŭ������ ������ ���ؼ��� SU_auto2.cpp�� �����Ͻʽÿ�.
//

class CSU_auto2App : public CWinApp
{
public:
	CSU_auto2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	int ExecuteOutsideEditor();
	int IsOutsideEditorRunning();
	//bool FirstInstance();
// �����Դϴ�.

protected:
	PROCESS_INFORMATION pinfo;
	//BOOL WindowCheck(CString strWindowName, CRect& WindowRect);
	DECLARE_MESSAGE_MAP()

};

extern CSU_auto2App theApp;