
/*================================================================================
// 文件名		 ： ImgProcApi.h 
// 版本			 ： this 1.0.0 ; QGIS1.7.4 ;QT 4.7.1 ;GDAL 1.8.1                            
// 目的及主要功能： 影像处理接口
// 创建日期		 ： 2012.05.09
// 最后修改日期  ： 2012.05.15
// 作者			 ：  yq
// 修改者		 ：   
// 描述			 ： 波段号从1开始；整型返回值为CPLErr；
//				 ：	目前功能有：影像AOI裁剪 ， 影像重采样
//				 ：
//				 ：
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
* @brief AOI截图(GDAL) 
* @param pszInFile          输入文件的路径 
* @param pszOutFile         截图后输出文件的路径 
* @param pszAOIFile         AOI文件路径 
* @param pszSQL             指定AOI文件中的属性字段值来裁剪 
* @param pBandInex          指定裁剪的波段，默认为NULL，表示裁剪所有波段,波段号从1开始
* @param piBandCount        指定裁剪波段的个数，同上一个参数同时使用 
* @param iBuffer            指定AOI文件外扩范围，默认为0，表示不外扩 
* @param pszFormat          截图后输出文件的格式 
* @param pProgress          进度条指针 
* @return 成功返回 
*/ 
int CutImageByAOIGDAL(const char* pszInFile, const char* pszOutFile, const char* pszAOIFile, const char* pszSQL=NULL,   
					int *pBandInex=NULL, int *piBandCount=NULL, int iBuffer=0, const char* pszFormat=NULL) ; 


int CutImageByAOIGDAL(GDALDatasetH hSrcDS, const char* pszOutFile, const char* pszAOIFile, const char* pszSQL=NULL,   
					  int *pBandInex=NULL, int *piBandCount=NULL, int iBuffer=0, const char* pszFormat=NULL); 

int CutImageByPolyset(GDALDatasetH hSrcDS, const char* pszOutFile,
					  D_DOT *pPolySet, long *pLenSet, long SetNum,
					  int *pBandInex=NULL, int *piBandCount=NULL, int iBuffer=0, const char* pszFormat=NULL) ; 

/** 
* 重采样函数(GDAL) 
* @param pszSrcFile        输入文件的路径 
* @param pszOutFile        写入的结果图像的路径 
* @param fResX             X转换采样比，默认大小为1.0，大于1图像变大，小于1表示图像缩小 
* @param fResY             Y转换采样比，默认大小为1.0 
* @param nResampleMode     采样模式，有五种，具体参见GDALResampleAlg定义，默认为双线性内插 
* @param pExtent           采样范围，为NULL表示计算全图 
* @param pBandIndex        指定的采样波段序号，为NULL表示采样全部波段 ,波段号从1开始
* @param pBandCount        采样的波段个数，同pBandIndex一同使用，表示采样波段的个数 
* @param pszFormat         写入的结果图像的格式 
* @param pProgress         进度条指针 
* @return 成功返回0，否则为其他值 
*/ 
int ResampleGDAL(const char* pszSrcFile, const char* pszOutFile, double fResX , double fResY, GDALResampleAlg nResampleMode=GRA_NearestNeighbour,  
			    D_RECT *pRect/*OGREnvelope* pExtent*/=NULL, int* pBandIndex=NULL, int *pBandCount=NULL, const char* pszFormat=NULL);



int ResampleGDAL(GDALDatasetH  hDSrc, const char* pszOutFile, double fResX , double fResY, GDALResampleAlg nResampleMode=GRA_NearestNeighbour,  
				D_RECT *pRect/* OGREnvelope* pExtent*/=NULL, int* pBandIndex=NULL, int *pBandCount=0, const char* pszFormat=NULL) ;



/** 
* 矢量转栅格
* @param pszVectorFile     输入文件的路径 
* @param pszRasterFile     写入的结果图像的路径 
* @param xSize             x方向列数
* @param ySize             y方向行数
* @param szAttName         获得栅格数据亮度值的字段名
* @param pszFormat		   栅格数据格式 
* @return 成功返回0，否则为其他值 
*/ 
long Vector2Raster(const char* pszVectorFile,const char* pszRasterFile,
				   int xSize,int ySize,const char* pszAttName,const char* pszFormat);  

/** 
* 矢量转栅格
* @param pszVectorFile     输入文件的路径 
* @param pszRasterFile     写入的结果图像的路径 
* @param xResolution             x方向分辨率
* @param yResolution             y方向分辨率
* @param szAttName         获得栅格数据亮度值的字段名
* @param pszFormat		   栅格数据格式 
* @return 成功返回0，否则为其他值 
*/ 
long Vector2Raster2(const char* pszVectorFile,const char* pszRasterFile,
				   double xResolution,double yResolution,const char* pszAttName,const char* pszFormat);  

/** 
* 矢量区裁剪矢量点
* @param pszTarget			目标文件，矢量点文件 
* @param pszReference	    参考文件，矢量区文件 
* @param pszResult          结果路径
*/ 
//void ClipPointsByPolygon(char *pszTarget,char *pszReference,char *pszResult);
#endif