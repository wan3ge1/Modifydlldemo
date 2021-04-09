
// GenerateDllToyDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CGenerateDllToyDlg 对话框



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


// CGenerateDllToyDlg 消息处理程序

BOOL CGenerateDllToyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGenerateDllToyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGenerateDllToyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGenerateDllToyDlg::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//////////上线信息//////////////////////
	strcpy(g_myAddress.strIP, strIP);
	g_myAddress.nPort = atoi(strPort);
	try
	{
		/*
		//此处得到未处理前的文件名
		GetModuleFileName(NULL, strTemp, MAX_PATH);     //得到文件名  
		strCurrentPath = strTemp;
		int nPos = strCurrentPath.ReverseFind('\\');
		strCurrentPath = strCurrentPath.Left(nPos);
		strFile = strCurrentPath + "\\client\\DllDemo.dll";   //得到当前未处理文件名
															//打开文件
		file.Open(strFile, CFile::modeRead | CFile::typeBinary);
		dwFileSize = file.GetLength();
		lpBuffer = new BYTE[dwFileSize];
		ZeroMemory(lpBuffer, dwFileSize);
		//读取文件内容
		file.Read(lpBuffer, dwFileSize);
		file.Close();
		//写入上线IP和端口 主要是寻找0x1234567这个标识然后写入这个位置
		int nOffset = memfind((char*)lpBuffer, (char*)&g_myAddress.dwstact, dwFileSize, sizeof(DWORD));
		memcpy(lpBuffer + nOffset, &g_myAddress, sizeof(Connect_Address));
		//保存到文件
		strSeverFile = strCurrentPath + "\\client.dll";
		file.Open(strSeverFile, CFile::typeBinary | CFile::modeCreate | CFile::modeWrite);
		file.Write(lpBuffer, dwFileSize);
		file.Close();
		delete[] lpBuffer;
		MessageBox("生成成功");
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

		MessageBox("生成成功");
	}
	catch (CMemoryException* e)
	{
		MessageBox("内存不足");
	}
	catch (CFileException* e)
	{
		MessageBox("文件操作错误");
	}
	catch (CException* e)
	{
		MessageBox("未知错误");
	}
	// CDialogEx::OnOK();
}
