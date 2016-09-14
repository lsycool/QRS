// CImgSegDlg.h : main header file for the CImgSegDlg DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "MSSFunction.h"
#include "ocMultiScaleManage.h"
#include "resource.h"		// main symbols


 /*CCImgSegDlgApp
 See CImgSegDlg.cpp for the implementation of this class*/


class CCImgSegDlgApp : public CWinApp
{
public:
	CCImgSegDlgApp();
// Overrides
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};

class MutiSegManage
{
public:
	MutiSegManage();
	virtual ~MutiSegManage();
public:
	long		m_lPrjBands;		//工程波段数
	long		m_lLayerNums;		//层数
	LAYERNET	m_AllLayerNet;		//工程中生成的全部层
	LAYERIDX	m_LayerIdx;			//层号索引
	int			m_nCurLayerNo;		//当前层号，(当前进行处理的层号)
	char		m_pOrgImgName[256];	//原始影像名
	CString		m_strTmpDir;		//为工程创建的临时文件夹
	MSRSDatasetH m_pOrgImg;

	//每次影像对象使用后都要关闭相应的文件指针
	CImgObj		m_CurImgObj;		//当前层影像对象
	CImgObj		m_SuperImgObj;		//父对象
	CImgObj		m_SubImgObj;		//子对象

	CObjAtt		m_CurObjRAtt;
	CObjAtt		m_CurObjWAtt;
	CObjAtt		m_SuperObjRAtt;
	CObjAtt		m_SuperObjWAtt;
	CObjAtt		m_SubObjRAtt;
	CObjAtt		m_SubObjWAtt;

	MSRSDatasetH m_pCurLayerImg;	//当前层MSI  7.12 add 当前层的指针从外部传入，在外部关闭
	MSRSDatasetH m_pCurClsImg;	//当前层分类影像 lc20110322添加
public:
	bool RemoveLevel(int i);
	bool CreateTempDirForPrj();
	void InitialProject();
	//初始化文件路径
	BOOL setFilePath(char* m_strRstImgName);
	//lBufLen	缓冲区长度
	//每个工程只初始化一次，并且使用属性缓冲本身的析构函数进行析构
	bool PrepareImgObj(long lBufLen);
	bool PrepareWorking();
	void ClearProject();
	//多尺度分割
	BOOL RS_MultiScaleSegment(char* m_strRstImgName);
};

extern "C" __declspec(dllexport) BOOL MultiScaleSegment(char* m_strRstImgName);

//#ifdef __cplusplus
//extern "C"{
//#endif

//BOOL CRsImgSegDll MultiScaleSegment();									//多尺度分割
//BOOL CRsImgSegDll _MultiScaleSegment(double fscale,double fWShape,double fWCompact);

//#ifdef __cplusplus
//}
//#endif

//#ifdef _DEBUG
//#pragma comment(lib, "RsImgSegD.lib")
//#else
//#pragma comment(lib, "RsImgSeg.lib")
//#endif
