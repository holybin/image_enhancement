// hw1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "hw1.h"
#include "hw1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define uchar unsigned char

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Chw1Dlg �Ի���




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


// Chw1Dlg ��Ϣ�������

BOOL Chw1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//saveFileName = _T("");
	//ѡ�ϵ�һ����ѡ��
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	//û��ͼ��ǰ��ֹ���
	GetDlgItem(IDC_SAVE_ENHANCED_HIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_ENHANCED_IMAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SAVE_INITIAL_HIST)->EnableWindow(FALSE);

	GetDlgItem(IDC_MEDIAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEAN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SHARPEN_FILTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_HIST_EQUAL)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);

	//�ı�����
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

	//���ݴ�ֱ����
	CRect rect;
	CWnd* pEdit1 = GetDlgItem(IDC_MSG);
	pEdit1->GetClientRect(&rect);
	::OffsetRect(&rect, 0, 40);
	::SendMessage(pEdit1->m_hWnd, EM_SETRECT, 0, (LPARAM)&rect);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Chw1Dlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Chw1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Chw1Dlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ͼ��Ի���
	CFileDialog   dlgOpenFile(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_FILEMUSTEXIST|OFN_ENABLESIZING, 
		_T("All Files (*.*)|*.*|BMP (*.bmp)|*.bmp|JPEG (*.jpg;*.jpeg;*.jpe;*.jfif)|*.jpg;*.jpeg;*.jpe;*.jfif|PNG (*.png)|*.png|TIF (*.tif;*.tiff)|*.tif;*.tiff||"));   
	if(IDOK == dlgOpenFile.DoModal())
	{
		//��ȡͼ��·�����ļ���
		initImgFilePath = dlgOpenFile.GetPathName(); 
	}
	else
	{
		return;
	}

	//����ͼƬ
	if(!srcImg.IsNull())
		srcImg.Destroy();
	HRESULT res = srcImg.Load(initImgFilePath);
	if(FAILED(res))
	{
		//ʧ����ʾ
		SetDlgItemText(IDC_MSG, _T("Load image file \"") + initImgFilePath + _T("\" failed!"));
		return;
	}
	//�ɹ���ʾ
	SetDlgItemText(IDC_MSG, _T("Load image file \"") + initImgFilePath + _T("\" successfully!"));

	//���ͼ��ؼ����ڵľ��
	CWnd *pWnd = GetDlgItem(IDC_SHOW_IMAGE1);
	//���ͼ��ؼ���DC
	CDC *pDC = pWnd->GetDC();	
	//��ȡͼƬ�ؼ��Ŀ�͸�
	CRect rect;
	pWnd->GetClientRect(&rect);
	//��ͼ
	pDC->SetStretchBltMode(HALFTONE);	//��ֹͼƬʧ��
	srcImg.Draw(pDC->m_hDC, rect); //��ͼƬ����ͼ��ؼ���ʾ�ľ�������
	ReleaseDC(pDC);	//�ͷ�ͼ��ؼ���DC

	//��ȡͼ��Ŀ�͸�
	int imgWidth = srcImg.GetWidth();
	int imgHeight = srcImg.GetHeight();
	//ͼ��Ҷ�ͳ������
	int histData[256] = {0};	

	//���ͼ��ؼ����ڵľ��
	pWnd = GetDlgItem(IDC_SHOW_HIST1);
	//ͳ�ƻҶ�����
	GetHistData(&srcImg, histData);
	//����ֱ��ͼ
	DrawHistogram(pWnd, histData);

	//�ָ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ָ�����ڷ�Χ
	CWnd* pWnd = GetDlgItem(IDC_SHOW_HIST1);
	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->ClientToScreen(&rect);
	//ָ�������ļ���
	CString totalFileName = initImgFilePath.Right(initImgFilePath.GetLength() - initImgFilePath.ReverseFind('\\') - 1);
	CString fileName = totalFileName.Left(totalFileName.Find('.')) +  _T("_Hist");
	SaveImageFile(rect, fileName);
}

void Chw1Dlg::OnBnClickedSaveEnhancedImage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ָ�����ڷ�Χ
	CWnd* pWnd = GetDlgItem(IDC_SHOW_IMAGE2);
	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->ClientToScreen(&rect);
	//ָ�������ļ���
	CString totalFileName = initImgFilePath.Right(initImgFilePath.GetLength() - initImgFilePath.ReverseFind('\\') - 1);
	CString fileName = totalFileName.Left(totalFileName.Find('.')) +  _T("_Enhanced");
	SaveImageFile(rect, fileName);
}

void Chw1Dlg::OnBnClickedSaveEnhancedHist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ָ�����ڷ�Χ
	CWnd* pWnd = GetDlgItem(IDC_SHOW_HIST2);
	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->ClientToScreen(&rect);
	//ָ�������ļ���
	CString totalFileName = initImgFilePath.Right(initImgFilePath.GetLength() - initImgFilePath.ReverseFind('\\') - 1);
	CString fileName = totalFileName.Left(totalFileName.Find('.')) +  _T("_Enhanced_Hist");
	SaveImageFile(rect, fileName);
}

