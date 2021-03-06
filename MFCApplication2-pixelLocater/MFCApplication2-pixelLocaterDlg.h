
// MFCApplication2-pixelLocaterDlg.h: 头文件
//

#pragma once


// CMFCApplication2pixelLocaterDlg 对话框
class CMFCApplication2pixelLocaterDlg : public CDialogEx
{
// 构造
public:
	CMFCApplication2pixelLocaterDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2PIXELLOCATER_DIALOG };
#endif

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
public:
	afx_msg void OnEnChangeFrameheight();
	int frame_height;
	int frame_width;
	afx_msg void OnBnClickedOk();
	int stride;

	// 在YUV文件中，像素的地址
	CString pixel_pos_in_yuv_file_str;// 在YUV文件中，像素的地址	unsigned long long pixel_pos_in_yuv_file_dec;
	unsigned long long pixel_pos_in_yuv_file;// 在YUV文件中，像素的地址	unsigned long long pixel_pos_in_yuv_file_dec;
	unsigned long long pixel_pos_in_yuv_file_dec;
	int frame_index; //像素所在的帧号，从0开始
	int comp_index; //像素所在的分量号，0-Y，1-U，V-2
	unsigned long long comp_pos_in_yuv_file;//所在分量在YUV文件中的偏移地址；
	CString comp_pos_in_yuv_file_str;
	int mb_index_in_comp; //像素所在的宏块在分量中的号；即MB相对该分量开头的偏移；
	int mb_x_in_comp; //像素所在的宏块在分量中的横坐标
	int mb_y_in_comp; //像素所在的宏块在分量中的纵坐标

	int pixel_index_in_frame; //像素相对所在帧的起始位置的偏移；

	int pixel_index_in_comp; //像素相对所在分量的起始位置的偏移；
	int pixel_x_in_comp; //像素在分量中的横坐标；
	int pixel_y_in_comp; //像素在分量中的纵坐标

	int pixel_index_in_mb_in_frame; //像素相对本宏块起始位置的偏移，范围从[0~stride*15+16]

	int pixel_index_in_mb; //单宏块范围内看，像素相对本宏块起始位置的偏移，取值范围[0~255]
	int pixel_x_in_mb; //单宏块范围看，像素在宏块内的x坐标；
	int pixel_y_in_mb; //单宏块范围看，像素在宏块内的y坐标；
	afx_msg void OnBnClickedGetresult();
};
