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
	long		m_lPrjBands;		//���̲�����
	long		m_lLayerNums;		//����
	LAYERNET	m_AllLayerNet;		//���������ɵ�ȫ����
	LAYERIDX	m_LayerIdx;			//�������
	int			m_nCurLayerNo;		//��ǰ��ţ�(��ǰ���д���Ĳ��)
	char		m_pOrgImgName[256];	//ԭʼӰ����
	CString		m_strTmpDir;		//Ϊ���̴�������ʱ�ļ���
	MSRSDatasetH m_pOrgImg;

	//ÿ��Ӱ�����ʹ�ú�Ҫ�ر���Ӧ���ļ�ָ��
	CImgObj		m_CurImgObj;		//��ǰ��Ӱ�����
	CImgObj		m_SuperImgObj;		//������
	CImgObj		m_SubImgObj;		//�Ӷ���

	CObjAtt		m_CurObjRAtt;
	CObjAtt		m_CurObjWAtt;
	CObjAtt		m_SuperObjRAtt;
	CObjAtt		m_SuperObjWAtt;
	CObjAtt		m_SubObjRAtt;
	CObjAtt		m_SubObjWAtt;

	MSRSDatasetH m_pCurLayerImg;	//��ǰ��MSI  7.12 add ��ǰ���ָ����ⲿ���룬���ⲿ�ر�
	MSRSDatasetH m_pCurClsImg;	//��ǰ�����Ӱ�� lc20110322���
public:
	bool RemoveLevel(int i);
	bool CreateTempDirForPrj();
	void InitialProject();
	//��ʼ���ļ�·��
	BOOL setFilePath(char* m_strRstImgName);
	//lBufLen	����������
	//ÿ������ֻ��ʼ��һ�Σ�����ʹ�����Ի��屾�������������������
	bool PrepareImgObj(long lBufLen);
	bool PrepareWorking();
	void ClearProject();
	//��߶ȷָ�
	BOOL RS_MultiScaleSegment(char* m_strRstImgName);
};

extern "C" __declspec(dllexport) BOOL MultiScaleSegment(char* m_strRstImgName);

//#ifdef __cplusplus
//extern "C"{
//#endif

//BOOL CRsImgSegDll MultiScaleSegment();									//��߶ȷָ�
//BOOL CRsImgSegDll _MultiScaleSegment(double fscale,double fWShape,double fWCompact);

//#ifdef __cplusplus
//}
//#endif

//#ifdef _DEBUG
//#pragma comment(lib, "RsImgSegD.lib")
//#else
//#pragma comment(lib, "RsImgSeg.lib")
//#endif
