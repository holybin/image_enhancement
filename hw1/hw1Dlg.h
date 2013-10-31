// hw1Dlg.h : ͷ�ļ�
//

#pragma once

//ʹ��CImage��
#include <atlimage.h>
//#include <GdiPlusImaging.h>
//#include <GdiPlus.h>
#include "afxwin.h"

// Chw1Dlg �Ի���
class Chw1Dlg : public CDialog
{
// ����
public:
	Chw1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HW1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
//�Զ�����Ϣ������
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSaveInitialHist();
	afx_msg void OnBnClickedSaveEnhancedImage();
	afx_msg void OnBnClickedSaveEnhancedHist();
	afx_msg void OnBnClickedHistEqual();
	afx_msg void OnBnClickedMedianFilter();
	afx_msg void OnBnClickedMeanFilter();
	afx_msg void OnBnClickedSharpenFilter();

//�Զ����Ա����
public:
	CStatic m_showImage;
	ATL::CImage srcImg;	//ԭʼͼ��
	CString initImgFilePath;	//ԭʼͼ��·��

//�Զ����Ա����
public:
	//����ֱ��ͼ
	void DrawHistogram(CWnd* pWnd, int histdata[]);

	//����ͼ��
	void SaveImageFile(LPRECT rect, CString fileName);

	//��ָ������ͼ�񿽱���λͼ
	HBITMAP CopyScreenToBitmap(LPRECT lpRect);

	//����ͼ�񵥸�����ֵ
	void SetPixelValueOfIndexImg(ATL::CImage *pImage, int height, int width, BYTE pixel);	//256ɫͼ
	void SetPixelValueOfTruColorImage(ATL::CImage *pImage, int height, int width, DWORD dwPixel);	//���ɫͼ
	//��ȡ������������
	DWORD GetPixelValue(ATL::CImage *pImage, int height, int width);

	//���Ƶ�ɫ��
	void CopyColorTables(ATL::CImage *pNewImage, ATL::CImage*pImage);

	//ͳ�ƻҶ�����
	void GetHistData(ATL::CImage *pImage, int histData[]);

	//���������е����ֵ
	BYTE GetMax(BYTE cData1, BYTE cData2, BYTE cData3);

	//���������е���Сֵ
	BYTE GetMin(BYTE cData1, BYTE cData2, BYTE cData3);

	//����HSIɫ��ֵ
	int  GetHueFromRGB(int nAngle, int nRed, int nGreen, int nBlue);

	//RGB�ռ�ת��HSV�ռ�
	void RGBToHSV(BYTE *pHue, BYTE *pSaturation, BYTE *pValue, BYTE cRed, BYTE cGreen, BYTE cBlue);
	//HSV�ռ�ת��RGB�ռ�
	void HSVToRGB(BYTE *pRed, BYTE *pGreen, BYTE *pBlue, BYTE cHue, BYTE cSaturation, BYTE cValue);

	//ͼ��ӱߣ������·������չһ�У������ҷ������չһ��
	void AddImageBorder(ATL::CImage *pNewImage, ATL::CImage *pImage);
	//ͼ��ȥ��
	void SubtractImageBorder(ATL::CImage *pNewImage,ATL::CImage *pImage);

	//CImage�����֮��ĸ���
	void CopyImage(ATL::CImage *pNewImage, ATL::CImage *pImage);

	//ͼ������Scale˥�����ӣ�Offsetƫ��ֵ
	void Convolution(ATL::CImage *pNewImage,ATL::CImage *pImage,char OP[5][5],int Scale,int Offset,int nOPWidth,int nOPHeight);

	//���þ������
	void  SetOperator(char oper[5][5]);

	//��ͼ�����ȡRGBģʽ�к��������
	void GetRedOfTrueColor(ATL::CImage *pNewImage, ATL::CImage *pImage);
	//��ͼ�����ȡRGBģʽ���̷�������
	void GetGreenOfTrueColor(ATL::CImage  *pNewImage, ATL::CImage  *pImage);
	//��ͼ�����ȡRGBģʽ������������
	void GetBlueOfTrueColor(ATL::CImage *pNewImage, ATL::CImage *pImage);

	//���õ�ͨ��ͼ��ĵ�ɫ��
	void SetOneColorTableInPalette(ATL::CImage *pImage,int n,BYTE r,BYTE g,BYTE b);

	/////////////////////////////////////////////////////////////////////��ǿ����/////////////////////////////////////////////////////////////////////
	//3*3��ֵ�˲�
	void MedianFilter9(ATL::CImage *pNewImage, ATL::CImage *pImage);
	//5*5��ֵ�˲�
	void MedianFilter25(ATL::CImage *pNewImage, ATL::CImage *pImage);
	int GetMedian(BYTE pixels[], int count);	//�Ҷ�ֵ����

	//ֱ��ͼ���⻯
	void HistEqualization(ATL::CImage *pImage, ATL::CImage *pNewImage);

	//3*3��ֵ�˲�
	void MeanFilter9(ATL::CImage *pNewImage, ATL::CImage *pImage);
	//5*5��ֵ�˲�
	void MeanFilter25(ATL::CImage *pNewImage, ATL::CImage *pImage);

	//�ռ����˲�(ˮƽ��������)
	void SharpenFilter(ATL::CImage *pNewImage, ATL::CImage *pImage);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnOK();
};
