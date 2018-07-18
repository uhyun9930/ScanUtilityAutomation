
// SU_auto2.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "SU_auto2.h"
#include "SU_auto2Dlg.h"
//#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//using namespace std;

// CSU_auto2App

BEGIN_MESSAGE_MAP(CSU_auto2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSU_auto2App 생성

CSU_auto2App::CSU_auto2App()
{
	// 다시 시작 관리자 지원
	pinfo.hProcess=NULL;
	pinfo.hThread=NULL;
	pinfo.dwProcessId=0L;
	pinfo.dwThreadId=0L;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CSU_auto2App 개체입니다.

CSU_auto2App theApp;


// CSU_auto2App 초기화


BOOL CSU_auto2App::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	ExecuteOutsideEditor(); //SU_OPEN
	//WindowCheck(CString strWindowName, CRect& WindowRect);

	AfxEnableControlContainer();
	
	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	CSU_auto2Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}
	
	
	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}


int CSU_auto2App::ExecuteOutsideEditor()
{

	STARTUPINFO sinfo;
	//CString szCmdLine; 
	//szCmdLine.Format("c:\\Windows\\notepad.exe c:\\help.txt");
	

	LPTSTR szCmdline=_tcsdup(TEXT("C:\\Program Files\\Canon\\MF Scan Utility\\MFSCANUTILITY.exe")); //SU 위치 저장 

	if(IsOutsideEditorRunning())
		return -2;
	memset(&sinfo, 0x00, sizeof(sinfo)); 

	if(CreateProcess(NULL, szCmdline, NULL, NULL, FALSE, 0, NULL, NULL, &sinfo, &pinfo))
		return -1;

	else
		return 0;

}


int CSU_auto2App::IsOutsideEditorRunning()
{
	unsigned long l;
	if(pinfo.hProcess)
	{
		GetExitCodeProcess(pinfo.hProcess, &l);
		if(l==STILL_ACTIVE)
			return -1;
	}

	return 0;
}
