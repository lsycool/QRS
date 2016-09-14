//ocMultiScaleManage.h create in 2006.5
//��߶ȹ���ʵ�ֵĻ�����������߶ȵķָ����ͳ�ƣ�����
/*************************************************************************************
m_strPrjDir��ʱ�ļ������������ϲ�Լ��ʱ������ʱ����

�ڶ�߶��������õ�ǰ�㣬�������²������õ�ǰ�㣬�ڶ�߶��ڲ����ٴ����ļ�
*************************************************************************************/
#ifndef _OC_MultiScale_Manage_H_
#define _OC_MultiScale_Manage_H_
#pragma once

#include "ImgSeg.h" 

class CMultiScaleManage
{
public:
	CMultiScaleManage();
	virtual	~CMultiScaleManage();

//�������²������õ�ǰ��
	bool	SetCurLayer(CImgObj *pCurLayer);	
	bool	SetSuperLayer(CImgObj *pSuperLayer);
	bool	SetSubLayer(CImgObj *pSubLayer);
	bool	SetOrgImgLayer(MSRSDatasetH OrghDS);//bool	SetOrgImgLayer(MSI *pOrgMsi);
	
	bool	SetCurPrjDir(char *pszCurPrjDir);

//��߶ȹ����֧�ֶ�߶ȷָ����ͳ�ơ�����
public:

	//��߶ȷָ�
	long MultiScaleSeg(float fScale,long lBands,float *fpWBands,float fWColor,float fWCompact,bool bMrgMethod);
	//Ӱ�����ϲ�
	long ClassObjUnite(long lBands,long lObjNums,long *plClsID);

private:
	CImgObj		 *m_pCurLayer;		//��ǰ�����
	CImgObj		 *m_pSuperLayer;	//�������
	CImgObj		 *m_pSubLayer;		//�Ӷ����
	MSRSDatasetH m_OrghDS;			//ԭʼӰ��
	bool		 m_bIsSuper;		//���������ڱ�־
	bool		 m_bIsSub;			//�Ӷ������ڱ�־
	CString		 m_strPrjDir;		//����·���ɷ�delete 
};


#endif