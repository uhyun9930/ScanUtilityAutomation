
// SU_auto2.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CSU_auto2App:
// 이 클래스의 구현에 대해서는 SU_auto2.cpp을 참조하십시오.
//

class CSU_auto2App : public CWinApp
{
public:
	CSU_auto2App();

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	int ExecuteOutsideEditor();
	int IsOutsideEditorRunning();
	//bool FirstInstance();
// 구현입니다.

protected:
	PROCESS_INFORMATION pinfo;
	//BOOL WindowCheck(CString strWindowName, CRect& WindowRect);
	DECLARE_MESSAGE_MAP()

};

extern CSU_auto2App theApp;