
//================================================================================
// �ļ���		 �� RasterIO.h 
// �汾			 �� this 1.0.0 ; QGIS1.7.4 ;QT 4.7.1 ;GDAL 1.8.1                            
// Ŀ�ļ���Ҫ���ܣ� Ӱ��IO�ӿ�
// ��������		 �� 2012.04.25
// ����޸�����  �� 2012.05.15 
// ����			 ��  yq
// �޸���		 ��  yq,lxd
// ����			 �� ���κŴ�1��ʼ��
//				 �����ͷ���ֵΪCPLErr���ɹ�/ʧ�� 0/�������
//================================================================================

//���ͷ���ֵ
//typedef enum
//{
//	CE_None = 0,
//	CE_Debug = 1,
//	CE_Warning = 2,
//	CE_Failure = 3,
//	CE_Fatal = 4
//} CPLErr;
//�µ�������
// ��Ԫֵ��������
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
typedef void *MSRSMajorObjectH;		// ���������
typedef void *MSRSDatasetH;			// Ӱ�����ݼ����
typedef void *MSRSRasterBandH;		// Ӱ�񲨶ξ��
typedef void *MSRSDriverH;			// Ӱ�������������
typedef void *RSRasterCacheH;		// Ӱ������IO������
typedef void *MSRSColorTableH;		// Ӱ������ɫ��

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


//��Ӱ���ļ�
MSRSDatasetH  msRSOpen(const char *pszFilename, MSRSAccess eAccess, void *pRSGDB=0);

//��Ӱ����������ȡ��������
MSRSDriverH  msRSGetDriverByName(const char * pszFormat);

//����Ӱ�����ݼ�
MSRSDatasetH  msRSCreate(MSRSDriverH hDriver, const char* pszFilename, int nXSize, int nYSize,
						 int nBands, MSRSDataType eDataType, char ** papszOptions, void *pRSGDB=0);
//�ر�Ӱ���ļ�
void  msRSClose(MSRSDatasetH hDS);


//��ȡָ������,ע�Ⲩ��ID��1��ʼ���������
MSRSRasterBandH	msRSGetRasterBand(MSRSDatasetH hDs,int nBandID);

//����ɫ����Ϣ���ɹ�����0.ʧ�ܷ����������������
long dtmCopyDislayLutFromOrgRaster(MSRSDatasetH hDs,MSRSRasterBandH hOutDs); 

//��ȡӰ������/����/������
int  msRSGetRasterXSize( MSRSDatasetH hDS );
int  msRSGetRasterYSize( MSRSDatasetH hDS );
int  msRSGetRasterCount( MSRSDatasetH hDS );

//��ȡӰ��ռ�ֱ���
long  msGetImgCellSize(MSRSDatasetH hDS,double &dXCellSize,double &dYCellSize);//��ȡ��Ԫ��С

//��ȡӰ����Ԫ������Ϣ
MSRSDataType  msRSGetDatasetType(MSRSDatasetH hDS);

//�������ݶ�д
long  msRSRasterIO(MSRSRasterBandH hBand, MSRSRWFlag eRWFlag,int nDSXOff, int nDSYOff, 
						   int nDSXSize, int nDSYSize, void *pData, int nBufXSize, int nBufYSize,
						   MSRSDataType eBufType, int nPixelSpace, int nLineSpace);

//���������ڴ�,���ֽ�Ϊ��λ
void * msMalloc(long size);
//�ͷ������ڴ�
void   msFree(void *pData);

//������Ԫ���ͽ����ݿ�תΪ��Ԫֵ����ֵת
//void  msRSConvValue(MSRSDataType eDataType, void *pData, double &dVal);


//��ȡ��Чֵ��Ϣ
double  msRSGetRasterNoDataValue( MSRSRasterBandH hBand, int *pbSuccess=0 );
long  msRSSetRasterNoDataValue( MSRSRasterBandH hBand, double dfValue );

// ��д����
long  msRSSetCell(MSRSDatasetH hDS, short BandNo, long RowNo, long ColNo, double Value);
long  msRSGetCell(MSRSDatasetH hDS, short BandNo, long RowNo, long ColNo, double &Value, char *pInvalidFlag=0);

//��������任����
long  msCopyCoordinateInfo(MSRSDatasetH hSrcDS,MSRSDatasetH hDstDS,long lStartLine,long lStartCell); 
//����ͶӰ��Ϣ
long  msCopyProjectionInfo(MSRSDatasetH hSrcDS,MSRSDatasetH hDstDS); 

