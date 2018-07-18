
// SU_auto2Dlg.cpp : ���� ����
//
#include "stdafx.h"
#include "SU_auto2.h"
#include "SU_auto2Dlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
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


// CSU_auto2Dlg ��ȭ ����




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


// CSU_auto2Dlg �޽��� ó����

BOOL CSU_auto2Dlg::OnInitDialog() //�ʱ�ȭ
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

	InputCombo.AddString(_T("�ڵ� ���"));
	InputCombo.AddString(_T("���� ����"));
	InputCombo.AddString(_T("���� ��ġ"));
	InputCombo.SelectString(1, _T("�ڵ� ���"));

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

	ColorMode.AddString(_T("�÷�"));
	ColorMode.AddString(_T("ȸ����"));
	ColorMode.AddString(_T("���"));
	ColorMode.SelectString(1, _T("�÷�"));

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


	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSU_auto2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSU_auto2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CSU_auto2Dlg::AddValueButton() //�߰� ��ư ����
{
	CString addValue[6];
	this->ModeCombo.GetLBText(this->ModeCombo.GetCurSel(), addValue[0]); 
	this->InputCombo.GetLBText(this->InputCombo.GetCurSel(), addValue[1]); 
	this->SizeCombo.GetLBText(this->SizeCombo.GetCurSel(), addValue[2]); 
	this->ColorMode.GetLBText(this->ColorMode.GetCurSel(), addValue[3]); 
	this->ResolutionCombo.GetLBText(this->ResolutionCombo.GetCurSel(), addValue[4]); 
	this->DataTypeCombo.GetLBText(this->DataTypeCombo.GetCurSel(), addValue[5]); 
	//�޺��ڽ����� ���õ� �� �迭�� �Է�



	int index=ListBox.InsertString(0,addValue[0]+", "+addValue[1]+", "+addValue[2]+", "+addValue[3]+", "+addValue[4]+", "+addValue[5]);
	ListBox.SetCurSel(index);
	//����Ʈ�ڽ��� �� �Է�

	//MessageBox(temp, _T("title")); //temp�� ���� alertâ���� ���


}


void CSU_auto2Dlg::DeleteButton() //���� ��ư ����
{
	int index=ListBox.GetCurSel();
	ListBox.DeleteString(index);

}


void CSU_auto2Dlg::OnBnClickedOk() //Ȯ�� ��ư ����
{
	CDialogEx::OnOK(); 
	HWND bt_hwnd,c_hwnd=NULL, c2_hwnd=NULL;
	CString ProcessName;
	ProcessName.MakeUpper();


	HWND m_hwnd=::FindWindow(_T("#32770"), _T("Canon MF Scan Utility")); //TOP WINDOW
	int cnt = ListBox.GetCount();
	if(NULL != m_hwnd){
		bt_hwnd=::FindWindowEx(m_hwnd, NULL, _T("BUTTON"),_T("����(&S)...")); // ���� ��ư�� �ڵ� 
		if(NULL != bt_hwnd){
			::SendMessageA(bt_hwnd, BM_CLICK,0,0); //������ư Ŭ�� 
		}


		HANDLE hSnapshot = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0); //���ǵ� �÷��׿� ���μ��� id�� �޾Ƽ� �ڵ��� �Ѱ���

		if ((int)hSnapshot != -1)
		{
			PROCESSENTRY32 pe32;
			pe32.dwSize=sizeof(PROCESSENTRY32);
			BOOL bContinue;
			CString tempProcessName;
			HANDLE hProcess= NULL;
			if ( Process32First (hSnapshot, &pe32))
			{
				//���μ��� ��� �˻� ����
				do
				{
					tempProcessName = pe32.szExeFile;  //���μ��� ��� �� ���� ���μ��� �̸�
					tempProcessName.MakeUpper();
					if((tempProcessName.Find(ProcessName, 0) != -1))
					{
						hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pe32.th32ProcessID);  //���μ��� �ڵ� ���
					}
					bContinue = Process32Next (hSnapshot, &pe32);
				} while (bContinue);
			}
			CloseHandle(hSnapshot);
		}




		c_hwnd=::FindWindow(_T("#32770"), _T("����(���� ��ĵ)"));
		c_hwnd=::FindWindowEx(c_hwnd, 0, _T("#32770"), NULL);




	}

}


ULONG ProcIDFromWnd(HWND hwnd) // ������ �ڵ�� ���μ��� ���̵� ���
{
	ULONG idProc;
	GetWindowThreadProcessId( hwnd, &idProc );
	return idProc;
}

HWND GetWinHandle(ULONG pid) // ���μ��� ���̵�� ������ �ڵ� ���
{
	HWND tempHwnd = FindWindow(NULL,NULL); // �ֻ��� ������ �ڵ� ã��

	while( tempHwnd != NULL )
	{
		if( GetParent(tempHwnd) == NULL ) // �ֻ��� �ڵ����� üũ, ��ư � �ڵ��� ���� �� �����Ƿ� �����ϱ� ����
			if( pid == ProcIDFromWnd(tempHwnd) )
				return tempHwnd;
		tempHwnd = GetWindow(tempHwnd, GW_HWNDNEXT); // ���� ������ �ڵ� ã��
	}
	return NULL;
}



LRESULT CSU_auto2Dlg::OnMSG(WPARAM wParam, LPARAM lParam)
{


	return 0;
}