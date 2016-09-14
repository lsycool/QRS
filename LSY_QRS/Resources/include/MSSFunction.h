//多尺度管理中需要用到的函数
//注意：有些函数已经作废

/************************************************************************************
2006.5.23	增加扫描线寻找子对象的函数


*************************************************************************************/
#pragma once
#ifndef _MSS_Function_H_
#define _MSS_Function_H_

#include "Afxtempl.h"
#include "msoodef.h"
#include "RasterIO.h"

using namespace RASTER_IO;

//保持底层扫描线代码逻辑不变，封装直接返回像元值方法，cqh
double v7x_rsGetCell0(LPRASTER_ADAPT pRasOBJ, short BandNo, long RowNo, long ColNo, char *pInvalidFlag=NULL);

//将影像IO操作提到对象个数循环之外，提高速度，cqh
//只有父对象，没有子对象
long GetSubPixels0(LPRASTER_ADAPT rsadp_sp,OCREGPOS FatherObjPos,OBJECTSARR& SubObjs,long lLines,long lLineCells);

long GetNeighborObjs0(LPRASTER_ADAPT lpRasAdpt,OCREGPOS CurObjPos,int nFeatureDis,OBJECTSARR& NeiObjs,long lLines, long lLineCells);

//取一个父对象对应的一组子对象
long GetSubObjs0(LPRASTER_ADAPT rsadp_sp, LPRASTER_ADAPT rsadp_sub, OCREGPOS FatherObjPos, OBJECTSARR& SubObjs,long lLines,long lLineCells);

long UpdateObjectID0(LPRASTER_ADAPT rsadp_old, LPRASTER_ADAPT rsadp_rst,OCREGPOS& ObjPos,long lObjID, long lLines,long lLineCells);

//bool mssCalTotalHeterogeneity(OOOBJATT *pObjAtt1,OOOBJATT *pObjAtt2,long lMtlEdgeNum,long lBands,float *dpWBands,float dWColor,float dWSmooth,double *dpTotalHeter);

//double mssCalMergeMean(long n1,double Mean1,long n2,double Mean2);
//
//double mssCalMergeDeviation(long n1,double Mean1,double StdDev1,long n2,double Mean2,double StdDev2);
//
////计算对象合并后的包围盒
//void   mssCalMergeBoundRect(RECT drObjRect1,RECT drObjRect2,RECT *pMrgRect);

//计算融合后的对象属性
//bool  mssCalMergeObjAtt(OOOBJATT *pObjAtt1, OOOBJATT *pObjAtt2, OOOBJATT *pMrgObjAtt,long lBands);

//判断文件夹是否存在
bool  IsDirectoryExist(const char *sCurDir);

//获取当前系统时间
long  msGetSystemCurDateTime(short *mS);

//long	SearchSeed(MSI *pMsi, long lCurY, long lXLeft, long lXRight, long lCurVal, AryObjPos& StackPos);
void	SearchSeed(LPRASTER_ADAPT lpRasAdpt, long lCurY, long lXLeft, long lXRight, long lCurVal, AryObjPos& StackPos);

void	InsertSubObjID(long lSubObjID,OBJECTSARR& SubObjs);

bool	DeleteDirectory(char *pszDir);	//删除指定目录下的全部内容

bool	CalPixelsCovMatrix(POINT *pPixles,long lNums,double *dpMatrix);


//只有父对象，没有子对象
long GetSubPixels(MSRSDatasetH SuperhDS,MSRSDatasetH SubhDS,OCREGPOS FatherObjPos,OBJECTSARR& SubObjs);

long GetNeighborObjs(MSRSDatasetH hDS,OCREGPOS CurObjPos,int nFeatureDis,OBJECTSARR& NeiObjs); //20090416

long FillAObject(LPRASTER_ADAPT lpRasAdpt,OCREGPOS& ObjPos, long lObjFill, long lLines, long lLineCells);



//取一个父对象对应的一组子对象
long GetSubObjs(MSRSDatasetH SuperhDS,MSRSDatasetH SubhDS,OCREGPOS FatherObjPos,OBJECTSARR& SubObjs);

long UpdateObjectID(MSRSDatasetH OldhDS,MSRSDatasetH RsthDS,OCREGPOS& ObjPos,long lObjID);


bool CalObjCenter(MSRSDatasetH hDS,MSRSDatasetH OrghDS,OCREGPOS& ObjPos,double& dXCenter,double& dYCenter);


double  msGetDataSetCellValue(MSRSDatasetH hDS,long lBandNo,long Line,long LineCell);
long   msSetDataSetCellValue(MSRSDatasetH hDS,long lBandNo,long Line,long LineCell,double CellValue);


#endif