void Chw1Dlg::OnBnClickedHistEqual()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ֹ���
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

	//ֱ��ͼ���⻯
	ATL::CImage newImg;
	HistEqualization(&srcImg, &newImg);

	//���ͼ��ؼ����ڵľ��
	CWnd *pWnd = GetDlgItem(IDC_SHOW_IMAGE2);
	//���ͼ��ؼ���DC
	CDC *pDC = pWnd->GetDC();	
	//��ȡͼƬ�ؼ��Ŀ�͸�
	CRect rect;
	pWnd->GetClientRect(&rect);
	//��ͼ
	pDC->SetStretchBltMode(HALFTONE);	//��ֹͼƬʧ��
	newImg.Draw(pDC->m_hDC, rect); //��ͼƬ����ͼ��ؼ���ʾ�ľ�������

	//��ÿؼ��ľ��
	pWnd = GetDlgItem(IDC_SHOW_HIST2);
	//ͼ��Ҷ�ͳ������
	int histData[256] = {0};
	//ͳ�ƻҶ�����
	GetHistData(&newImg, histData);
	//����ֱ��ͼ
	DrawHistogram(pWnd, histData);

	//�ͷ�ͼ��ؼ���DC
	ReleaseDC(pDC);	
	//��Ϣ��ʾ
	SetDlgItemText(IDC_MSG, _T("Histogram Equalization for image file \"") + initImgFilePath + _T("\" succeed!"));
	//�ָ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ֹ���
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
	//ѡ��3*3
	if(choose)
		MedianFilter9(&newImg, &srcImg);
	//ѡ��5*5
	else
		MedianFilter25(&newImg, &srcImg);

	//���ͼ��ؼ����ڵľ��
	CWnd *pWnd = GetDlgItem(IDC_SHOW_IMAGE2);
	//���ͼ��ؼ���DC
	CDC *pDC = pWnd->GetDC();	
	//��ȡͼƬ�ؼ��Ŀ�͸�
	CRect rect;
	pWnd->GetClientRect(&rect);
	//��ͼ
	pDC->SetStretchBltMode(HALFTONE);	//��ֹͼƬʧ��
	newImg.Draw(pDC->m_hDC, rect); //��ͼƬ����ͼ��ؼ���ʾ�ľ�������

	//��ÿؼ��ľ��
	pWnd = GetDlgItem(IDC_SHOW_HIST2);
	//ͼ��Ҷ�ͳ������
	int histData[256] = {0};
	//ͳ�ƻҶ�����
	GetHistData(&newImg, histData);
	//����ֱ��ͼ
	DrawHistogram(pWnd, histData);

	//�ͷ�ͼ��ؼ���DC
	ReleaseDC(pDC);
	//��Ϣ��ʾ
	if(choose)
		SetDlgItemText(IDC_MSG, _T("Median Filtering (3*3) for image file \"") + initImgFilePath + _T("\" succeed!"));
	else
		SetDlgItemText(IDC_MSG, _T("Median Filtering (5*5) for image file \"") + initImgFilePath + _T("\" succeed!"));

	//�ָ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ֹ���
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
	//ѡ��3*3
	if(choose)
		MeanFilter9(&newImg, &srcImg);
	//ѡ��5*5
	else
		MeanFilter25(&newImg, &srcImg);

	//���ͼ��ؼ����ڵľ��
	CWnd *pWnd = GetDlgItem(IDC_SHOW_IMAGE2);
	//���ͼ��ؼ���DC
	CDC *pDC = pWnd->GetDC();	
	//��ȡͼƬ�ؼ��Ŀ�͸�
	CRect rect;
	pWnd->GetClientRect(&rect);
	//��ͼ
	pDC->SetStretchBltMode(HALFTONE);	//��ֹͼƬʧ��
	newImg.Draw(pDC->m_hDC, rect); //��ͼƬ����ͼ��ؼ���ʾ�ľ�������

	//��ÿؼ��ľ��
	pWnd = GetDlgItem(IDC_SHOW_HIST2);
	//ͼ��Ҷ�ͳ������
	int histData[256] = {0};
	//ͳ�ƻҶ�����
	GetHistData(&newImg, histData);
	//����ֱ��ͼ
	DrawHistogram(pWnd, histData);

	//�ͷ�ͼ��ؼ���DC
	ReleaseDC(pDC);	
	//��Ϣ��ʾ
	if(choose)
		SetDlgItemText(IDC_MSG, _T("Mean Filtering (3*3) for image file \"") + initImgFilePath + _T("\" succeed!"));
	else
		SetDlgItemText(IDC_MSG, _T("Mean Filtering (5*5) for image file \"") + initImgFilePath + _T("\" succeed!"));

	//�ָ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ֹ���
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

	//�ռ����˲�
	ATL::CImage newImg;
	SharpenFilter(&newImg, &srcImg);
	//���ͼ��ؼ����ڵľ��
	CWnd *pWnd = GetDlgItem(IDC_SHOW_IMAGE2);
	//���ͼ��ؼ���DC
	CDC *pDC = pWnd->GetDC();	
	//��ȡͼƬ�ؼ��Ŀ�͸�
	CRect rect;
	pWnd->GetClientRect(&rect);
	//��ͼ
	pDC->SetStretchBltMode(HALFTONE);	//��ֹͼƬʧ��
	newImg.Draw(pDC->m_hDC, rect); //��ͼƬ����ͼ��ؼ���ʾ�ľ�������

	//��ÿؼ��ľ��
	pWnd = GetDlgItem(IDC_SHOW_HIST2);
	//ͼ��Ҷ�ͳ������
	int histData[256] = {0};
	//ͳ�ƻҶ�����
	GetHistData(&newImg, histData);
	//����ֱ��ͼ
	DrawHistogram(pWnd, histData);

	//�ͷ�ͼ��ؼ���DC
	ReleaseDC(pDC);	
	//��Ϣ��ʾ
	SetDlgItemText(IDC_MSG, _T("Horizontal Stripe Elimination for image file \"") + initImgFilePath + _T("\" succeed!"));
	//�ָ����
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

//���þ������
void  Chw1Dlg::SetOperator(char oper[5][5])
{
	//ȥ��ˮƽ����
	oper[0][0]=0;	oper[0][1]=1;	oper[0][2]=0;
	oper[1][0]=0;	oper[1][1]=1;	oper[1][2]=0;
	oper[2][0]=0;	oper[2][1]=1;	oper[2][2]=0;
}

