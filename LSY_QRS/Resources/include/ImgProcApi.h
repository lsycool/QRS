
/*================================================================================
// �ļ���		 �� ImgProcApi.h 
// �汾			 �� this 1.0.0 ; QGIS1.7.4 ;QT 4.7.1 ;GDAL 1.8.1                            
// Ŀ�ļ���Ҫ���ܣ� Ӱ����ӿ�
// ��������		 �� 2012.05.09
// ����޸�����  �� 2012.05.15
// ����			 ��  yq
// �޸���		 ��   
// ����			 �� ���κŴ�1��ʼ�����ͷ���ֵΪCPLErr��
//				 ��	Ŀǰ�����У�Ӱ��AOI�ü� �� Ӱ���ز���
//				 ��
//				 ��
//================================================================================*/
#pragma once 
#ifndef IMAGE_PROC_API_H
#define IMAGE_PROC_API_H

#include <gdal.h>
#include <gdal_priv.h>
#include <gdalwarper.h>
/*#include <gdal_alg.h>  *///for GDALPolygoniz

#include <ogr_api.h>
#include <ogr_srs_api.h>
#include <ogr_spatialref.h>
#include "ogrsf_frmts.h" //for ogr 

#include "RasterIOBaseDefine.h"

/** 
* @brief AOI��ͼ(GDAL) 
* @param pszInFile          �����ļ���·�� 
* @param pszOutFile         ��ͼ������ļ���·�� 
* @param pszAOIFile         AOI�ļ�·�� 
* @param pszSQL             ָ��AOI�ļ��е������ֶ�ֵ���ü� 
* @param pBandInex          ָ���ü��Ĳ��Σ�Ĭ��ΪNULL����ʾ�ü����в���,���κŴ�1��ʼ
* @param piBandCount        ָ���ü����εĸ�����ͬ��һ������ͬʱʹ�� 
* @param iBuffer            ָ��AOI�ļ�������Χ��Ĭ��Ϊ0����ʾ������ 
* @param pszFormat          ��ͼ������ļ��ĸ�ʽ 
* @param pProgress          ������ָ�� 
* @return �ɹ����� 
*/ 
int CutImageByAOIGDAL(const char* pszInFile, const char* pszOutFile, const char* pszAOIFile, const char* pszSQL=NULL,   
					int *pBandInex=NULL, int *piBandCount=NULL, int iBuffer=0, const char* pszFormat=NULL) ; 


int CutImageByAOIGDAL(GDALDatasetH hSrcDS, const char* pszOutFile, const char* pszAOIFile, const char* pszSQL=NULL,   
					  int *pBandInex=NULL, int *piBandCount=NULL, int iBuffer=0, const char* pszFormat=NULL); 

int CutImageByPolyset(GDALDatasetH hSrcDS, const char* pszOutFile,
					  D_DOT *pPolySet, long *pLenSet, long SetNum,
					  int *pBandInex=NULL, int *piBandCount=NULL, int iBuffer=0, const char* pszFormat=NULL) ; 

/** 
* �ز�������(GDAL) 
* @param pszSrcFile        �����ļ���·�� 
* @param pszOutFile        д��Ľ��ͼ���·�� 
* @param fResX             Xת�������ȣ�Ĭ�ϴ�СΪ1.0������1ͼ����С��1��ʾͼ����С 
* @param fResY             Yת�������ȣ�Ĭ�ϴ�СΪ1.0 
* @param nResampleMode     ����ģʽ�������֣�����μ�GDALResampleAlg���壬Ĭ��Ϊ˫�����ڲ� 
* @param pExtent           ������Χ��ΪNULL��ʾ����ȫͼ 
* @param pBandIndex        ָ���Ĳ���������ţ�ΪNULL��ʾ����ȫ������ ,���κŴ�1��ʼ
* @param pBandCount        �����Ĳ��θ�����ͬpBandIndexһͬʹ�ã���ʾ�������εĸ��� 
* @param pszFormat         д��Ľ��ͼ��ĸ�ʽ 
* @param pProgress         ������ָ�� 
* @return �ɹ�����0������Ϊ����ֵ 
*/ 
int ResampleGDAL(const char* pszSrcFile, const char* pszOutFile, double fResX , double fResY, GDALResampleAlg nResampleMode=GRA_NearestNeighbour,  
			    D_RECT *pRect/*OGREnvelope* pExtent*/=NULL, int* pBandIndex=NULL, int *pBandCount=NULL, const char* pszFormat=NULL);



int ResampleGDAL(GDALDatasetH  hDSrc, const char* pszOutFile, double fResX , double fResY, GDALResampleAlg nResampleMode=GRA_NearestNeighbour,  
				D_RECT *pRect/* OGREnvelope* pExtent*/=NULL, int* pBandIndex=NULL, int *pBandCount=0, const char* pszFormat=NULL) ;



/** 
* ʸ��תդ��
* @param pszVectorFile     �����ļ���·�� 
* @param pszRasterFile     д��Ľ��ͼ���·�� 
* @param xSize             x��������
* @param ySize             y��������
* @param szAttName         ���դ����������ֵ���ֶ���
* @param pszFormat		   դ�����ݸ�ʽ 
* @return �ɹ�����0������Ϊ����ֵ 
*/ 
long Vector2Raster(const char* pszVectorFile,const char* pszRasterFile,
				   int xSize,int ySize,const char* pszAttName,const char* pszFormat);  

/** 
* ʸ��תդ��
* @param pszVectorFile     �����ļ���·�� 
* @param pszRasterFile     д��Ľ��ͼ���·�� 
* @param xResolution             x����ֱ���
* @param yResolution             y����ֱ���
* @param szAttName         ���դ����������ֵ���ֶ���
* @param pszFormat		   դ�����ݸ�ʽ 
* @return �ɹ�����0������Ϊ����ֵ 
*/ 
long Vector2Raster2(const char* pszVectorFile,const char* pszRasterFile,
				   double xResolution,double yResolution,const char* pszAttName,const char* pszFormat);  

/** 
* ʸ�����ü�ʸ����
* @param pszTarget			Ŀ���ļ���ʸ�����ļ� 
* @param pszReference	    �ο��ļ���ʸ�����ļ� 
* @param pszResult          ���·��
*/ 
//void ClipPointsByPolygon(char *pszTarget,char *pszReference,char *pszResult);
#endif