//ImgSeg.h  create in 2006.4
//影像分割类，采用的方法为Fractal Net Evolution Approach

/**********************************************************************************
2006.5.19	增加对一个父对象的所有子对象进行合并的函数

2006.5.22   在临时影像对象上进行的子对象迭代过程的代码提成一个函数 MergeObjsByBF()

2006.6.6    为基于子像元的分割函数增加一个参数，有父对象分割子像元时在处理对象号和属性号
不一致时存在问题，需要增加一个参数

2010.7.10   扩展支持通用影像数据
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
	//设置波段数
	void SetSegBandNums(long lBands);

	//设置分割参数
	bool SetSegParameter(float fScale,long lBands,float *fpWBands,float fWColor,float fWCompact,bool bMrgMethod);

	//{	对于无上层约束的从下向上进行分割的两种情况
	//在原始影像上进行分割
	long SegBaseImage(CImgObj *pImgObj,MSRSDatasetH hDS);
	//在分割对象上进行分割
	long SegBaseObject(CImgObj *pImgObj);
	//}

	//{	对于有上层约束的分割，注意这两个函数都是针对一个父对象进行处理，要完成全部子对象的合并需要循环调用
	//在子对象上的分割
	long SegObjBaseSubObjs(CImgObj *pCurObj,CImgObj *pSuperObj,long lFatherObjID, OBJECTSARR& SubObjs,CImgObj *pTmpObj);
	//在子像元上的分割
	long SegObjBaseSubPixels(CImgObj *pCurObj,CImgObj *pSuperObj,MSRSDatasetH OrghDS,long lFatherObjID,
							 OBJECTSARR& SubObjs,CImgObj *pTmpObj,long &lStartObjID);

	//只有子对象层的，直接合并子对象层作为当前层
	long MergeObjsOnlyHaveSubLayer(CImgObj *pImgObj,long lObjNums,long *plClsID);
	long MergeObjsHaveSubAndSuperLayer(CImgObj *pCurObj,CImgObj *pSuperObj,long lFatherObjID,
									   OBJECTSARR& SubObjs,CImgObj *pTmpObj,long *plClsID);
	//}

	//////////////////////////////////////////////////////////////////////////
	// 新增分割方法，实验代码，未正式使用
	//在原始影像上进行分割 CHESS-FENA
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

	//计算两个对象的异质度
	void CalTotalHeterogeneity(OOOBJATT *pObjAtt1,OOOBJATT *pObjAtt2,long lMtlEdgeNum,double& dTotalHeter);

	//采用BF策略在已有对象上进行合并
	long SegObjByBF(CImgObj *pImgObj);

	//采用LMBF策略在已有对象上进行合并
	long SegObjByLMBF(CImgObj *pImgObj);

	//采用BF策略在原始影像上形成初始对象
	long SegImgByBF(CImgObj *pImgObj,MSRSDatasetH hDS);

	//采用LMBF策略在原始影像上形成初始对象
	long SegImgByLMBF(CImgObj *pImgObj,MSRSDatasetH hDS);

	//按BF策略分割一个父对象的所有子对象
	long SegSubObjsByBF(CImgObj *pCurObj,CImgObj *pSuperObj,long lFatherObjID,OBJECTSARR& SubObjs,CImgObj *pTmpObj);

	//按LMBF策略分割一个父对象的所有子对象
	long SegSubObjsByLMBF(CImgObj *pCurObj,CImgObj *pSuperObj,long lFatherObjID,OBJECTSARR& SubObjs,CImgObj *pTmpObj);

	//按BF策略分割一个父对象的所有子像元
	long SegSubPixelsByBF(CImgObj *pCurObj,CImgObj *pSuperObj,MSRSDatasetH OrghDS,long lFatherObjID,
						  OBJECTSARR& SubObjs,CImgObj *pTmpObj,long &lStartObjID);

	//按LMBF策略分割一个父对象的所有子像元
	long SegSubPixelsByLMBF(CImgObj *pCurObj,CImgObj *pSuperObj,MSRSDatasetH OrghDS,long lFatherObjID,
							OBJECTSARR& SubObjs,CImgObj *pTmpObj,long &lStartObjID);

	//合并临时对象 todo 暂时不改，结构确定以后再修改5.29
	long MergeObjsByBF();

	//////////////////////////////////////////////////////////////////////////
	// 新增分割方法，实验代码，未正式使用
	//均值漂移分割
	long SegImgByMeanShift(CImgObj *pImgObj,MSRSDatasetH hDS);

	//棋盘分割
	long SegImgByChess(CImgObj *pImgObj,MSRSDatasetH hDS);

	//long SegImgByQuadTree(CImgObj *pImgObj,MSRSDatasetH hDS);
	//long SetSegParameter2(long lPreScale);
	//long SegBaseImage2(CImgObj *pImgObj,MSRSDatasetH hDS);//QUADTREE-FENA Bug很多

public:
	long	m_lBands;		//分割的影像波段数
	float	m_fScale;		//尺度阀值  是输入值的平方
	float	*m_fpWBands;	//各波段权值，归一化以后的值，多尺度管理上进行归一化
	float	m_fWColor;		//颜色权值	
	float	m_fWShape;		//形状权值
	float	m_fWCompact;	//紧致度
	float	m_fWSmooth;		//光滑度
	bool	m_bMrgMethod;	//合并策略标志	true:BF / false:LMBF
	//long    m_lPreScale;    //棋盘与四叉树分割尺度

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