//��ȡ�����������Ϣ
// MSRSMajorObjectH hObject	��������������Դ���MSRSDatasetH/MSRSRasterBandH������������
const char* msRSGetDescription( MSRSMajorObjectH hObject );

//�򿪽������㣬Ӱ�����ݶ�/дǰ����򿪣�PyLayerNo��1��ʼ
//��Ҫ���MapGIS7դ�����ݼ���Ϊ��ͳһ����дǰ��Ҫ��
long msRSOpenPyramidLayer(MSRSDatasetH hDS, short PyLayerNo);

//�رս�������
long msRSClosePyramidLayer(MSRSDatasetH hDS);

//������Ԫ���ͺ���Ŀ������Ԫֵ���ݿ�ռ�
long msRSNewValueData(MSRSDataType eDataType, void **pData, long lCellNum);

//�ͷ���Ԫֵ���ݿ�Ŀռ�
void msRSDelValueData(void *pData);

//������Ԫ���������ݿ�ת��Ԫֵ����ת
void msRSConvValue(MSRSDataType eDataType, void *pData, double &dVal);

//������Ԫ���������ݿ�ת��Ԫֵ����ת
void msRSConvNValues(MSRSDataType eDataType, void *pData, long lCellNum, double *pdVal);

//��msiȡ����double���͵�����ת��Ϊ��Ӧ���͵����ݣ���Ҫ���ڽ�ֱ������msGetCellȡ����
//double������ת��ΪmsRSRasterIOд��ʱ��Ҫ������
//ע��pData���ڵ��øú���ǰ���ն�Ӧ���ͷ�����ڴ�ռ�
void msConvNDValues(double *pdVal,MSRSDataType eDataType, void *pData, long lCellNum);

// -------------------- ȡ�������ֽ�����������зֿ��� -------------------- //
long  msRSCalPyramidLayerRowColTileNums(MSRSDatasetH hDS,long lPyramidLayerNo,long lTileWidth,long  lTileHeight,
										long *plRowTileNums,long  *plColTileNums);
int msRSGetDataTypeSize( MSRSDataType eDataType );
int msRSGetOverviewCount( MSRSRasterBandH hBand );

/** 
* @brief Ӱ��������귶Χ
* @param hSrcDS          ��ԭʼӰ������ָ�� 
* @param rc				 ��Ӱ��������εĵ������� 
*/ 
bool  _msRSGetMapRange(MSRSDatasetH hDS, D_RECT &rc);
// ��ȡ����Χ
bool msRSGetMapRange(MSRSDatasetH hDS, D_RECT &rc);

/** 
* @brief ͨ�����ݲ��ز�������
* @param hSrcDS          ��ԭʼӰ������ָ�� 
* @param pszOutFile      �����Ӱ������ָ�� 
* @param dXScale         �� Xת�������ȣ�����1ͼ����С��1��ʾͼ����С 
* @param dYScale         �� Yת�������ȣ�
* @param lInterpolate    ���ز�����ʽ, 0���ڽ���1˫���� 
* @param dXOff			 ��X�������ͼ������
* @param dYOff           ��Y�������ͼ������
* @return �ɹ�/����  0/�������
*/ 

long  msReSample0(MSRSDatasetH hSrcDS,const char* pszOutFile,double dXScale,double dYScale,
				  long lInterpolate=0,double dXOff=0,double dYOff=0);


/** 
* @brief ��AOI�ļ��ü�Ӱ��
* @param pszInFile          �����ļ���·�� 
* @param pszOutFile         ��ͼ������ļ���·�� 
* @param pszAOIFile         AOI�ļ�·�� 
* @param pszSQL             ָ��AOI�ļ��е������ֶ�ֵ���ü� 
* @param pBandInex          ָ���ü��Ĳ��Σ�Ĭ��ΪNULL����ʾ�ü����в��� 
* @param piBandCount        ָ���ü����εĸ�����ͬ��һ������ͬʱʹ�� 
* @param iBuffer            ָ��AOI�ļ�������Χ��Ĭ��Ϊ0����ʾ������ 
* @param pszFormat          ��ͼ������ļ��ĸ�ʽ ��Ϊ0ʱ��ԭʼ���ݱ���һ���ĸ�ʽ
* @return �ɹ�/����  0/�������
*/ 

int msRSClipImgByFeature(MSRSDatasetH hSrcDS, const char* pszOutFile, const char* pszAOIFile, const char* pszSQL=0,   
					  int *pBandInex=0, int *piBandCount=0, int iBuffer=0, const char* pszFormat=0); 