//�ռ����˲�
void Chw1Dlg::SharpenFilter(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	CopyImage(pNewImage, pImage);
	//���ģ��
	char	 oper[5][5];
	//���þ������
	SetOperator(oper);
	//��ͨ��
	if(pImage->GetBPP() / 8 == 1)
	{
		ATL::CImage	images[3];
		//ͼ��ӱ�
		AddImageBorder(&images[0], pImage);
		//ͼ�������Ӿ��
		Convolution(&images[1], &images[0],oper,3,0,3,3);
		//ͼ��ȥ��
		SubtractImageBorder(pNewImage, &images[1]);
	}
	//3ͨ��
	else if (pImage->GetBPP() / 8 == 3)
	{
		//���ΪR��G��B��������ͼ��
		ATL::CImage images[3];
		GetRedOfTrueColor(&images[0], pImage);
		GetGreenOfTrueColor(&images[1], pImage);
		GetBlueOfTrueColor(&images[2], pImage);
		//�ֱ������
		for (int i = 0; i < 3; i++)
		{
			ATL::CImage	tmpImages[3];
			//ͼ��ӱ�
			AddImageBorder(&tmpImages[0], &images[i]);
			//ͼ�������Ӿ��
			Convolution(&tmpImages[1], &tmpImages[0],oper,3,0,3,3);
			//ͼ��ȥ��
			SubtractImageBorder(&images[i], &tmpImages[1]);
		}
		//�ϲ�ΪRGBͼ��
		for( int x = 0; x < pImage->GetHeight(); x++) 
		{
			for( int y = 0; y < pImage->GetWidth(); y++)
			{
				//��ȡͼ������ֵ
				BYTE rgb[3] = {0};
				for (int z = 0; z < 3; z++)
				{
					//��ǰͼ���������ݵ�ָ��
					BYTE* pRealData = (BYTE*)images[z].GetBits();
					//�������������׵�ַ֮��ļ��
					int pitch = images[z].GetPitch();
					//int bitCount = images[z].GetBPP() / 8;
					rgb[z] = *(pRealData + pitch * x + y);
				}
				pNewImage->SetPixelRGB(y, x, rgb[0], rgb[1], rgb[2]);
			}
		}
	}
}

//��ֵ�˲�: 3*3
void Chw1Dlg::MedianFilter9(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	//��ȡͼ��Ŀ�͸ߣ�������ռλ��
	int imgWidth = pImage->GetWidth();
	int imgHeight = pImage->GetHeight();
	int bitCount = pImage->GetBPP();
	//������ͼ��
	pNewImage->Create(imgWidth, imgHeight, bitCount);
	//���Ƶ�ɫ��
	CopyColorTables(pNewImage, pImage);

	BYTE pValue[9], cNewPixel;
	//��ͨ��
	if(bitCount / 8 == 1)
	{
		for (int i = 1; i < imgHeight - 1; i++)
		{
			for (int j = 1; j < imgWidth - 1; j++)
			{
				//ȡ�����8�ڵ�����
				int count = 0;
				for(int m = -1; m <= 1; m++)
				{
					for(int n = -1; n <= 1; n++)
					{
						pValue[count++] = (BYTE)GetPixelValue(pImage, i + m, j + n);
					}
				}
				//ȡ��ֵ
				cNewPixel = GetMedian(pValue, 9);
				//������ͼ������
				SetPixelValueOfIndexImg(pNewImage, i, j, cNewPixel);
			}
		}
	}
	//3ͨ��
	else if (pImage->GetBPP() / 8 == 3)
	{
		//���ΪR��G��B��������ͼ��
		ATL::CImage images[3];
		GetRedOfTrueColor(&images[0], pImage);
		GetGreenOfTrueColor(&images[1], pImage);
		GetBlueOfTrueColor(&images[2], pImage);
		//�ֱ����˲�
		ATL::CImage	tmpImages[3];
		for (int i = 0; i < 3; i++)
		{
			MedianFilter9(&tmpImages[i], &images[i]);
		}
		//�ϲ�ΪRGBͼ��
		for( int x = 0; x < imgHeight; x++) 
		{
			for( int y = 0; y < imgWidth; y++)
			{
				//��ȡͼ������ֵ
				BYTE rgb[3] = {0};
				for (int z = 0; z < 3; z++)
				{
					//��ǰͼ���������ݵ�ָ��
					BYTE* pRealData = (BYTE*)tmpImages[z].GetBits();
					//�������������׵�ַ֮��ļ��
					int pitch = tmpImages[z].GetPitch();
					//int bitCount = images[z].GetBPP() / 8;
					rgb[z] = *(pRealData + pitch * x + y);
				}
				pNewImage->SetPixelRGB(y, x, rgb[0], rgb[1], rgb[2]);
			}
		}
	}
}

//��ֵ�˲�: 5*5
void Chw1Dlg::MedianFilter25(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	//��ȡͼ��Ŀ�͸ߣ�������ռλ��
	int imgWidth = pImage->GetWidth();
	int imgHeight = pImage->GetHeight();
	int bitCount = pImage->GetBPP();
	//������ͼ��
	pNewImage->Create(imgWidth, imgHeight, bitCount);
	//���Ƶ�ɫ��
	CopyColorTables(pNewImage, pImage);

	BYTE pValue[25], cNewPixel;
	//��ͨ��
	if(bitCount / 8 == 1)
	{
		for (int i = 2; i < imgHeight - 2; i++)
		{
			for (int j = 2; j < imgWidth - 2; j++)
			{
				//ȡ�����24�ڵ�����
				int count = 0;
				for(int m = -2; m <= 2; m++)
				{
					for(int n = -2; n <= 2; n++)
					{
						pValue[count++] = (BYTE)GetPixelValue(pImage, i + m, j + n);
					}
				}
				//ȡ��ֵ
				cNewPixel = GetMedian(pValue, 25);
				//������ͼ������
				SetPixelValueOfIndexImg(pNewImage, i, j, cNewPixel);
			}
		}
	}
	//3ͨ��
	else if (pImage->GetBPP() / 8 == 3)
	{
		//���ΪR��G��B��������ͼ��
		ATL::CImage images[3];
		GetRedOfTrueColor(&images[0], pImage);
		GetGreenOfTrueColor(&images[1], pImage);
		GetBlueOfTrueColor(&images[2], pImage);
		//�ֱ����˲�
		ATL::CImage	tmpImages[3];
		for (int i = 0; i < 3; i++)
		{
			MedianFilter25(&tmpImages[i], &images[i]);
		}
		//�ϲ�ΪRGBͼ��
		for( int x = 0; x < imgHeight; x++) 
		{
			for( int y = 0; y < imgWidth; y++)
			{
				//��ȡͼ������ֵ
				BYTE rgb[3] = {0};
				for (int z = 0; z < 3; z++)
				{
					//��ǰͼ���������ݵ�ָ��
					BYTE* pRealData = (BYTE*)tmpImages[z].GetBits();
					//�������������׵�ַ֮��ļ��
					int pitch = tmpImages[z].GetPitch();
					//int bitCount = images[z].GetBPP() / 8;
					rgb[z] = *(pRealData + pitch * x + y);
				}
				pNewImage->SetPixelRGB(y, x, rgb[0], rgb[1], rgb[2]);
			}
		}
	}
}

