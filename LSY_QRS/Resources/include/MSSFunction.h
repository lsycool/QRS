//��߶ȹ�������Ҫ�õ��ĺ���
//ע�⣺��Щ�����Ѿ�����

/************************************************************************************
2006.5.23	����ɨ����Ѱ���Ӷ���ĺ���


*************************************************************************************/
#pragma once
#ifndef _MSS_Function_H_
#define _MSS_Function_H_

#include "Afxtempl.h"
#include "msoodef.h"
#include "RasterIO.h"

using namespace RASTER_IO;

//���ֵײ�ɨ���ߴ����߼����䣬��װֱ�ӷ�����Ԫֵ������cqh
double v7x_rsGetCell0(LPRASTER_ADAPT pRasOBJ, short BandNo, long RowNo, long ColNo, char *pInvalidFlag=NULL);

//��Ӱ��IO�����ᵽ�������ѭ��֮�⣬����ٶȣ�cqh
//ֻ�и�����û���Ӷ���
long GetSubPixels0(LPRASTER_ADAPT rsadp_sp,OCREGPOS FatherObjPos,OBJECTSARR& SubObjs,long lLines,long lLineCells);

long GetNeighborObjs0(LPRASTER_ADAPT lpRasAdpt,OCREGPOS CurObjPos,int nFeatureDis,OBJECTSARR& NeiObjs,long lLines, long lLineCells);

//ȡһ���������Ӧ��һ���Ӷ���
long GetSubObjs0(LPRASTER_ADAPT rsadp_sp, LPRASTER_ADAPT rsadp_sub, OCREGPOS FatherObjPos, OBJECTSARR& SubObjs,long lLines,long lLineCells);

long UpdateObjectID0(LPRASTER_ADAPT rsadp_old, LPRASTER_ADAPT rsadp_rst,OCREGPOS& ObjPos,long lObjID, long lLines,long lLineCells);

//bool mssCalTotalHeterogeneity(OOOBJATT *pObjAtt1,OOOBJATT *pObjAtt2,long lMtlEdgeNum,long lBands,float *dpWBands,float dWColor,float dWSmooth,double *dpTotalHeter);

//double mssCalMergeMean(long n1,double Mean1,long n2,double Mean2);
//
//double mssCalMergeDeviation(long n1,double Mean1,double StdDev1,long n2,double Mean2,double StdDev2);
//
////�������ϲ���İ�Χ��
//void   mssCalMergeBoundRect(RECT drObjRect1,RECT drObjRect2,RECT *pMrgRect);

//�����ںϺ�Ķ�������
//bool  mssCalMergeObjAtt(OOOBJATT *pObjAtt1, OOOBJATT *pObjAtt2, OOOBJATT *pMrgObjAtt,long lBands);

//�ж��ļ����Ƿ����
bool  IsDirectoryExist(const char *sCurDir);

//��ȡ��ǰϵͳʱ��
long  msGetSystemCurDateTime(short *mS);

//long	SearchSeed(MSI *pMsi, long lCurY, long lXLeft, long lXRight, long lCurVal, AryObjPos& StackPos);
void	SearchSeed(LPRASTER_ADAPT lpRasAdpt, long lCurY, long lXLeft, long lXRight, long lCurVal, AryObjPos& StackPos);

void	InsertSubObjID(long lSubObjID,OBJECTSARR& SubObjs);

bool	DeleteDirectory(char *pszDir);	//ɾ��ָ��Ŀ¼�µ�ȫ������

bool	CalPixelsCovMatrix(POINT *pPixles,long lNums,double *dpMatrix);


//ֻ�и�����û���Ӷ���
long GetSubPixels(MSRSDatasetH SuperhDS,MSRSDatasetH SubhDS,OCREGPOS FatherObjPos,OBJECTSARR& SubObjs);

long GetNeighborObjs(MSRSDatasetH hDS,OCREGPOS CurObjPos,int nFeatureDis,OBJECTSARR& NeiObjs); //20090416

long FillAObject(LPRASTER_ADAPT lpRasAdpt,OCREGPOS& ObjPos, long lObjFill, long lLines, long lLineCells);



//ȡһ���������Ӧ��һ���Ӷ���
long GetSubObjs(MSRSDatasetH SuperhDS,MSRSDatasetH SubhDS,OCREGPOS FatherObjPos,OBJECTSARR& SubObjs);

long UpdateObjectID(MSRSDatasetH OldhDS,MSRSDatasetH RsthDS,OCREGPOS& ObjPos,long lObjID);


bool CalObjCenter(MSRSDatasetH hDS,MSRSDatasetH OrghDS,OCREGPOS& ObjPos,double& dXCenter,double& dYCenter);


double  msGetDataSetCellValue(MSRSDatasetH hDS,long lBandNo,long Line,long LineCell);
long   msSetDataSetCellValue(MSRSDatasetH hDS,long lBandNo,long Line,long LineCell,double CellValue);


#endif
