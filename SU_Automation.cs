using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.Collections;

namespace ScanUtility_Automation
{
    public partial class SU_Automation : Form
    {
        [DllImport("user32.dll")]
        public static extern void keybd_event(byte vk, byte scan, uint flags, int extrainfo);

        [DllImport("user32.dll")]
        public static extern uint FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll")]
        public static extern uint FindWindowEx(uint hWnd1, uint hWnd2, string lpsz1, string lpsz2);

        [DllImport("user32.dll")]
        public static extern uint GetWindow(uint hWnd1, int uCmd);

        [DllImport("user32.dll")]
        public static extern uint SendMessage(uint hwnd, uint wMsg, uint wParam, uint lParam);

        [DllImport("user32.dll")]
        public static extern uint PostMessage(uint hwnd, uint wMsg, uint wParam, uint lParam);

        [DllImport("user32.dll")]
        public static extern void SetForegroundWindow(uint hWnd);


        const int WM_SETCURSOR = 0x0020;
        const int WM_LBUTTONDOWN = 0x0201;
        const int WM_LBUTTONUP = 0x0202;
        const int WM_KEYDOWN = 0x0100;
        const int WM_SETTEXT = 0x000C;

        const int BM_CLICK = 0x00F5; //버튼 클릭 
        const int BM_SETCHECK = 0x00f1; //체크박스 클릭
        const int TCM_SETCURFOCUS = 0x1330; //상위 탭

        const int CB_SETCURSEL = 0x014E; // ComboBox Index변경
        const int CB_GETLBTEXT = 0x0148;
        const int CB_SHOWDROPDOWN = 0x014f; // ComboBox 클릭

        const int VK_UP = 0x26; //UP ARROW KEY
        const int VK_RIGHT = 0x27; //RIGHT ARROW KEY
        const int VK_DOWN = 0x28; //DOWN ARROW KEY
        const int VK_ESCAPE = 0x1B; //ESC KEY
        const int VK_F4 = 0x73; //F4 KEY
        const int VK_RETURN = 0x0D; //ENTER KEY

        const uint KEYEVENTF_EXTENDEDKEY = 0x00001;
        const int KEYEVENTF_KEYUP = 0x0002;
        const int TAB_KEY = 9;
        
        const int GW_HWNDFIRST = 0;
        const int GW_HWNDLAST = 1;
        const int GW_HWNDNEXT = 2;
        const int GW_HWNDPREV = 3;
        const int GW_OWNER = 4;
        const int GW_CHILD = 5;

        private const int SW_SHOWNORMAL = 1;
        private const int SW_SHOWMINIMIZED = 2;
        private const int SW_SHOWMAXIMIZED = 3;

        uint handle;
        public Boolean run = false; //Thread Flag
        String[] v = new string[8];
        Form1 form1 = new Form1(); // 종료 창 생성
        Thread spThread;
        Mode m;
        


        public SU_Automation()
        {

            InitializeComponent();
            FormClosing += new FormClosingEventHandler(closing);

            comboBox1.SelectedItem = "Document";
            comboBox2.SelectedItem = "평판 유리";
            comboBox3.SelectedItem = "A4";
            comboBox4.SelectedItem = "컬러";
            comboBox5.SelectedItem = "300dpi";
            comboBox6.SelectedItem = "TIFF";
            comboBox7.SelectedItem = "표준";
            textBox1.SelectedText = "1";
            //ComboBox Default값 설정

            //checkStateOfScanUtility(); // SCAN Utility 창 띄우기

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e) //모드
        {

            ArrayList arrType = new ArrayList();

            Object selectedItem = comboBox1.SelectedItem;
            v[0] = selectedItem.ToString();

            SelectMode(v[0]);
            ComboboxSetting(v[0]); //모드별 콤보박스 세팅
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e) //원고 입력방식
        {
            Object selectedItem = comboBox2.SelectedItem;
            v[1] = selectedItem.ToString();
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e) //용지크기
        {
            Object selectedItem = comboBox3.SelectedItem;
            v[2] = selectedItem.ToString();

        }

        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e) //컬러모드
        {
            Object selectedItem = comboBox4.SelectedItem;
            v[3] = selectedItem.ToString();
        }

