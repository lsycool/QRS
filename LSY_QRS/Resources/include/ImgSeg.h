//ImgSeg.h  create in 2006.4
//Ӱ��ָ��࣬���õķ���ΪFractal Net Evolution Approach

/**********************************************************************************
2006.5.19	���Ӷ�һ��������������Ӷ�����кϲ��ĺ���

2006.5.22   ����ʱӰ������Ͻ��е��Ӷ���������̵Ĵ������һ������ MergeObjsByBF()

2006.6.6    Ϊ��������Ԫ�ķָ������һ���������и�����ָ�����Ԫʱ�ڴ������ź����Ժ�
��һ��ʱ�������⣬��Ҫ����һ������

2010.7.10   ��չ֧��ͨ��Ӱ������
***********************************************************************************/
#pragma once
#ifndef _OC_FNEA_Segment_H_
#define _OC_FNEA_Segment_H_

#include "ocGridImgObj.h"
//////////////////////////////////////////////////////////////////////////

class CImgSeg
{
public:
	CImgSeg();
	virtual	~CImgSeg();

public:
	//���ò�����
	void SetSegBandNums(long lBands);

	//���÷ָ����
	bool SetSegParameter(float fScale,long lBands,float *fpWBands,float fWColor,float fWCompact,bool bMrgMethod);

	//{	�������ϲ�Լ���Ĵ������Ͻ��зָ���������
	//��ԭʼӰ���Ͻ��зָ�
	long SegBaseImage(CImgObj *pImgObj,MSRSDatasetH hDS);
	//�ڷָ�����Ͻ��зָ�
	long SegBaseObject(CImgObj *pImgObj);
	//}

	//{	�������ϲ�Լ���ķָע�������������������һ����������д���Ҫ���ȫ���Ӷ���ĺϲ���Ҫѭ������
	//���Ӷ����ϵķָ�
	long SegObjBaseSubObjs(CImgObj *pCurObj,CImgObj *pSuperObj,long lFatherObjID, OBJECTSARR& SubObjs,CImgObj *pTmpObj);
	//������Ԫ�ϵķָ�
	long SegObjBaseSubPixels(CImgObj *pCurObj,CImgObj *pSuperObj,MSRSDatasetH OrghDS,long lFatherObjID,
							 OBJECTSARR& SubObjs,CImgObj *pTmpObj,long &lStartObjID);

	//ֻ���Ӷ����ģ�ֱ�Ӻϲ��Ӷ������Ϊ��ǰ��
	long MergeObjsOnlyHaveSubLayer(CImgObj *pImgObj,long lObjNums,long *plClsID);
	long MergeObjsHaveSubAndSuperLayer(CImgObj *pCurObj,CImgObj *pSuperObj,long lFatherObjID,
									   OBJECTSARR& SubObjs,CImgObj *pTmpObj,long *plClsID);
	//}

	//////////////////////////////////////////////////////////////////////////
	// �����ָ����ʵ����룬δ��ʽʹ��
	//��ԭʼӰ���Ͻ��зָ� CHESS-FENA
	long SegBaseImage1(CImgObj *pImgObj,MSRSDatasetH hDS);

private:
	__inline 
	double mssCalMergeMean(long n1,double Mean1,long n2,double Mean2){
		//return	(n1*Mean1+n2*Mean2)/(n1+n2);
		const float dn(1.0f/(n1+n2));
		return (n1*Mean1+n2*Mean2)*dn;
	}
	__inline 
	double mssCalMergeDeviation(long n1,double Mean1,double StdDev1,long n2,double Mean2,double StdDev2) {
		//return	(n1*StdDev1*StdDev1+n2*StdDev2*StdDev2)/(n1+n2)+n1*n2*(Mean1-Mean2)*(Mean1-Mean2)/((n1+n2)*(n1+n2));
		const float dn(1.0f/(n1+n2));
		return (n1*StdDev1*StdDev1+n2*StdDev2*StdDev2)*dn + n1*n2*(Mean1-Mean2)*(Mean1-Mean2)*dn*dn;
	}
	__inline 
	void mssCalMergeBoundRect(RECT drObjRect1,RECT drObjRect2,RECT *pMrgRect)	{
		drObjRect1.right>drObjRect2.right ? pMrgRect->right=drObjRect1.right : pMrgRect->right=drObjRect2.right;
		drObjRect1.left<drObjRect2.left ? pMrgRect->left=drObjRect1.left : pMrgRect->left=drObjRect2.left;
		drObjRect1.top<drObjRect2.top ? pMrgRect->top=drObjRect1.top : pMrgRect->top=drObjRect2.top;
		drObjRect1.bottom>drObjRect2.bottom ? pMrgRect->bottom=drObjRect1.bottom : pMrgRect->bottom=drObjRect2.bottom;
	}

