// UIDlg.cpp: 实现文件
#include "pch.h"
#include "framework.h"
#include "UI.h"
#include "UIDlg.h"
#include "afxdialogex.h"
#include "core.h"
#include "tchar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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


// CUIDlg 对话框



CUIDlg::CUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUIDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUIDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUIDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUIDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CUIDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CUIDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CUIDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CUIDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CUIDlg::OnBnClickedButton9)
	ON_EN_CHANGE(IDC_EDIT3, &CUIDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT6, &CUIDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT6, &CUIDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT1, &CUIDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CUIDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CUIDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CUIDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CUIDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CUIDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CUIDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CUIDlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, &CUIDlg::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, &CUIDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, &CUIDlg::OnEnChangeEdit11)
END_MESSAGE_MAP()


// CUIDlg 消息处理程序

BOOL CUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

void CUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUIDlg::OnPaint()
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
HCURSOR CUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool isDigit(string str) {
	if (str.at(0) == '-') {
		for (unsigned int i = 1; i < str.size(); i++) {
			if (!isdigit(str[i])) {
				return false;
			}
		}
	}
	else {
		for (unsigned int i = 0; i < str.size(); i++) {
			if (!isdigit(str[i])) {
				return false;
			}
		}
	}
	return true;
}

string c2s(CString cstr) {
	int n = cstr.GetLength();
	int len = WideCharToMultiByte(CP_ACP, 0, cstr, n, NULL, 0, NULL, NULL);
	char* ch = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, cstr, n, ch, len, NULL, NULL);
	ch[len] = '\0';
	return (string)ch;
}

CString s2c(const char * msg) {
	string str = (string)msg;
	CString cstr(str.c_str());
	return cstr;
}

void CUIDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	draw();
}

void CUIDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	solve();
	draw();
	drawPoint();
}

void CUIDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	try {
		CString cstr;
		GetDlgItemText(IDC_EDIT1, cstr);
		int n = cstr.GetLength();
		int len = WideCharToMultiByte(CP_ACP, 0, cstr, n, NULL, 0, NULL, NULL);
		char* path = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, cstr, n, path, len, NULL, NULL);
		path[len] = '\0';
		inputFile((char*)path);

		string str = "import from file succeed!";
		string cap = "Message";
		MessageBox((CString)str.c_str(), (CString)cap.c_str());
	}
	catch (const char* msg) {
		CString cmsg = s2c(msg);
		AfxMessageBox(cmsg);
		return;
	}
}

void CUIDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	try {
		CString ctype, cx1, cy1, cx2, cy2;
		GetDlgItemText(IDC_EDIT2, ctype);
		GetDlgItemText(IDC_EDIT3, cx1);
		GetDlgItemText(IDC_EDIT4, cy1);
		GetDlgItemText(IDC_EDIT5, cx2);
		GetDlgItemText(IDC_EDIT6, cy2);
		if (ctype.GetLength() == 0 || cx1.GetLength() == 0 || cy1.GetLength() == 0
			|| cx2.GetLength() == 0 || cy2.GetLength() == 0) {
			throw "type or parameters can not be NULL";
		}
		string type = c2s(ctype);
		string x1 = c2s(cx1);
		string y1 = c2s(cy1);
		string x2 = c2s(cx2);
		string y2 = c2s(cy2);
		if (type != "L" && type != "R" && type != "S") {
			throw "Line type must be L, R or S!";
		}
		if (!isDigit(x1) || !isDigit(y1) || !isDigit(x2) || !isDigit(y2)) {
			throw "parameters must be integer!";
		}
		addLine(type, (long long)stoi(x1), (long long)stoi(y1), 
			(long long)stoi(x2), (long long)stoi(y2));

		string str = "Add line succeed!";
		string cap = "Message";
		MessageBox((CString)str.c_str(), (CString)cap.c_str());
	}
	catch (const char* msg) {
		CString cmsg = s2c(msg);
		AfxMessageBox(cmsg);
	}
}

void CUIDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	try {
		CString cindex;
		GetDlgItemText(IDC_EDIT7, cindex);
		if (cindex.GetLength() == 0) {
			throw "index can not be NULL";
		}
		string index = c2s(cindex);
		if (!isDigit(index)) {
			throw "index must be integer!";
		}
		delLine((long long)stoi(index));

		string str = "Delete line succeed!";
		string cap = "Message";
		MessageBox((CString)str.c_str(), (CString)cap.c_str());
	}
	catch (const char* msg) {
		CString cmsg = s2c(msg);
		AfxMessageBox(cmsg);
	}
}

void CUIDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	showLine();

}

void CUIDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	try {
		CString cx, cy, cr;
		GetDlgItemText(IDC_EDIT8, cx);
		GetDlgItemText(IDC_EDIT9, cy);
		GetDlgItemText(IDC_EDIT10, cr);
		if (cx.GetLength() == 0 || cy.GetLength() == 0 || cr.GetLength() == 0) {
			throw "parameters can not be NULL";
		}
		string x = c2s(cx);
		string y = c2s(cy);
		string r = c2s(cr);
		if (!isDigit(x) || !isDigit(y) || !isDigit(r)) {
			throw "parameters must be integer!";
		}
		addCircle((long long)stoi(x), (long long)stoi(y), (long long)stoi(r));

		string str = "Add Circle succeed!";
		string cap = "Message";
		MessageBox((CString)str.c_str(), (CString)cap.c_str());
	}
	catch (const char* msg) {
		CString cmsg = s2c(msg);
		AfxMessageBox(cmsg);
	}
}

void CUIDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	try {
		CString cindex;
		GetDlgItemText(IDC_EDIT11, cindex);
		if (cindex.GetLength() == 0) {
			throw "index can not be NULL";
		}
		string index = c2s(cindex);
		if (!isDigit(index)) {
			throw "index must be integer!";
		}
		delCircle((long long)stoi(index));

		string str = "Delete Circle succeed!";
		string cap = "Message";
		MessageBox((CString)str.c_str(), (CString)cap.c_str());
	}
	catch (const char* msg) {
		CString cmsg = s2c(msg);
		AfxMessageBox(cmsg);
	}
	
}

void CUIDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	showCircle();
}


void CUIDlg::OnEnChangeEdit1()
{
}


void CUIDlg::OnEnChangeEdit2()
{
}


void CUIDlg::OnEnChangeEdit3()
{
}


void CUIDlg::OnEnChangeEdit4()
{
}


void CUIDlg::OnEnChangeEdit5()
{
}

void CUIDlg::OnEnChangeEdit6()
{
}


void CUIDlg::OnEnChangeEdit7()
{
}


void CUIDlg::OnEnChangeEdit8()
{
}


void CUIDlg::OnEnChangeEdit9()
{
}


void CUIDlg::OnEnChangeEdit10()
{
}


void CUIDlg::OnEnChangeEdit11()
{
}
