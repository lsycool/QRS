#ifndef _GD_RASTER_VECTOR_H_     // prevent multiple includes.
#define _GD_RASTER_VECTOR_H_

//#include "RasBase.h"
//#include <msRSDataIOApi.h>
#include "RasterIO.h"
using namespace RASTER_IO;

#ifndef __GD_RASTER_VECTOR_EXPORTS__
#define gdvecDll __declspec(dllimport)
#else
#define gdvecDll __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif


//===================================栅格转矢量=====================================

//栅格转矢量接口(直接给出栅格对象)
//输入参数:
//hRaster                待转换影通用数据集句柄(支持RAS_1BIT,RAS_UINT8,RAS_UINT16).
//BandNo                 待转换影像波段号(从1开始).
//lMaxCellNumOfSmallReg  合并小区最大的象元数,<1表示不进行小区合并处理.
//bMakeTopo              是否建立区拓扑 
//dTolerence             拓扑重建平差半径
//输出参数:
//strReOutType           输出影像格式串(许空)
//pReRasGDB              输出影像所在地理数据库对象(允许为NULL).
//pReRasName             输出影像数据集名(允许为NULL).
//pOutGDB                输出区要素类所在地理数据库对象.
//pFClsName              输出区要素类名.
//返回值:                0/1--成功/失败
long gdvecDll msRSRaster2FCls(MSRSDatasetH hRaster, 
                              short BandNo,
                              /*CGDataBase *pReRasGDB,*/
							  const char *strReOutType,
                              const char *pReRasName,
                              /*CGDataBase *pOutGDB, */
                              const char *pFClsName,
                              long lMaxCellNumOfSmallReg=0,
                              BOOL bMakeTopo=FALSE,
							  double dTolerence=0.0001);

//栅格转矢量接口(直接给出栅格对象)
//输入参数:
//hRaster                待转换影通用数据集句柄(支持RAS_1BIT,RAS_UINT8,RAS_UINT16).
//BandNo                 待转换影像波段号(从1开始).
//lMaxCellNumOfSmallReg  合并小区最大的象元数,<1表示不进行小区合并处理.
//bMakeTopo              是否建立区拓扑 
//dTolerence             拓扑重建平差半径
//输出参数:
//strReOutType           输出影像格式串(许空)
//pReRasGDB              输出影像所在地理数据库对象(允许为NULL).
//pReRasName             输出影像数据集名(允许为NULL).
//pOutGDB                输出区要素类所在地理数据库对象.
//pFClsName              输出简单区要素类名.
//返回值:                0/1--成功/失败
long gdvecDll msRSRaster2SFCls(MSRSDatasetH hRaster, 
							  short BandNo,
							  /*CGDataBase *pReRasGDB,*/
							  const char *strReOutType,
							  const char *pReRasName,
							  /*CGDataBase *pOutGDB, */
							  const char *pFClsName,
							  long lMaxCellNumOfSmallReg=0,
							  BOOL bMakeTopo=FALSE,
							  double dTolerence=0.0001);

//小区合并
//输入参数:
//hRaster                待转换影通用数据集句柄(支持RAS_1BIT,RAS_UINT8,RAS_UINT16).
//BandNo                 待转换影像波段号(从1开始).
//strReOutType           输出影像格式串
//pReRasGDB              输出影像所在地理数据库对象(允许为NULL).
//pReRasName             输出影像数据集名(允许为NULL).
//lMaxCellNumOfSmallReg  合并小区最大的象元数,<1表示不进行小区合并处理.
//返回值                 0/1--成功/失败
//long gdvecDll msRSMergeRasterSmallRegion(MSRSDatasetH hRaster, short BandNo,
//	                                   CGDataBase *pReRasGDB, const char *strReOutType,
//									   const char *pReRasName,long lMaxCellNumOfSmallReg);

//===================================================================================

//===================================影像裁剪=======================================

