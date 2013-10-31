// hw1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "hw1.h"
#include "hw1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define uchar unsigned char

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Chw1Dlg 对话框




Chw1Dlg::Chw1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Chw1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Chw1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOW_IMAGE1, m_showImage);
}

BEGIN_MESSAGE_MAP(Chw1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPEN, &Chw1Dlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE_INITIAL_HIST, &Chw1Dlg::OnBnClickedSaveInitialHist)
	ON_BN_CLICKED(IDC_SAVE_ENHANCED_IMAGE, &Chw1Dlg::OnBnClickedSaveEnhancedImage)
	ON_BN_CLICKED(IDC_SAVE_ENHANCED_HIST, &Chw1Dlg::OnBnClickedSaveEnhancedHist)
	ON_BN_CLICKED(IDC_HIST_EQUAL, &Chw1Dlg::OnBnClickedHistEqual)
	ON_BN_CLICKED(IDC_MEDIAN_FILTER, &Chw1Dlg::OnBnClickedMedianFilter)
	ON_BN_CLICKED(IDC_MEAN_FILTER, &Chw1Dlg::OnBnClickedMeanFilter)
	ON_BN_CLICKED(IDC_SHARPEN_FILTER, &Chw1Dlg::OnBnClickedSharpenFilter)
END_MESSAGE_MAP()


// Chw1Dlg 消息处理程序

BOOL Chw1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//saveFileName = _T("");
	//选上第一个单选框
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	//没打开图像前禁止点击
	GetDlgItem(IDC_SAVE_ENHANCED_HIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_ENHANCED_IMAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(FALSE);

	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);

	//改变字体
	LOGFONT logfont2;
	CFont m_font2;
	CWnd* pGroup = GetDlgItem(IDC_MSG);
	CFont* pGroupFont = pGroup -> GetFont();
	pGroupFont->GetLogFont(&logfont2);
	logfont2.lfHeight = -20;
	logfont2.lfWeight = FW_BOLD;
	//::lstrcpy(logfont2.lfFaceName, _T("Arial"));

	m_font2.CreateFontIndirect(&logfont2);
	pGroup->SetFont(&m_font2);

	//内容垂直居中
	CRect rect;
	CWnd* pEdit1 = GetDlgItem(IDC_MSG);
	pEdit1->GetClientRect(&rect);
	::OffsetRect(&rect, 0, 40);
	::SendMessage(pEdit1->m_hWnd, EM_SETRECT, 0, (LPARAM)&rect);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Chw1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Chw1Dlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Chw1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Chw1Dlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码

	//打开图像对话框
	CFileDialog   dlgOpenFile(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_FILEMUSTEXIST|OFN_ENABLESIZING, 
		_T("All Files (*.*)|*.*|BMP (*.bmp)|*.bmp|JPEG (*.jpg;*.jpeg;*.jpe;*.jfif)|*.jpg;*.jpeg;*.jpe;*.jfif|PNG (*.png)|*.png|TIF (*.tif;*.tiff)|*.tif;*.tiff||"));   
	if(IDOK == dlgOpenFile.DoModal())
	{
		//获取图像路径及文件名
		initImgFilePath = dlgOpenFile.GetPathName(); 
	}
	else
	{
		return;
	}

	//加载图片
	if(!srcImg.IsNull())
		srcImg.Destroy();
	HRESULT res = srcImg.Load(initImgFilePath);
	if(FAILED(res))
	{
		//失败提示
		SetDlgItemText(IDC_MSG, _T("Load image file \"") + initImgFilePath + _T("\" failed!"));
		return;
	}
	//成功提示
	SetDlgItemText(IDC_MSG, _T("Load image file \"") + initImgFilePath + _T("\" successfully!"));

	//获得图像控件窗口的句柄
	CWnd *pWnd = GetDlgItem(IDC_SHOW_IMAGE1);
	//获得图像控件的DC
	CDC *pDC = pWnd->GetDC();	
	//获取图片控件的宽和高
	CRect rect;
	pWnd->GetClientRect(&rect);
	//绘图
	pDC->SetStretchBltMode(HALFTONE);	//防止图片失真
	srcImg.Draw(pDC->m_hDC, rect); //将图片画到图像控件表示的矩形区域
	ReleaseDC(pDC);	//释放图像控件的DC

	//获取图像的宽和高
	int imgWidth = srcImg.GetWidth();
	int imgHeight = srcImg.GetHeight();
	//图像灰度统计数据
	int histData[256] = {0};	

	//获得图像控件窗口的句柄
	pWnd = GetDlgItem(IDC_SHOW_HIST1);
	//统计灰度数据
	GetHistData(&srcImg, histData);
	//绘制直方图
	DrawHistogram(pWnd, histData);

	//恢复点击
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(TRUE);

	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
}

void Chw1Dlg::OnBnClickedSaveInitialHist()
{
	// TODO: 在此添加控件通知处理程序代码
	//指定窗口范围
	CWnd* pWnd = GetDlgItem(IDC_SHOW_HIST1);
	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->ClientToScreen(&rect);
	//指定保存文件名
	CString totalFileName = initImgFilePath.Right(initImgFilePath.GetLength() - initImgFilePath.ReverseFind('\\') - 1);
	CString fileName = totalFileName.Left(totalFileName.Find('.')) +  _T("_Hist");
	SaveImageFile(rect, fileName);
}

void Chw1Dlg::OnBnClickedSaveEnhancedImage()
{
	// TODO: 在此添加控件通知处理程序代码
	//指定窗口范围
	CWnd* pWnd = GetDlgItem(IDC_SHOW_IMAGE2);
	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->ClientToScreen(&rect);
	//指定保存文件名
	CString totalFileName = initImgFilePath.Right(initImgFilePath.GetLength() - initImgFilePath.ReverseFind('\\') - 1);
	CString fileName = totalFileName.Left(totalFileName.Find('.')) +  _T("_Enhanced");
	SaveImageFile(rect, fileName);
}

void Chw1Dlg::OnBnClickedSaveEnhancedHist()
{
	// TODO: 在此添加控件通知处理程序代码
	//指定窗口范围
	CWnd* pWnd = GetDlgItem(IDC_SHOW_HIST2);
	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->ClientToScreen(&rect);
	//指定保存文件名
	CString totalFileName = initImgFilePath.Right(initImgFilePath.GetLength() - initImgFilePath.ReverseFind('\\') - 1);
	CString fileName = totalFileName.Left(totalFileName.Find('.')) +  _T("_Enhanced_Hist");
	SaveImageFile(rect, fileName);
}

