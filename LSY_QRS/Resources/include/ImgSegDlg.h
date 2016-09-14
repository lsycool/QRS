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
//{	�����м�¼�Ĳ����Ϣ  2006.6
//�ָ����
//typedef struct SegParam
//{
//	float	fScale;		//�߶Ȳ������ڷָ��ڲ�ƽ��
//	float	*fpWBands;	//������Ȩֵ
//	float	fWColor;	//��ɫȨֵ
//	float	fWSmooth;	//�⻬��Ȩֵ
//	bool	IsNormal;	//�ָʽ BF/LMBF;  true/false
//}SEGPARAM;
//////////////////////////////////////////////////////////////////////////
//typedef struct LayerInfo    //ÿ����Ҫ��¼����Ϣ
//{
//	bool	bIsDel;			//��ǰ���ļ��Ƿ�ɾ��
//	//	long	lLayerNo;		//���,��ǰ���ڷּ��ṹ�е�λ��
//	SEGPARAM *pParam;		//�ָ����
//	char	LayerTitle[128];//����
//	char	GrdName[128];	//դ���ļ���
//	char	AttName[128];	//�����ļ���
//	char	ClsName[128];	//�����ļ���
//	char	ClsImg[128];	//����Ӱ����	lc20100317���
//	char	VecName[128];	//ʸ���ļ���
//	bool	bIsCls;			//�Ƿ����
//	bool	bIsVec;			//�Ƿ�ʸ����
//	//	MSI		*pGrdMsi;		//դ��ָ�룬Ϊ��ʱΪNULL
//}LAYERINFO;

//typedef struct LevelIdx
//{
//	long	Idx;
//	bool	IsNew;
//} LEVELIDX;

typedef LAYERINFO* LEVELINFO;

typedef CArray<LEVELINFO, LEVELINFO&> LAYERNET;	//�ּ���
typedef CArray<LEVELIDX, LEVELIDX&>	  LAYERIDX;	//������������
//////////////////////////////////////////////////////////////////////////

class CImgSegDlg : public CDialog
{
public:
	CString		m_strOrgImgName;	//ԭʼӰ����,����·��
	long		m_lBands;			//ԭʼӰ�񲨶���
	LAYERNET	*m_pAllLayerNet;	//���������ɵ�ȫ����
	LAYERIDX	*m_pLayerIdx;		//�������
	int			m_CurSelLayer;		//ѡ���Ĳ��
	int			m_nSelLayer;
	bool		m_bIsInsertNew;		//�Ƿ�����µķָ��
	float		*m_fWBands;
	bool		bIsNormal;
	int         m_nID;              //������ʾ�ڷָ�ʱ�Ƿ񸲸ǵ�ǰ��
	int			m_nItemNo;
	int			m_nCurItemNo;		//��ǰѡ�н���Ȩֵ�޸ĵĲ���
	int			m_nRate;			//�������ı���

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