        private void comboBox5_SelectedIndexChanged(object sender, EventArgs e) //해상도
        {
            Object selectedItem = comboBox5.SelectedItem;
            v[4] = selectedItem.ToString();
        }

        private void comboBox6_SelectedIndexChanged(object sender, EventArgs e) //데이터 형식
        {

            Object selectedItem = comboBox6.SelectedItem;
            v[5] = selectedItem.ToString();

            if (v[5] == "JPEG/Exif") //데이터형식에 따라 데이터형식별 옵션 달라짐
            {
                comboBox7.Enabled = true;
                comboBox7.Items.Clear();
                this.comboBox7.Items.AddRange(new object[] { "낮음", "표준", "높음" });
                comboBox7.SelectedItem = "표준";
            }
            else if (v[5] == "PDF(단일 페이지)" || v[5] == "PDF")
            {
                comboBox7.Enabled = true;
                comboBox7.Items.Clear();
                this.comboBox7.Items.AddRange(new object[] { "표준", "높음" });
                comboBox7.SelectedItem = "표준";
            }
            else //JPEG/Exif, PDF이외의 항목은 옵션X
            {
                comboBox7.Items.Clear();
                comboBox7.Enabled = false; //콤보박스 비활성화
                v[6] = "없음";
            }

        }

        private void comboBox7_SelectedIndexChanged(object sender, EventArgs e) //데이터 형식별 옵션
        {
            Object selectedItem = comboBox7.SelectedItem;
            v[6] = selectedItem.ToString();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            Object selectedItem = textBox1.Text;
            v[7] = selectedItem.ToString();
        }

        private void button1_Click(object sender, EventArgs e) //listBox [추가]버튼
        {
            listBox1.Items.Add(v[0] + ", " + v[1] + ", " + v[2] + ", " + v[3] + ", " + v[4] + ", " + v[5] + ", " + v[6] + ", " + v[7]);
            
        }

        private void button2_Click(object sender, EventArgs e) //listBox [삭제]버튼
        {
            int index;
            if (listBox1.SelectedIndex > -1)
            {
                index = listBox1.SelectedIndex;
                listBox1.Items.RemoveAt(index);
            } //listbox에서 선택되지 않았을 때 (혹은 listbox에 아무것도 없을 때) 예외처리
            

        }

        private void DieaseUpdateEventMethod(Boolean sender)
        {
            //Form1에서 델리게이트로 이벤트 발생하면 현재 함수 Call
            run = sender;
            spThread.Abort();

            foreach (Process process in Process.GetProcesses())
            {
                if (process.ProcessName.StartsWith("MFSCANUTILITY"))
                {
                    process.Kill();
                }
            }
        }
        
        public void button3_Click(object sender, EventArgs e) //설정 완료 후 [확인]버튼
        {
           // checkStateOfScanUtility(); //Scan Utility 창 생성 
            run = true; //스레드 실행 상태로 변경 
            form1 = new Form1(); // 종료 창 생성
            form1.Visible = true;
            form1.FormSendEvent += new Form1.FormSendDataHandler(DieaseUpdateEventMethod);

            FileTracking ft = new FileTracking();
            ft.InitWatcher();

            try
            {
                spThread = new Thread(new ThreadStart(Scanning));
                spThread.Start();

            }

            catch (ThreadAbortException)
            {
                return;
            }


        }
        public void SelectMode(String mode)
        {
            switch (mode)
            {
                //부모클래스로 업캐스팅
                case "Document":
                    m = new DocumentMode();
                    break;
                case "Photo":
                    m = new PhotoMode();
                    break;
                case "Custom":
                    m = new CustomMode();
                    break;
                case "Stitch":
                    m = new StitchMode();
                    break;
                case "ScanGear":
                    m = new ScanGearMode();
                    break;
                case "OCR":
                    m = new OCRMode();
                    break;
                case "E-mail":
                    m = new EmailMode();
                    break;
            }

        }
        