void Chw1Dlg::OnBnClickedHistEqual()
{
	// TODO: 在此添加控件通知处理程序代码
	//禁止点击
	GetDlgItem(IDC_SAVE_ENHANCED_HIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_ENHANCED_IMAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_OPEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(FALSE);

	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);

	//直方图均衡化
	ATL::CImage newImg;
	HistEqualization(&srcImg, &newImg);

	//获得图像控件窗口的句柄
	CWnd *pWnd = GetDlgItem(IDC_SHOW_IMAGE2);
	//获得图像控件的DC
	CDC *pDC = pWnd->GetDC();	
	//获取图片控件的宽和高
	CRect rect;
	pWnd->GetClientRect(&rect);
	//绘图
	pDC->SetStretchBltMode(HALFTONE);	//防止图片失真
	newImg.Draw(pDC->m_hDC, rect); //将图片画到图像控件表示的矩形区域

	//获得控件的句柄
	pWnd = GetDlgItem(IDC_SHOW_HIST2);
	//图像灰度统计数据
	int histData[256] = {0};
	//统计灰度数据
	GetHistData(&newImg, histData);
	//绘制直方图
	DrawHistogram(pWnd, histData);

	//释放图像控件的DC
	ReleaseDC(pDC);	
	//信息提示
	SetDlgItemText(IDC_MSG, _T("Histogram Equalization for image file \"") + initImgFilePath + _T("\" succeed!"));
	//恢复点击
	GetDlgItem(IDC_SAVE_ENHANCED_HIST)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVE_ENHANCED_IMAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(TRUE);

	GetDlgItem(IDC_OPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(TRUE);

	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
}

void Chw1Dlg::OnBnClickedMedianFilter()
{
	// TODO: 在此添加控件通知处理程序代码
	//禁止点击
	GetDlgItem(IDC_SAVE_ENHANCED_HIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_ENHANCED_IMAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(FALSE);

	GetDlgItem(IDC_OPEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(FALSE);

	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);

	ATL::CImage newImg;
	int choose = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();
	//选中3*3
	if(choose)
		MedianFilter9(&newImg, &srcImg);
	//选中5*5
	else
		MedianFilter25(&newImg, &srcImg);

	//获得图像控件窗口的句柄
	CWnd *pWnd = GetDlgItem(IDC_SHOW_IMAGE2);
	//获得图像控件的DC
	CDC *pDC = pWnd->GetDC();	
	//获取图片控件的宽和高
	CRect rect;
	pWnd->GetClientRect(&rect);
	//绘图
	pDC->SetStretchBltMode(HALFTONE);	//防止图片失真
	newImg.Draw(pDC->m_hDC, rect); //将图片画到图像控件表示的矩形区域

	//获得控件的句柄
	pWnd = GetDlgItem(IDC_SHOW_HIST2);
	//图像灰度统计数据
	int histData[256] = {0};
	//统计灰度数据
	GetHistData(&newImg, histData);
	//绘制直方图
	DrawHistogram(pWnd, histData);

	//释放图像控件的DC
	ReleaseDC(pDC);
	//信息提示
	if(choose)
		SetDlgItemText(IDC_MSG, _T("Median Filtering (3*3) for image file \"") + initImgFilePath + _T("\" succeed!"));
	else
		SetDlgItemText(IDC_MSG, _T("Median Filtering (5*5) for image file \"") + initImgFilePath + _T("\" succeed!"));

	//恢复点击
	GetDlgItem(IDC_SAVE_ENHANCED_HIST)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVE_ENHANCED_IMAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(TRUE);

	GetDlgItem(IDC_OPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(TRUE);

	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
}

void Chw1Dlg::OnBnClickedMeanFilter()
{
	// TODO: 在此添加控件通知处理程序代码
	//禁止点击
	GetDlgItem(IDC_SAVE_ENHANCED_HIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_ENHANCED_IMAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(FALSE);

	GetDlgItem(IDC_OPEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(FALSE);

	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);

	ATL::CImage newImg;
	int choose = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();
	//选中3*3
	if(choose)
		MeanFilter9(&newImg, &srcImg);
	//选中5*5
	else
		MeanFilter25(&newImg, &srcImg);

	//获得图像控件窗口的句柄
	CWnd *pWnd = GetDlgItem(IDC_SHOW_IMAGE2);
	//获得图像控件的DC
	CDC *pDC = pWnd->GetDC();	
	//获取图片控件的宽和高
	CRect rect;
	pWnd->GetClientRect(&rect);
	//绘图
	pDC->SetStretchBltMode(HALFTONE);	//防止图片失真
	newImg.Draw(pDC->m_hDC, rect); //将图片画到图像控件表示的矩形区域

	//获得控件的句柄
	pWnd = GetDlgItem(IDC_SHOW_HIST2);
	//图像灰度统计数据
	int histData[256] = {0};
	//统计灰度数据
	GetHistData(&newImg, histData);
	//绘制直方图
	DrawHistogram(pWnd, histData);

	//释放图像控件的DC
	ReleaseDC(pDC);	
	//信息提示
	if(choose)
		SetDlgItemText(IDC_MSG, _T("Mean Filtering (3*3) for image file \"") + initImgFilePath + _T("\" succeed!"));
	else
		SetDlgItemText(IDC_MSG, _T("Mean Filtering (5*5) for image file \"") + initImgFilePath + _T("\" succeed!"));

	//恢复点击
	GetDlgItem(IDC_SAVE_ENHANCED_HIST)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVE_ENHANCED_IMAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(TRUE);

	GetDlgItem(IDC_OPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(TRUE);

	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
}

void Chw1Dlg::OnBnClickedSharpenFilter()
{
	// TODO: 在此添加控件通知处理程序代码
	//禁止点击
	GetDlgItem(IDC_SAVE_ENHANCED_HIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_ENHANCED_IMAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(FALSE);

	GetDlgItem(IDC_OPEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(FALSE);

	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);

	//空间锐化滤波
	ATL::CImage newImg;
	SharpenFilter(&newImg, &srcImg);
	//获得图像控件窗口的句柄
	CWnd *pWnd = GetDlgItem(IDC_SHOW_IMAGE2);
	//获得图像控件的DC
	CDC *pDC = pWnd->GetDC();	
	//获取图片控件的宽和高
	CRect rect;
	pWnd->GetClientRect(&rect);
	//绘图
	pDC->SetStretchBltMode(HALFTONE);	//防止图片失真
	newImg.Draw(pDC->m_hDC, rect); //将图片画到图像控件表示的矩形区域

	//获得控件的句柄
	pWnd = GetDlgItem(IDC_SHOW_HIST2);
	//图像灰度统计数据
	int histData[256] = {0};
	//统计灰度数据
	GetHistData(&newImg, histData);
	//绘制直方图
	DrawHistogram(pWnd, histData);

	//释放图像控件的DC
	ReleaseDC(pDC);	
	//信息提示
	SetDlgItemText(IDC_MSG, _T("Horizontal Stripe Elimination for image file \"") + initImgFilePath + _T("\" succeed!"));
	//恢复点击
	GetDlgItem(IDC_SAVE_ENHANCED_HIST)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVE_ENHANCED_IMAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(TRUE);

	GetDlgItem(IDC_OPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(TRUE);

	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
}

//设置卷积算子
void  Chw1Dlg::SetOperator(char oper[5][5])
{
	//去除水平条纹
	oper[0][0]=0;	oper[0][1]=1;	oper[0][2]=0;
	oper[1][0]=0;	oper[1][1]=1;	oper[1][2]=0;
	oper[2][0]=0;	oper[2][1]=1;	oper[2][2]=0;
}

//空间锐化滤波
void Chw1Dlg::SharpenFilter(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	CopyImage(pNewImage, pImage);
	//卷积模板
	char	 oper[5][5];
	//设置卷积算子
	SetOperator(oper);
	//单通道
	if(pImage->GetBPP() / 8 == 1)
	{
		ATL::CImage	images[3];
		//图像加边
		AddImageBorder(&images[0], pImage);
		//图像与算子卷积
		Convolution(&images[1], &images[0],oper,3,0,3,3);
		//图像去边
		SubtractImageBorder(pNewImage, &images[1]);
	}
	//3通道
	else if (pImage->GetBPP() / 8 == 3)
	{
		//拆分为R，G，B三个分量图像
		ATL::CImage images[3];
		GetRedOfTrueColor(&images[0], pImage);
		GetGreenOfTrueColor(&images[1], pImage);
		GetBlueOfTrueColor(&images[2], pImage);
		//分别做卷积
		for (int i = 0; i < 3; i++)
		{
			ATL::CImage	tmpImages[3];
			//图像加边
			AddImageBorder(&tmpImages[0], &images[i]);
			//图像与算子卷积
			Convolution(&tmpImages[1], &tmpImages[0],oper,3,0,3,3);
			//图像去边
			SubtractImageBorder(&images[i], &tmpImages[1]);
		}
		//合并为RGB图像
		for( int x = 0; x < pImage->GetHeight(); x++) 
		{
			for( int y = 0; y < pImage->GetWidth(); y++)
			{
				//读取图像像素值
				BYTE rgb[3] = {0};
				for (int z = 0; z < 3; z++)
				{
					//当前图像像素数据的指针
					BYTE* pRealData = (BYTE*)images[z].GetBits();
					//相邻两行像素首地址之间的间隔
					int pitch = images[z].GetPitch();
					//int bitCount = images[z].GetBPP() / 8;
					rgb[z] = *(pRealData + pitch * x + y);
				}
				pNewImage->SetPixelRGB(y, x, rgb[0], rgb[1], rgb[2]);
			}
		}
	}
}

//中值滤波: 3*3
void Chw1Dlg::MedianFilter9(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	//获取图像的宽和高，像素所占位数
	int imgWidth = pImage->GetWidth();
	int imgHeight = pImage->GetHeight();
	int bitCount = pImage->GetBPP();
	//创建新图像
	pNewImage->Create(imgWidth, imgHeight, bitCount);
	//复制调色板
	CopyColorTables(pNewImage, pImage);

	BYTE pValue[9], cNewPixel;
	//单通道
	if(bitCount / 8 == 1)
	{
		for (int i = 1; i < imgHeight - 1; i++)
		{
			for (int j = 1; j < imgWidth - 1; j++)
			{
				//取本点和8邻点数据
				int count = 0;
				for(int m = -1; m <= 1; m++)
				{
					for(int n = -1; n <= 1; n++)
					{
						pValue[count++] = (BYTE)GetPixelValue(pImage, i + m, j + n);
					}
				}
				//取中值
				cNewPixel = GetMedian(pValue, 9);
				//设置新图像像素
				SetPixelValueOfIndexImg(pNewImage, i, j, cNewPixel);
			}
		}
	}
	//3通道
	else if (pImage->GetBPP() / 8 == 3)
	{
		//拆分为R，G，B三个分量图像
		ATL::CImage images[3];
		GetRedOfTrueColor(&images[0], pImage);
		GetGreenOfTrueColor(&images[1], pImage);
		GetBlueOfTrueColor(&images[2], pImage);
		//分别做滤波
		ATL::CImage	tmpImages[3];
		for (int i = 0; i < 3; i++)
		{
			MedianFilter9(&tmpImages[i], &images[i]);
		}
		//合并为RGB图像
		for( int x = 0; x < imgHeight; x++) 
		{
			for( int y = 0; y < imgWidth; y++)
			{
				//读取图像像素值
				BYTE rgb[3] = {0};
				for (int z = 0; z < 3; z++)
				{
					//当前图像像素数据的指针
					BYTE* pRealData = (BYTE*)tmpImages[z].GetBits();
					//相邻两行像素首地址之间的间隔
					int pitch = tmpImages[z].GetPitch();
					//int bitCount = images[z].GetBPP() / 8;
					rgb[z] = *(pRealData + pitch * x + y);
				}
				pNewImage->SetPixelRGB(y, x, rgb[0], rgb[1], rgb[2]);
			}
		}
	}
}

//中值滤波: 5*5
void Chw1Dlg::MedianFilter25(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	//获取图像的宽和高，像素所占位数
	int imgWidth = pImage->GetWidth();
	int imgHeight = pImage->GetHeight();
	int bitCount = pImage->GetBPP();
	//创建新图像
	pNewImage->Create(imgWidth, imgHeight, bitCount);
	//复制调色板
	CopyColorTables(pNewImage, pImage);

	BYTE pValue[25], cNewPixel;
	//单通道
	if(bitCount / 8 == 1)
	{
		for (int i = 2; i < imgHeight - 2; i++)
		{
			for (int j = 2; j < imgWidth - 2; j++)
			{
				//取本点和24邻点数据
				int count = 0;
				for(int m = -2; m <= 2; m++)
				{
					for(int n = -2; n <= 2; n++)
					{
						pValue[count++] = (BYTE)GetPixelValue(pImage, i + m, j + n);
					}
				}
				//取中值
				cNewPixel = GetMedian(pValue, 25);
				//设置新图像像素
				SetPixelValueOfIndexImg(pNewImage, i, j, cNewPixel);
			}
		}
	}
	//3通道
	else if (pImage->GetBPP() / 8 == 3)
	{
		//拆分为R，G，B三个分量图像
		ATL::CImage images[3];
		GetRedOfTrueColor(&images[0], pImage);
		GetGreenOfTrueColor(&images[1], pImage);
		GetBlueOfTrueColor(&images[2], pImage);
		//分别做滤波
		ATL::CImage	tmpImages[3];
		for (int i = 0; i < 3; i++)
		{
			MedianFilter25(&tmpImages[i], &images[i]);
		}
		//合并为RGB图像
		for( int x = 0; x < imgHeight; x++) 
		{
			for( int y = 0; y < imgWidth; y++)
			{
				//读取图像像素值
				BYTE rgb[3] = {0};
				for (int z = 0; z < 3; z++)
				{
					//当前图像像素数据的指针
					BYTE* pRealData = (BYTE*)tmpImages[z].GetBits();
					//相邻两行像素首地址之间的间隔
					int pitch = tmpImages[z].GetPitch();
					//int bitCount = images[z].GetBPP() / 8;
					rgb[z] = *(pRealData + pitch * x + y);
				}
				pNewImage->SetPixelRGB(y, x, rgb[0], rgb[1], rgb[2]);
			}
		}
	}
}

//对像素值进行排序
int Chw1Dlg::GetMedian(BYTE pixels[], int count)
{
	//冒泡排序
	for (int i = 0; i < count; i++)
	{
		for (int j = count - 2; j > i; j--) 
		{
			if (pixels[j] > pixels[j+1]) 
			{	                           
				int temp = pixels[j];
				pixels[j] = pixels[j+1];  
				pixels[j+1] = temp;    
			}
		}
	}
	return pixels[(count - 1) / 2];
}

//均值滤波: 3*3
void Chw1Dlg::MeanFilter9(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	//获取图像的宽和高，像素所占位数
	int imgWidth = pImage->GetWidth();
	int imgHeight = pImage->GetHeight();
	int bitCount = pImage->GetBPP();
	//创建新图像
	pNewImage->Create(imgWidth, imgHeight, bitCount);
	//复制调色板
	CopyColorTables(pNewImage, pImage);

	BYTE pValue[9], cNewPixel;
	//单通道
	if(bitCount / 8 == 1)
	{
		for (int i = 1; i < imgHeight - 1; i++)
		{
			for (int j = 1; j < imgWidth - 1; j++)
			{
				//取本点和8邻点数据
				int count = 0;
				for(int m = -1; m <= 1; m++)
				{
					for(int n = -1; n <= 1; n++)
					{
						pValue[count++] = (BYTE)GetPixelValue(pImage, i + m, j + n);
					}
				}
				//取均值
				int sum = 0;
				for(int k = 0; k < 9; k++)
					sum += pValue[k];
				cNewPixel = (int)(sum / 9.0);
				//设置新图像像素
				SetPixelValueOfIndexImg(pNewImage, i, j, cNewPixel);
			}
		}
	}
	//3通道
	else if (pImage->GetBPP() / 8 == 3)
	{
		//拆分为R，G，B三个分量图像
		ATL::CImage images[3];
		GetRedOfTrueColor(&images[0], pImage);
		GetGreenOfTrueColor(&images[1], pImage);
		GetBlueOfTrueColor(&images[2], pImage);
		//分别做滤波
		ATL::CImage	tmpImages[3];
		for (int i = 0; i < 3; i++)
		{
			MeanFilter9(&tmpImages[i], &images[i]);
		}
		//合并为RGB图像
		for( int x = 0; x < imgHeight; x++) 
		{
			for( int y = 0; y < imgWidth; y++)
			{
				//读取图像像素值
				BYTE rgb[3] = {0};
				for (int z = 0; z < 3; z++)
				{
					//当前图像像素数据的指针
					BYTE* pRealData = (BYTE*)tmpImages[z].GetBits();
					//相邻两行像素首地址之间的间隔
					int pitch = tmpImages[z].GetPitch();
					//int bitCount = images[z].GetBPP() / 8;
					rgb[z] = *(pRealData + pitch * x + y);
				}
				pNewImage->SetPixelRGB(y, x, rgb[0], rgb[1], rgb[2]);
			}
		}
	}
}

//均值滤波: 5*5
void Chw1Dlg::MeanFilter25(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	//获取图像的宽和高，像素所占位数
	int imgWidth = pImage->GetWidth();
	int imgHeight = pImage->GetHeight();
	int bitCount = pImage->GetBPP();
	//创建新图像
	pNewImage->Create(imgWidth, imgHeight, bitCount);
	//复制调色板
	CopyColorTables(pNewImage, pImage);

	BYTE pValue[25], cNewPixel;
	//单通道
	if(bitCount / 8 == 1)
	{
		for (int i = 2; i < imgHeight - 2; i++)
		{
			for (int j = 2; j < imgWidth - 2; j++)
			{
				//取本点和24邻点数据
				int count = 0;
				for(int m = -2; m <= 2; m++)
				{
					for(int n = -2; n <= 2; n++)
					{
						pValue[count++] = (BYTE)GetPixelValue(pImage, i + m, j + n);
					}
				}
				//取均值
				int sum = 0;
				for(int k = 0; k < 25; k++)
					sum += pValue[k];
				cNewPixel = (int)(sum / 25.0);
				//设置新图像像素
				SetPixelValueOfIndexImg(pNewImage, i, j, cNewPixel);
			}
		}
	}
	//3通道
	else if (pImage->GetBPP() / 8 == 3)
	{
		//拆分为R，G，B三个分量图像
		ATL::CImage images[3];
		GetRedOfTrueColor(&images[0], pImage);
		GetGreenOfTrueColor(&images[1], pImage);
		GetBlueOfTrueColor(&images[2], pImage);
		//分别做滤波
		ATL::CImage	tmpImages[3];
		for (int i = 0; i < 3; i++)
		{
			MeanFilter25(&tmpImages[i], &images[i]);
		}
		//合并为RGB图像
		for( int x = 0; x < imgHeight; x++) 
		{
			for( int y = 0; y < imgWidth; y++)
			{
				//读取图像像素值
				BYTE rgb[3] = {0};
				for (int z = 0; z < 3; z++)
				{
					//当前图像像素数据的指针
					BYTE* pRealData = (BYTE*)tmpImages[z].GetBits();
					//相邻两行像素首地址之间的间隔
					int pitch = tmpImages[z].GetPitch();
					//int bitCount = images[z].GetBPP() / 8;
					rgb[z] = *(pRealData + pitch * x + y);
				}
				pNewImage->SetPixelRGB(y, x, rgb[0], rgb[1], rgb[2]);
			}
		}
	}
}

//绘制图像灰度直方图
void Chw1Dlg::DrawHistogram(CWnd* pWnd, int histData[])
{
	int i;	// 循环变量
	CDC* pDC = pWnd->GetDC();	//获取设备上下文

	//获取绘图区大小
	CRect rect;
	pWnd->GetClientRect(&rect);
	//刷新绘图区
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	//画一个矩形从而当做画直方图的区域
	//pDC->Rectangle(rect);	
	//pDC->Rectangle(0, 0, 400, 203);			//画一个矩形从而当做画直方图的区域

	CPaintDC dc(this); //获取绘图设备上下文
	// 创建画笔对象
	CPen* pPenRed = new CPen;
	// 创建红色画笔（用于绘制坐标轴）
	pPenRed->CreatePen(PS_SOLID, 1, RGB(255,0,0));
	// 选入红色画笔，并保存以前的画笔
	CPen* pOldPen = pDC->SelectObject(pPenRed);

	// 直方图中最大计数值
	LONG maxCount = 0;
	// 计算最大计数值
	for (i = 0; i <= 255; i ++)
	{
		// 判断是否大于当前最大值
		if (histData[i] > maxCount)
		{
			// 更新最大值
			maxCount = histData[i];
		}
	}

	// 画直方图的坐标
	// 绘制y轴
	pDC->MoveTo(10,5);	
	pDC->LineTo(10, 210);
	// 绘制x轴
	pDC->MoveTo(10,210);	
	pDC->LineTo(270, 210);
	// 绘制X轴刻度值
	CString strTemp;
	strTemp.Format(_T("0"));
	pDC->TextOut(5, 215, strTemp);
	strTemp.Format(_T("50"));
	pDC->TextOut(55, 215, strTemp);
	strTemp.Format(_T("100"));
	pDC->TextOut(105, 215, strTemp);
	strTemp.Format(_T("150"));
	pDC->TextOut(155, 215, strTemp);
	strTemp.Format(_T("200"));
	pDC->TextOut(205, 215, strTemp);
	strTemp.Format(_T("255"));
	pDC->TextOut(250, 215, strTemp);
	// 绘制X轴刻度
	for (i = 0; i < 256; i += 5)
	{
		if ((i & 1) == 0)		//偶数，即10的倍数
		{		
			pDC->MoveTo(i + 10, 210);
			pDC->LineTo(i + 10, 215);
		}
		else					//奇数，即 5的奇数倍数
		{
			pDC->MoveTo(i + 10, 210);
			pDC->LineTo(i + 10, 212);
		}
	}
	//画横纵坐标的箭头
	// 绘制X轴箭头
	pDC->MoveTo(270, 210);
	pDC->LineTo(265, 205);
	pDC->MoveTo(270, 210);
	pDC->LineTo(265, 215);
	// 绘制Y轴箭头
	pDC->MoveTo(10, 5);
	pDC->LineTo(15, 10);
	pDC->MoveTo(10, 5);
	pDC->LineTo(5, 10);

	// 绘制Y轴刻度
	int Ystep = 200 / 20;	//y轴坐标系数的刻度步长
	for (i = 1; i <= 20; i += 1)
	{
		double yValue = 210 - Ystep * i;
		pDC->MoveTo(10, (int)yValue);
		if (i % 2 == 0)
			pDC->LineTo(15, (int)yValue);
		else
			pDC->LineTo(12, (int)yValue);
	}

	// 输出最大计数值
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 10);
	strTemp.Format(_T("%d"), maxCount);
	pDC->TextOut(16, 5, strTemp);

	// 声名画笔对象
	CPen* pPenBlue = new CPen;
	// 创建蓝色画笔（用于绘制直方图）
	pPenBlue->CreatePen(PS_SOLID, 1, RGB(0,0,255));
	// 选入蓝色画笔
	pDC->SelectObject(pPenBlue);
	CString str;
	if(maxCount > 0)
	{
		// 绘制直方图
		for (i = 0; i < 256; i ++)
		{
			pDC->MoveTo(i + 10, 210);
			pDC->LineTo(i + 10, 210 - (int) (histData[i] * 200 / maxCount) );
		}
	}
	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);	

	// 释放图像控件的DC
	ReleaseDC(pDC);
	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
	// Do not call CDialog::OnPaint() for painting messages
}

//截取图片空间内显示的图片并保存
HBITMAP Chw1Dlg::CopyScreenToBitmap(LPRECT lpRect)
{
	HDC hScrDC, hMemDC;      
	// 屏幕和内存设备描述表
	HBITMAP hBitmap,hOldBitmap;   
	// 位图句柄
	int nX, nY, nX2, nY2;      
	// 选定区域坐标
	int nWidth, nHeight;      
	// 位图宽度和高度
	int xScrn, yScrn;         
	// 屏幕分辨率
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;
	//为屏幕创建设备描述表
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// 获得屏幕分辨率
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > xScrn)
		nX2 = xScrn;
	if (nY2 > yScrn)
		nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
	//得到屏幕位图的句柄
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// 返回位图句柄
	return hBitmap;
}

//保存图像文件
void Chw1Dlg::SaveImageFile(LPRECT rect, CString fileName)
{
	//界面截图
	HBITMAP hBitmap = CopyScreenToBitmap(rect);	//截为位图
	//将位图与CImage对象相连接
	ATL::CImage saveImage;
	saveImage.Attach(hBitmap);

	//保存图像对话框
	CString strExtension = _T(".bmp"); //默认扩展名是.bmp 
	CFileDialog saveFileDlg(FALSE, strExtension, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, _T("位图文件(*.bmp)|*.bmp|JPEG 图像文件(*.jpg)|*.jpg|GIF 图像文件(*.gif)|*.gif|PNG 图像文件(*.png)|*.png|所有文件(*.*)|*.*||")); 
	if ( IDOK != saveFileDlg.DoModal()) 
		return; 

	// 如果用户没有指定文件扩展名，则为其添加一个 
	CString strFileName = saveFileDlg.m_ofn.lpstrFile;	//文件名
	if (saveFileDlg.m_ofn.nFileExtension == 0) 
	{ 
		switch (saveFileDlg.m_ofn.nFilterIndex) 
		{ 
		case 1: 
			strExtension = _T(".bmp"); 
			break; 
		case 2: 
			strExtension = _T(".jpg");
			break; 
		case 3: 
			strExtension = _T(".gif"); 
			break; 
		case 4: 
			strExtension = _T(".png"); 
			break; 
		default: 
			strExtension = _T(".bmp");
			break; 
		} 
		strFileName = strFileName + strExtension; 
	}

	//图像保存提示
	HRESULT hResult = saveImage.Save(strFileName);
	if (FAILED(hResult)) 
		SetDlgItemText(IDC_MSG, _T("Save image file \"") + strFileName + _T("\" failed!"));
	else
		SetDlgItemText(IDC_MSG, _T("Save image file \"") + strFileName + _T("\" successfully!"));
}

//从图象数据中取单个像素数据
DWORD Chw1Dlg::GetPixelValue(ATL::CImage *pImage, int height, int width)
{
	DWORD	dwPixelValue;
	BYTE		*pPixel;

	//取像素数据存放地址
	pPixel = (BYTE*) pImage->GetPixelAddress(width, height);
	switch(pImage->GetBPP())
	{
	case 1:		//传出二值图象像素数据
		memcpy(&dwPixelValue, pPixel, 1);
		dwPixelValue = dwPixelValue & 0x1;
		break;

	case 4:		//传出16色图象像素数据
		memcpy(&dwPixelValue, pPixel, 1);
		dwPixelValue = dwPixelValue & 0xf;
		break;

	case 8:		//传出256色图象像素数据
		memcpy(&dwPixelValue, pPixel, 1);
		break;

	case 24:		//传出真彩色图象像素数据
		memcpy(&dwPixelValue, pPixel, 3);
		dwPixelValue=dwPixelValue & 0xffffff;
		break;
	}
	return (dwPixelValue);
}

//复制调色板
void Chw1Dlg::CopyColorTables(ATL::CImage *pNewImage, ATL::CImage*pImage)
{
	int nColorTableEntries;
	RGBQUAD	ColorTabs[256];

	nColorTableEntries = pImage->GetMaxColorTableEntries();
	if (nColorTableEntries > 0)
	{
		pImage->GetColorTable(0,nColorTableEntries,ColorTabs);    
		pNewImage->SetColorTable(0,nColorTableEntries,ColorTabs);   //  复制调色板
	}
}

//设置256色图象单个像素数据
void Chw1Dlg::SetPixelValueOfIndexImg(ATL::CImage *pImage, int height, int width, BYTE pixel)
{
	BYTE *pPixel;
	//取像素数据存放地址
	pPixel = (BYTE*) pImage->GetPixelAddress(width, height);
	memcpy(pPixel, &pixel, 1);
}

//设置真彩色图象单个像素数据
void Chw1Dlg::SetPixelValueOfTruColorImage(ATL::CImage *pImage, int height, int width, DWORD dwPixel)
{
	BYTE *pPixel;
	//取像素数据存放地址
	pPixel= (BYTE*) pImage->GetPixelAddress(width, height);
	memcpy(pPixel, &dwPixel, 3);
}

//统计灰度数据
void Chw1Dlg::GetHistData(ATL::CImage *pImage, int histData[])
{
	//当前图像像素数据的指针
	BYTE* pRealData = (BYTE*)pImage->GetBits();
	//获取图像的宽和高
	int imgWidth = pImage->GetWidth();
	int imgHeight = pImage->GetHeight();
	//相邻两行像素首地址之间的间隔
	int pitch = pImage->GetPitch();
	//当前图像的每像素位数
	int bitCount = pImage->GetBPP() / 8;
	//1.如果是单通道图像，直接读取一个BYTE位为灰度值
	if(bitCount == 1)
	{
		for (int y = 0; y < imgHeight; y++) 
		{
			for (int x = 0; x < imgWidth; x++) 
			{
				//读取图像像素值
				int grayValue = *(pRealData + pitch * y + x * bitCount);
				histData[grayValue]++;
				//imgData[y][x] = grayValue;
			}
		}
		//for(int i = 0; i < imgHeight; i++) 
		//{   
		//	//行首地址
		//	BYTE* pLinePixels = (BYTE*)srcImg.GetPixelAddress(0, i);
		//	for (int j = 0; j < imgWidth; j++)
		//	{
		//		//灰度值计数
		//		int cPixel = (int)(*(pLinePixels + j));
		//		histData[cPixel]++;
		//	}
		//}
	}
	//2.如果是3通道图像，则依次读取pixAddr, pixAddr+1, pixAddr+2为B、G、R分量值
	else if(bitCount == 3)
	{
		for (int y = 0; y < imgHeight; y++) 
		{
			for (int x = 0; x < imgWidth; x++) 
			{
				//读取图像像素值
				int bValue = *(pRealData + pitch * y + x * bitCount);
				int gValue = *(pRealData + pitch * y + x * bitCount + 1);
				int rValue = *(pRealData + pitch * y + x * bitCount + 2);

				//灰度化操作
				//int grayVal=(int)(int)(bValue)*0.3+(int)(int)(gValue)*0.59+(int)(int)(rValue)*0.11;
				int grayValue = ((int)rValue*299 + (int)gValue*587 + (int)bValue*114 + 500) / 1000;
				histData[grayValue]++;
				//imgData[y][x] = grayValue;
			}
		}
	}
}

//求三个数中的最大值
BYTE Chw1Dlg::GetMax(BYTE cData1,BYTE cData2,BYTE cData3)
{
	BYTE cMax;
	cMax=cData1>cData2?cData1:cData2;
	cMax=cMax>cData3?cMax:cData3;

	return cMax;
}

//求三个数中的最小值
BYTE Chw1Dlg::GetMin(BYTE cData1,BYTE cData2,BYTE cData3)
{
	BYTE cMin;
	cMin=cData1>cData2?cData2:cData1;
	cMin=cMin>cData3?cData3:cMin;

	return cMin;
}

//计算HSV色调值
int  Chw1Dlg::GetHueFromRGB(int nAngle, int nRed, int nGreen, int nBlue)
{
	int	nHue256;
	float	fHue360;

	fHue360=(float)(nAngle+120.0*(nGreen-nBlue)/(nGreen-nBlue+nRed-nBlue));
	nHue256=(int)(256.0*fHue360/360.0+0.5);//将0~360度转换为0~256

	return (nHue256);
}

//RGB空间转到HSV空间
void Chw1Dlg::RGBToHSV(BYTE *pHue, BYTE *pSaturation, BYTE *pValue, BYTE cRed, BYTE cGreen, BYTE cBlue)
{
	BYTE	cMax, cMin;
	int	nAngle;

	//找出最大最小值
	cMax = GetMax(cRed,cGreen,cBlue);             
	cMin = GetMin(cRed,cGreen,cBlue);    
	//三分量相同为灰阶，无色调
	if (cMax==cMin) 
	{                 
		*pHue=0;    
		*pSaturation=0;
	}
	//为彩色 
	else
	{                                   
		//计算饱和度     
		*pSaturation=(int) (255.0*(cMax-cMin)/cMax);      
		//最小值为蓝分量
		if (cMin==cBlue)
		{
			nAngle=0;
			*pHue=GetHueFromRGB(nAngle,cRed,cGreen,cBlue);//计算色调值       
		}
		//最小值为红分量    
		else if (cMin==cRed) 
		{               
			nAngle=120;
			*pHue=GetHueFromRGB(nAngle,cGreen,cBlue,cRed);//计算色调值       
		}
		//最小值为绿分量   
		else if (cMin==cGreen) 
		{                 
			nAngle=240;
			*pHue=GetHueFromRGB(nAngle,cBlue,cRed,cGreen);//计算色调值       
		}
	}
	*pValue=cMax;
}

//HSV 模式转换成 RGB 模式
void Chw1Dlg::HSVToRGB(BYTE *pRed, BYTE *pGreen, BYTE *pBlue, BYTE cHue, BYTE cSaturation, BYTE cValue)
{
	int  nMin,nHue;
	nHue=(int)(360.0*cHue/255.0);//色调值转换成角度

	if (cSaturation==0) 
	{//饱和度等于 0 时为灰阶
		*pRed=*pGreen=*pBlue=cValue;//三分量相等
	}
	else 
	{//否则，为彩色
		nMin=(int)((255.0-cSaturation)*cValue/255.0);//计算最小分量
		if (nHue<=120) 
		{//颜色在红绿区                           
			*pBlue=nMin;//蓝分量最小
			if (nHue<=60) 
			{
				*pRed=cValue;//红分量最大
				*pGreen=(int)(nMin+(double)nHue*(cValue-nMin)/(120.0-nHue));
			}
			else
			{
				*pGreen=cValue;                              
				*pRed=(int)(nMin+(120.0-nHue)*(cValue-nMin)/nHue);
			}
		}
		else 
			if (nHue<=240) 
			{//颜色在绿蓝区
				*pRed=nMin;//红分量最小
				if (nHue<=180) 
				{
					*pGreen=cValue;//绿分量最大
					*pBlue=(int)(nMin+(nHue-120.0)*(cValue-nMin)/(240.0-nHue));
				}
				else 
				{
					*pBlue=cValue;//蓝分量最大
					*pGreen=(int)(nMin+(240.0-nHue)*(cValue-nMin)/(nHue-120.0));
				}
			}
			else 
			{//颜色在蓝红区                                    
				*pGreen=nMin;                                 
				if (nHue<=300) 
				{
					*pBlue=cValue;//蓝分量最大                              
					*pRed=(int)(nMin+(nHue-240.0)*(cValue-nMin)/(360.0-nHue));
				}
				else 
				{
					*pRed=cValue;                              
					*pBlue=(int)(nMin+(360.0-nHue)*(cValue-nMin)/(nHue-240.0));
				}
			}
	}
}

//直方图均衡化
void Chw1Dlg::HistEqualization(ATL::CImage *pImage, ATL::CImage *pNewImage)
{
	int i, j;
	BYTE cRed,cGreen,cBlue,cHue,cSaturation,cValue;
	int valueHistData[256] = {0};

	//获取图像的宽和高
	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	pNewImage->Create(nWidth, nHeight, pImage->GetBPP());
	//复制调色板
	CopyColorTables(pNewImage, pImage);

	//新建数组存放均衡化后数据
	int** newValueData = new int*[nHeight];
	for(int i = 0; i < nHeight; i++)
	{
		newValueData[i] = new int[nWidth];
	}
	int** newSaturData = new int*[nHeight];
	for(int i = 0; i < nHeight; i++)
	{
		newSaturData[i] = new int[nWidth];
	}
	int** newHueData = new int*[nHeight];
	for(int i = 0; i < nHeight; i++)
	{
		newHueData[i] = new int[nWidth];
	}

	//当前图像像素数据的指针
	BYTE* pRealData = (BYTE*)pImage->GetBits();
	//相邻两行像素首地址之间的间隔
	int pitch = pImage->GetPitch();
	int bitCount = pImage->GetBPP() / 8;
	//获取V分量直方图数据
	for( i = 0; i < nHeight; i++) 
	{
		for( j = 0; j < nWidth; j++)
		{
			//读取图像像素值
			cBlue= *(pRealData + pitch * i + j * bitCount);
			cGreen= *(pRealData + pitch * i + j * bitCount + 1);
			cRed= *(pRealData + pitch * i + j * bitCount + 2);
			//RGB 模式转换成 HSV 模式
			RGBToHSV(&cHue, &cSaturation, &cValue, cRed, cGreen, cBlue);
			//按灰度值在相应单元增量计数
			valueHistData[cValue]++;
			newValueData[i][j] = cValue;
			newSaturData[i][j] = cSaturation;
			newHueData[i][j] = cHue;
		}
	}
	//均衡化
	double valueHistDataRatio[256] = {0.0};
	for(i = 0; i <= 255; i++)
	{
		//求灰度值比例
		valueHistDataRatio[i] = (double) valueHistData[i] / (nWidth * nHeight);
		//求灰度值比例和
		if(i != 0)
			valueHistDataRatio[i] += valueHistDataRatio[i - 1];
	}
	//重新映射
	for(i = 0; i <= 255; i++)
	{
		valueHistData[i] = (int)(valueHistDataRatio[i] * 255);
	}
	//处理得到新图像
	for( i = 0; i < nHeight; i++) 
	{
		for ( j = 0; j < nWidth; j++)
		{
			int index = newValueData[i][j];
			BYTE satur= newSaturData[i][j];
			BYTE hue= newHueData[i][j];
			BYTE val= valueHistData[index];
			//HSV 模式转换成 RGB 模式
			HSVToRGB(&cRed,&cGreen,&cBlue,hue,satur,val);
			DWORD	dwPixelValue;
			dwPixelValue=cRed;
			dwPixelValue<<=8;
			dwPixelValue+=cGreen;
			dwPixelValue<<=8;
			dwPixelValue+=cBlue;
			SetPixelValueOfTruColorImage(pNewImage, i, j, dwPixelValue);
		}
	}
	delete newHueData;
	delete newSaturData;
	delete newValueData;
}

//加宽图像(图像加边)，在上下方向各扩展一行，在左右方向各扩展一列
void Chw1Dlg::AddImageBorder(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	BYTE	*pPixel,*pNewPixel;
	int		i,nWidth,nHeight,nBytesPerLine,nBytesPerPixel;

	nWidth=pImage->GetWidth();
	nHeight=pImage->GetHeight();
	nBytesPerLine=(pImage->GetWidth()*pImage->GetBPP()+31)/32*4;
	nBytesPerPixel=pImage->GetBPP() / 8;

	pNewImage->Create(nWidth+2,nHeight+2,pImage->GetBPP());
	CopyColorTables(pNewImage,pImage);//复制调色板

	//向新图像逐行复制像素数据
	for (i=0;i<nHeight;i++) 
	{
		pPixel  = (BYTE*) pImage->GetPixelAddress(0,i);       
		pNewPixel = (BYTE*) pNewImage->GetPixelAddress(1,i+1);
		memcpy(pNewPixel, pPixel,nBytesPerLine);                         
	}

	//扩展顶边一行
	pPixel  = (BYTE*) pImage->GetPixelAddress(0,0); 
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(1,0);
	memcpy(pNewPixel, pPixel,nBytesPerLine);

	//扩展底边一行
	pPixel  = (BYTE*) pImage->GetPixelAddress(0,nHeight-1);
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(1,nHeight+1);
	memcpy(pNewPixel, pPixel,nBytesPerLine);

	//扩展左边一列
	for(i=0;i<nHeight;i++)
	{
		pPixel  = (BYTE*) pImage->GetPixelAddress(0,i);
		pNewPixel = (BYTE*) pNewImage->GetPixelAddress(0,i+1);
		memcpy(pNewPixel,pPixel,nBytesPerPixel);
	}

	//扩展右边一列
	for(i=0;i<nHeight;i++)
	{
		pPixel  = (BYTE*) pImage->GetPixelAddress(nWidth-1,i);
		pNewPixel = (BYTE*) pNewImage->GetPixelAddress(nWidth+1,i+1);
		memcpy(pNewPixel,pPixel,nBytesPerPixel);
	}

	//复制左上角点
	pPixel  = (BYTE*) pImage->GetPixelAddress(0,0);
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(0,0);
	memcpy(pNewPixel,pPixel,nBytesPerPixel);

	//复制右上角点
	pPixel  = (BYTE*) pImage->GetPixelAddress(nWidth-1,0);
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(nWidth+1,0);
	memcpy(pNewPixel,pPixel,nBytesPerPixel);

	//复制左下角点
	pPixel  = (BYTE*) pImage->GetPixelAddress(0,nHeight-1);
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(0,nHeight+1);
	memcpy(pNewPixel,pPixel,nBytesPerPixel);

	//复制右下角点
	pPixel  = (BYTE*) pImage->GetPixelAddress(nWidth-1,nHeight-1);
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(nWidth+1,nHeight+1);
	memcpy(pNewPixel,pPixel,nBytesPerPixel);
}

//图像卷积，Scale衰减因子，Offset偏移值
void Chw1Dlg::Convolution(ATL::CImage *pNewImage,ATL::CImage *pImage,char OP[5][5],int Scale,int Offset,int nOPWidth,int nOPHeight)
{
	int	i,j,m,n,nWidth,nHeight,nNewPixel;
	CopyImage(pNewImage,pImage);

	nWidth=pImage->GetWidth();
	nHeight=pImage->GetHeight();

	for (i=1;i<nHeight-1;i++)
	{
		for (j=1;j<nWidth-1;j++) 
		{
			nNewPixel=0;
			for(m=0;m<nOPHeight;m++)//计算卷积
				for(n=0;n<nOPWidth;n++)
					nNewPixel+=(int)OP[m][n]*(BYTE)GetPixelValue(pImage,i-nOPHeight/2+m,j-nOPWidth/2+n);

			nNewPixel=nNewPixel/Scale+Offset;
			if (nNewPixel>0xff) //计算结果的范围检查
				nNewPixel=0xff;
			else 
				if (nNewPixel<0) 
					nNewPixel=0;

			SetPixelValueOfIndexImg(pNewImage,i,j,(BYTE)nNewPixel);//结果送入输出单元
		}
	}
}

//图像去边
void Chw1Dlg::SubtractImageBorder(ATL::CImage *pNewImage,ATL::CImage *pImage)
{
	BYTE	*pNewLine,*pLine;
	int		i,nBytesPerLine,nHeight;

	CopyImage(pNewImage,pImage);
	//pNewImage->Create(pImage->GetWidth()-2, pImage->GetHeight()-2, pImage->GetBPP());
	//CopyColorTables(pNewImage, pImage);//复制调色板

	nHeight=pNewImage->GetHeight()-2;
	nBytesPerLine=(pImage->GetWidth()*pImage->GetBPP()+31)/32*4;

	for (i=0;i<nHeight;i++) 
	{
		pLine=(BYTE*)pImage->GetPixelAddress(1,i+1);
		pNewLine=(BYTE*)pNewImage->GetPixelAddress(0,i);       
		memcpy(pNewLine,pLine,nBytesPerLine);                         
	}
}

//CImage类对象之间的复制
void Chw1Dlg::CopyImage(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	int nWidth,nHeight,nBitsPerPixel;
	nWidth=pImage->GetWidth();
	nHeight=pImage->GetHeight();
	nBitsPerPixel=pImage->GetBPP();

	//目标位图非空则删除目标位图
	if(!pNewImage->IsNull())
		pNewImage->Destroy();
	//建立CImage类对象新位图
	pNewImage->Create(nWidth,nHeight,nBitsPerPixel,0);
	//复制调色板
	CopyColorTables(pNewImage, pImage);
}

//对图象进行取RGB模式中红分量处理
void Chw1Dlg::GetRedOfTrueColor(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	DWORD	dwPixelValue;
	BYTE cPixel7_0;
	int	i,j,nWidth,nHeight;

	nWidth=pImage->GetWidth();
	nHeight=pImage->GetHeight();

	if(!pNewImage->IsNull())
		pNewImage->Destroy();
	pNewImage->Create(nWidth,nHeight,8,0);
	for (i=0;i<256;i++) 
		SetOneColorTableInPalette(pNewImage,i,i,0,0);

	for(i=0;i<nHeight;i++)
	{
		for (j=0;j<nWidth;j++) 
		{
			dwPixelValue=GetPixelValue(pImage,i,j);
			cPixel7_0=(BYTE)(dwPixelValue & 0xff);

			SetPixelValueOfIndexImg(pNewImage,i,j,cPixel7_0);
		}
	}
}

//对图象进行取RGB模式中绿分量处理
void Chw1Dlg::GetGreenOfTrueColor(ATL::CImage  *pNewImage, ATL::CImage  *pImage)
{
	DWORD	dwPixelValue;
	BYTE		cPixel15_8;
	int				i,j,nWidth,nHeight;

	nWidth=pImage->GetWidth();
	nHeight=pImage->GetHeight();

	if(!pNewImage->IsNull())
		pNewImage->Destroy();
	pNewImage->Create(nWidth,nHeight,8,0);
	for (i=0;i<256;i++) 
		SetOneColorTableInPalette(pNewImage,i,0,i,0);

	for(i=0;i<nHeight;i++)
	{
		for (j=0;j<nWidth;j++) 
		{
			dwPixelValue=GetPixelValue(pImage,i,j);
			cPixel15_8=(BYTE)((dwPixelValue & 0xff00)>>8);

			SetPixelValueOfIndexImg(pNewImage,i,j,cPixel15_8);
		}
	}
}

//对图象进行取RGB模式中蓝分量处理
void Chw1Dlg::GetBlueOfTrueColor(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	DWORD	dwPixelValue;
	BYTE		cPixel23_16;
	int				i,j,nWidth,nHeight;

	nWidth=pImage->GetWidth();
	nHeight=pImage->GetHeight();

	if(!pNewImage->IsNull())
		pNewImage->Destroy();
	pNewImage->Create(nWidth,nHeight,8,0);
	for (i=0;i<256;i++) 
		SetOneColorTableInPalette(pNewImage,i,0,0,i);

	for(i=0;i<nHeight;i++)
	{
		for (j=0;j<nWidth;j++) 
		{
			dwPixelValue=GetPixelValue(pImage,i,j);
			cPixel23_16=(BYTE)((dwPixelValue & 0xff0000)>>16);
			SetPixelValueOfIndexImg(pNewImage,i,j,cPixel23_16);
		}
	}
}

//设置单通道图像的调色板
void Chw1Dlg::SetOneColorTableInPalette(ATL::CImage *pImage,int n,BYTE r,BYTE g,BYTE b)
{
	RGBQUAD ColorTab;

	ColorTab.rgbRed   = r;
	ColorTab.rgbGreen = g; 
	ColorTab.rgbBlue  = b; 

	pImage->SetColorTable(n, 1, &ColorTab);
}

//屏蔽esc按键
BOOL Chw1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN   &&   pMsg->wParam == VK_ESCAPE)   
	{   
		//将ESC键的消息替换为回车键的消息，这样，按ESC的时候 
		//也会去调用OnOK函数，而OnOK什么也不做，这样ESC也被屏蔽
		pMsg->wParam = VK_RETURN;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//屏蔽enter按键
void Chw1Dlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	// CDialog::OnOK();
}
