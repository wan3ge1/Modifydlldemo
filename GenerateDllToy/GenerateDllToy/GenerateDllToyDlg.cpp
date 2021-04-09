
// GenerateDllToyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GenerateDllToy.h"
#include "GenerateDllToyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct Connect_Address
{
	DWORD dwstact;
	char strIP[MAX_PATH];
	int nPort;
}g_myAddress = { 0x1789714,"",0 };

int memfind(const char *mem, const char *str, int sizem, int sizes)
{
	int   da, i, j;
	if (sizes == 0) da = strlen(str);
	else da = sizes;
	for (i = 0; i < sizem; i++)
	{
		for (j = 0; j < da; j++)
			if (mem[i + j] != str[j])	break;
		if (j == da) return i;
	}
	return -1;
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGenerateDllToyDlg �Ի���



CGenerateDllToyDlg::CGenerateDllToyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GENERATEDLLTOY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGenerateDllToyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGenerateDllToyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OK, &CGenerateDllToyDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CGenerateDllToyDlg ��Ϣ�������

BOOL CGenerateDllToyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGenerateDllToyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGenerateDllToyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGenerateDllToyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGenerateDllToyDlg::OnBnClickedButtonOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strIP, strPort;
	GetDlgItemText(IDC_EDIT_IP, strIP);
	GetDlgItemText(IDC_EDIT_PORT, strPort);

	CFile file;
	char strTemp[MAX_PATH];
	ZeroMemory(strTemp, MAX_PATH);
	CString strCurrentPath;
	CString strFile;
	CString strSeverFile;
	// BYTE *lpBuffer = NULL;
	DWORD dwFileSize;
	UpdateData(TRUE);
	//////////������Ϣ//////////////////////
	strcpy(g_myAddress.strIP, strIP);
	g_myAddress.nPort = atoi(strPort);
	try
	{
		/*
		//�˴��õ�δ����ǰ���ļ���
		GetModuleFileName(NULL, strTemp, MAX_PATH);     //�õ��ļ���  
		strCurrentPath = strTemp;
		int nPos = strCurrentPath.ReverseFind('\\');
		strCurrentPath = strCurrentPath.Left(nPos);
		strFile = strCurrentPath + "\\client\\DllDemo.dll";   //�õ���ǰδ�����ļ���
															//���ļ�
		file.Open(strFile, CFile::modeRead | CFile::typeBinary);
		dwFileSize = file.GetLength();
		lpBuffer = new BYTE[dwFileSize];
		ZeroMemory(lpBuffer, dwFileSize);
		//��ȡ�ļ�����
		file.Read(lpBuffer, dwFileSize);
		file.Close();
		//д������IP�Ͷ˿� ��Ҫ��Ѱ��0x1234567�����ʶȻ��д�����λ��
		int nOffset = memfind((char*)lpBuffer, (char*)&g_myAddress.dwstact, dwFileSize, sizeof(DWORD));
		memcpy(lpBuffer + nOffset, &g_myAddress, sizeof(Connect_Address));
		//���浽�ļ�
		strSeverFile = strCurrentPath + "\\client.dll";
		file.Open(strSeverFile, CFile::typeBinary | CFile::modeCreate | CFile::modeWrite);
		file.Write(lpBuffer, dwFileSize);
		file.Close();
		delete[] lpBuffer;
		MessageBox("���ɳɹ�");
		*/
		
		/*HRSRC hRes = FindResource(theApp.m_hInstance, MAKEINTRESOURCE(IDR_DLL_32), "DLL");
		DWORD len = SizeofResource(theApp.m_hInstance, hRes);
		HGLOBAL hg = LoadResource(theApp.m_hInstance, hRes);
		LPVOID lp = (LPSTR)LockResource(hg);
		BYTE *lpBuffer = new BYTE[len];
		memcpy(lpBuffer, lp, len);
		GetModuleFileName(NULL, strTemp, MAX_PATH);
		strCurrentPath = strTemp;
		int nPos = strCurrentPath.ReverseFind('\\');
		strCurrentPath = strCurrentPath.Left(nPos);
		FreeResource(hg);
		int nOffset = memfind((char*)lpBuffer, (char*)&g_myAddress.dwstact, len, sizeof(DWORD));
		memcpy(lpBuffer + nOffset, &g_myAddress, sizeof(Connect_Address));
		strSeverFile = strCurrentPath + "\\client.dll";
		file.Open(strSeverFile, CFile::typeBinary | CFile::modeCreate | CFile::modeWrite);
		file.Write(lpBuffer, len);
		file.Close();*/
		if (strIP.IsEmpty())
		{
			MessageBox("IP cannot be null.");
			return;
		}
		std::regex pattern("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
		if (!(std::regex_match(strIP.GetBuffer(), pattern)))
		{
			MessageBox("Please input valid IP.");
			return;
		}
		if (strPort.IsEmpty())
		{
			MessageBox("Port cannot be null.");
			return;
		}
		if (!(strPort.SpanIncluding("0123456789") == strPort))
		{
			MessageBox("Port must be a number.");
			return;
		}
		int port = _ttoi(strPort);
		if (port < 1 || port > 65535)
		{
			MessageBox("Port range must be between 1 - 65535.");
			return;
		}

		MessageBox("���ɳɹ�");
	}
	catch (CMemoryException* e)
	{
		MessageBox("�ڴ治��");
	}
	catch (CFileException* e)
	{
		MessageBox("�ļ���������");
	}
	catch (CException* e)
	{
		MessageBox("δ֪����");
	}
	// CDialogEx::OnOK();
}