//多边形裁剪通用影像
//hDS				被裁影像数据集对象
//pPolySet			裁剪多边形坐标(多圈).
//pLenSet			每圈点数数组.
//SetNum			裁剪多边形的圈数.
//ReserveMode		1/2/else,保留图形点/中心点/边界全路径.
//CoordSysType		坐标类型(图像坐标/图形坐标).
//bAddClipRangeAsAoi是否将裁剪多边形作为AOI添加到结果影像
//输出参数:
//pOutGDB			输出地理数据库对象.
//pOutImageName		输出影像全路径名.
//strOutDriver      输出影像类型
//strFrameName      对图幅裁剪是图幅号
//pProcBandList     选择的裁剪波段号数组，如果要对整幅影像裁剪给NULL
//lProcBandNum      pProcBandList的长度
//返回值:           0/1,成功/失败.
//注：现为ReserveMode添加新含义，它的二进制码的最后两位代表“保留图形点/中心点/边界全路径”的含义，
//它的二进制码的倒数第三位表示内裁和外裁 add by wangbo
//0000 0100 外裁；0000 00000内裁
//0000 0001 保留图形点；0000 0010 中心点；其他情况保留全路径
//0000 0101 外裁且保留图形点
short gdvecDll msRSClipImage(MSRSDatasetH hDS,
							 D_DOT *pPolySet, long *pLenSet, long SetNum,
							 BYTE  ReserveMode,
							 RAS_COORDSYSTYPE CoordSysType,
							 BOOL bAddClipRangeAsAoi,
							 /*CGDataBase *pOutGDB,*/ const char *pOutImageName,
							 const char *strOutDriver,const char *strFrameName=_T(""),
							 long *pProcBandList=NULL,long *lProcBandNum=NULL);

//影像内部AOI裁剪通用影像
//hDS			　　被裁影像数据集对象.
//ReserveMode		1/2/else,保留图形点/中心点/边界全路径.
//CoordSysType		坐标类型(图像坐标/图形坐标).
//bMultiAoiClip     TRUR－多AOI裁剪生成一结果影像，FALSE-每个AOI生成一结果影像
//输出参数:
//pOutGDB			输出地理数据库对象.
//pOutImageName		输出影像全路径名.
//strOutDriver      输出影像类型
//pProcBandList     选择的裁剪波段号数组，如果要对整幅影像裁剪给NULL
//lProcBandNum      pProcBandList的长度
//返回值:           0/1,成功/失败.
short gdvecDll msRSClipImgByAOI(MSRSDatasetH hDS,BYTE  ReserveMode, RAS_COORDSYSTYPE CoordSysTypelong ,BOOL bMultiAoiClip,
	                            /*CGDataBase *pOutGDB,*/const char *pOutImageName,const char *strOutDriver,long *pProcBandList=NULL,long *lProcBandNum=NULL);

//区要素类裁剪影像
//hDS			　　被裁影像数据集对象.
//CFeatureCls &ClipFeature  裁剪的区要素类
//ReserveMode		1/2/else,保留图形点/中心点/边界全路径.
//CoordSysType		坐标类型(图像坐标/图形坐标)－注意与裁剪区要素类的坐标类型一致.
//plRegIDArr        要素类中的区要素的ID数组---此处可为NULL,为Null表示要素类中所有区都参与裁剪
//ClipRegNum        参与裁剪的要素类中区要素的个数
//bMultiPolygonClip TRUR－对所有的裁剪区要素生成一结果影像，FALSE-每个裁剪区要素生成一结果影像
//输出参数:
//pOutGDB			输出地理数据库对象.
//pOutImageName		输出影像全路径名.
//szFormat          输出影像类型
//pProcBandList     选择的裁剪波段号数组，如果要对整幅影像裁剪给NULL
//lProcBandNum      pProcBandList的长度
//返回值:           0/1,成功/失败.
//说明：CoordSysType与裁剪区要素类的坐标类型必须一致，否则算法会出现死循环－－psq 08.07.08
short gdvecDll msRSClipImgByFeature(MSRSDatasetH hDS,/*CFeatureCls &ClipFeature,*/BYTE  ReserveMode,RAS_COORDSYSTYPE CoordSysType,
	                                long* plRegIDArr,long ClipRegNum,BOOL bMultiPolygonClip,/*CGDataBase *pOutGDB,*/
	                                const char *pOutImageName,const char *szFormat,long *pProcBandList=NULL,long *lProcBandNum=NULL);