        private void Scanning()
        {

            Thread.Sleep(100000000);

            /*for (int i = 0; i < listBox1.Items.Count; i++)
            {
                String s = listBox1.Items[i].ToString();
                String[] words = s.Split(new string[] { ", " }, StringSplitOptions.None); //listBox의 설정 내용 split후 변수에 저장

                SelectMode(words[0]);
                m.SetSize(words[2]);
                m.SetColor(words[3]);
                m.SetResolution(words[4]);
                m.SetDataType(words[5]);

                int cnt = Int32.Parse(words[7]);

                handle = FindWindow("#32770", "Canon MF Scan Utility");

                SetForegroundWindow(handle);
                handle = FindWindowEx(handle, 0, "button", "설정(&S)...");

                PostMessage(handle, BM_CLICK, 0, 0);
                //Scan Utility창의 설정버튼 클릭

                do
                {
                    Thread.Sleep(10);
                    handle = 0;
                    handle = FindWindow("#32770", "설정(문서 스캔)");

                } while (handle == 0);
                //상세 설정창 뜰때까지 기다림

                uint setInput = 0;

                SetForegroundWindow(handle);
                handle = FindWindowEx(handle, 0, "#32770", null);

                SetMode(m.GetModeNum()); // 번호로 모드 setting

                SetCheckBox(m.GetModeNum()); // 체크박스 설정

                SetInput(setInput); // 원고 입력방식 : 평판유리 한정

                SetSize(m.GetModeNum(), m.GetSizeNum()); // 용지 크기
                
                SetColorMode(m.GetModeNum(), m.GetColorNum()); // 컬러 모드 
                
                SetResolution(m.GetModeNum(), m.GetResolutionNum()); // 해상도 
                
                SetDataType(m.GetDataTypeNum()); // 데이터 형식
                
                Thread.Sleep(1500);
                SetDataTypeOption(words[5], words[6]);

                Thread.Sleep(1000);
                OKButton_Click(m.GetModeNum());


                for(int j=0; j<cnt; j++)
                {
                    if (m.GetModeNum() == 6) {
                        SetStart(m.GetModeNum());

                        do
                        {
                            Thread.Sleep(1000);
                            handle = 0;
                            handle = FindWindow(null, "ScanGear MF");
                        }
                        while (handle == 0);
                        //ScanGear창이 뜰때까지 while

                        handle = FindWindowEx(handle, 0, "#32770", "ScanGear MF");
                        handle = FindWindowEx(handle, 0, "#32770", "고급 모드");

                        SetForegroundWindow(handle);

                        //데이터형식, PDF압축형식 설정 위에서 완료
                        SetSize(m.GetModeNum(), m.GetSizeNum()); // 용지 크기
                        SetColorMode(m.GetModeNum(), m.GetColorNum()); // 컬러 모드 
                        SetResolution(m.GetModeNum(), m.GetResolutionNum()); // 해상도 

                        Thread.Sleep(500);

                        handle = FindWindowEx(handle, 0, "CMyBmpButton2_Class", "스캔(&S)");
                        PostMessage(handle, WM_LBUTTONDOWN, 0, 0);
                        Thread.Sleep(1000);
                        PostMessage(handle, WM_KEYDOWN, VK_RETURN, 0);
                        Thread.Sleep(1500);

                        do
                        {
                            Thread.Sleep(10);
                            handle = 0;
                            handle = FindWindow(null, "ScanGear MF");
                        }
                        while (handle != 0);
                        Thread.Sleep(1000);

                    }
                    else
                    {
                        SetStart(m.GetModeNum());
                        Thread.Sleep(1000);

                    }

                    if (words[5] == "PDF")
                    {
                        do
                        {
                            
                            handle = 0;
                            handle = FindWindow("#32770", "스캔 완료");

                        }
                        while (handle == 0);
                        handle = FindWindowEx(handle, 0, "Button", "종료");
                        PostMessage(handle, BM_CLICK, 0, 0);
                    }

                    Thread.Sleep(2000);
                    do
                    {
                        Thread.Sleep(10);
                        handle = 0;
                        handle = FindWindow("#32770", "스캔 중");
                    }
                    while (handle != 0);


                }
            }
            */
            CheckForIllegalCrossThreadCalls = false;

            form1.Close();

        }


