// ImgSegDlg.h : header file

#if !defined(AFX_SEGDLG_H__D8E8E0C4_06D1_4C7B_B997_517BE0425F68__INCLUDED_)
#define AFX_SEGDLG_H__D8E8E0C4_06D1_4C7B_B997_517BE0425F68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif


/////////////////////////////////////////////////////////////////////////////
#include "msOOdef.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////////
//{	工程中记录的层次信息  2006.6
//分割参数
//typedef struct SegParam
//{
//	float	fScale;		//尺度参数，在分割内部平方
//	float	*fpWBands;	//各波段权值
//	float	fWColor;	//颜色权值
//	float	fWSmooth;	//光滑度权值
//	bool	IsNormal;	//分割方式 BF/LMBF;  true/false
//}SEGPARAM;
//////////////////////////////////////////////////////////////////////////
//typedef struct LayerInfo    //每层需要记录的信息
//{
//	bool	bIsDel;			//当前层文件是否被删除
//	//	long	lLayerNo;		//层号,当前层在分级结构中的位置
//	SEGPARAM *pParam;		//分割参数
//	char	LayerTitle[128];//层名
//	char	GrdName[128];	//栅格文件名
//	char	AttName[128];	//属性文件名
//	char	ClsName[128];	//分类文件名
//	char	ClsImg[128];	//分类影像名	lc20100317添加
//	char	VecName[128];	//矢量文件名
//	bool	bIsCls;			//是否分类
//	bool	bIsVec;			//是否矢量化
//	//	MSI		*pGrdMsi;		//栅格指针，为打开时为NULL
//}LAYERINFO;

//typedef struct LevelIdx
//{
//	long	Idx;
//	bool	IsNew;
//} LEVELIDX;

typedef LAYERINFO* LEVELINFO;

typedef CArray<LEVELINFO, LEVELINFO&> LAYERNET;	//分级网
typedef CArray<LEVELIDX, LEVELIDX&>	  LAYERIDX;	//多层网络的索引
//////////////////////////////////////////////////////////////////////////

class CImgSegDlg : public CDialog
{
public:
	CString		m_strOrgImgName;	//原始影像名,不带路径
	long		m_lBands;			//原始影像波段数
	LAYERNET	*m_pAllLayerNet;	//工程中生成的全部层
	LAYERIDX	*m_pLayerIdx;		//层号索引
	int			m_CurSelLayer;		//选定的层号
	int			m_nSelLayer;
	bool		m_bIsInsertNew;		//是否插入新的分割层
	float		*m_fWBands;
	bool		bIsNormal;
	int         m_nID;              //用来表示在分割时是否覆盖当前层
	int			m_nItemNo;
	int			m_nCurItemNo;		//当前选中进行权值修改的波段
	int			m_nRate;			//滑动条的比例

	// Construction
public:
	CImgSegDlg(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CImgSegDlg)
	enum { IDD = IDD_IMGSEGDLG };

	CSliderCtrl	m_SliderCpt;
	CSliderCtrl	m_SliderShp;
	CComboBox	m_SegMode;
	CListCtrl	m_ImgList;
	CListBox	m_LayerSel;
	float	    m_fScale;
	float	    m_fWShape;
	float	    m_fWCompact;
	int		    m_nSegModeIdx;
	float	    m_WBands;
	float	    m_fWSmooth;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgSegDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImgSegDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeSegMode();
	afx_msg void OnSelchangeLayerListBox();
	afx_msg void OnKillfocusScale();
	afx_msg void OnKillfocusBandWeight();
	afx_msg void OnClickImgListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateBandWeight();
	afx_msg void OnUpdateCompactWeight();
	afx_msg void OnUpdateShapeWeight();
	afx_msg void OnChangeSmoothWeight();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void ShowLayerSel();
	void ShowImgWeight();
	void SetSelLayerInfo();
	void SetInitParam(long lBands);

	afx_msg void OnBnImportXML();
	afx_msg void OnBnExportXML();
	afx_msg void OnBnClickedOk();
	afx_msg void _OnBnImportXML();
	afx_msg void _OnBnExportXML();
	afx_msg void OnCreateMaskImg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEGDLG_H__D8E8E0C4_06D1_4C7B_B997_517BE0425F68__INCLUDED_)