//������ֵ��������
int Chw1Dlg::GetMedian(BYTE pixels[], int count)
{
	//ð������
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

//��ֵ�˲�: 3*3
void Chw1Dlg::MeanFilter9(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	//��ȡͼ��Ŀ�͸ߣ�������ռλ��
	int imgWidth = pImage->GetWidth();
	int imgHeight = pImage->GetHeight();
	int bitCount = pImage->GetBPP();
	//������ͼ��
	pNewImage->Create(imgWidth, imgHeight, bitCount);
	//���Ƶ�ɫ��
	CopyColorTables(pNewImage, pImage);

	BYTE pValue[9], cNewPixel;
	//��ͨ��
	if(bitCount / 8 == 1)
	{
		for (int i = 1; i < imgHeight - 1; i++)
		{
			for (int j = 1; j < imgWidth - 1; j++)
			{
				//ȡ�����8�ڵ�����
				int count = 0;
				for(int m = -1; m <= 1; m++)
				{
					for(int n = -1; n <= 1; n++)
					{
						pValue[count++] = (BYTE)GetPixelValue(pImage, i + m, j + n);
					}
				}
				//ȡ��ֵ
				int sum = 0;
				for(int k = 0; k < 9; k++)
					sum += pValue[k];
				cNewPixel = (int)(sum / 9.0);
				//������ͼ������
				SetPixelValueOfIndexImg(pNewImage, i, j, cNewPixel);
			}
		}
	}
	//3ͨ��
	else if (pImage->GetBPP() / 8 == 3)
	{
		//���ΪR��G��B��������ͼ��
		ATL::CImage images[3];
		GetRedOfTrueColor(&images[0], pImage);
		GetGreenOfTrueColor(&images[1], pImage);
		GetBlueOfTrueColor(&images[2], pImage);
		//�ֱ����˲�
		ATL::CImage	tmpImages[3];
		for (int i = 0; i < 3; i++)
		{
			MeanFilter9(&tmpImages[i], &images[i]);
		}
		//�ϲ�ΪRGBͼ��
		for( int x = 0; x < imgHeight; x++) 
		{
			for( int y = 0; y < imgWidth; y++)
			{
				//��ȡͼ������ֵ
				BYTE rgb[3] = {0};
				for (int z = 0; z < 3; z++)
				{
					//��ǰͼ���������ݵ�ָ��
					BYTE* pRealData = (BYTE*)tmpImages[z].GetBits();
					//�������������׵�ַ֮��ļ��
					int pitch = tmpImages[z].GetPitch();
					//int bitCount = images[z].GetBPP() / 8;
					rgb[z] = *(pRealData + pitch * x + y);
				}
				pNewImage->SetPixelRGB(y, x, rgb[0], rgb[1], rgb[2]);
			}
		}
	}
}

//��ֵ�˲�: 5*5
void Chw1Dlg::MeanFilter25(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	//��ȡͼ��Ŀ�͸ߣ�������ռλ��
	int imgWidth = pImage->GetWidth();
	int imgHeight = pImage->GetHeight();
	int bitCount = pImage->GetBPP();
	//������ͼ��
	pNewImage->Create(imgWidth, imgHeight, bitCount);
	//���Ƶ�ɫ��
	CopyColorTables(pNewImage, pImage);

	BYTE pValue[25], cNewPixel;
	//��ͨ��
	if(bitCount / 8 == 1)
	{
		for (int i = 2; i < imgHeight - 2; i++)
		{
			for (int j = 2; j < imgWidth - 2; j++)
			{
				//ȡ�����24�ڵ�����
				int count = 0;
				for(int m = -2; m <= 2; m++)
				{
					for(int n = -2; n <= 2; n++)
					{
						pValue[count++] = (BYTE)GetPixelValue(pImage, i + m, j + n);
					}
				}
				//ȡ��ֵ
				int sum = 0;
				for(int k = 0; k < 25; k++)
					sum += pValue[k];
				cNewPixel = (int)(sum / 25.0);
				//������ͼ������
				SetPixelValueOfIndexImg(pNewImage, i, j, cNewPixel);
			}
		}
	}
	//3ͨ��
	else if (pImage->GetBPP() / 8 == 3)
	{
		//���ΪR��G��B��������ͼ��
		ATL::CImage images[3];
		GetRedOfTrueColor(&images[0], pImage);
		GetGreenOfTrueColor(&images[1], pImage);
		GetBlueOfTrueColor(&images[2], pImage);
		//�ֱ����˲�
		ATL::CImage	tmpImages[3];
		for (int i = 0; i < 3; i++)
		{
			MeanFilter25(&tmpImages[i], &images[i]);
		}
		//�ϲ�ΪRGBͼ��
		for( int x = 0; x < imgHeight; x++) 
		{
			for( int y = 0; y < imgWidth; y++)
			{
				//��ȡͼ������ֵ
				BYTE rgb[3] = {0};
				for (int z = 0; z < 3; z++)
				{
					//��ǰͼ���������ݵ�ָ��
					BYTE* pRealData = (BYTE*)tmpImages[z].GetBits();
					//�������������׵�ַ֮��ļ��
					int pitch = tmpImages[z].GetPitch();
					//int bitCount = images[z].GetBPP() / 8;
					rgb[z] = *(pRealData + pitch * x + y);
				}
				pNewImage->SetPixelRGB(y, x, rgb[0], rgb[1], rgb[2]);
			}
		}
	}
}

//����ͼ��Ҷ�ֱ��ͼ
void Chw1Dlg::DrawHistogram(CWnd* pWnd, int histData[])
{
	int i;	// ѭ������
	CDC* pDC = pWnd->GetDC();	//��ȡ�豸������

	//��ȡ��ͼ����С
	CRect rect;
	pWnd->GetClientRect(&rect);
	//ˢ�»�ͼ��
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	//��һ�����δӶ�������ֱ��ͼ������
	//pDC->Rectangle(rect);	
	//pDC->Rectangle(0, 0, 400, 203);			//��һ�����δӶ�������ֱ��ͼ������

	CPaintDC dc(this); //��ȡ��ͼ�豸������
	// �������ʶ���
	CPen* pPenRed = new CPen;
	// ������ɫ���ʣ����ڻ��������ᣩ
	pPenRed->CreatePen(PS_SOLID, 1, RGB(255,0,0));
	// ѡ���ɫ���ʣ���������ǰ�Ļ���
	CPen* pOldPen = pDC->SelectObject(pPenRed);

	// ֱ��ͼ��������ֵ
	LONG maxCount = 0;
	// ����������ֵ
	for (i = 0; i <= 255; i ++)
	{
		// �ж��Ƿ���ڵ�ǰ���ֵ
		if (histData[i] > maxCount)
		{
			// �������ֵ
			maxCount = histData[i];
		}
	}

	// ��ֱ��ͼ������
	// ����y��
	pDC->MoveTo(10,5);	
	pDC->LineTo(10, 210);
	// ����x��
	pDC->MoveTo(10,210);	
	pDC->LineTo(270, 210);
	// ����X��̶�ֵ
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
	// ����X��̶�
	for (i = 0; i < 256; i += 5)
	{
		if ((i & 1) == 0)		//ż������10�ı���
		{		
			pDC->MoveTo(i + 10, 210);
			pDC->LineTo(i + 10, 215);
		}
		else					//�������� 5����������
		{
			pDC->MoveTo(i + 10, 210);
			pDC->LineTo(i + 10, 212);
		}
	}
	//����������ļ�ͷ
	// ����X���ͷ
	pDC->MoveTo(270, 210);
	pDC->LineTo(265, 205);
	pDC->MoveTo(270, 210);
	pDC->LineTo(265, 215);
	// ����Y���ͷ
	pDC->MoveTo(10, 5);
	pDC->LineTo(15, 10);
	pDC->MoveTo(10, 5);
	pDC->LineTo(5, 10);

	// ����Y��̶�
	int Ystep = 200 / 20;	//y������ϵ���Ŀ̶Ȳ���
	for (i = 1; i <= 20; i += 1)
	{
		double yValue = 210 - Ystep * i;
		pDC->MoveTo(10, (int)yValue);
		if (i % 2 == 0)
			pDC->LineTo(15, (int)yValue);
		else
			pDC->LineTo(12, (int)yValue);
	}

	// ���������ֵ
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 10);
	strTemp.Format(_T("%d"), maxCount);
	pDC->TextOut(16, 5, strTemp);

	// �������ʶ���
	CPen* pPenBlue = new CPen;
	// ������ɫ���ʣ����ڻ���ֱ��ͼ��
	pPenBlue->CreatePen(PS_SOLID, 1, RGB(0,0,255));
	// ѡ����ɫ����
	pDC->SelectObject(pPenBlue);
	CString str;
	if(maxCount > 0)
	{
		// ����ֱ��ͼ
		for (i = 0; i < 256; i ++)
		{
			pDC->MoveTo(i + 10, 210);
			pDC->LineTo(i + 10, 210 - (int) (histData[i] * 200 / maxCount) );
		}
	}
	// �ָ���ǰ�Ļ���
	pDC->SelectObject(pOldPen);	

	// �ͷ�ͼ��ؼ���DC
	ReleaseDC(pDC);
	// ɾ���µĻ���
	delete pPenRed;
	delete pPenBlue;
	// Do not call CDialog::OnPaint() for painting messages
}