        public void checkStateOfScanUtility() // SCAN Utility 창이 열려있는지 확인
        {
            handle = 0;
            handle = FindWindow("#32770", "Canon MF Scan Utility");
            if (handle == 0)
            {
              System.Diagnostics.Process abc = new System.Diagnostics.Process();
              abc.StartInfo.UseShellExecute = false;
              abc.StartInfo.FileName = "C:\\Program Files\\Canon\\MF Scan Utility\\MFSCANUTILITY.exe";
              abc.Start(); // SCAN Utility 창 띄우기
              Thread.Sleep(1000);
            }
            
        }


        public void ComboboxSetting(String mode)
        {
            comboBox3.Enabled = true;//용지 크기 comboBox 초기화
            comboBox3.Items.Clear();
            String[] size = m.GetSizeArray();
            comboBox3.Items.AddRange(size);
            comboBox3.SelectedItem = "A4";

            comboBox4.Enabled = true;//컬러 모드 comboBox 초기화
            comboBox4.Items.Clear();
            String[] col = m.GetColorArray();
            comboBox4.Items.AddRange(col);
            comboBox4.SelectedItem = "컬러";

            comboBox5.Enabled = true;//해상도 comboBox 초기화
            comboBox5.Items.Clear();
            String[] res = m.GetResolutionArray();
            comboBox5.Items.AddRange(res);
            comboBox5.SelectedItem = "300dpi";


            comboBox6.Enabled = true; //데이터 형식 comboBox 초기화
            comboBox6.Items.Clear();
            String[] type = m.GetDataTypeArray();
            comboBox6.Items.AddRange(type);
            comboBox6.SelectedItem = "PNG";

        }

