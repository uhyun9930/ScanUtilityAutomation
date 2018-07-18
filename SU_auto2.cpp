
// SU_auto2.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
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


// CSU_auto2App ����

CSU_auto2App::CSU_auto2App()
{
	// �ٽ� ���� ������ ����
	pinfo.hProcess=NULL;
	pinfo.hThread=NULL;
	pinfo.dwProcessId=0L;
	pinfo.dwThreadId=0L;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CSU_auto2App ��ü�Դϴ�.

CSU_auto2App theApp;


// CSU_auto2App �ʱ�ȭ


BOOL CSU_auto2App::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	ExecuteOutsideEditor(); //SU_OPEN
	//WindowCheck(CString strWindowName, CRect& WindowRect);

	AfxEnableControlContainer();
	
	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CSU_auto2Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}
	
	
	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}


int CSU_auto2App::ExecuteOutsideEditor()
{

	STARTUPINFO sinfo;
	//CString szCmdLine; 
	//szCmdLine.Format("c:\\Windows\\notepad.exe c:\\help.txt");
	

	LPTSTR szCmdline=_tcsdup(TEXT("C:\\Program Files\\Canon\\MF Scan Utility\\MFSCANUTILITY.exe")); //SU ��ġ ���� 

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