//��ȡͼƬ�ռ�����ʾ��ͼƬ������
HBITMAP Chw1Dlg::CopyScreenToBitmap(LPRECT lpRect)
{
	HDC hScrDC, hMemDC;      
	// ��Ļ���ڴ��豸������
	HBITMAP hBitmap,hOldBitmap;   
	// λͼ���
	int nX, nY, nX2, nY2;      
	// ѡ����������
	int nWidth, nHeight;      
	// λͼ��Ⱥ͸߶�
	int xScrn, yScrn;         
	// ��Ļ�ֱ���
	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
		return NULL;
	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//ȷ��ѡ�������ǿɼ���
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
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
	//�õ���Ļλͼ�ľ��
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//��� 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// ����λͼ���
	return hBitmap;
}

//����ͼ���ļ�
void Chw1Dlg::SaveImageFile(LPRECT rect, CString fileName)
{
	//�����ͼ
	HBITMAP hBitmap = CopyScreenToBitmap(rect);	//��Ϊλͼ
	//��λͼ��CImage����������
	ATL::CImage saveImage;
	saveImage.Attach(hBitmap);

	//����ͼ��Ի���
	CString strExtension = _T(".bmp"); //Ĭ����չ����.bmp 
	CFileDialog saveFileDlg(FALSE, strExtension, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, _T("λͼ�ļ�(*.bmp)|*.bmp|JPEG ͼ���ļ�(*.jpg)|*.jpg|GIF ͼ���ļ�(*.gif)|*.gif|PNG ͼ���ļ�(*.png)|*.png|�����ļ�(*.*)|*.*||")); 
	if ( IDOK != saveFileDlg.DoModal()) 
		return; 

	// ����û�û��ָ���ļ���չ������Ϊ�����һ�� 
	CString strFileName = saveFileDlg.m_ofn.lpstrFile;	//�ļ���
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

	//ͼ�񱣴���ʾ
	HRESULT hResult = saveImage.Save(strFileName);
	if (FAILED(hResult)) 
		SetDlgItemText(IDC_MSG, _T("Save image file \"") + strFileName + _T("\" failed!"));
	else
		SetDlgItemText(IDC_MSG, _T("Save image file \"") + strFileName + _T("\" successfully!"));
}