	//����������������ʶ�
	void CalTotalHeterogeneity(OOOBJATT *pObjAtt1,OOOBJATT *pObjAtt2,long lMtlEdgeNum,double& dTotalHeter);

	//����BF���������ж����Ͻ��кϲ�
	long SegObjByBF(CImgObj *pImgObj);

	//����LMBF���������ж����Ͻ��кϲ�
	long SegObjByLMBF(CImgObj *pImgObj);

	//����BF������ԭʼӰ�����γɳ�ʼ����
	long SegImgByBF(CImgObj *pImgObj,MSRSDatasetH hDS);

	//����LMBF������ԭʼӰ�����γɳ�ʼ����
	long SegImgByLMBF(CImgObj *pImgObj,MSRSDatasetH hDS);

	//��BF���Էָ�һ��������������Ӷ���
	long SegSubObjsByBF(CImgObj *pCurObj,CImgObj *pSuperObj,long lFatherObjID,OBJECTSARR& SubObjs,CImgObj *pTmpObj);

	//��LMBF���Էָ�һ��������������Ӷ���
	long SegSubObjsByLMBF(CImgObj *pCurObj,CImgObj *pSuperObj,long lFatherObjID,OBJECTSARR& SubObjs,CImgObj *pTmpObj);

	//��BF���Էָ�һ�����������������Ԫ
	long SegSubPixelsByBF(CImgObj *pCurObj,CImgObj *pSuperObj,MSRSDatasetH OrghDS,long lFatherObjID,
						  OBJECTSARR& SubObjs,CImgObj *pTmpObj,long &lStartObjID);

	//��LMBF���Էָ�һ�����������������Ԫ
	long SegSubPixelsByLMBF(CImgObj *pCurObj,CImgObj *pSuperObj,MSRSDatasetH OrghDS,long lFatherObjID,
							OBJECTSARR& SubObjs,CImgObj *pTmpObj,long &lStartObjID);

	//�ϲ���ʱ���� todo ��ʱ���ģ��ṹȷ���Ժ����޸�5.29
	long MergeObjsByBF();

	//////////////////////////////////////////////////////////////////////////
	// �����ָ����ʵ����룬δ��ʽʹ��
	//��ֵƯ�Ʒָ�
	long SegImgByMeanShift(CImgObj *pImgObj,MSRSDatasetH hDS);

	//���̷ָ�
	long SegImgByChess(CImgObj *pImgObj,MSRSDatasetH hDS);

	//long SegImgByQuadTree(CImgObj *pImgObj,MSRSDatasetH hDS);
	//long SetSegParameter2(long lPreScale);
	//long SegBaseImage2(CImgObj *pImgObj,MSRSDatasetH hDS);//QUADTREE-FENA Bug�ܶ�

public:
	long	m_lBands;		//�ָ��Ӱ�񲨶���
	float	m_fScale;		//�߶ȷ�ֵ  ������ֵ��ƽ��
	float	*m_fpWBands;	//������Ȩֵ����һ���Ժ��ֵ����߶ȹ����Ͻ��й�һ��
	float	m_fWColor;		//��ɫȨֵ	
	float	m_fWShape;		//��״Ȩֵ
	float	m_fWCompact;	//���¶�
	float	m_fWSmooth;		//�⻬��
	bool	m_bMrgMethod;	//�ϲ����Ա�־	true:BF / false:LMBF
	//long    m_lPreScale;    //�������Ĳ����ָ�߶�

public:
	long	m_lLineCells;
	long	m_lLines;
	int*	m_pMaskImg;
	long	QickSegBaseImage(CImgObj *pImgObj,MSRSDatasetH hDS);
	long	QickSegImgByBF(CImgObj *pImgObj,MSRSDatasetH hDS,long&lInvalidObjNum);
	long	QickSegObjByBF(CImgObj *pImgObj, long lInvalidObjNum);
	void	SetMaskImg(MSRSDatasetH hDS);
};

#endif