long msRSClipImage(MSRSDatasetH hSrcDS,const char *pszOutFile,
							 D_DOT *pPolySet, long *pLenSet, long SetNum, 
							 int *pProcBandList=0,int *lProcBandNum=0,
							 const char* pszFormat=0);

void msRSGetStatFileName(MSRSDatasetH pDataset,char *sStaFileName);

void msRSAllRegister();//ע������֧�ֵ���������

//�����ļ�����ȡ��Ӧ���ļ����ͣ����崦����������ͨ�ú������ļ�������򿪳ɹ�
//����ݵ�ǰ��Driver�������ļ�����,�������Ա��ⵥ�����ݺ�׺�����Ĵ���
const char* msGetFileTypeByNameExt(LPCSTR pszFilename,void *pRSGDB);

//�������е����ݼ������µ�Ӱ�����ݼ�
//int bStrict		TRUE - �ϸ񿽱�; FALSE - ����������Ϣ
MSRSDatasetH msRSCreateCopy( MSRSDriverH hDriver, const char * pszFilename, MSRSDatasetH hSrcDS, int bStrict, char ** papszOptions);

//������������
long msRSBuildOverviews(MSRSDatasetH hDS,const char *pszResampling, 
						int nOverviews, int *panOverviewList, int nListBands, int *panBandList);


/* ==================================================================== */
/*                       Ӱ�񲨶�ֱ��ͼ��غ���                         */
/* ==================================================================== */

// double dfMin,dfMax		ֱ��ͼ������(��˵�)/����(�Ҷ˵�)
// int nBuckets				ֱ��ͼͰ��(�ּ���)��Ͱ��С = (dfMax-dfMin)/nBuckets
// int *panHistogram		ֱ��ͼ����
// int bIncludeOutOfRange	(TRUE/FALSE)�Ƿ�ͳ�Ʒ�Χ�⣻FALSE - ֻͳ��(dfMin,dfMax)��Χ����Ԫֵ��
//							TRUE - С��dfMin�ı�ӳ�䵽panHistogram[0]������dfMax�ı�ӳ�䵽panHistogram[nBuckets-1]

//��ȡֱ��ͼ��Ϣ
// ��Բ�����ɣ�panHistogramֱ��ͼ�ռ��ڵ���ǰ����
// ��8λ�޷�������256����ֱ��ͼͳ��Ϊ���� 
// Ϊ�˷�ֹ�������������ֱ��ͼ�߽�ȡ��ʱ���ܲ����Ĵ������������¸�ֵ -0.5, 255.5��
// int anHistogram[256];
// long lErr = msRSGetRasterHistogram( -0.5, 255.5, 256, anHistogram, FALSE, FALSE );
long msRSGetRasterHistogram( MSRSRasterBandH hBand,double dfMin,double dfMax,int nBuckets,
							int *panHistogram, int bIncludeOutOfRange, int bApproxOK);

//��ȡȱʡֱ��ͼ��Ϣ
// ��Բ�����ɣ�int **ppanHistogramֱ��ͼ�ռ��ɺ������ڲ��Զ�����
// double *pdfMin,double *pdfMax,int *pnBuckets��������/����/Ͱ����ֱ��ͼ��Ϣ
long msRSGetDefaultHistogram( MSRSRasterBandH hBand, double *pdfMin, double *pdfMax, 
							 int *pnBuckets, int **ppanHistogram, int bForce);

//����ȱʡֱ��ͼ��Ϣ
long msRSSetDefaultHistogram( MSRSRasterBandH hBand,double dfMin,double dfMax,int nBuckets,int *panHistogram );

//���㲨��ͳ����Ϣ(��ֵ/��׼��)
long msRSComputeBandStats( MSRSRasterBandH hSrcBand,int nSampleStep,double *pdfMean, double *pdfStdDev);

//����Ӱ�񲨶ε���ֵ
//int bApproxOK			TRUE - ȡ����ֵ������msRSGetRasterMinimum()/msRSGetRasterMaximum()��
//						FALSE - ���ͳ����ֵ
//double adfMinMax[2]	adfMinMax[0] - ��Сֵ; adfMinMax[1] - ���ֵ;
long msRSComputeRasterMinMax(MSRSRasterBandH hBand, int bApproxOK, double adfMinMax[2]);

//ȡӰ���ͼ�η�Χ���൱��MSI API�е�msGetUserCoordiate
long msRSGetUserCoordiate(MSRSDatasetH hDS,double *dXMin,double *dXMax,double *dYMin,double *dYMax);