//��ͼ��������ȡ������������
DWORD Chw1Dlg::GetPixelValue(ATL::CImage *pImage, int height, int width)
{
	DWORD	dwPixelValue;
	BYTE		*pPixel;

	//ȡ�������ݴ�ŵ�ַ
	pPixel = (BYTE*) pImage->GetPixelAddress(width, height);
	switch(pImage->GetBPP())
	{
	case 1:		//������ֵͼ����������
		memcpy(&dwPixelValue, pPixel, 1);
		dwPixelValue = dwPixelValue & 0x1;
		break;

	case 4:		//����16ɫͼ����������
		memcpy(&dwPixelValue, pPixel, 1);
		dwPixelValue = dwPixelValue & 0xf;
		break;

	case 8:		//����256ɫͼ����������
		memcpy(&dwPixelValue, pPixel, 1);
		break;

	case 24:		//�������ɫͼ����������
		memcpy(&dwPixelValue, pPixel, 3);
		dwPixelValue=dwPixelValue & 0xffffff;
		break;
	}
	return (dwPixelValue);
}

//���Ƶ�ɫ��
void Chw1Dlg::CopyColorTables(ATL::CImage *pNewImage, ATL::CImage*pImage)
{
	int nColorTableEntries;
	RGBQUAD	ColorTabs[256];

	nColorTableEntries = pImage->GetMaxColorTableEntries();
	if (nColorTableEntries > 0)
	{
		pImage->GetColorTable(0,nColorTableEntries,ColorTabs);    
		pNewImage->SetColorTable(0,nColorTableEntries,ColorTabs);   //  ���Ƶ�ɫ��
	}
}

//����256ɫͼ�󵥸���������
void Chw1Dlg::SetPixelValueOfIndexImg(ATL::CImage *pImage, int height, int width, BYTE pixel)
{
	BYTE *pPixel;
	//ȡ�������ݴ�ŵ�ַ
	pPixel = (BYTE*) pImage->GetPixelAddress(width, height);
	memcpy(pPixel, &pixel, 1);
}

//�������ɫͼ�󵥸���������
void Chw1Dlg::SetPixelValueOfTruColorImage(ATL::CImage *pImage, int height, int width, DWORD dwPixel)
{
	BYTE *pPixel;
	//ȡ�������ݴ�ŵ�ַ
	pPixel= (BYTE*) pImage->GetPixelAddress(width, height);
	memcpy(pPixel, &dwPixel, 3);
}

//ͳ�ƻҶ�����
void Chw1Dlg::GetHistData(ATL::CImage *pImage, int histData[])
{
	//��ǰͼ���������ݵ�ָ��
	BYTE* pRealData = (BYTE*)pImage->GetBits();
	//��ȡͼ��Ŀ�͸�
	int imgWidth = pImage->GetWidth();
	int imgHeight = pImage->GetHeight();
	//�������������׵�ַ֮��ļ��
	int pitch = pImage->GetPitch();
	//��ǰͼ���ÿ����λ��
	int bitCount = pImage->GetBPP() / 8;
	//1.����ǵ�ͨ��ͼ��ֱ�Ӷ�ȡһ��BYTEλΪ�Ҷ�ֵ
	if(bitCount == 1)
	{
		for (int y = 0; y < imgHeight; y++) 
		{
			for (int x = 0; x < imgWidth; x++) 
			{
				//��ȡͼ������ֵ
				int grayValue = *(pRealData + pitch * y + x * bitCount);
				histData[grayValue]++;
				//imgData[y][x] = grayValue;
			}
		}
		//for(int i = 0; i < imgHeight; i++) 
		//{   
		//	//���׵�ַ
		//	BYTE* pLinePixels = (BYTE*)srcImg.GetPixelAddress(0, i);
		//	for (int j = 0; j < imgWidth; j++)
		//	{
		//		//�Ҷ�ֵ����
		//		int cPixel = (int)(*(pLinePixels + j));
		//		histData[cPixel]++;
		//	}
		//}
	}
	//2.�����3ͨ��ͼ�������ζ�ȡpixAddr, pixAddr+1, pixAddr+2ΪB��G��R����ֵ
	else if(bitCount == 3)
	{
		for (int y = 0; y < imgHeight; y++) 
		{
			for (int x = 0; x < imgWidth; x++) 
			{
				//��ȡͼ������ֵ
				int bValue = *(pRealData + pitch * y + x * bitCount);
				int gValue = *(pRealData + pitch * y + x * bitCount + 1);
				int rValue = *(pRealData + pitch * y + x * bitCount + 2);

				//�ҶȻ�����
				//int grayVal=(int)(int)(bValue)*0.3+(int)(int)(gValue)*0.59+(int)(int)(rValue)*0.11;
				int grayValue = ((int)rValue*299 + (int)gValue*587 + (int)bValue*114 + 500) / 1000;
				histData[grayValue]++;
				//imgData[y][x] = grayValue;
			}
		}
	}
}

//���������е����ֵ
BYTE Chw1Dlg::GetMax(BYTE cData1,BYTE cData2,BYTE cData3)
{
	BYTE cMax;
	cMax=cData1>cData2?cData1:cData2;
	cMax=cMax>cData3?cMax:cData3;

	return cMax;
}

//���������е���Сֵ
BYTE Chw1Dlg::GetMin(BYTE cData1,BYTE cData2,BYTE cData3)
{
	BYTE cMin;
	cMin=cData1>cData2?cData2:cData1;
	cMin=cMin>cData3?cData3:cMin;

	return cMin;
}

//����HSVɫ��ֵ
int  Chw1Dlg::GetHueFromRGB(int nAngle, int nRed, int nGreen, int nBlue)
{
	int	nHue256;
	float	fHue360;

	fHue360=(float)(nAngle+120.0*(nGreen-nBlue)/(nGreen-nBlue+nRed-nBlue));
	nHue256=(int)(256.0*fHue360/360.0+0.5);//��0~360��ת��Ϊ0~256

	return (nHue256);
}