        public void SetMode(int modeNum)
        {
            for (int i = 0; i < modeNum; i++)
            {
                keybd_event((byte)VK_RIGHT, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                Thread.Sleep(500);
            }
        }

        public void SetCheckBox(int mode)
        {
            uint n_handle=0;
            switch (mode)
            {
                case 0:
                    n_handle = FindWindow("#32770", "설정(문서 스캔)");
                    break;
                case 3:
                    n_handle = FindWindow("#32770", "설정(사진 스캔)");
                    break;
                case 4:
                    n_handle = FindWindow("#32770", "설정(사용자 정의 스캔)");
                    break;
                case 5:
                    n_handle = FindWindow("#32770", "설정(스캔 및 스티치)");
                    break;
                case 6:
                    n_handle = FindWindow("#32770", "설정(ScanGear)");
                    break;
                case 7:
                    n_handle = FindWindow("#32770", "설정(OCR)");
                    break;
                case 8:
                    n_handle = FindWindow("#32770", "설정(전자 메일)");
                    break;

            }
            n_handle = FindWindowEx(n_handle, 0, "#32770", null);

            n_handle = FindWindowEx(n_handle, 0, "Button", "현재 날짜의 하위 폴더에 저장(&W)");
            PostMessage(n_handle, BM_SETCHECK, 1, 0);
            Thread.Sleep(500);

            n_handle = FindWindowEx(n_handle, 0, "Button", "스캔 결과 확인(&H)");
            PostMessage(n_handle, BM_SETCHECK, 0, 0);
            Thread.Sleep(500);

            n_handle = FindWindowEx(n_handle, 0, "Button", "어플리케이션 시작 안 함");
            PostMessage(n_handle, BM_SETCHECK, 1, 0);

        }

        public void SetInput(uint setIn) //압판 스캔 자동화시 선택지는 평판 유리 한정
        {
            uint n_handle;
            n_handle = FindWindowEx(handle, 0, "Static", "스캔 방법(&S):");
            n_handle = GetWindow(n_handle, GW_HWNDNEXT);
            n_handle = FindWindowEx(n_handle, 0, "ComboBox", null);

            PostMessage(n_handle, CB_SETCURSEL, setIn, 0);
            Thread.Sleep(500);

            PostMessage(n_handle, CB_SHOWDROPDOWN, setIn, 0);
            Thread.Sleep(500);
            keybd_event((byte)VK_F4, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);

            SetForegroundWindow(n_handle);


        }

        public void SetColorMode(int mode, uint col) // 컬러 모드 설정 
        {
            uint n_handle;

            if (mode == 6)
            {

                n_handle = FindWindowEx(handle, 0, "Static", "컬러 모드:");
                n_handle = GetWindow(n_handle, GW_HWNDNEXT);

            }
            else
            {
                n_handle = FindWindowEx(handle, 0, "Static", "컬러 모드(&C):");
                n_handle = GetWindow(n_handle, GW_HWNDNEXT);
                n_handle = FindWindowEx(n_handle, 0, "ComboBox", null);

            }
            PostMessage(n_handle, CB_SETCURSEL, col, 0);
            Thread.Sleep(500);

            PostMessage(n_handle, CB_SHOWDROPDOWN, col, 0);
            Thread.Sleep(500);
            keybd_event((byte)VK_F4, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);

            SetForegroundWindow(n_handle);
        }

        public void SetSize(int mode, uint size) // 입력 크기 설정
        {
            uint n_handle;

            if (mode == 6)
            {
                n_handle = FindWindowEx(handle, 0, "Static", "입력 크기:");
                n_handle = GetWindow(n_handle, GW_HWNDNEXT);

            }
            else
            {
                n_handle = FindWindowEx(handle, 0, "Static", "용지 크기(&E):");
                n_handle = GetWindow(n_handle, GW_HWNDNEXT);
                n_handle = FindWindowEx(n_handle, 0, "ComboBox", null);

            }
            PostMessage(n_handle, CB_SETCURSEL, size, 0);
            Thread.Sleep(500);

            PostMessage(n_handle, CB_SHOWDROPDOWN, size, 0);
            Thread.Sleep(500);
            keybd_event((byte)VK_F4, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);

            SetForegroundWindow(n_handle);

        }

        public void SetResolution(int mode, uint resol) // 해상도 설정
        {
            uint n_handle;

            if (mode == 6)
            {
                n_handle = FindWindowEx(handle, 0, "Static", "출력 해상도:");
                n_handle = GetWindow(n_handle, GW_HWNDNEXT);

            }
            else
            {

                n_handle = FindWindowEx(handle, 0, "Static", "해상도(&R):");
                n_handle = GetWindow(n_handle, GW_HWNDNEXT);
                n_handle = FindWindowEx(n_handle, 0, "ComboBox", null);
            }

            PostMessage(n_handle, CB_SETCURSEL, resol, 0);
            Thread.Sleep(500);

            PostMessage(n_handle, CB_SHOWDROPDOWN, resol, 0);
            Thread.Sleep(500);
            keybd_event((byte)VK_F4, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);

            SetForegroundWindow(n_handle);
        }

        public void SetDataType(uint dType)
        {
            uint n_handle;
            n_handle = FindWindowEx(handle, 0, "Static", "데이터 형식(&O):");
            n_handle = GetWindow(n_handle, GW_HWNDNEXT);
            n_handle = FindWindowEx(n_handle, 0, "ComboBox", null);
            
            PostMessage(n_handle, CB_SETCURSEL, dType, 0);
            Thread.Sleep(500);
            PostMessage(n_handle, CB_SHOWDROPDOWN, dType, 0);
            Thread.Sleep(500);
            keybd_event((byte)VK_F4, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);

            SetForegroundWindow(n_handle);
        }


        public void SetDataTypeOption(String type, String option)
        {
            uint n_handle;
            uint num = 0;

            if (type == "JPEG/Exif")
            {
                n_handle = FindWindowEx(handle, 0, "Static", "JPEG 이미지 품질(&J):");
                n_handle = GetWindow(n_handle, GW_HWNDNEXT);
                n_handle = FindWindowEx(n_handle, 0, "ComboBox", null);

                switch (option)
                {
                    case "낮음": num = 0;
                        break;
                    case "표준": num = 1;
                        break;
                    case "높음": num = 2;
                        break;

                }
                PostMessage(n_handle, CB_SETCURSEL, num, 0);
                Thread.Sleep(1000);
                PostMessage(n_handle, CB_SHOWDROPDOWN, num, 0);
                Thread.Sleep(500);
                keybd_event((byte)VK_F4, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);

            }
            else if (type == "PDF(단일 페이지)" || type =="PDF")
            {
                n_handle = FindWindowEx(handle, 0, "Static", "PDF 압축(&P):");
                n_handle = GetWindow(n_handle, GW_HWNDNEXT);
                n_handle = FindWindowEx(n_handle, 0, "ComboBox", null);
                switch (option)
                {
                    case "표준": num = 0;
                        break;
                    case "높음": num = 1;
                        break;
                }

                PostMessage(n_handle, CB_SETCURSEL, num, 0);
                Thread.Sleep(1000);
                PostMessage(n_handle, CB_SHOWDROPDOWN, num, 0);
                Thread.Sleep(500);
                keybd_event((byte)VK_F4, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);

            }

            Thread.Sleep(1000);
        }



        public void OKButton_Click(int mode) // 설정 끝난 후 최종적으로 확인버튼 클릭
        {
            uint n_handle;
            switch (mode)
            {
                case 0:
                    handle = FindWindow("#32770", "설정(문서 스캔)");
                    break;
                case 3:
                    handle = FindWindow("#32770", "설정(사진 스캔)");
                    break;
                case 4:
                    handle = FindWindow("#32770", "설정(사용자 정의 스캔)");
                    break;
                case 5:
                    handle = FindWindow("#32770", "설정(스캔 및 스티치)");
                    break;
                case 6:
                    handle = FindWindow("#32770", "설정(ScanGear)");
                    break;
                case 7:
                    handle = FindWindow("#32770", "설정(OCR)");
                    break;
                case 8:
                    handle = FindWindow("#32770", "설정(전자 메일)");
                    break;

            }
            n_handle = FindWindowEx(handle, 0, "button", "확인");
            PostMessage(n_handle, BM_CLICK, 0, 0);
            Thread.Sleep(1000);
        }

        public void SetStart(int mode)
        {
            uint n_handle = FindWindow("#32770", "Canon MF Scan Utility");
            switch (mode)
            {
                case 0:
                    n_handle = FindWindowEx(n_handle, 0, "button", "문서");
                    break;
                case 3:
                    n_handle = FindWindowEx(n_handle, 0, "button", "사진");
                    break;
                case 4:
                    n_handle = FindWindowEx(n_handle, 0, "button", "사용자 정의");
                    break;
                case 5:
                    n_handle = FindWindowEx(n_handle, 0, "button", "스티치");
                    break;
                case 6:
                    n_handle = FindWindowEx(n_handle, 0, "button", "ScanGear");
                    break;
                case 7:
                    n_handle = FindWindowEx(n_handle, 0, "button", "OCR");
                    break;
                case 8:
                    n_handle = FindWindowEx(n_handle, 0, "button", "전자 메일");
                    break;

            }
            PostMessage(n_handle, BM_CLICK, 0, 0);
            Thread.Sleep(1000);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void closing(object sender, FormClosingEventArgs e) //  X버튼
        {
            if (run == true) spThread.Abort();
            if (form1.Visible == true) form1.Close();
            Application.Exit();

            foreach (Process process in Process.GetProcesses())
            {
                if (process.ProcessName.StartsWith("MFSCANUTILITY"))
                {
                    process.Kill();
                }
            }
        }

        private void button4_Click(object sender, EventArgs e) //취소버튼
        {


            if (run == true) spThread.Abort();
            if (form1.Visible == true) form1.Close();
            Application.Exit();


            foreach (Process process in Process.GetProcesses())
            {
                if (process.ProcessName.StartsWith("MFSCANUTILITY"))
                {
                    process.Kill();
                }
            }

            Close();
        }

        private void SU_Automation_Load(object sender, EventArgs e)
        {


        }

    }
}

