
//================================================================================
// 文件名		 ： RasterIO.h 
// 版本			 ： this 1.0.0 ; QGIS1.7.4 ;QT 4.7.1 ;GDAL 1.8.1                            
// 目的及主要功能： 影像IO接口
// 创建日期		 ： 2012.04.25
// 最后修改日期  ： 2012.05.15 
// 作者			 ：  yq
// 修改者		 ：  yq,lxd
// 描述			 ： 波段号从1开始；
//				 ：整型返回值为CPLErr；成功/失败 0/错误代码
//================================================================================

//整型返回值
//typedef enum
//{
//	CE_None = 0,
//	CE_Debug = 1,
//	CE_Warning = 2,
//	CE_Failure = 3,
//	CE_Fatal = 4
//} CPLErr;
//新调整函数
// 像元值联合类型
#pragma once
#ifndef RASTER_IO_H
#define RASTER_IO_H

#ifndef STD_API  
#define STD_API __stdcall  
#endif 

#include "RasterIOBaseDefine.h"
#include "RasterCache.h"
#include "RasBaseDefine.h"
#include "msOOdef.h"

namespace RASTER_IO
{
typedef void *MSRSMajorObjectH;		// 抽象对象句柄
typedef void *MSRSDatasetH;			// 影像数据集句柄
typedef void *MSRSRasterBandH;		// 影像波段句柄
typedef void *MSRSDriverH;			// 影像数据驱动句柄
typedef void *RSRasterCacheH;		// 影像数据IO缓存句柄
typedef void *MSRSColorTableH;		// 影像数据色表

union CellVal
{
	unsigned  char  *ucData;
	unsigned  short *usData;
	signed    short *ssData;
	unsigned  long  *ulData;
	signed    long  *slData;	
	float   *flData;
	double  *dfData;
};


//打开影像文件
MSRSDatasetH  msRSOpen(const char *pszFilename, MSRSAccess eAccess, void *pRSGDB=0);

//由影像类型名获取数据驱动
MSRSDriverH  msRSGetDriverByName(const char * pszFormat);

//创建影像数据集
MSRSDatasetH  msRSCreate(MSRSDriverH hDriver, const char* pszFilename, int nXSize, int nYSize,
						 int nBands, MSRSDataType eDataType, char ** papszOptions, void *pRSGDB=0);
//关闭影像文件
void  msRSClose(MSRSDatasetH hDS);


//获取指定波段,注意波段ID从1开始，刘旭东添加
MSRSRasterBandH	msRSGetRasterBand(MSRSDatasetH hDs,int nBandID);

//拷贝色表信息，成功返回0.失败返回其他，刘旭东添加
long dtmCopyDislayLutFromOrgRaster(MSRSDatasetH hDs,MSRSRasterBandH hOutDs); 

//获取影像行数/列数/波段数
int  msRSGetRasterXSize( MSRSDatasetH hDS );
int  msRSGetRasterYSize( MSRSDatasetH hDS );
int  msRSGetRasterCount( MSRSDatasetH hDS );

//获取影像空间分辨率
long  msGetImgCellSize(MSRSDatasetH hDS,double &dXCellSize,double &dYCellSize);//获取像元大小

//获取影像像元类型信息
MSRSDataType  msRSGetDatasetType(MSRSDatasetH hDS);

//波段数据读写
long  msRSRasterIO(MSRSRasterBandH hBand, MSRSRWFlag eRWFlag,int nDSXOff, int nDSYOff, 
						   int nDSXSize, int nDSYSize, void *pData, int nBufXSize, int nBufYSize,
						   MSRSDataType eBufType, int nPixelSpace, int nLineSpace);

//分配数组内存,以字节为单位
void * msMalloc(long size);
//释放数组内存
void   msFree(void *pData);

//根据像元类型将数据块转为像元值，单值转
//void  msRSConvValue(MSRSDataType eDataType, void *pData, double &dVal);


//获取无效值信息
double  msRSGetRasterNoDataValue( MSRSRasterBandH hBand, int *pbSuccess=0 );
long  msRSSetRasterNoDataValue( MSRSRasterBandH hBand, double dfValue );

// 读写操作
long  msRSSetCell(MSRSDatasetH hDS, short BandNo, long RowNo, long ColNo, double Value);
long  msRSGetCell(MSRSDatasetH hDS, short BandNo, long RowNo, long ColNo, double &Value, char *pInvalidFlag=0);

//拷贝坐标变换参数
long  msCopyCoordinateInfo(MSRSDatasetH hSrcDS,MSRSDatasetH hDstDS,long lStartLine,long lStartCell); 
//拷贝投影信息
long  msCopyProjectionInfo(MSRSDatasetH hSrcDS,MSRSDatasetH hDstDS); 

//获取对象的描述信息
// MSRSMajorObjectH hObject	抽象对象句柄，可以传入MSRSDatasetH/MSRSRasterBandH等派生对象句柄
const char* msRSGetDescription( MSRSMajorObjectH hObject );

//打开金字塔层，影像数据读/写前必须打开，PyLayerNo从1开始
//主要针对MapGIS7栅格数据集，为了统一，读写前均要打开
long msRSOpenPyramidLayer(MSRSDatasetH hDS, short PyLayerNo);

//关闭金字塔层
long msRSClosePyramidLayer(MSRSDatasetH hDS);

//根据像元类型和数目申请像元值数据块空间
long msRSNewValueData(MSRSDataType eDataType, void **pData, long lCellNum);

//释放像元值数据块的空间
void msRSDelValueData(void *pData);

//根据像元类型由数据块转像元值，单转
void msRSConvValue(MSRSDataType eDataType, void *pData, double &dVal);

//根据像元类型由数据块转像元值，批转
void msRSConvNValues(MSRSDataType eDataType, void *pData, long lCellNum, double *pdVal);

//将msi取出的double类型的数据转换为对应类型的数据，主要用于将直接利用msGetCell取出的
//double型数据转换为msRSRasterIO写入时需要的类型
//注：pData已在调用该函数前按照对应类型分配好内存空间
void msConvNDValues(double *pdVal,MSRSDataType eDataType, void *pData, long lCellNum);

// -------------------- 取各个金字金字塔层的行列分块数 -------------------- //
long  msRSCalPyramidLayerRowColTileNums(MSRSDatasetH hDS,long lPyramidLayerNo,long lTileWidth,long  lTileHeight,
										long *plRowTileNums,long  *plColTileNums);
int msRSGetDataTypeSize( MSRSDataType eDataType );
int msRSGetOverviewCount( MSRSRasterBandH hBand );

/** 
* @brief 影像地理坐标范围
* @param hSrcDS          ：原始影像数据指针 
* @param rc				 ：影像外包矩形的地理坐标 
*/ 
bool  _msRSGetMapRange(MSRSDatasetH hDS, D_RECT &rc);
// 获取地理范围
bool msRSGetMapRange(MSRSDatasetH hDS, D_RECT &rc);

/** 
* @brief 通用数据层重采样函数
* @param hSrcDS          ：原始影像数据指针 
* @param pszOutFile      ：结果影像数据指针 
* @param dXScale         ： X转换采样比，大于1图像变大，小于1表示图像缩小 
* @param dYScale         ： Y转换采样比，
* @param lInterpolate    ：重采样方式, 0最邻近，1双线性 
* @param dXOff			 ：X方向起点图像坐标
* @param dYOff           ：Y方向起点图像坐标
* @return 成功/返回  0/错误代码
*/ 

long  msReSample0(MSRSDatasetH hSrcDS,const char* pszOutFile,double dXScale,double dYScale,
				  long lInterpolate=0,double dXOff=0,double dYOff=0);


/** 
* @brief 区AOI文件裁剪影像
* @param pszInFile          输入文件的路径 
* @param pszOutFile         截图后输出文件的路径 
* @param pszAOIFile         AOI文件路径 
* @param pszSQL             指定AOI文件中的属性字段值来裁剪 
* @param pBandInex          指定裁剪的波段，默认为NULL，表示裁剪所有波段 
* @param piBandCount        指定裁剪波段的个数，同上一个参数同时使用 
* @param iBuffer            指定AOI文件外扩范围，默认为0，表示不外扩 
* @param pszFormat          截图后输出文件的格式 ，为0时与原始数据保持一样的格式
* @return 成功/返回  0/错误代码
*/ 

int msRSClipImgByFeature(MSRSDatasetH hSrcDS, const char* pszOutFile, const char* pszAOIFile, const char* pszSQL=0,   
					  int *pBandInex=0, int *piBandCount=0, int iBuffer=0, const char* pszFormat=0); 



long msRSClipImage(MSRSDatasetH hSrcDS,const char *pszOutFile,
							 D_DOT *pPolySet, long *pLenSet, long SetNum, 
							 int *pProcBandList=0,int *lProcBandNum=0,
							 const char* pszFormat=0);

void msRSGetStatFileName(MSRSDatasetH pDataset,char *sStaFileName);

void msRSAllRegister();//注册所有支持的数据类型

//根据文件名获取对应的文件类型，具体处理方法是利用通用函数打开文件，如果打开成功
//则根据当前的Driver名返回文件类型,这样可以避免单纯依据后缀产生的错误
const char* msGetFileTypeByNameExt(LPCSTR pszFilename,void *pRSGDB);

//根据已有的数据集复制新的影像数据集
//int bStrict		TRUE - 严格拷贝; FALSE - 拷贝必需信息
MSRSDatasetH msRSCreateCopy( MSRSDriverH hDriver, const char * pszFilename, MSRSDatasetH hSrcDS, int bStrict, char ** papszOptions);

//创建金字塔层
long msRSBuildOverviews(MSRSDatasetH hDS,const char *pszResampling, 
						int nOverviews, int *panOverviewList, int nListBands, int *panBandList);


/* ==================================================================== */
/*                       影像波段直方图相关函数                         */
/* ==================================================================== */

// double dfMin,dfMax		直方图的下限(左端点)/上限(右端点)
// int nBuckets				直方图桶数(分级数)，桶大小 = (dfMax-dfMin)/nBuckets
// int *panHistogram		直方图数组
// int bIncludeOutOfRange	(TRUE/FALSE)是否统计范围外；FALSE - 只统计(dfMin,dfMax)范围内像元值；
//							TRUE - 小于dfMin的被映射到panHistogram[0]，大于dfMax的被映射到panHistogram[nBuckets-1]

//获取直方图信息
// 针对波段完成，panHistogram直方图空间在调用前申请
// 以8位无符号数据256级的直方图统计为例， 
// 为了防止计算比例过程中直方图边界取整时可能产生的错误，上下限如下赋值 -0.5, 255.5；
// int anHistogram[256];
// long lErr = msRSGetRasterHistogram( -0.5, 255.5, 256, anHistogram, FALSE, FALSE );
long msRSGetRasterHistogram( MSRSRasterBandH hBand,double dfMin,double dfMax,int nBuckets,
							int *panHistogram, int bIncludeOutOfRange, int bApproxOK);

//获取缺省直方图信息
// 针对波段完成，int **ppanHistogram直方图空间由函数在内部自动申请
// double *pdfMin,double *pdfMax,int *pnBuckets带回下限/上限/桶数等直方图信息
long msRSGetDefaultHistogram( MSRSRasterBandH hBand, double *pdfMin, double *pdfMax, 
							 int *pnBuckets, int **ppanHistogram, int bForce);

//设置缺省直方图信息
long msRSSetDefaultHistogram( MSRSRasterBandH hBand,double dfMin,double dfMax,int nBuckets,int *panHistogram );

//计算波段统计信息(均值/标准差)
long msRSComputeBandStats( MSRSRasterBandH hSrcBand,int nSampleStep,double *pdfMean, double *pdfStdDev);

//计算影像波段的最值
//int bApproxOK			TRUE - 取近似值，类似msRSGetRasterMinimum()/msRSGetRasterMaximum()；
//						FALSE - 逐点统计最值
//double adfMinMax[2]	adfMinMax[0] - 最小值; adfMinMax[1] - 最大值;
long msRSComputeRasterMinMax(MSRSRasterBandH hBand, int bApproxOK, double adfMinMax[2]);

//取影像的图形范围，相当于MSI API中的msGetUserCoordiate
long msRSGetUserCoordiate(MSRSDatasetH hDS,double *dXMin,double *dXMax,double *dYMin,double *dYMax);

//获取波段的颜色查找表句柄
MSRSColorTableH msRSGetRasterColorTable( MSRSRasterBandH hBand );

//获取影像的颜色查找表句柄
MSRSColorTableH msRSGetDatasetColorTable(MSRSDatasetH hDS);

//取色表条目数目
int msRSGetColorEntryCount(MSRSColorTableH hTable);

void msRSApplyGeoTransform( double *padfGeoTransform, double dfPixel, double dfLine, 
									  double *pdfGeoX, double *pdfGeoY );
//获取当前变换系数
long msRSGetGeoTransform( MSRSDatasetH hDS, double * padfGeoTransform );

//获取控制点数目
int msRSGetGCPCount( MSRSDatasetH hDS );

//获取颜色查找表信息
// long lLutNums	查找表项数
// BYTE *pRLut,BYTE *pGLut,BYTE *pBLut	查找表项信息R/G/B
long msGetLUTInfoByComImg(MSRSDatasetH hDS,long lLutNums,BYTE *pRLut,BYTE *pGLut,BYTE *pBLut);

const MSRSColorEntry *  msRSGetColorEntry(MSRSColorTableH hTable,int i);

long msRSGCPsToGeoTransform( int nCount,const MSRS_GCP *pasGCPList,double *padfGeoTransform, int bApproxOK );

//获取控制点数目
const MSRS_GCP* msRSGetGCPs( MSRSDatasetH hDS );

//由正变换系数求逆变换系数
//相当于原Msi操作中的一次多项式逆变换
long msRSInvGeoTransform( double *padfGeoTransformIn, double *padfInvGeoTransformOut );

long msRSGetCoordinate(MSRSDatasetH hDS,double * pdSx,double * pdSy,double dDx,double dDy,long lForm);

//获取控制点数目
const char* msRSGetGCPProjection( MSRSDatasetH hDS );

//将控制点设置到影像文件中
long msRSSetGCPs( MSRSDatasetH hDS, int nCount, const MSRS_GCP *pasGCPList, 
							const char *pszGCPProjection );

//获取数据集的驱动名称
const char* msRSGetDatasetDriverName( MSRSDatasetH hDS );

//读取Gdal影像显示信息
bool msRsReadImgDispInfo(LPCSTR sFileName,RASImgDispInfo *pGdalImgInfo);

//取影像显示参数
long msRSGetImgDispRGBNo(MSRSDatasetH hDS, RASImgDispInfo *pGetImgDispInfo);

//读取Gdal影像显示信息
bool msRsReadImgDispInfo(LPCSTR sFileName,RASImgDispInfo *pGdalImgInfo);

//设置影像显示参数
long msRSSetImgDispRGBNo(MSRSDatasetH hDS, RASImgDispInfo pImgDispInfo);

bool msRsWriteImgDispInfo(LPCSTR sFileName,RASImgDispInfo pGdalImgInfo);

//设置颜色查找表信息，将色表信息写入文件中
long msSetLUTInfoByComImg(MSRSDatasetH hDS,long lLutNums,BYTE *pRLut,BYTE *pGLut,BYTE *pBLut);

//由色表类型创建颜色查找表
// MSRSPaletteInterp eInterp		影像色表类型
MSRSColorTableH msRSCreateColorTable( MSRSPaletteInterp eInterp );

//设置色表的指定条目
void msRSSetColorEntry( MSRSColorTableH hTable, int i, const MSRSColorEntry * poEntry );

//设置波段的颜色查找表句柄
long msRSSetRasterColorTable( MSRSRasterBandH hBand, MSRSColorTableH hTable );

//获取波段的数据类型
MSRSDataType msRSGetRasterDataType( MSRSRasterBandH hBand );

//释放数据驱动
long msRSDeleteDataset( MSRSDriverH hDriver, const char * pszFilename );

//清除当前数据缓冲，相当于数据强制写盘
long msRSFlushRasterCache( MSRSRasterBandH hBand );

//获取影像的无效值和无效值替换值
long msRSGetNullCellAndInsteadValue(MSRSDatasetH hDS,double *dNullValue,double *dInsteadValue);

//获取影像的最小值
long msRsGetRasterMinValue(MSRSDatasetH pMsi,double *dMinValue);

//获取影像波段的最小值，无效值不参与统计
double msRSGetRasterMinimum( MSRSRasterBandH hBand, int *pbSuccess );

//获取影像波段的最大值，无效值不参与统计
double  msRSGetRasterMaximum( MSRSRasterBandH hBand, int *pbSuccess );

//GDAL进度条函数
int STD_API ALGTermProgress( double dfComplete, const char *pszMessage, void * pProgressArg );


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
long VectorToRaster(const char* pszVectorFile,const char* pszRasterFile,
					int xSize,int ySize,const char* pszAttName,const char* pszFormat="GTiff"); 
/** 
* 矢量转栅格
* @param pszVectorFile     输入文件的路径 
* @param pszRasterFile     写入的结果图像的路径 
* @param xSize             x方向分辨率
* @param ySize             y方向分辨率
* @param szAttName         获得栅格数据亮度值的字段名
* @param pszFormat		   栅格数据格式 
* @return 成功返回0，否则为其他值 
*/ 
long VectorToRaster2(const char* pszVectorFile,const char* pszRasterFile,
					double xSize,double ySize,const char* pszAttName,const char* pszFormat="GTiff");

//栅格转矢量
long ImagePolygonize(const char * pszSrcFile,const char* pszDstFile,const char* pszFormat="ESRI Shapefile");

//栅格转矢量
long ImagePolygonize(MSRSDatasetH hDS,const char* pszDstFile,const char* pszFormat="ESRI Shapefile");  


/** 
* 创建影像IO的缓存，每次只能缓存一个波段
* @param hSrcDS			源影像数据集
* @param lBandNo		波段号，从1开始
* @param lMaxBlockSize  最大可分配块大小，单位为字节，默认为8MB   
* @param lBufferSize    缓冲区大小（缓存的块与块之间重叠区大小），存在领域像元值计算式最好设置为2或更大
* @return 成功/失败，缓存句柄/0
*/
RSRasterCacheH CreateRasterCache(MSRSDatasetH hSrcDS,long lBandNo,long lMaxBlockSize=0,long lBufferSize=0);

/** 
* 将缓存中数据立即写入磁盘(文件为MS_Update打开状态下才可用)
* @param hCache			缓存句柄
* @return 成功/失败，0/错误代码
*/
long FlushRasterCache(RSRasterCacheH hCache);
/** 
* 设置亮度值(文件为MS_Update打开状态下才可用)
* @param hCache			缓存句柄
* @return 成功/失败，0/错误代码
*/
long RCSetCellValue(RSRasterCacheH hCache,long lRowNo,long lColNo,double dfValue);
/** 
* 取亮度值
* @param hCache			缓存句柄
* @return 成功/失败，0/错误代码
*/
long RCGetCellValue(RSRasterCacheH hCache,long lRowNo,long lColNo,double &dfValue);
/** 
* 释放缓存
* @param hCache			缓存句柄
* @return 成功/失败，0/错误代码
*/
long RealseRasterCache(RSRasterCacheH hCache);
/** 
* 缓存中是否只存在一个影像块
* @param hCache			缓存句柄
* @return 是/否，true/false
*/
bool IsOnlyOneBlock(RSRasterCacheH hCache);


//栅格计算
//针对整幅影像对像元处理方式相同的栅格计算,如：所有像元值加1
//T 的类型必须和影像的存储类型一致！！！！！！
template<typename T> 
class CRasterCalT
{
public:
	//处理单个像元值的函数指针模板
	//*pOrgVal 为原始像元值，*pDstVal 为处理后像元值

	 /*注意与原始数据的类型保持一致
	 	template<typename T>
		long RasterMulti0_01(T *pOrgVal,T *pDstVal )
		{
			*pDstVal=(T)(*pOrgVal)*0.01;
			return 0;
		}
	 */
	typedef long (*CellCalcFuncT)(T *pOrgVal/*in*/,T *pDstVal/*out*/ );
	//栅格计算函数
	static long RasterCalculateT(MSRSDatasetH hSrcDS,CellCalcFuncT  pCalFunc);
};
};
#endif