
// SU_auto2Dlg.cpp : 구현 파일
//
#include "stdafx.h"
#include "SU_auto2.h"
#include "SU_auto2Dlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSU_auto2Dlg 대화 상자




CSU_auto2Dlg::CSU_auto2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSU_auto2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSU_auto2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, ModeCombo);
	DDX_Control(pDX, IDC_COMBO2, InputCombo);
	DDX_Control(pDX, IDC_COMBO3, SizeCombo);
	DDX_Control(pDX, IDC_COMBO4, ColorMode);
	DDX_Control(pDX, IDC_COMBO5, ResolutionCombo);
	DDX_Control(pDX, IDC_COMBO7, DataTypeCombo);
	DDX_Control(pDX, IDC_LIST1, ListBox);
}

BEGIN_MESSAGE_MAP(CSU_auto2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL3, &CSU_auto2Dlg::AddValueButton)
	ON_BN_CLICKED(IDCANCEL4, &CSU_auto2Dlg::DeleteButton)
	ON_BN_CLICKED(IDOK, &CSU_auto2Dlg::OnBnClickedOk)
	ON_MESSAGE(WM_CLIENT_MSG,OnMSG)
END_MESSAGE_MAP()


// CSU_auto2Dlg 메시지 처리기

BOOL CSU_auto2Dlg::OnInitDialog() //초기화
{
	CDialogEx::OnInitDialog();


	ModeCombo.AddString(_T("Document"));
	ModeCombo.AddString(_T("Photo"));
	ModeCombo.AddString(_T("Custom"));
	ModeCombo.AddString(_T("Stitch"));
	ModeCombo.AddString(_T("ScanGear"));
	ModeCombo.AddString(_T("OCR"));
	ModeCombo.AddString(_T("E-mail"));
	ModeCombo.SelectString(1, _T("Document"));

	InputCombo.AddString(_T("자동 모드"));
	InputCombo.AddString(_T("평판 유리"));
	InputCombo.AddString(_T("공급 장치"));
	InputCombo.SelectString(1, _T("자동 모드"));

	SizeCombo.AddString(_T("A3"));
	SizeCombo.AddString(_T("A4"));
	SizeCombo.AddString(_T("A4R"));
	SizeCombo.AddString(_T("A5"));
	SizeCombo.AddString(_T("A5R"));
	SizeCombo.AddString(_T("11x17"));
	SizeCombo.AddString(_T("Legal"));
	SizeCombo.AddString(_T("Letter"));
	SizeCombo.AddString(_T("LetterR"));
	SizeCombo.AddString(_T("Statement"));
	SizeCombo.SelectString(1, _T("A4"));

	ColorMode.AddString(_T("컬러"));
	ColorMode.AddString(_T("회색조"));
	ColorMode.AddString(_T("흑백"));
	ColorMode.SelectString(1, _T("컬러"));

	ResolutionCombo.AddString(_T("75dpi"));
	ResolutionCombo.AddString(_T("100dpi"));
	ResolutionCombo.AddString(_T("150dpi"));
	ResolutionCombo.AddString(_T("200dpi"));
	ResolutionCombo.AddString(_T("300dpi"));
	ResolutionCombo.SelectString(1, _T("200dpi"));

	DataTypeCombo.AddString(_T("JPEG/Exif"));
	DataTypeCombo.AddString(_T("TIFF"));
	DataTypeCombo.AddString(_T("PNG"));
	DataTypeCombo.AddString(_T("PDF"));
	DataTypeCombo.SelectString(1, _T("PNG"));


	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSU_auto2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSU_auto2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSU_auto2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CSU_auto2Dlg::AddValueButton() //추가 버튼 동작
{
	CString addValue[6];
	this->ModeCombo.GetLBText(this->ModeCombo.GetCurSel(), addValue[0]); 
	this->InputCombo.GetLBText(this->InputCombo.GetCurSel(), addValue[1]); 
	this->SizeCombo.GetLBText(this->SizeCombo.GetCurSel(), addValue[2]); 
	this->ColorMode.GetLBText(this->ColorMode.GetCurSel(), addValue[3]); 
	this->ResolutionCombo.GetLBText(this->ResolutionCombo.GetCurSel(), addValue[4]); 
	this->DataTypeCombo.GetLBText(this->DataTypeCombo.GetCurSel(), addValue[5]); 
	//콤보박스에서 선택된 값 배열에 입력



	int index=ListBox.InsertString(0,addValue[0]+", "+addValue[1]+", "+addValue[2]+", "+addValue[3]+", "+addValue[4]+", "+addValue[5]);
	ListBox.SetCurSel(index);
	//리스트박스에 값 입력

	//MessageBox(temp, _T("title")); //temp의 값을 alert창으로 띄움


}


void CSU_auto2Dlg::DeleteButton() //삭제 버튼 동작
{
	int index=ListBox.GetCurSel();
	ListBox.DeleteString(index);

}


void CSU_auto2Dlg::OnBnClickedOk() //확인 버튼 동작
{
	CDialogEx::OnOK(); 
	HWND bt_hwnd,c_hwnd=NULL, c2_hwnd=NULL;
	CString ProcessName;
	ProcessName.MakeUpper();


	HWND m_hwnd=::FindWindow(_T("#32770"), _T("Canon MF Scan Utility")); //TOP WINDOW
	int cnt = ListBox.GetCount();
	if(NULL != m_hwnd){
		bt_hwnd=::FindWindowEx(m_hwnd, NULL, _T("BUTTON"),_T("설정(&S)...")); // 설정 버튼의 핸들 
		if(NULL != bt_hwnd){
			::SendMessageA(bt_hwnd, BM_CLICK,0,0); //설정버튼 클릭 
		}


		HANDLE hSnapshot = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0); //정의된 플래그와 프로세스 id를 받아서 핸들을 넘겨줌

		if ((int)hSnapshot != -1)
		{
			PROCESSENTRY32 pe32;
			pe32.dwSize=sizeof(PROCESSENTRY32);
			BOOL bContinue;
			CString tempProcessName;
			HANDLE hProcess= NULL;
			if ( Process32First (hSnapshot, &pe32))
			{
				//프로세스 목록 검색 시작
				do
				{
					tempProcessName = pe32.szExeFile;  //프로세스 목록 중 비교할 프로세스 이름
					tempProcessName.MakeUpper();
					if((tempProcessName.Find(ProcessName, 0) != -1))
					{
						hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pe32.th32ProcessID);  //프로세스 핸들 얻기
					}
					bContinue = Process32Next (hSnapshot, &pe32);
				} while (bContinue);
			}
			CloseHandle(hSnapshot);
		}




		c_hwnd=::FindWindow(_T("#32770"), _T("설정(문서 스캔)"));
		c_hwnd=::FindWindowEx(c_hwnd, 0, _T("#32770"), NULL);




	}

}


ULONG ProcIDFromWnd(HWND hwnd) // 윈도우 핸들로 프로세스 아이디 얻기
{
	ULONG idProc;
	GetWindowThreadProcessId( hwnd, &idProc );
	return idProc;
}

HWND GetWinHandle(ULONG pid) // 프로세스 아이디로 윈도우 핸들 얻기
{
	HWND tempHwnd = FindWindow(NULL,NULL); // 최상위 윈도우 핸들 찾기

	while( tempHwnd != NULL )
	{
		if( GetParent(tempHwnd) == NULL ) // 최상위 핸들인지 체크, 버튼 등도 핸들을 가질 수 있으므로 무시하기 위해
			if( pid == ProcIDFromWnd(tempHwnd) )
				return tempHwnd;
		tempHwnd = GetWindow(tempHwnd, GW_HWNDNEXT); // 다음 윈도우 핸들 찾기
	}
	return NULL;
}



LRESULT CSU_auto2Dlg::OnMSG(WPARAM wParam, LPARAM lParam)
{


	return 0;
}