//��ȡ���ε���ɫ���ұ���
MSRSColorTableH msRSGetRasterColorTable( MSRSRasterBandH hBand );

//��ȡӰ�����ɫ���ұ���
MSRSColorTableH msRSGetDatasetColorTable(MSRSDatasetH hDS);

//ȡɫ����Ŀ��Ŀ
int msRSGetColorEntryCount(MSRSColorTableH hTable);

void msRSApplyGeoTransform( double *padfGeoTransform, double dfPixel, double dfLine, 
									  double *pdfGeoX, double *pdfGeoY );
//��ȡ��ǰ�任ϵ��
long msRSGetGeoTransform( MSRSDatasetH hDS, double * padfGeoTransform );

//��ȡ���Ƶ���Ŀ
int msRSGetGCPCount( MSRSDatasetH hDS );

//��ȡ��ɫ���ұ���Ϣ
// long lLutNums	���ұ�����
// BYTE *pRLut,BYTE *pGLut,BYTE *pBLut	���ұ�����ϢR/G/B
long msGetLUTInfoByComImg(MSRSDatasetH hDS,long lLutNums,BYTE *pRLut,BYTE *pGLut,BYTE *pBLut);

const MSRSColorEntry *  msRSGetColorEntry(MSRSColorTableH hTable,int i);

long msRSGCPsToGeoTransform( int nCount,const MSRS_GCP *pasGCPList,double *padfGeoTransform, int bApproxOK );

//��ȡ���Ƶ���Ŀ
const MSRS_GCP* msRSGetGCPs( MSRSDatasetH hDS );

//�����任ϵ������任ϵ��
//�൱��ԭMsi�����е�һ�ζ���ʽ��任
long msRSInvGeoTransform( double *padfGeoTransformIn, double *padfInvGeoTransformOut );

long msRSGetCoordinate(MSRSDatasetH hDS,double * pdSx,double * pdSy,double dDx,double dDy,long lForm);

//��ȡ���Ƶ���Ŀ
const char* msRSGetGCPProjection( MSRSDatasetH hDS );

//�����Ƶ����õ�Ӱ���ļ���
long msRSSetGCPs( MSRSDatasetH hDS, int nCount, const MSRS_GCP *pasGCPList, 
							const char *pszGCPProjection );

//��ȡ���ݼ�����������
const char* msRSGetDatasetDriverName( MSRSDatasetH hDS );

//��ȡGdalӰ����ʾ��Ϣ
bool msRsReadImgDispInfo(LPCSTR sFileName,RASImgDispInfo *pGdalImgInfo);

//ȡӰ����ʾ����
long msRSGetImgDispRGBNo(MSRSDatasetH hDS, RASImgDispInfo *pGetImgDispInfo);

//��ȡGdalӰ����ʾ��Ϣ
bool msRsReadImgDispInfo(LPCSTR sFileName,RASImgDispInfo *pGdalImgInfo);

//����Ӱ����ʾ����
long msRSSetImgDispRGBNo(MSRSDatasetH hDS, RASImgDispInfo pImgDispInfo);

bool msRsWriteImgDispInfo(LPCSTR sFileName,RASImgDispInfo pGdalImgInfo);

//������ɫ���ұ���Ϣ����ɫ����Ϣд���ļ���
long msSetLUTInfoByComImg(MSRSDatasetH hDS,long lLutNums,BYTE *pRLut,BYTE *pGLut,BYTE *pBLut);

//��ɫ�����ʹ�����ɫ���ұ�
// MSRSPaletteInterp eInterp		Ӱ��ɫ������
MSRSColorTableH msRSCreateColorTable( MSRSPaletteInterp eInterp );

//����ɫ���ָ����Ŀ
void msRSSetColorEntry( MSRSColorTableH hTable, int i, const MSRSColorEntry * poEntry );

//���ò��ε���ɫ���ұ���
long msRSSetRasterColorTable( MSRSRasterBandH hBand, MSRSColorTableH hTable );

//��ȡ���ε���������
MSRSDataType msRSGetRasterDataType( MSRSRasterBandH hBand );

//�ͷ���������
long msRSDeleteDataset( MSRSDriverH hDriver, const char * pszFilename );

//�����ǰ���ݻ��壬�൱������ǿ��д��
long msRSFlushRasterCache( MSRSRasterBandH hBand );

//��ȡӰ�����Чֵ����Чֵ�滻ֵ
long msRSGetNullCellAndInsteadValue(MSRSDatasetH hDS,double *dNullValue,double *dInsteadValue);

//��ȡӰ�����Сֵ
long msRsGetRasterMinValue(MSRSDatasetH pMsi,double *dMinValue);

