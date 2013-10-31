// hw1Dlg.h : 头文件
//

#pragma once

//使用CImage类
#include <atlimage.h>
//#include <GdiPlusImaging.h>
//#include <GdiPlus.h>
#include "afxwin.h"

// Chw1Dlg 对话框
class Chw1Dlg : public CDialog
{
// 构造
public:
	Chw1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HW1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
//自定义消息处理函数
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSaveInitialHist();
	afx_msg void OnBnClickedSaveEnhancedImage();
	afx_msg void OnBnClickedSaveEnhancedHist();
	afx_msg void OnBnClickedHistEqual();
	afx_msg void OnBnClickedMedianFilter();
	afx_msg void OnBnClickedMeanFilter();
	afx_msg void OnBnClickedSharpenFilter();

//自定义成员变量
public:
	CStatic m_showImage;
	ATL::CImage srcImg;	//原始图像
	CString initImgFilePath;	//原始图像路径

//自定义成员函数
public:
	//绘制直方图
	void DrawHistogram(CWnd* pWnd, int histdata[]);

	//保存图像
	void SaveImageFile(LPRECT rect, CString fileName);

	//将指定区域图像拷贝至位图
	HBITMAP CopyScreenToBitmap(LPRECT lpRect);

	//设置图像单个像素值
	void SetPixelValueOfIndexImg(ATL::CImage *pImage, int height, int width, BYTE pixel);	//256色图
	void SetPixelValueOfTruColorImage(ATL::CImage *pImage, int height, int width, DWORD dwPixel);	//真彩色图
	//获取单个像素数据
	DWORD GetPixelValue(ATL::CImage *pImage, int height, int width);

	//复制调色板
	void CopyColorTables(ATL::CImage *pNewImage, ATL::CImage*pImage);

	//统计灰度数据
	void GetHistData(ATL::CImage *pImage, int histData[]);

	//求三个数中的最大值
	BYTE GetMax(BYTE cData1, BYTE cData2, BYTE cData3);

	//求三个数中的最小值
	BYTE GetMin(BYTE cData1, BYTE cData2, BYTE cData3);

	//计算HSI色调值
	int  GetHueFromRGB(int nAngle, int nRed, int nGreen, int nBlue);

	//RGB空间转到HSV空间
	void RGBToHSV(BYTE *pHue, BYTE *pSaturation, BYTE *pValue, BYTE cRed, BYTE cGreen, BYTE cBlue);
	//HSV空间转到RGB空间
	void HSVToRGB(BYTE *pRed, BYTE *pGreen, BYTE *pBlue, BYTE cHue, BYTE cSaturation, BYTE cValue);

	//图像加边：在上下方向各扩展一行，在左右方向各扩展一列
	void AddImageBorder(ATL::CImage *pNewImage, ATL::CImage *pImage);
	//图像去边
	void SubtractImageBorder(ATL::CImage *pNewImage,ATL::CImage *pImage);

	//CImage类对象之间的复制
	void CopyImage(ATL::CImage *pNewImage, ATL::CImage *pImage);

	//图像卷积，Scale衰减因子，Offset偏移值
	void Convolution(ATL::CImage *pNewImage,ATL::CImage *pImage,char OP[5][5],int Scale,int Offset,int nOPWidth,int nOPHeight);

	//设置卷积算子
	void  SetOperator(char oper[5][5]);

	//对图象进行取RGB模式中红分量处理
	void GetRedOfTrueColor(ATL::CImage *pNewImage, ATL::CImage *pImage);
	//对图象进行取RGB模式中绿分量处理
	void GetGreenOfTrueColor(ATL::CImage  *pNewImage, ATL::CImage  *pImage);
	//对图象进行取RGB模式中蓝分量处理
	void GetBlueOfTrueColor(ATL::CImage *pNewImage, ATL::CImage *pImage);

	//设置单通道图像的调色板
	void SetOneColorTableInPalette(ATL::CImage *pImage,int n,BYTE r,BYTE g,BYTE b);

	/////////////////////////////////////////////////////////////////////增强操作/////////////////////////////////////////////////////////////////////
	//3*3中值滤波
	void MedianFilter9(ATL::CImage *pNewImage, ATL::CImage *pImage);
	//5*5中值滤波
	void MedianFilter25(ATL::CImage *pNewImage, ATL::CImage *pImage);
	int GetMedian(BYTE pixels[], int count);	//灰度值排序

	//直方图均衡化
	void HistEqualization(ATL::CImage *pImage, ATL::CImage *pNewImage);

	//3*3均值滤波
	void MeanFilter9(ATL::CImage *pNewImage, ATL::CImage *pImage);
	//5*5均值滤波
	void MeanFilter25(ATL::CImage *pNewImage, ATL::CImage *pImage);

	//空间锐化滤波(水平条纹消除)
	void SharpenFilter(ATL::CImage *pNewImage, ATL::CImage *pImage);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnOK();
};
