//ocMultiScaleManage.h create in 2006.5
//多尺度管理实现的基本操作：多尺度的分割，特征统计，分类
/*************************************************************************************
m_strPrjDir临时文件夹用来在有上层约束时创建临时对象

在多尺度外面设置当前层，根据上下层来设置当前层，在多尺度内部不再创建文件
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

//根据上下层来设置当前层
	bool	SetCurLayer(CImgObj *pCurLayer);	
	bool	SetSuperLayer(CImgObj *pSuperLayer);
	bool	SetSubLayer(CImgObj *pSubLayer);
	bool	SetOrgImgLayer(MSRSDatasetH OrghDS);//bool	SetOrgImgLayer(MSI *pOrgMsi);
	
	bool	SetCurPrjDir(char *pszCurPrjDir);

//多尺度管理可支持多尺度分割、特征统计、分类
public:

	//多尺度分割
	long MultiScaleSeg(float fScale,long lBands,float *fpWBands,float fWColor,float fWCompact,bool bMrgMethod);
	//影像对象合并
	long ClassObjUnite(long lBands,long lObjNums,long *plClsID);

private:
	CImgObj		 *m_pCurLayer;		//当前对象层
	CImgObj		 *m_pSuperLayer;	//父对象层
	CImgObj		 *m_pSubLayer;		//子对象层
	MSRSDatasetH m_OrghDS;			//原始影像
	bool		 m_bIsSuper;		//父对象层存在标志
	bool		 m_bIsSub;			//子对象层存在标志
	CString		 m_strPrjDir;		//工程路径可否delete 
};


#endif