//��ȡӰ�񲨶ε���Сֵ����Чֵ������ͳ��
double msRSGetRasterMinimum( MSRSRasterBandH hBand, int *pbSuccess );

//��ȡӰ�񲨶ε����ֵ����Чֵ������ͳ��
double  msRSGetRasterMaximum( MSRSRasterBandH hBand, int *pbSuccess );

//GDAL����������
int STD_API ALGTermProgress( double dfComplete, const char *pszMessage, void * pProgressArg );


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
long VectorToRaster(const char* pszVectorFile,const char* pszRasterFile,
					int xSize,int ySize,const char* pszAttName,const char* pszFormat="GTiff"); 
/** 
* ʸ��תդ��
* @param pszVectorFile     �����ļ���·�� 
* @param pszRasterFile     д��Ľ��ͼ���·�� 
* @param xSize             x����ֱ���
* @param ySize             y����ֱ���
* @param szAttName         ���դ����������ֵ���ֶ���
* @param pszFormat		   դ�����ݸ�ʽ 
* @return �ɹ�����0������Ϊ����ֵ 
*/ 
long VectorToRaster2(const char* pszVectorFile,const char* pszRasterFile,
					double xSize,double ySize,const char* pszAttName,const char* pszFormat="GTiff");

//դ��תʸ��
long ImagePolygonize(const char * pszSrcFile,const char* pszDstFile,const char* pszFormat="ESRI Shapefile");

//դ��תʸ��
long ImagePolygonize(MSRSDatasetH hDS,const char* pszDstFile,const char* pszFormat="ESRI Shapefile");  


/** 
* ����Ӱ��IO�Ļ��棬ÿ��ֻ�ܻ���һ������
* @param hSrcDS			ԴӰ�����ݼ�
* @param lBandNo		���κţ���1��ʼ
* @param lMaxBlockSize  ���ɷ�����С����λΪ�ֽڣ�Ĭ��Ϊ8MB   
* @param lBufferSize    ��������С������Ŀ����֮���ص�����С��������������Ԫֵ����ʽ�������Ϊ2�����
* @return �ɹ�/ʧ�ܣ�������/0
*/
RSRasterCacheH CreateRasterCache(MSRSDatasetH hSrcDS,long lBandNo,long lMaxBlockSize=0,long lBufferSize=0);

/** 
* ����������������д�����(�ļ�ΪMS_Update��״̬�²ſ���)
* @param hCache			������
* @return �ɹ�/ʧ�ܣ�0/�������
*/
long FlushRasterCache(RSRasterCacheH hCache);
/** 
* ��������ֵ(�ļ�ΪMS_Update��״̬�²ſ���)
* @param hCache			������
* @return �ɹ�/ʧ�ܣ�0/�������
*/
long RCSetCellValue(RSRasterCacheH hCache,long lRowNo,long lColNo,double dfValue);
/** 
* ȡ����ֵ
* @param hCache			������
* @return �ɹ�/ʧ�ܣ�0/�������
*/
long RCGetCellValue(RSRasterCacheH hCache,long lRowNo,long lColNo,double &dfValue);
/** 
* �ͷŻ���
* @param hCache			������
* @return �ɹ�/ʧ�ܣ�0/�������
*/
long RealseRasterCache(RSRasterCacheH hCache);
/** 
* �������Ƿ�ֻ����һ��Ӱ���
* @param hCache			������
* @return ��/��true/false
*/
bool IsOnlyOneBlock(RSRasterCacheH hCache);


//դ�����
//�������Ӱ�����Ԫ����ʽ��ͬ��դ�����,�磺������Ԫֵ��1
//T �����ͱ����Ӱ��Ĵ洢����һ�£�����������
template<typename T> 
class CRasterCalT
{
public:
	//��������Ԫֵ�ĺ���ָ��ģ��
	//*pOrgVal Ϊԭʼ��Ԫֵ��*pDstVal Ϊ�������Ԫֵ

	 /*ע����ԭʼ���ݵ����ͱ���һ��
	 	template<typename T>
		long RasterMulti0_01(T *pOrgVal,T *pDstVal )
		{
			*pDstVal=(T)(*pOrgVal)*0.01;
			return 0;
		}
	 */
	typedef long (*CellCalcFuncT)(T *pOrgVal/*in*/,T *pDstVal/*out*/ );
	//դ����㺯��
	static long RasterCalculateT(MSRSDatasetH hSrcDS,CellCalcFuncT  pCalFunc);
};
};
#endif