//RGB�ռ�ת��HSV�ռ�
void Chw1Dlg::RGBToHSV(BYTE *pHue, BYTE *pSaturation, BYTE *pValue, BYTE cRed, BYTE cGreen, BYTE cBlue)
{
	BYTE	cMax, cMin;
	int	nAngle;

	//�ҳ������Сֵ
	cMax = GetMax(cRed,cGreen,cBlue);             
	cMin = GetMin(cRed,cGreen,cBlue);    
	//��������ͬΪ�ҽף���ɫ��
	if (cMax==cMin) 
	{                 
		*pHue=0;    
		*pSaturation=0;
	}
	//Ϊ��ɫ 
	else
	{                                   
		//���㱥�Ͷ�     
		*pSaturation=(int) (255.0*(cMax-cMin)/cMax);      
		//��СֵΪ������
		if (cMin==cBlue)
		{
			nAngle=0;
			*pHue=GetHueFromRGB(nAngle,cRed,cGreen,cBlue);//����ɫ��ֵ       
		}
		//��СֵΪ�����    
		else if (cMin==cRed) 
		{               
			nAngle=120;
			*pHue=GetHueFromRGB(nAngle,cGreen,cBlue,cRed);//����ɫ��ֵ       
		}
		//��СֵΪ�̷���   
		else if (cMin==cGreen) 
		{                 
			nAngle=240;
			*pHue=GetHueFromRGB(nAngle,cBlue,cRed,cGreen);//����ɫ��ֵ       
		}
	}
	*pValue=cMax;
}