//区简单要素类裁剪影像
//hDS			　　被裁影像数据集对象.
//ClipSFeature      裁剪的简单区要素类
//ReserveMode		1/2/else,保留图形点/中心点/边界全路径.
//CoordSysType		坐标类型(图像坐标/图形坐标)－注意与裁剪区要素类的坐标类型一致.
//plRegIDArr        要素类中的区要素的ID数组---此处可为NULL,为Null表示要素类中所有区都参与裁剪
//ClipRegNum        参与裁剪的要素类中区要素的个数
//bMultiPolygonClip TRUR－对所有的裁剪区要素生成一结果影像，FALSE-每个裁剪区要素生成一结果影像
//输出参数:
//pOutGDB			输出地理数据库对象.
//pOutImageName		输出影像全路径名.
//szFormat          输出影像类型
//pProcBandList     选择的裁剪波段号数组，如果要对整幅影像裁剪给NULL
//lProcBandNum      pProcBandList的长度
//返回值:           0/1,成功/失败.
//说明：CoordSysType与裁剪区要素类的坐标类型必须一致，否则算法会出现死循环
short gdvecDll msRSClipImgBySFeature(MSRSDatasetH hDS,/*CSFeatureCls &ClipSFeature,*/BYTE  ReserveMode,RAS_COORDSYSTYPE CoordSysType,
									long* plRegIDArr,long ClipRegNum,BOOL bMultiPolygonClip,/*CGDataBase *pOutGDB,*/
									const char *pOutImageName,const char *szFormat,long *pProcBandList=NULL,long *lProcBandNum=NULL);


//---------------------------------------------------------------------//
// 成功返回0，失败返回错误码(见mserrors.h) Created by zyk
// hSrcDS,plSrcBandNo,lSrcBandNum	[in]--被裁影像数据集,波段号,波段数
// pcClipScls,plObjID,lObjNum		[in]--裁剪要素类,选择区OID,选择区个数(plObjID==NULL时对整个矢量外框范围裁剪)
// pdClipDots,plDotNum,lDotRegNum	[in]--所有圈点集,各圈的点数,圈数
// pszDstFile,lDstFileNum,pszDstFmt	[in]--结果影像名数组,结果影像名个数(裁剪多幅),结果影像格式(GTiff)
// pDstGdb,bMulClip					[in]--输出地理数据库,true/false--每区生成一幅影像/生成一幅影像
// lClipType,bGeoRange				[in]--0/1/2/3--像元左上角/中心/部分/全部在区内会保留,true/false--地理范围/行列范围
// pszSubProg						[in]--进度条子标题(主标题“影像裁剪...”,传NULL不会有进度条)
//---------------------------------------------------------------------//
// 简单要素类裁剪
long gdvecDll msRSClipImgByScls(MSRSDatasetH hSrcDS, long *plSrcBandNo, long lSrcBandNum,/* CSFeatureCls *pcClipScls,*/ long *plObjID,
								long lObjNum, const char *pszDstFile, const char *pszDstFmt, void *pDstGdb=NULL,
								long lClipType=2, bool bGeoRange=true, const char *pszSubProg=NULL);

// 点集裁剪
long gdvecDll msRSClipImgByDot(MSRSDatasetH hSrcDS, long *plSrcBandNo, long lSrcBandNum, D_DOT *pdClipDots, long *plDotNum, 
							   long lDotRegNum, const char *pszDstFile, const char *pszDstFmt, void *pDstGdb=NULL,
							   long lClipType=2, bool bGeoRange=true, const char *pszSubProg=NULL);

//===================================================================================

//////////////////////////////////////////////////////////////////////////
// 功能：搜索影像的裁剪AOI, 弹出对话框设置参数
// 输入参数：
//	MSRSDatasetH hDataset -- 输入影像句柄
// 返回值：long 0/Success， 其他/错误码
long gdvecDll msRsAppendRasClipAoiByDlg(MSRSDatasetH hDataset);

//////////////////////////////////////////////////////////////////////////
// 功能：搜索影像的裁剪AOI, 指定无效值区间，有4角点/边界追踪2种类型
// 注意：此接口相比67接口功能有所变化，(1)搜索无效区只对一个波段进行
//		(2)无效值是一个区段，而非以前的一个值
// 输入参数：
//	MSRSDatasetH hDataset -- 输入影像句柄
//	long lBandNo -- 用于搜索无效区的波段ID，从1开始
//	double dExcludeMinVal -- 无效值的范围[MinVal, MaxVal]
//	double dExcludeMaxVal -- 无效值范围是闭区间
//	long lSrchType -- 0/角点模式 1/边界模式，边界模式耗时，但准确
// 返回值：long 0/Success， 其他/错误码
long gdvecDll msRsAppendRasClipAoi(MSRSDatasetH hDataset, long lBandNo, double dExcludeMinVal, double dExcludeMaxVal, long lSrchType);

#ifdef __cplusplus
}
#endif

//#ifndef __GD_RASTER_VECTOR_EXPORTS__
//#pragma comment(lib, "W70_VRTr.lib")
//#endif	

#endif
