
// MFCApplication2-pixelLocaterDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication2-pixelLocater.h"
#include "MFCApplication2-pixelLocaterDlg.h"
#include "afxdialogex.h"

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


// CMFCApplication2pixelLocaterDlg 对话框



CMFCApplication2pixelLocaterDlg::CMFCApplication2pixelLocaterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2PIXELLOCATER_DIALOG, pParent)
	, frame_height(0)
	, stride(0)
	, frame_index(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2pixelLocaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FRAMEHEIGHT, frame_height);
	DDX_Text(pDX, IDC_FRAMEWIDTH, frame_width);
	DDX_Text(pDX, IDC_FRAMESTRIDE, stride);
	DDX_Text(pDX, IDC_PIXEL_POS_IN, pixel_pos_in_yuv_file_str);
	DDX_Text(pDX, IDC_PIXEL_POS_IN2, pixel_pos_in_yuv_file_dec);	
	DDV_MinMaxInt(pDX, stride, 0, 66666);
	DDX_Text(pDX, IDC_FRAMEINDEX, frame_index);
	DDX_Text(pDX, IDC_COMPINDEX, comp_index);
	DDX_Text(pDX, IDC_MB_INDEX_IN_COMP, mb_index_in_comp);
	DDX_Text(pDX, IDC_MB_X_IN_COMP, mb_x_in_comp);
	DDX_Text(pDX, IDC_MB_Y_IN_COMP, mb_y_in_comp);
	DDX_Text(pDX, IDC_PIXEL_INDEX_IN_FRAME, pixel_index_in_frame);
	DDX_Text(pDX, IDC_PIXEL_INDEX_IN_COMP, pixel_index_in_comp);
	DDX_Text(pDX, IDC_PIXEL_X_IN_COMP, pixel_x_in_comp);
	DDX_Text(pDX, IDC_PIXEL_Y_IN_COMP, pixel_y_in_comp);
	DDX_Text(pDX, IDC_PIXEL_INDEX_IN_MB_IN_FRAME, pixel_index_in_mb_in_frame);
	DDX_Text(pDX, IDC_PIXEL_INDEX_IN_MB, pixel_index_in_mb);
	DDX_Text(pDX, IDC_PIXEL_X_IN_MB, pixel_x_in_mb);
	DDX_Text(pDX, IDC_PIXEL_Y_IN_MB, pixel_y_in_mb);
	DDX_Text(pDX, IDC_COMP_POS_IN_YUV_FILE, comp_pos_in_yuv_file);
}

BEGIN_MESSAGE_MAP(CMFCApplication2pixelLocaterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_FRAMEHEIGHT, &CMFCApplication2pixelLocaterDlg::OnEnChangeFrameheight)
	ON_BN_CLICKED(IDOK, &CMFCApplication2pixelLocaterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_GETRESULT, &CMFCApplication2pixelLocaterDlg::OnBnClickedGetresult)
END_MESSAGE_MAP()


// CMFCApplication2pixelLocaterDlg 消息处理程序

BOOL CMFCApplication2pixelLocaterDlg::OnInitDialog()
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
	// 设置帧宽、高默认值
	GetDlgItem(IDC_FRAMEHEIGHT)->SetWindowText(_T("1080"));
	GetDlgItem(IDC_FRAMEWIDTH)->SetWindowText(_T("1920"));
	GetDlgItem(IDC_FRAMESTRIDE)->SetWindowText(_T("2176")); 
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication2pixelLocaterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication2pixelLocaterDlg::OnPaint()
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
HCURSOR CMFCApplication2pixelLocaterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2pixelLocaterDlg::OnEnChangeFrameheight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2pixelLocaterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
#if 0
	CString test;
	test.Format(_T("%d"), frame_height);
	MessageBox(test);
	UpdateData(TRUE);
	test.Format(_T("%d"), frame_height);
	MessageBox(test);
	CDialogEx::OnOK();
#endif
}


void CMFCApplication2pixelLocaterDlg::OnBnClickedGetresult()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); //读控件，获取像素位置值

	char *p = (char*)(LPCTSTR)pixel_pos_in_yuv_file_str;
	char p1[20];
	memset(p1, 0, sizeof(p1));
	memcpy(p1, p, 20);
	char *ptr;
	unsigned long long pixel_pos_in_yuv_file = strtol(p1, &ptr, 16); //_ttoi();

	
	//计算各个变量
	int mb_in_row = (frame_width - 1) / 16 + 1;//一帧的一行有多少个MB
	int mb_in_col = (frame_height - 1) / 16 + 1;//一帧的一列有多少个MB
	//像素所在帧号，从0开始
	frame_index = pixel_pos_in_yuv_file / (frame_width * frame_height * 3);
	//像素所在分量号，0/1/2
	comp_index = pixel_pos_in_yuv_file % (frame_width * frame_height * 3) / (frame_width * frame_height);
	//本分量在YUV文件中的起始位置
	comp_pos_in_yuv_file = frame_index * (frame_width * frame_height * 3) + comp_index * (frame_width * frame_height);

	//像素所在的宏块在分量中的坐标（从0开始），以及序号（即MB相对该分量开头的偏移；0~8659）
	mb_y_in_comp = (pixel_pos_in_yuv_file - comp_pos_in_yuv_file) / frame_width / 16;//宏块在分量中的y坐标
	mb_x_in_comp = (pixel_pos_in_yuv_file - comp_pos_in_yuv_file) % frame_width / 16;//宏块在分量中的x坐标
	mb_index_in_comp = mb_in_row * mb_y_in_comp + mb_x_in_comp;

	//像素相对所在帧的起始位置的偏移；
	pixel_index_in_frame = pixel_pos_in_yuv_file - frame_index * (frame_width * frame_height * 3);

	//像素相对所在分量的起始位置的偏移；
	pixel_index_in_comp = pixel_pos_in_yuv_file - frame_index * (frame_width * frame_height * 3)
		- comp_index * (frame_width * frame_height);
	//像素在分量中的横坐标；
	pixel_x_in_comp = pixel_index_in_comp % frame_width;
	//像素在分量中的纵坐标；
	pixel_y_in_comp = pixel_index_in_comp / frame_width;

	//像素相对本宏块起始位置的偏移，范围从[0~frame_width*15+16]
	unsigned long long mb_seat = comp_pos_in_yuv_file + mb_y_in_comp * 16 * frame_width + mb_x_in_comp*16;//宏块首元素在YUV文件中的绝对位置
	pixel_index_in_mb_in_frame = pixel_pos_in_yuv_file - mb_seat;

	//单宏块范围内看，像素相对本宏块起始位置的(x,y)坐标，以及偏移（取值范围[0~255]）；
	pixel_y_in_mb = pixel_index_in_mb_in_frame / frame_width;
	pixel_x_in_mb = pixel_index_in_mb_in_frame % frame_width;
	pixel_index_in_mb = 16 * pixel_y_in_mb + pixel_x_in_mb;

	UpdateData(FALSE);
	UpdateWindow();
}