//HSV ģʽת���� RGB ģʽ
void Chw1Dlg::HSVToRGB(BYTE *pRed, BYTE *pGreen, BYTE *pBlue, BYTE cHue, BYTE cSaturation, BYTE cValue)
{
	int  nMin,nHue;
	nHue=(int)(360.0*cHue/255.0);//ɫ��ֵת���ɽǶ�

	if (cSaturation==0) 
	{//���Ͷȵ��� 0 ʱΪ�ҽ�
		*pRed=*pGreen=*pBlue=cValue;//���������
	}
	else 
	{//����Ϊ��ɫ
		nMin=(int)((255.0-cSaturation)*cValue/255.0);//������С����
		if (nHue<=120) 
		{//��ɫ�ں�����                           
			*pBlue=nMin;//��������С
			if (nHue<=60) 
			{
				*pRed=cValue;//��������
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
			{//��ɫ��������
				*pRed=nMin;//�������С
				if (nHue<=180) 
				{
					*pGreen=cValue;//�̷������
					*pBlue=(int)(nMin+(nHue-120.0)*(cValue-nMin)/(240.0-nHue));
				}
				else 
				{
					*pBlue=cValue;//���������
					*pGreen=(int)(nMin+(240.0-nHue)*(cValue-nMin)/(nHue-120.0));
				}
			}
			else 
			{//��ɫ��������                                    
				*pGreen=nMin;                                 
				if (nHue<=300) 
				{
					*pBlue=cValue;//���������                              
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

//ֱ��ͼ���⻯
void Chw1Dlg::HistEqualization(ATL::CImage *pImage, ATL::CImage *pNewImage)
{
	int i, j;
	BYTE cRed,cGreen,cBlue,cHue,cSaturation,cValue;
	int valueHistData[256] = {0};

	//��ȡͼ��Ŀ�͸�
	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	pNewImage->Create(nWidth, nHeight, pImage->GetBPP());
	//���Ƶ�ɫ��
	CopyColorTables(pNewImage, pImage);

	//�½������ž��⻯������
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

	//��ǰͼ���������ݵ�ָ��
	BYTE* pRealData = (BYTE*)pImage->GetBits();
	//�������������׵�ַ֮��ļ��
	int pitch = pImage->GetPitch();
	int bitCount = pImage->GetBPP() / 8;
	//��ȡV����ֱ��ͼ����
	for( i = 0; i < nHeight; i++) 
	{
		for( j = 0; j < nWidth; j++)
		{
			//��ȡͼ������ֵ
			cBlue= *(pRealData + pitch * i + j * bitCount);
			cGreen= *(pRealData + pitch * i + j * bitCount + 1);
			cRed= *(pRealData + pitch * i + j * bitCount + 2);
			//RGB ģʽת���� HSV ģʽ
			RGBToHSV(&cHue, &cSaturation, &cValue, cRed, cGreen, cBlue);
			//���Ҷ�ֵ����Ӧ��Ԫ��������
			valueHistData[cValue]++;
			newValueData[i][j] = cValue;
			newSaturData[i][j] = cSaturation;
			newHueData[i][j] = cHue;
		}
	}
	//���⻯
	double valueHistDataRatio[256] = {0.0};
	for(i = 0; i <= 255; i++)
	{
		//��Ҷ�ֵ����
		valueHistDataRatio[i] = (double) valueHistData[i] / (nWidth * nHeight);
		//��Ҷ�ֵ������
		if(i != 0)
			valueHistDataRatio[i] += valueHistDataRatio[i - 1];
	}
	//����ӳ��
	for(i = 0; i <= 255; i++)
	{
		valueHistData[i] = (int)(valueHistDataRatio[i] * 255);
	}
	//����õ���ͼ��
	for( i = 0; i < nHeight; i++) 
	{
		for ( j = 0; j < nWidth; j++)
		{
			int index = newValueData[i][j];
			BYTE satur= newSaturData[i][j];
			BYTE hue= newHueData[i][j];
			BYTE val= valueHistData[index];
			//HSV ģʽת���� RGB ģʽ
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

//�ӿ�ͼ��(ͼ��ӱ�)�������·������չһ�У������ҷ������չһ��
void Chw1Dlg::AddImageBorder(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	BYTE	*pPixel,*pNewPixel;
	int		i,nWidth,nHeight,nBytesPerLine,nBytesPerPixel;

	nWidth=pImage->GetWidth();
	nHeight=pImage->GetHeight();
	nBytesPerLine=(pImage->GetWidth()*pImage->GetBPP()+31)/32*4;
	nBytesPerPixel=pImage->GetBPP() / 8;

	pNewImage->Create(nWidth+2,nHeight+2,pImage->GetBPP());
	CopyColorTables(pNewImage,pImage);//���Ƶ�ɫ��

	//����ͼ�����и�����������
	for (i=0;i<nHeight;i++) 
	{
		pPixel  = (BYTE*) pImage->GetPixelAddress(0,i);       
		pNewPixel = (BYTE*) pNewImage->GetPixelAddress(1,i+1);
		memcpy(pNewPixel, pPixel,nBytesPerLine);                         
	}

	//��չ����һ��
	pPixel  = (BYTE*) pImage->GetPixelAddress(0,0); 
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(1,0);
	memcpy(pNewPixel, pPixel,nBytesPerLine);

	//��չ�ױ�һ��
	pPixel  = (BYTE*) pImage->GetPixelAddress(0,nHeight-1);
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(1,nHeight+1);
	memcpy(pNewPixel, pPixel,nBytesPerLine);

	//��չ���һ��
	for(i=0;i<nHeight;i++)
	{
		pPixel  = (BYTE*) pImage->GetPixelAddress(0,i);
		pNewPixel = (BYTE*) pNewImage->GetPixelAddress(0,i+1);
		memcpy(pNewPixel,pPixel,nBytesPerPixel);
	}

	//��չ�ұ�һ��
	for(i=0;i<nHeight;i++)
	{
		pPixel  = (BYTE*) pImage->GetPixelAddress(nWidth-1,i);
		pNewPixel = (BYTE*) pNewImage->GetPixelAddress(nWidth+1,i+1);
		memcpy(pNewPixel,pPixel,nBytesPerPixel);
	}

	//�������Ͻǵ�
	pPixel  = (BYTE*) pImage->GetPixelAddress(0,0);
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(0,0);
	memcpy(pNewPixel,pPixel,nBytesPerPixel);

	//�������Ͻǵ�
	pPixel  = (BYTE*) pImage->GetPixelAddress(nWidth-1,0);
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(nWidth+1,0);
	memcpy(pNewPixel,pPixel,nBytesPerPixel);

	//�������½ǵ�
	pPixel  = (BYTE*) pImage->GetPixelAddress(0,nHeight-1);
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(0,nHeight+1);
	memcpy(pNewPixel,pPixel,nBytesPerPixel);

	//�������½ǵ�
	pPixel  = (BYTE*) pImage->GetPixelAddress(nWidth-1,nHeight-1);
	pNewPixel = (BYTE*) pNewImage->GetPixelAddress(nWidth+1,nHeight+1);
	memcpy(pNewPixel,pPixel,nBytesPerPixel);
}

//ͼ������Scale˥�����ӣ�Offsetƫ��ֵ
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
			for(m=0;m<nOPHeight;m++)//������
				for(n=0;n<nOPWidth;n++)
					nNewPixel+=(int)OP[m][n]*(BYTE)GetPixelValue(pImage,i-nOPHeight/2+m,j-nOPWidth/2+n);

			nNewPixel=nNewPixel/Scale+Offset;
			if (nNewPixel>0xff) //�������ķ�Χ���
				nNewPixel=0xff;
			else 
				if (nNewPixel<0) 
					nNewPixel=0;

			SetPixelValueOfIndexImg(pNewImage,i,j,(BYTE)nNewPixel);//������������Ԫ
		}
	}
}

//ͼ��ȥ��
void Chw1Dlg::SubtractImageBorder(ATL::CImage *pNewImage,ATL::CImage *pImage)
{
	BYTE	*pNewLine,*pLine;
	int		i,nBytesPerLine,nHeight;

	CopyImage(pNewImage,pImage);
	//pNewImage->Create(pImage->GetWidth()-2, pImage->GetHeight()-2, pImage->GetBPP());
	//CopyColorTables(pNewImage, pImage);//���Ƶ�ɫ��

	nHeight=pNewImage->GetHeight()-2;
	nBytesPerLine=(pImage->GetWidth()*pImage->GetBPP()+31)/32*4;

	for (i=0;i<nHeight;i++) 
	{
		pLine=(BYTE*)pImage->GetPixelAddress(1,i+1);
		pNewLine=(BYTE*)pNewImage->GetPixelAddress(0,i);       
		memcpy(pNewLine,pLine,nBytesPerLine);                         
	}
}

//CImage�����֮��ĸ���
void Chw1Dlg::CopyImage(ATL::CImage *pNewImage, ATL::CImage *pImage)
{
	int nWidth,nHeight,nBitsPerPixel;
	nWidth=pImage->GetWidth();
	nHeight=pImage->GetHeight();
	nBitsPerPixel=pImage->GetBPP();

	//Ŀ��λͼ�ǿ���ɾ��Ŀ��λͼ
	if(!pNewImage->IsNull())
		pNewImage->Destroy();
	//����CImage�������λͼ
	pNewImage->Create(nWidth,nHeight,nBitsPerPixel,0);
	//���Ƶ�ɫ��
	CopyColorTables(pNewImage, pImage);
}

//��ͼ�����ȡRGBģʽ�к��������
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

//��ͼ�����ȡRGBģʽ���̷�������
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

//��ͼ�����ȡRGBģʽ������������
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

//���õ�ͨ��ͼ��ĵ�ɫ��
void Chw1Dlg::SetOneColorTableInPalette(ATL::CImage *pImage,int n,BYTE r,BYTE g,BYTE b)
{
	RGBQUAD ColorTab;

	ColorTab.rgbRed   = r;
	ColorTab.rgbGreen = g; 
	ColorTab.rgbBlue  = b; 

	pImage->SetColorTable(n, 1, &ColorTab);
}

//����esc����
BOOL Chw1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN   &&   pMsg->wParam == VK_ESCAPE)   
	{   
		//��ESC������Ϣ�滻Ϊ�س�������Ϣ����������ESC��ʱ�� 
		//Ҳ��ȥ����OnOK��������OnOKʲôҲ����������ESCҲ������
		pMsg->wParam = VK_RETURN;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//����enter����
void Chw1Dlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	// CDialog::OnOK();
}
